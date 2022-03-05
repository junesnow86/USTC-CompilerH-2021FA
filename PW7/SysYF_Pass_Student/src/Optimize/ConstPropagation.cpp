#include "ConstPropagation.h"

// 给出了返回整型值的常数折叠实现，大家可以参考，在此基础上拓展
// 当然如果同学们有更好的方式，不强求使用下面这种方式

ConstantInt *ConstFolder::compute(Instruction::OpID op, ConstantInt *value1, ConstantInt *value2) {
    int const_value1 = value1->get_value();
    int const_value2 = value2->get_value();
    switch (op) {
    case Instruction::add:
        return ConstantInt::get(const_value1 + const_value2, module_);
        break;
    case Instruction::sub:
        return ConstantInt::get(const_value1 - const_value2, module_);
        break;
    case Instruction::mul:
        return ConstantInt::get(const_value1 * const_value2, module_);
        break;
    case Instruction::sdiv:
        return ConstantInt::get((int)(const_value1 / const_value2), module_);
        break;
    case Instruction::srem:
        return ConstantInt::get(const_value1 % const_value2, module_);
        break;
    default:
        return nullptr;
        break;
    }
}

// 用来判断value是否为ConstantInt，如果不是则会返回nullptr
ConstantInt *cast_to_const_int(Value *value) {
    auto const_int_ptr = dynamic_cast<ConstantInt *>(value);
    if (const_int_ptr) {
        return const_int_ptr;
    } else {
        return nullptr;
    }
}

ConstantFloat *cast_to_const_float(Value *value) {
    auto const_float_ptr = dynamic_cast<ConstantFloat *>(value);
    if (const_float_ptr) {
        return const_float_ptr;
    } else {
        return nullptr;
    }
}

void ConstPropagation::execute() {
    // Start from here!
}
