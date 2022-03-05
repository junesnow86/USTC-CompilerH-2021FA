#ifndef SYSYF_COMSUBEXPRELI_H
#define SYSYF_COMSUBEXPRELI_H

#include "Pass.h"
#include <map>
#include <set>
#include "Instruction.h"



/*****************************CommonSubExprElimination**************************************/
/***************************This class is based on SSA form*********************************/
/***************************you need to finish this class***********************************/
class ComSubExprEli : public Pass {
public:
    explicit ComSubExprEli(Module* module):Pass(module){}
    const std::string get_name() const override {return name;}
    void execute() override;
    static bool is_valid_expr(Instruction* inst);
private:
    const std::string name = "ComSubExprEli";
};

#endif // SYSYF_COMSUBEXPRELI_H