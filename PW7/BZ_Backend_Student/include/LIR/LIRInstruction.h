#ifndef BAZINGA_COMPILER_LIRINSTRUCTION_H
#define BAZINGA_COMPILER_LIRINSTRUCTION_H

#include <vector>
#include <cassert>

#include "LIR/LIROperand.h"

class LIRLabel;
class LIRBasicBlock;
class LIRFunction;

class LIRInstruction {
public:
    enum LIRInstType {
        LAddTy,
        LSubTy,
        LMulTy,
        LDivTy,
        LLslTy,
        LLsrTy,
        LAsrTy,
        LSMMulTy,
        LBranchTy,
        LMovTy,
        LLoadTy,
        LStoreTy,
        LPushTy,
        LPopTy,
        LCmpTy
    };
protected:
    LIRInstruction(LIRInstType ty, int numOp) : _code(ty) {
        _opr_list.resize(numOp);
    }

    LIRInstruction(LIRInstType ty, int numOp, LIROperand *result) : _code(ty), _result(result) {
        assert(!result->isConstantTy() && "Constant type can't be used as an destination.");
        _opr_list.resize(numOp);
        result->addUse(-1, this);
    }

private:
    LIRBasicBlock *_parent = nullptr;
    LIROperand *_result = nullptr;
    LIRInstType _code;
    int _id = -1;
    std::vector<LIROperand *> _opr_list;
protected:
    void setNumOperands(int nop) { _opr_list.resize(nop); }

public:
    LIRInstruction() = delete;

    void assignInstId(int id) { _id = id; }
    void setParent(LIRBasicBlock *p) { _parent = p; }
    void setResult(LIROperand *r) { _result = r; }
    void setOperand(unsigned idx, LIROperand *opr) {
        _opr_list[idx] = opr;
        opr->addUse((int)idx, this);
    }
    LIROperand *getOperand(int idx) const { return _opr_list.at(idx); }
    std::vector<LIROperand *> getOperands() const { return _opr_list; }
    std::vector<LIROperand *> &getOperands() { return _opr_list; }
    std::vector<LIROperand *> getOperandsWithResult() {
        std::vector<LIROperand *> result = _opr_list;
        if (getResult() != nullptr) {
            result.push_back(getResult());
        }
        return result;
    }
    int getNumOperands() const { return _opr_list.size(); }
    int getInstId() const { return _id; }
    LIRInstType getInstType() const { return _code; }
    LIRBasicBlock *getParent() const { return _parent; }
    LIROperand *getResult() const { return _result; }
    bool hasResult() const { return _result != nullptr; }
    virtual std::string print() = 0;
};

class LIRCond {
public:
    enum LCondTy {
        LCondGT,
        LCondGE,
        LCondLT,
        LCondLE,
        LCondEQ,
        LCondNE,
        LCondNone
    };
private:
    LCondTy _cond;

public:
    void inverse() {
        switch (_cond) {
            case LCondEQ:
                _cond = LCondNE;
                break;
            case LCondNE:
                _cond = LCondEQ;
                break;
            case LCondLE:
                _cond = LCondGT;
                break;
            case LCondLT:
                _cond = LCondGE;
                break;
            case LCondGT:
                _cond = LCondLE;
                break;
            case LCondGE:
                _cond = LCondLT;
                break;
            case LCondNone:
                break;
            default:
                assert(0 && "Invalid condition type");
        }
    }

    const LCondTy &getCondition() const { return _cond; }
    void setCondition(LCondTy ty) { _cond = ty; }

    std::string print() const {
        switch (getCondition()) {
            case LCondNone: return "";
            case LCondLE: return "le";
            case LCondEQ: return "eq";
            case LCondNE: return "ne";
            case LCondGE: return "ge";
            case LCondGT: return "gt";
            case LCondLT: return "lt";
            default: return "err";
        }
    }
};

class LIRMovInst : public LIRInstruction {
private:
    LIRCond _cond{};

    /**
     * 创建MOV指令，我们在这个构建阶段暂时不考虑立即数超过有效范围的问题
     * 在构建完成后再进行一次指令扫描、替换与常量池构造过程来进行修复
     * @param dst 目的寄存器
     * @param src 来源寄存器/立即数
     */
    LIRMovInst(LIROperand *dst, LIROperand *src) : LIRInstruction(LMovTy, 1, dst) {
        setOperand(0, src);
        _cond.setCondition(LIRCond::LCondNone);
    }

