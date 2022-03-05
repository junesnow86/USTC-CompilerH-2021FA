#ifndef BAZINGA_COMPILER_ACTIVE_VARS_H
#define BAZINGA_COMPILER_ACTIVE_VARS_H
#include "pass_manager.h"
#include "IR/Constant.h"
#include "IR/Instruction.h"
#include "IR/Module.h"
#include "IR/Value.h"
#include "IR/IRbuilder.h"
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <queue>

class ActiveVars: public Pass {
public:
    explicit ActiveVars(Module *m): Pass(m){}
    void run() override;
    std::unordered_set<Value *> getLiveIn(BasicBlock *bb) { return live_in[bb]; }
    std::unordered_set<Value *> getLiveOut(BasicBlock *bb) { return live_out[bb]; }

    /**
     * 判断指令是否在出口处是活跃的
     * @param i
     * @return
     */
    bool isLiveOut(Instruction *i) {
        auto &m = live_out[i->get_parent()];
        return m.find(i) != m.end();
    }
    std::unordered_set<Value *> getUse(BasicBlock *bb) { return use[bb]; }
    std::unordered_set<Value *> getDef(BasicBlock *bb) { return def[bb]; }
private:
    Function *func_{};
    std::map<BasicBlock*,std::unordered_set<Value *> > active, live_in, live_out;
    std::map<BasicBlock*,std::unordered_set<Value *> > use, def, phi_op;
    std::map<BasicBlock*,std::set<std::pair<BasicBlock *,Value  *>>> phi_op_pair;

};


#endif //BAZINGA_COMPILER_ACTIVE_VARS_H
