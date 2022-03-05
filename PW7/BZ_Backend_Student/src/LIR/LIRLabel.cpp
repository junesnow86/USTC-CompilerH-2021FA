#include "LIR/LIRLabel.h"
#include <IR/Constant.h>

LIRGlobalVariable::LIRGlobalVariable(std::string name, Type *ty, Constant *init, const std::vector<int> &flat) : LIRLabel(std::move(name), LIRLabelTy::LGlobalVariableTy){
    ty = ty->get_pointer_element_type();
    if (ty->is_int32_type()) {
        _num_elem = 1;
        if (auto ci = dynamic_cast<ConstantInt *>(init)) {
            _initial.push_back(ci->get_value());
        }
        else {
            _initial.push_back(0);
        }
    }
    else {
        int sz = 1;
        auto arr_ty = dynamic_cast<ArrayType *>(ty);
        while (arr_ty) {
            sz *= (int)arr_ty->get_num_of_elements();
            arr_ty = dynamic_cast<ArrayType *>(arr_ty->get_array_element_type());
        }
        _num_elem = sz;
        if(dynamic_cast<ConstantArray *>(init)) {
            _initial = flat;
        }
    }
}

std::string ConstantPool::getLabelName() const {
    return ".L" + getName();
}

std::string ConstantPool::print() const {
    auto ret = getLabelName();
    ret += ":\n";
    for (auto v: _literalList) {
        ret += "\t.word\t";
        if (cSet.find(static_cast<LIRConstantOperand *>(v)) != cSet.end()) {
            ret += std::to_string(static_cast<LIRConstantOperand *>(v)->getValue());
        } else if (lSet.find(static_cast<LIRLabel *>(v)) != lSet.end()) {
            ret += static_cast<LIRLabel *>(v)->getLabelName();
        } else {
            assert(0 && "Error: unknown type");
        }
        ret += "\n";
    }
    return ret;
}

int ConstantPool::getPoolOffset(LIRConstantOperand *c) {
    if (_posMap.find(c) == _posMap.end()) {
        _posMap[c] = topPos;
        cSet.insert(c);
        topPos+=4;
        _literalList.push_back(c);
    }
    return _posMap.at(c);
}

int ConstantPool::getPoolOffset(LIRLabel *l) {
    if (_posMap.find(l) == _posMap.end()) {
        _posMap[l] = topPos;
        lSet.insert(l);
        topPos+=4;
        _literalList.push_back(l);
    }
    return _posMap.at(l);
}
