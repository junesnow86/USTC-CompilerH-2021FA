#include "LIR/LIROperand.h"
#include "LIR/LIRInstruction.h"

int LIRVirtualRegister::_totalRegId = 0;

const std::map<int, std::string> LIRPhysicsRegister::_regNameMap = {
        {-1, "error"},
        {0, "r0"},
        {1, "r1"},
        {2, "r2"},
        {3, "r3"},
        {4, "r4"},
        {5, "r5"},
        {6, "r6"},
        {7, "r7"},
        {8, "r8"},
        {9, "r9"},
        {10, "sl"},
        {11, "fp"},
        {12, "ip"},
        {13, "sp"},
        {14, "lr"},
        {15, "pc"},
};

void LIRVirtualRegister::replaceAllUseWith(LIROperand *opr) {
    assert(opr != this && "Should not replace VReg with itself");
    for (auto use: getUseList()) {
        if (use->idx >= 0) {
            use->user->setOperand(use->idx, opr);
        } else {
            use->user->setResult(opr);
        }
    }
    clearUse();
}

void LIRVirtualRegister::replaceAllUseAfterID(LIROperand *opr, int after) {
    assert(opr != this && "Should not replace VReg with itself");
    auto &u = getUseList();
    auto use = u.begin();
    while (use != u.end()) {
        if ((*use)->user->getInstId() > after) {
            if ((*use)->idx >= 0) {
                (*use)->user->setOperand((*use)->idx, opr);
            } else {
                (*use)->user->setResult(opr);
            }
            use = u.erase(use);
        } else {
            use ++;
        }
    }
}
