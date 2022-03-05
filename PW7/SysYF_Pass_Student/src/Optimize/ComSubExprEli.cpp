#include "Pass.h"
#include "ComSubExprEli.h"
#include <algorithm>
#include <set>

void ComSubExprEli::execute() {
    module->set_print_name();
    /*you need to finish this function*/
    for (auto fun : module->get_functions()) {
        if (fun->get_basic_blocks().empty())
            continue;
        func_ = fun;
        do {
            gens.clear();
            INs.clear();
            OUTs.clear();
            all.clear();
            delete_list.clear();
            FindAvailExpr();
            ReplaceComSubExpr();
            RemoveComSubExpr();
        } while (!delete_list.empty()); // 当没有指令要删除时才停止
    }
}

bool ComSubExprEli::is_valid_expr(Instruction *inst) {
    return !(inst->is_void() || inst->is_call() || inst->is_phi() || inst->is_alloca() || inst->is_load() || inst->is_cmp() || inst->is_zext());  // TODO:CHECK VALID INST
}

void ComSubExprEli::FindAvailExpr() {
    /* 可用表达式分析 */
    // 第一次遍历整个函数，获取所有表达式的全集
    for (auto bb : func_->get_basic_blocks()) {
        // 遍历每一个块，获取函数内所有表达式的集合
        for (auto inst : bb->get_instructions()) {
            if (!is_valid_expr(inst))
                continue;
            Expr expr(inst);
            if (std::find(all.begin(), all.end(), expr) != all.end()) {
                // 该表达式已经加入到all集中，什么也不用做
            } else {
                // 第一次遇到该表达式，加入到all集合
                all.push_back(expr);
            }
        }
    }

    // 第二次遍历整个函数，计算每个bb的gen集合
    for (auto bb : func_->get_basic_blocks()) {
        std::vector<bool> gen;
        // 初始化
        for (long unsigned i = 0; i < all.size(); i++) {
            gen.push_back(false);
        }

        for (auto inst : bb->get_instructions()) {
            if (!is_valid_expr(inst))
                continue;
            Expr expr(inst);
            auto iter = std::find(all.begin(), all.end(), expr);
            if (iter != all.end()) {
                // 该表达式在全集all中的位置就是它的编号
                gen[iter - all.begin()] = true;
            } else {
                // 第一次遇到该表达式
                // something wrong!
                std::cout << "something wrong?" << std::endl;
            }
        }
        gens.insert({bb, gen});
    }

    // 迭代计算每个bb的IN和OUT
    std::vector<bool> empty;  // 空集
    std::vector<bool> full;   // 全集
    for (long unsigned i = 0; i < all.size(); i++) {
        empty.push_back(false);
        full.push_back(true);
    }
    INs.insert({func_->get_basic_blocks().front(), empty});  // IN[B1] = 空集
    for (auto bb : func_->get_basic_blocks()) {
        OUTs.insert({bb, full});
    }
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto bb : func_->get_basic_blocks()) {
            // 算IN
            if (bb != func_->get_basic_blocks().front()) {
                // 第一个bb的IN不用更新
                if (INs.find(bb) != INs.end()) {
                    INs[bb] = full;
                    for (auto prebb : bb->get_pre_basic_blocks()) {
                        // 获取bb的全部前驱
                        for (long unsigned i = 0; i < all.size(); i++) {
                            INs[bb][i] = INs[bb][i] && OUTs[prebb][i];
                        }
                    }
                } else {
                    // 该bb是第一次计算IN，需要新push一个IN
                    std::vector<bool> newIN;
                    newIN = full;
                    for (auto prebb : bb->get_pre_basic_blocks()) {
                        for (long unsigned i = 0; i < all.size(); i++) {
                            newIN[i] = newIN[i] && OUTs[prebb][i];
                        }
                    }
                    INs.insert({bb, newIN});
                }
            }

            // 算OUT
            if (OUTs.find(bb) != OUTs.end()) {
                std::vector<bool> before = OUTs[bb];
                for (long unsigned i = 0; i < all.size(); i++) {
                    OUTs[bb][i] = gens[bb][i] || INs[bb][i];
                }
                if (before != OUTs[bb])
                    changed = true;
            } else {
                /*
                std::vector<bool> newOUT = empty;
                for (long unsigned i = 0; i < all.size(); i++) {
                    newOUT[i] = gens[bb][i] || INs[bb][i];
                }
                OUTs.insert({bb, newOUT});
                */
                // std::cout << "something wrong2?" << std::endl;
            }
        }
    }
    // std::cout << "INs size: " << INs.size() << std::endl;
    // std::cout << "OUTs size: " << OUTs.size() << std::endl;

    // 可能存在“并列”基本块
    // 一个可用表达式可能有多个“第一次出现时对应的指令”
    // 再次遍历整个函数，找出这样的指令，加入到表达式的“第一次”指令集合
    for (auto bb : func_->get_basic_blocks()) {
        for (auto inst : bb->get_instructions()) {
            if (!is_valid_expr(inst))
                continue;
            Expr expr(inst);
            auto expr_iter = std::find(all.begin(), all.end(), expr);  // 找到该表达式
            if (expr_iter != all.end()) {
                // 考察当前指令要不要加入该表达式的“第一次出现指令”集合
                auto begin = expr_iter->inst_.begin();
                auto end = expr_iter->inst_.end();
                if (std::find(begin, end, inst) == end) {
                    // 该指令不在该表达式的“第一次出现指令”集合中
                    if (INs[bb][expr_iter - all.begin()] == false) {
                        // 该基本块的IN中没有该表达式
                        // 还要判断块内该指令前面是否已经出现了该表达式
                        bool appeared = false;
                        for (auto preinst : bb->get_instructions()) {
                            if (preinst != inst) {
                                Expr preexpr(preinst);
                                if (preexpr == expr)
                                    appeared = true;
                            } else
                                break;
                        }
                        if (appeared == false) {
                            expr_iter->inst_.push_back(inst);
                        }
                    }
                }
            }
        }
    }
}

