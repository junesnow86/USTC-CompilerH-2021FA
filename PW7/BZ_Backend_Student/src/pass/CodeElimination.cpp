#include "pass/CodeElimination.h"
#include "IR/Instruction.h"

/**
 * 部分指令可能对全局量或CFG产生影响，不予删除
 * @param i
 * @return
 */
static bool isSafeToDelete(Instruction *i) {
    if (i->is_store() || i->is_call() || i->is_br() || i->is_ret()) return false;
    return true;
}

void CodeElimination::run() {
    // 对所有BB块，反向扫描指令，若遇到不活跃指令则直接删除
    act->run();
    for (auto f: m_->get_functions()) {
        if (f->is_declaration()) continue;
        for (auto bb: f->get_basic_blocks()) {
            std::vector<Instruction *> tbd;
            do {
                tbd.clear();
                for (auto inst: bb->get_instructions()) {
                    if (isSafeToDelete(inst)) {
                        if (!act->isLiveOut(inst) && inst->get_use_list().empty()) {
                            tbd.push_back(inst);
                        } else {
                            bool deletable = true;
                            for (auto u: inst->get_use_list()) {
                                if (u.val_ != inst) {
                                    deletable = false;
                                }
                            }
                            if (deletable) {
                                tbd.push_back(inst);
                            }
                        }
                    }
                }
                for (auto inst: tbd) {
                    bb->delete_instr(inst);
                }
            } while (!tbd.empty());
        }
    }
}