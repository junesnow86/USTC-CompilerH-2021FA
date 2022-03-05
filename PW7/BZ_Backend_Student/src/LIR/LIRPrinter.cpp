#include <utility>
#include "LIR/LIRLabel.h"
#include "LIR/LIRBuilder.h"

const static std::map<LIRInstruction::LIRInstType, std::string> opNameMap = {
        {LIRInstruction::LIRInstType::LAddTy, "add"},
        {LIRInstruction::LIRInstType::LSubTy, "sub"},
        {LIRInstruction::LIRInstType::LMulTy, "mul"},
        {LIRInstruction::LIRInstType::LDivTy, "sdiv"},
        {LIRInstruction::LIRInstType::LLslTy, "lsl"},
        {LIRInstruction::LIRInstType::LLsrTy, "lsr"},
        {LIRInstruction::LIRInstType::LAsrTy, "asr"},
        {LIRInstruction::LIRInstType::LSMMulTy, "smmul"},
};

std::string LIRBranchInstruction::print() {
    std::string ret = "\t";
    if (getTarget() == nullptr) {
        ret += "bx";
        ret += '\t';
        ret += getOperand(0)->print();
    } else {
        if (getTarget()->isFunctionType()) {
            ret += "bl";
        } else {
            ret += "b";
            ret += getCond().print();
        }
        ret += '\t';
        ret += getTarget()->getLabelName();
    }
    ret += '\n';
    return ret;
}

std::string LIRMovInst::print() {
    std::string ret = "\t";
    ret += "mov";
    ret += getCondition().print();
    ret += "\t";
    ret += getResult()->print();
    ret += ",\t";
    ret += getOperand(0)->print();
    ret += '\n';
    return ret;
}

std::string LIRBinaryInst::print() {
    std::string ret = "\t";
    ret += opNameMap.at(getInstType());
    ret += '\t';
    ret += getResult()->print();
    ret += ",\t";
    ret += getOperand(0)->print();
    ret += ",\t";
    ret += getOperand(1)->print();
    ret += '\n';
    return ret;
}

std::string LIRLoadInst::print() {
    std::string ret = "\t";
    ret += "ldr";
    ret += '\t';
    ret += getResult()->print();
    ret += ",\t";
    if (getNumOperands() == 1) {
        if (dynamic_cast<LIRConstantOperand *>(getOperand(0))) {
            ret += "=";
            ret += getOperand(0)->print();
        } else {
            ret += "[";
            ret += getOperand(0)->print();
            ret += "]";
        }
    } else if (getNumOperands() == 2) {
        ret += "[";
        ret += getOperand(0)->print();
        ret += ",\t";
        ret += getOperand(1)->print();
        ret += "]";
    } else {
        if (constOffset) {
            ret += _lb->getLabelName();
            ret += "+";
            ret += std::to_string(constOffset->getValue());
        } else {
            ret += "=";
            ret += _lb->getLabelName();
        }
    }
    ret += '\n';
    return ret;
}

std::string LIRStoreInst::print() {
    std::string ret = "\t";
    ret += "str";
    ret += '\t';
    ret += getDataSrc()->print();
    ret += ",\t";
    ret += '[';
    ret += getOperand(1)->print();
    if (getNumOperands() > 2) {
        ret += ",\t";
        ret += getOperand(2)->print();
    }
    ret += "]\n";
    return ret;
}

std::string LIRCmpInst::print() {
    std::string ret = "\t";
    ret += "cmp";
    ret += '\t';
    ret += getOperand(0)->print();
    ret += ",\t";
    ret += getOperand(1)->print();
    ret += '\n';
    return ret;
}

std::string LIRBasicBlock::print() const {
    std::string ret = getLabelName();
    ret += ":\n";
    for (const auto i: *this) {
        ret += i->print();
    }
    if (getConstantPool() != nullptr) {
        ret += getConstantPool()->print();
    }
    return ret;
}

std::string LIRBasicBlock::getLabelName() const {
    return getParent()->getName() + "." + getName();
}