    LIRMovInst(LIROperand *dst, LIROperand *src, LIRCond::LCondTy ty) : LIRInstruction(LMovTy, 1, dst) {
        setOperand(0, src);
        _cond.setCondition(ty);
    }

public:
    static LIRMovInst *create(LIROperand *dst, LIROperand *src) {
        return new LIRMovInst(dst, src);
    }

    static LIRMovInst *createCond(LIROperand *dst, LIROperand *src, LIRCond::LCondTy cond) {
        return new LIRMovInst(dst, src, cond);
    }

    std::string print() final;
    const LIRCond &getCondition() const { return _cond; }
};

class LIRBinaryInst : public LIRInstruction {
private:
    LIRBinaryInst(LIRInstType ty, LIROperand *dst, LIROperand *lhs, LIROperand *rhs) : LIRInstruction(ty, 2, dst) {
        assert(!lhs->isConstantTy() && "Left operand of binary operation can't be a constant");
        setOperand(0, lhs);
        setOperand(1, rhs);
    }

public:
    static LIRBinaryInst *createAdd(LIROperand *dst, LIROperand *lhs, LIROperand *rhs) {
        return new LIRBinaryInst(LAddTy, dst, lhs, rhs);
    }

    static LIRBinaryInst *createSub(LIROperand *dst, LIROperand *lhs, LIROperand *rhs) {
        return new LIRBinaryInst(LSubTy, dst, lhs, rhs);
    }

    static LIRBinaryInst *createLsl(LIROperand *dst, LIROperand *lhs, LIROperand *rhs) {
        return new LIRBinaryInst(LLslTy, dst, lhs, rhs);
    }

    static LIRBinaryInst *createLsr(LIROperand *dst, LIROperand *lhs, LIROperand *rhs) {
        return new LIRBinaryInst(LLsrTy, dst, lhs, rhs);
    }

    static LIRBinaryInst *createAsr(LIROperand *dst, LIROperand *lhs, LIROperand *rhs) {
        return new LIRBinaryInst(LAsrTy, dst, lhs, rhs);
    }

    static LIRBinaryInst *createSMMul(LIROperand *dst, LIROperand *lhs, LIROperand *rhs){
        return new LIRBinaryInst(LSMMulTy, dst, lhs, rhs);
    }

    static LIRBinaryInst *createMul(LIROperand *dst, LIROperand *lhs, LIROperand *rhs) {
        assert(!rhs->isConstantTy() && "Right operand of MUL can't be a constant");
        return new LIRBinaryInst(LMulTy, dst, lhs, rhs);
    }

    static LIRBinaryInst *createDiv(LIROperand *dst, LIROperand *lhs, LIROperand *rhs) {
        assert(!rhs->isConstantTy() && "Right operand of SDIV can't be a constant");
        return new LIRBinaryInst(LDivTy, dst, lhs, rhs);
    }

    std::string print() final;
};

class LIRLoadInst : public LIRInstruction {
private:
    LIRLabel *_lb = nullptr;
    LIRConstantOperand *constOffset = nullptr;

    LIRLoadInst(LIROperand *dst, int numOps) : LIRInstruction(LLoadTy, numOps, dst) {}

public:
    LIRLabel *getLabel() const { return _lb; }

    /**
     * 创建 ldr 指令
     * ldr rd, [rs]
     * ldr rd, =0x0
     */
    static LIRLoadInst *create(LIROperand *dst, LIROperand *memSrc) {
        auto ret = new LIRLoadInst(dst, 1);
        ret->setOperand(0, memSrc);
        return ret;
    }

    /**
     * 创建 ldr 指令
     * ldr rd, [rs, rm]
     */
    static LIRLoadInst *create(LIROperand *dst, LIROperand *memSrc, LIROperand *off) {
        auto ret = new LIRLoadInst(dst, 2);
        ret->setOperand(0, memSrc);
        ret->setOperand(1, off);
        return ret;
    }

    /**
     * 创建 ldr 指令
     * ldr rd, =label
     */
     static LIRLoadInst *create(LIROperand *dst, LIRLabel *label) {
         auto ret = new LIRLoadInst(dst, 0);
         ret->_lb = label;
         return ret;
     }

