#include <iostream>
#include "GlobalVal.h"

GlobalVal _global_val = GlobalVal();

int main()
{
    //表达式：1.0-(1<1.2)&&(1==0)
    _global_val.push(1.0f);
    _global_val.push(1);
    _global_val.push(1.2f);
    _global_val.cal(SyntaxTree::BinaryCondOp::LT);
    _global_val.push(1);
    _global_val.push(0);
    _global_val.cal(SyntaxTree::BinaryCondOp::EQ);
    _global_val.cal(SyntaxTree::BinaryCondOp::LAND);
    _global_val.cal(SyntaxTree::BinOp::MINUS);
    if (_global_val.top_is_int())
        std::cout << _global_val.pop_int() << std::endl;
    else
    {
        std::cout << _global_val.pop_float() << std::endl;
        std::cout << _global_val.top_is_int() << std::endl;
    }
}