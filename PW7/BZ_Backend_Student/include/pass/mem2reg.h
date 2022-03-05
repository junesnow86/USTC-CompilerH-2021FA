#ifndef BAZINGA_COMPILER_MEM2REG_H
#define BAZINGA_COMPILER_MEM2REG_H

#include "IR/Module.h"
#include "IR/Function.h"
#include "IR/IRbuilder.h"
#include "IR/BasicBlock.h"
#include "IR/Instruction.h"
#include "pass_manager.h"
#include "dominator.h"

class Mem2Reg : public Pass
{
private:
    Function * func_{};
    dominator *dom{};

public:
    explicit Mem2Reg(Module *m) : Pass(m){}
    ~Mem2Reg()= default;;
    void run() override;
    void rename(BasicBlock *bb);
};

#endif