     /**
      * 创建 ldr 指令
      * ldr rd, .L+0x80
      */
     static LIRLoadInst *create(LIROperand *dst, LIRLabel *label, LIRConstantOperand *off) {
         auto ret = new LIRLoadInst(dst, 0);
         ret->_lb = label;
         ret->constOffset = off;
         return ret;
     }

     std::string print() final;
};

class LIRStoreInst : public LIRInstruction {
private:
    LIRStoreInst(LIROperand *src, LIROperand* rs) : LIRInstruction(LStoreTy, 2) {
        setOperand(0, src);
        setOperand(1, rs);
    }

    LIRStoreInst(LIROperand *src, LIROperand *rs, LIROperand *rm) : LIRInstruction(LStoreTy, 3) {
        setOperand(0, src);
        setOperand(1, rs);
        setOperand(2, rm);
    }

public:
    /**
     * 创建 str 指令
     * str rd, [rs]
     */
    static LIRStoreInst *create(LIROperand *src, LIROperand *dst) {
        return new LIRStoreInst(src, dst);
    }

    /**
     * 创建 str 指令
     * str rd, [rs, rm]
     */
    static LIRStoreInst *create(LIROperand *src, LIROperand *dst, LIROperand *off) {
        assert(!dst->isConstantTy());
        return new LIRStoreInst(src, dst, off);
    }

    LIROperand *getDataSrc() const { return getOperand(0); }


    std::string print() final;
};

class LIRCmpInst : public LIRInstruction {
private:
    LIRCmpInst(LIROperand *lhs, LIROperand *rhs) : LIRInstruction(LCmpTy, 2) {
        setOperand(0, lhs);
        setOperand(1, rhs);
    }

public:
    static LIRCmpInst *create(LIROperand *lhs, LIROperand *rhs) {
        return new LIRCmpInst(lhs, rhs);
    }


    std::string print() final;
};


class LIRBranchInstruction : public LIRInstruction {
private:
    LIRLabel *_target = nullptr;
    LIRCond _cond{};

    explicit LIRBranchInstruction(LIRBasicBlock *lb);

    explicit LIRBranchInstruction(LIRFunction *lb);

    explicit LIRBranchInstruction(LIROperand *reg);
public:

    // bl func
    static LIRBranchInstruction *create(LIRFunction *func);
    // b label
    static LIRBranchInstruction *create(LIRBasicBlock *bb);
    // bge label
    static LIRBranchInstruction *create(LIRBasicBlock *bb, LIRCond::LCondTy cond);
    // bx lr / bx r1
    static LIRBranchInstruction *create(LIROperand *opr);

    LIRCond::LCondTy getCondition() const { return _cond.getCondition(); }
    const LIRCond &getCond() const { return _cond; }
    LIRLabel *getTarget() const { return _target; }
    bool isCall() const;
    void setTarget(LIRLabel *target) { _target = target; }

    std::string print() final;
};


class LIRPushInst : public LIRInstruction {
private:
    explicit LIRPushInst(const std::vector<LIRPhysicsRegister *> &list) : LIRInstruction(LPushTy, list.size()) {
        for (int i = 0; i < list.size(); ++i) {
            setOperand(i, list.at(i));
        }
    }
public:
    static LIRPushInst *create(const std::vector<LIRPhysicsRegister *> &list) {
        return new LIRPushInst(list);
    }

    std::string print() final;
};


class LIRPopInst : public LIRInstruction {
private:
    explicit LIRPopInst(const std::vector<LIRPhysicsRegister *> &list) : LIRInstruction(LPopTy, list.size()) {
        for (int i = 0; i < list.size(); ++i) {
            setOperand(i, list.at(i));
        }
    }
public:
    static LIRPopInst *create(const std::vector<LIRPhysicsRegister *> &list) {
        return new LIRPopInst(list);
    }

    std::string print() final;
};


class LIRAlloca {
    int _base;
    int _size;
    LIRAlloca(int base, int size) : _base(base), _size(size) {};
public:
    static LIRAlloca *create(int base, int size){
        return new LIRAlloca(base, size);
    }

    int getBase() const { return _base; }
};

#endif //BAZINGA_COMPILER_LIRINSTRUCTION_H