LIRBasicBlock *LIRBasicBlock::splitBB(LIRInstruction *after) {
    bool del = false;
    std::vector<LIRInstruction *> tbr;
    auto it = begin();
    while (it != end() && *it != after) {
        ++it;
    }
    if (it == end()) return nullptr;
    it++;
    if (it == end()) return nullptr;
    auto newBB = LIRBasicBlock::create(getName() + ".c");
    newBB->_instList.insert(newBB->_instList.end(), it, end());
    _instList.erase(it, end());
    // 为前面的块添加一个branch inst
    addInst(LIRBranchInstruction::create(newBB));
    return newBB;
}

std::string LIRFunction::print() const {
    std::string ret = getLabelName();
    ret += ":\n";
    for (const auto bb: *this) {
        ret += bb->print();
    }
    return ret;
}

std::string LIRFunction::getLabelName() const {
    return getName();
}

std::string LIRGlobalVariable::print() const {
    std::string ret = "\t.global ";
    ret += getLabelName();
    ret += "\n";
    ret += "\t.align\t2\n";
    ret += "\t.type\t" + getName() + ", %object\n";
    ret += "\t.size\t" + getName() + ", " + std::to_string(getNumElem() * 4) + '\n';
    ret += getLabelName();
    ret += ":\n";
    if (getNumElem() > 1) {
        int blank_size = 0;
        for (auto i: getInitialValue()) {
            if (i == 0) {
                blank_size += 1;
            }
            else {
                if (blank_size != 0) {
                    if (blank_size == 1) {
                        ret += '\t';
                        ret += ".word";
                        ret += '\t';
                        ret += "0\n";
                    } else {
                        ret += '\t';
                        ret += ".space";
                        ret += '\t';
                        ret += std::to_string(4 * blank_size);
                        ret += "\n";
                    }
                    blank_size = 0;
                }
                ret += '\t';
                ret += ".word";
                ret += '\t';
                ret += std::to_string(i);
                ret += '\n';
            }
        }
        if (blank_size != 0) {
            if (blank_size == 1) {
                ret += '\t';
                ret += ".word";
                ret += '\t';
                ret += "0\n";
            } else {
                ret += '\t';
                ret += ".space";
                ret += '\t';
                ret += std::to_string(4 * blank_size);
                ret += "\n";
            }
        }
        /*
        for (auto i: getArrayInitial()) {
            ret += l_spacing;
            ret += ".word";
            ret += s_spacing;
            ret += std::to_string(i);
            ret += '\n';
        }
        */
        // Uninitialized items
        int num_un = getNumElem() - (int) getInitialValue().size();
        if (num_un > 0) {
            ret += '\t';
            ret += ".space";
            ret += '\t';
            ret += std::to_string(4 * num_un);
            ret += '\n';
        }
    } else {
        ret += '\t';
        ret += ".word " + std::to_string(getInitialValue().at(0)) + '\n';
    }
    return ret;
}


std::string LIRBuilder::print() {
    std::string ret = "\t.arch armv8 -a\n";
    ret += "\t.file \"test.sy\"\n";
    ret += "\t.data\n";
    for (auto gv: _gvMap) {
        ret += gv.second->print();
    }
    ret += "\t.text\n";
    for (auto f: _funcList) {
        ret += "\t.global ";
        ret += f->getLabelName();
        ret += "\n";
    }
    for (auto f: _funcList) {
        ret += f->print();
    }
    return ret;
}

std::string LIRPushInst::print() {
    std::string ret = "\t";
    ret += "push";
    ret += "\t{";
    for (auto op: getOperands()) {
        ret += op->print();
        ret += ", ";
    }
    ret.pop_back();
    ret.pop_back();
    ret += "}\n";
    return ret;
}

std::string LIRPopInst::print() {
    std::string ret = "\t";
    ret += "pop";
    ret += "\t{";
    for (auto op: getOperands()) {
        ret += op->print();
        ret += ", ";
    }
    ret.pop_back();
    ret.pop_back();
    ret += "}\n";
    return ret;
}