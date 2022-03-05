#ifndef SYSYF_COMSUBEXPRELI_H
#define SYSYF_COMSUBEXPRELI_H

#include <map>
#include <set>
#include <vector>
#include "Instruction.h"
#include "Pass.h"

/* 表达式结构体 */
typedef struct Expr {
    std::vector<Instruction *> inst_;  // 第一次使用该表达式的指令集合，不参与表达式相等的判断
    Instruction::OpID opcode;
    std::vector<Value *> operands;  // 存操作数
    // FunctionType *func_type;    // 标识call指令的函数类型
    Expr(Instruction *inst) {
        // inst_ = inst;
        inst_.push_back(inst);
        opcode = inst->get_instr_type();
        operands = inst->get_operands();
    }
    bool operator==(const Expr &another) const {
        if (opcode != another.opcode) {
            return false;
        } else if (operands != another.operands) {
            // operands向量不直接相等，但是可能常量操作数的值是相等的
            if (operands.size() != another.operands.size())
                return false;
            for (long unsigned i = 0; i < operands.size(); i++) {
                auto const_int1 = dynamic_cast<ConstantInt *>(operands[i]);
                auto const_int2 = dynamic_cast<ConstantInt *>(another.operands[i]);
                auto const_float1 = dynamic_cast<ConstantFloat *>(operands[i]);
                auto const_float2 = dynamic_cast<ConstantFloat *>(another.operands[i]);
                if (const_int1 && const_int2) {
                    // 操作数同属于int常量
                    if (const_int1->get_value() != const_int2->get_value())
                        return false;
                } else if (const_float1 && const_float2) {
                    // 操作数同属于float常量
                    if (const_float1->get_value() != const_float2->get_value())
                        return false;
                } else {
                    // 操作数不是常量
                    if (operands[i] != another.operands[i])
                        return false;
                }
            }
            return true;
        } else {
            return true;
        }
    }
} Expr;

/*****************************CommonSubExprElimination**************************************/
/***************************This class is based on SSA form*********************************/
/***************************you need to finish this class***********************************/
class ComSubExprEli : public Pass {
public:
    explicit ComSubExprEli(Module *module) : Pass(module) {}
    const std::string get_name() const override { return name; }
    void execute() override;
    static bool is_valid_expr(Instruction *inst);
    void FindAvailExpr();
    void ReplaceComSubExpr();
    void RemoveComSubExpr();

private:
    Function *func_;
    std::map<BasicBlock *, std::vector<bool>> gens, INs, OUTs;
    std::vector<Expr> all;                              // 表达式全集
    std::map<Instruction *, BasicBlock *> delete_list;  // 要删除的表达式集合
    const std::string name = "ComSubExprEli";
};

#endif  // SYSYF_COMSUBEXPRELI_H