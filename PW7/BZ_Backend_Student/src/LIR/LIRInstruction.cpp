#include "LIR/LIRInstruction.h"
#include "LIR/LIRLabel.h"

LIRBranchInstruction *LIRBranchInstruction::create(LIRFunction *func) { return new LIRBranchInstruction(func); }
LIRBranchInstruction *LIRBranchInstruction::create(LIRBasicBlock *bb) { return new LIRBranchInstruction(bb); }
LIRBranchInstruction *LIRBranchInstruction::create(LIRBasicBlock *bb, LIRCond::LCondTy cond) {
    auto ret = new LIRBranchInstruction(bb);
    ret->_cond.setCondition(cond);
    return ret;
}

LIRBranchInstruction *LIRBranchInstruction::create(LIROperand *opr) {
    return new LIRBranchInstruction(opr);
}

bool LIRBranchInstruction::isCall() const {
    if (dynamic_cast<LIRFunction *>(getTarget())) {
        return true;
    }
    return false;
}

LIRBranchInstruction::LIRBranchInstruction(LIRFunction *lb)  : LIRInstruction(LBranchTy, 4) {
    _target = lb;
    _cond.setCondition(LIRCond::LCondNone);
    setOperand(0, LIRPhysicsRegister::create(0));
    setOperand(1, LIRPhysicsRegister::create(1));
    setOperand(2, LIRPhysicsRegister::create(2));
    setOperand(3, LIRPhysicsRegister::create(3));
}

LIRBranchInstruction::LIRBranchInstruction(LIRBasicBlock *lb)  : LIRInstruction(LBranchTy, 0) {
    _target = lb;
    _cond.setCondition(LIRCond::LCondNone);
}

LIRBranchInstruction::LIRBranchInstruction(LIROperand *reg) : LIRInstruction(LBranchTy, 1) {
    setOperand(0, reg);
}



