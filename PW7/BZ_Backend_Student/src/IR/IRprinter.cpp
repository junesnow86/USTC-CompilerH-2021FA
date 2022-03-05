#include "IR/IRprinter.h"

std::string print_as_op( Value *v, bool print_ty )
{
    std::string op_ir;
    if( print_ty )
    {
        op_ir += v->get_type()->print(); 
        op_ir += " ";
    }

    if (dynamic_cast<GlobalVariable *>(v))
    {
        op_ir += "@"+v->get_name();
    }
    else if ( dynamic_cast<Function *>(v) )
    {
        op_ir += "@"+v->get_name();
    }
    else if ( dynamic_cast<Constant *>(v))
    {
        op_ir += v->print();
    }
    else
    {
        op_ir += "%"+v->get_name();
    }

    return op_ir;
}

std::string print_cmp_type( CmpInst::CmpOp op )
{
    switch (op)
    {
    case CmpInst::GE:
        return "sge";
    case CmpInst::GT:
        return "sgt";
    case CmpInst::LE:
        return "sle";
    case CmpInst::LT:
        return "slt";
    case CmpInst::EQ:
        return "eq";
    case CmpInst::NE:
        return "ne";
    default:
        break;
    }
    return "wrong cmpop";
}