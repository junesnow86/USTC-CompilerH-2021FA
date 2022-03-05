#ifndef BAZINGA_COMPILER_GEP_SIMPLY_H
#define BAZINGA_COMPILER_GEP_SIMPLY_H

#include "IR/Module.h"
#include "IR/Function.h"
#include "IR/IRbuilder.h"
#include "IR/BasicBlock.h"
#include "IR/Instruction.h"
#include "pass_manager.h"

class GEP_Simply : public Pass{
private:

public:
    GEP_Simply(Module *m) : Pass(m){}
    ~GEP_Simply(){};
    void run() override;
    void remove_repeat_gep(BasicBlock *bb);
};

#endif