#include "pass/CFG_simply.h"
#include "pass/loop_search.h"


void CFG_simply::run() {

    for (auto fun : m_->get_functions())
    {
        func_ = fun;
        if(func_->is_declaration())
            continue;
        rebuildCFG();
        changed = true;
        while(changed) {
            changed = false;
            rebuildCFG();
            fix_phi();
            del_no_pre();
            del_singel_phi();
            merge_single();
            rebuildCFG();
            _ls->run();
            del_uncond();
            del_self_loop();
        }
    }
}

void CFG_simply::fix_phi()
{
    for (auto bb : func_->get_basic_blocks())
    {
        for (auto instr : bb->get_instructions())
            if (instr->is_phi()) {
                for (int i = 0; i < instr->get_num_operand(); i++)
                    if (i % 2 == 1) {
                        bool flag = true;
                        for(auto pre_bb : bb->get_pre_basic_blocks())
                        {
                            if(instr->get_operand(i) == pre_bb)
                            {
                                flag = false;
                                break;
                            }
                        }
                        if(flag)
                        {
                            instr->remove_operands(i-1,i);
                        }
                    }
            }
    }
}

void CFG_simply::del_self_loop() {
    bb_del.clear();
    for (auto bb : func_->get_basic_blocks())
    {
        if ((bb->get_pre_basic_blocks().size() == 1)&&
            (bb != func_->get_entry_block()) &&
            (*(bb->get_pre_basic_blocks().begin()) == bb))
            bb_del.push_back(bb);
    }
    for(auto bb : bb_del)
    {
        func_->remove(bb);
        changed = true;
    }
}

void CFG_simply::del_no_pre_(BasicBlock * bb) {
    if (bb->get_pre_basic_blocks().empty() && bb != func_->get_entry_block()) {
        for (auto succ_bb : _cfg->getSuccBB(bb)) {
            succ_bb->remove_pre_basic_block(bb);
            del_no_pre_(succ_bb);
        }
        bb_del.push_back(bb);
    }
}

void CFG_simply::del_no_pre() {
    bb_del.clear();
    for (auto bb : func_->get_basic_blocks()) {
        del_no_pre_(bb);
    }
    for(auto bb : bb_del)
    {
        changed = true;
        func_->remove(bb);
    }
}

void CFG_simply::merge_single() {
    bb_del.clear();
    for (auto bb : func_->get_basic_blocks()) {
        if (bb->get_pre_basic_blocks().size() == 1) {
            auto pre_bb = bb->get_pre_basic_blocks().begin();
            auto br = (*pre_bb)->get_terminator();
            if (br->get_num_operand() == 1) {
                (*pre_bb)->delete_instr(br);
                for (auto instr : bb->get_instructions()) {
                    instr->set_parent(*pre_bb);
                    (*pre_bb)->add_instruction(instr);
                }
                (*pre_bb)->remove_succ_basic_block(bb);
                for (auto succ_bb : bb->get_succ_basic_blocks()) {
                    (*pre_bb)->add_succ_basic_block(succ_bb);
                    succ_bb->get_pre_basic_blocks().remove(bb);
                    succ_bb->add_pre_basic_block(*pre_bb);
                }
                bb->replace_all_use_with(*pre_bb);
                bb_del.push_back(bb);
            }
        }
    }
    for(auto bb : bb_del)
    {
        changed = true;
        func_->remove(bb);
    }
}

void CFG_simply::del_singel_phi() {
    std::vector<Instruction*> instr_del;
    for (auto bb : func_->get_basic_blocks()) {
        instr_del.clear();
        if (bb->get_pre_basic_blocks().size() == 1 || bb == func_->get_entry_block()) {
            for (auto instr : bb->get_instructions()) {
                if (instr->is_phi()) {
                    for (auto use : instr->get_use_list())
                        dynamic_cast<User *>(use.val_)->set_operand(
                                    use.arg_no_, instr->get_operand(0));
                    instr_del.push_back(instr);
                }
            }
        }
        for(auto instr : instr_del)
        {
            changed = true;
            bb->delete_instr(instr);
        }
    }
}

void CFG_simply::del_uncond() {
    bb_del.clear();
    for (auto bb : func_->get_basic_blocks()) {
        if (bb->get_num_of_instr() == 1 && bb != func_->get_entry_block()) {
            auto terminator = bb->get_terminator();
            auto succ_bb = bb->get_succ_basic_blocks().begin();
            if (terminator->is_br() && terminator->get_num_operand() == 1) {
                bool if_del = true;
                for (auto pre_bb : bb->get_pre_basic_blocks()) {
                    auto br = dynamic_cast<BranchInst *>(pre_bb->get_terminator());
                    if (br->is_cond_br()) {
                        auto target1 = br->get_operand(1);
                        auto target2 = br->get_operand(2);
                        auto target3 = dynamic_cast<BranchInst *>(terminator)->get_operand(0);
                        if ((target1 == bb && target2 == target3) ||
                            (target2 == bb && target1 == target3)) {
                            if_del = false;
                            break;
                        }
                    } else if (br->is_cmp()) {
                        auto target1 = br->get_operand(2);
                        auto target2 = br->get_operand(3);
                        auto target3 = dynamic_cast<BranchInst *>(terminator)->get_operand(0);
                        if ((target1 == bb && target2 == target3) ||
                            (target2 == bb && target1 == target3)) {
                            if_del = false;
                            break;
                        }
                    }
                }

                std::vector<BasicBlock *> loopcheck;
                auto loop = _ls->get_smallest_loop(bb);
                if(loop != nullptr){
                    loop->getExitingBB(loopcheck);
                    if(loopcheck.size()==0)
                        if_del = false;
                }


                if (if_del) {
                    for (auto instr : (*succ_bb)->get_instructions()) {
                        if (instr->is_phi()) {
                            for (int i = 0; i < instr->get_num_operand(); i++) {
                                if (i % 2 == 1) {
                                    if (instr->get_operand(i) == bb) {
                                        auto idx = 0;
                                        auto val = instr->get_operand(i - 1);
                                        for (auto pre_bb : bb->get_pre_basic_blocks()) {
                                            if(pre_bb == bb)
                                                continue;
                                            if (idx == 0) {
                                                instr->set_operand(i, pre_bb);
                                                bb->remove_use(instr);
                                            } else {
                                                instr->add_operand(val);
                                                instr->add_operand(pre_bb);
                                            }
                                            idx++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    auto tmp = bb->get_use_list();
                    for (auto use : bb->get_use_list()) {
                        auto instr = dynamic_cast<Instruction *>(use.val_);
                        if (instr) {
                            if (instr->is_br()) {
                                dynamic_cast<User *>(use.val_)->set_operand(use.arg_no_,
                                                                        *succ_bb);
                            }
                        }
                    }

                    (*succ_bb)->remove_pre_basic_block(bb);
                    for (auto pre_bb : bb->get_pre_basic_blocks()) {
                        pre_bb->remove_succ_basic_block(bb);
                        pre_bb->add_succ_basic_block(*succ_bb);
                        (*succ_bb)->add_pre_basic_block(pre_bb);
                    }
                    bb_del.push_back(bb);
                }
            }
        }
    }
    for(auto bb : bb_del)
    {
        changed = true;
        func_->remove(bb);
    }
}

void CFG_simply::rebuildCFG() {
    _cfg->runOnFunction(func_);
    for (auto bb: func_->get_basic_blocks()) {
        bb->set_succ_bb(_cfg->getSuccBB(bb));
        bb->set_pre_bb(_cfg->getPrevBB(bb));
    }
}