void ComSubExprEli::ReplaceComSubExpr() {
    /* 利用IN、gen和inst_找到不必要的公共表达式及其指令，并记录要删除的指令 */
    for (auto bb : func_->get_basic_blocks()) {
        for (auto inst : bb->get_instructions()) {
            if (!is_valid_expr(inst))
                continue;
            Expr expr(inst);
            auto iter = find(all.begin(), all.end(), expr);
            if (iter != all.end() && (INs[bb][iter - all.begin()] == true || gens[bb][iter - all.begin()] == true)) {
                // 该指令中含有公共子表达式
                // 用第一次使用该表达式的指令值取代所有用到当前指令值的地方
                // if (inst != iter->inst_) {
                if (std::find(iter->inst_.begin(), iter->inst_.end(), inst) == iter->inst_.end()) {
                    // 不属于该表达式的“第一次出现指令”的指令可以删除
                    if (iter->inst_.size() == 1) {
                        // “第一次出现指令”只有一条
                        delete_list.insert({inst, bb});
                        inst->replace_all_use_with(iter->inst_.front());
                    } else {
                        // 有并列块, "第一次出现指令"有多条
                        // 在当前基本块的开头插入一条合理的phi指令
                        delete_list.insert({inst, bb});
                        auto newphi = PhiInst::create_phi(inst->get_type(), bb);
                        newphi->set_lval(inst);
                        bb->add_instr_begin(newphi);
                        inst->replace_all_use_with(newphi);
                        for (auto finst : iter->inst_) {
                            // 将每条“第一次出现指令”及其所在的基本块加入到phi指令参数中
                            newphi->add_phi_pair_operand(finst, finst->get_parent());
                        }
                    }
                    // std::cout << "instvec: " << iter->inst_.size() << std::endl;
                }
            }
        }
    }
    // std::cout << "delete_list: " << delete_list.size() << std::endl;
}

void ComSubExprEli::RemoveComSubExpr() {
    // int count = 0;
    for (auto iter = delete_list.begin(); iter != delete_list.end(); iter++) {
        iter->second->delete_instr(iter->first);
        // count++;
    }
    // std::cout << count << " inst deleted" << std::endl;
}