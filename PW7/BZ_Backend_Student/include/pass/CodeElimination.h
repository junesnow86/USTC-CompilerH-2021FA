#ifndef BAZINGA_COMPILER_CODEELIMINATION_H
#define BAZINGA_COMPILER_CODEELIMINATION_H

#include "pass_manager.h"
#include "active_vars.h"


/***===
 * 删除块中不活跃的指令。使用活跃变量分析方法
 */
class CodeElimination : public Pass {
public:
    explicit CodeElimination(Module *m) : Pass(m), act(new ActiveVars(m)) {}

    void run() final;

private:
    ActiveVars *act;
};

#endif //BAZINGA_COMPILER_CODEELIMINATION_H
