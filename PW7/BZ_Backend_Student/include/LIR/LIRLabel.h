#ifndef BAZINGA_COMPILER_LIRBASICBLOCK_H
#define BAZINGA_COMPILER_LIRBASICBLOCK_H

#include <string>
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <set>

#include "LIRInstruction.h"

class LIRFunction;
class Type;
class Constant;
class ConstantPool;

class LIRLabel {
public:
    enum LIRLabelTy {
        LFunctionTy,
        LBasicBlockTy,
        LGlobalVariableTy,
        LConstantPoolTy
    };
private:
    std::string _name;
    LIRLabelTy _ty;
protected:
    explicit LIRLabel(std::string name, LIRLabelTy ty) : _name(std::move(name)), _ty(ty) {}
public:
    std::string getName() const { return _name; };
    LIRLabelTy getType() const { return _ty; }
    bool isFunctionType() const { return getType() == LFunctionTy; }
    bool isBasicBlockType() const { return getType() == LBasicBlockTy; }
    bool isGlobalVariableType() const { return getType() == LGlobalVariableTy; }
    virtual std::string print() const = 0;
    virtual std::string getLabelName() const = 0;
};

class LIRBasicBlock : public LIRLabel {
private:
    LIRFunction *_parent = nullptr;
    std::list<LIRInstruction *> _instList;
    int blockId = 0;
    int incomingForwardBranches = 0;
    int loopIdx = 0;
    int loopDepth = 0;
    std::set<LIRBasicBlock *> _successor;
    std::set<LIRBasicBlock *> _predecessor;
    std::set<LIROperand *> _liveGen;
    std::set<LIROperand *> _liveKill;
    std::set<LIROperand *> _liveIn;
    std::set<LIROperand *> _liveOut;
    ConstantPool *pool = nullptr;

    explicit LIRBasicBlock(std::string name) : LIRLabel(std::move(name), LBasicBlockTy) {}
public:
    void setConstantPool(ConstantPool *p) { pool = p; }
    ConstantPool *getConstantPool() const { return pool; }
    static LIRBasicBlock *create(std::string name) { return new LIRBasicBlock(std::move(name)); }
    void setParent(LIRFunction *p) { _parent = p; }
    LIRFunction *getParent() const { return _parent; }
    void addInstFront(LIRInstruction *inst) {
        _instList.push_front(inst);
        inst->setParent(this);
    }
    void addInst(LIRInstruction *inst) {
        _instList.push_back(inst);
        inst->setParent(this);
    }
    LIRBasicBlock *splitBB(LIRInstruction *after);
    /**
     * 在BB尾部的br前插入指令
     * @param inst
     */
    void addInstBeforeBr(LIRInstruction *inst) {
        auto it = _instList.begin();
        for (; it != _instList.end(); ++it) {
            if ((*it)->getInstType() == LIRInstruction::LBranchTy && !dynamic_cast<LIRBranchInstruction *>(*it)->isCall()) {
                break;
            }
        }
        inst->setParent(this);
        _instList.insert(it, inst);
    }

    std::list<LIRInstruction *>::iterator removeInst(const std::list<LIRInstruction *>::iterator it) {
        (*it)->setParent(nullptr);
        return _instList.erase(it);
    }

    std::list<LIRInstruction *>::iterator insertInst(const std::list<LIRInstruction *>::iterator it, LIRInstruction *target) {
        target->setParent(this);
        return _instList.insert(it, target);
    }

    void removeInst(LIRInstruction *inst) {
        inst->setParent(nullptr);
        _instList.remove(inst);
    }

    std::string print() const final;

    std::string getLabelName() const final;

    std::list<LIRInstruction *> &getInstructions() { return _instList; }
    std::list<LIRInstruction *> getInstructions() const { return _instList; }
    std::list<LIRInstruction *>::iterator begin() { return _instList.begin(); }
    std::list<LIRInstruction *>::iterator end() { return _instList.end(); }
    std::list<LIRInstruction *>::const_iterator begin() const { return _instList.cbegin(); }
    std::list<LIRInstruction *>::const_iterator end() const { return _instList.cend(); }
    std::set<LIRBasicBlock *> getSuccessorBB() const { return _successor; }
    std::set<LIRBasicBlock *> getPredecessorBB() const { return _predecessor; }
    int getLoopIndex() const { return loopIdx; }
    int getLoopDepth() const { return loopDepth; }
    void setLoopIndex(int idx) { loopIdx = idx; }
    void setLoopDepth(int depth) { loopDepth = depth; }
    std::set<LIROperand *> &getLiveGen() { return _liveGen; }
    std::set<LIROperand *> &getLiveKill() { return _liveKill; }
    std::set<LIROperand *> &getLiveIn() { return _liveIn; }
    std::set<LIROperand *> &getLiveOut() { return _liveOut; }
    void addSuccessor(LIRBasicBlock *bb) { _successor.insert(bb); }
    void addPredecessor(LIRBasicBlock *bb) { _predecessor.insert(bb); }
    int getBlockID() const { return blockId; }
    void assignBlockID(int id) { blockId = id; }
    void setIncomingForwardBranches(int num) { incomingForwardBranches = num; }
    void decreaseForwardBranches() { incomingForwardBranches -= 1; }
    bool isForwardBranchesEQZero() const { return incomingForwardBranches == 0; }
};



class LIRFunction : public LIRLabel {
private:
    std::list<LIRBasicBlock *> _basicBlocks;
    LIRBasicBlock *_initBlock = nullptr;
    LIRBasicBlock *_exitBlock = nullptr;
    std::map<void *, int> _stack;
    int _stackPointer = 0;
    int _numArguments;
    bool _hasResult;
    std::map<int ,int>load_num;
    explicit LIRFunction(std::string name, int numArg, bool hasResult) : LIRLabel(std::move(name), LFunctionTy), _numArguments(numArg), _hasResult(hasResult) {}
public:
    static LIRFunction *create(std::string name, int numArg, bool hasResult) { return new LIRFunction(std::move(name), numArg, hasResult); }
    bool hasResult() const { return _hasResult; }
    int getNumArgs() const { return _numArguments; }
    void addBasicBlock(LIRBasicBlock *bb) {
        _basicBlocks.push_back(bb);
        bb->setParent(this);
    }

    void setInitBlock(LIRBasicBlock *bb) { _initBlock = bb; }
    void setExitBlock(LIRBasicBlock *bb) { _exitBlock = bb; }
    LIRBasicBlock *getInitBlock() const { return _initBlock; }
    LIRBasicBlock *getExitBlock() const { return _exitBlock; }
    std::list<LIRBasicBlock *> &getBasicBlocks() { return _basicBlocks; }
    std::list<LIRBasicBlock *> getBasicBlocks() const { return _basicBlocks; }
    std::list<LIRBasicBlock *>::iterator begin() { return _basicBlocks.begin(); }
    std::list<LIRBasicBlock *>::iterator end() { return _basicBlocks.end(); }
    std::list<LIRBasicBlock *>::iterator insert(std::list<LIRBasicBlock *>::iterator it, LIRBasicBlock *target) { target->setParent(this); return _basicBlocks.insert(it, target); }
    std::list<LIRBasicBlock *>::const_iterator begin() const { return _basicBlocks.cbegin(); }
    std::list<LIRBasicBlock *>::const_iterator end() const { return _basicBlocks.cend(); }

    std::string print() const final;
    std::string getLabelName() const final;

    int allocStack(void *ptr, int size) {
        if (_stack.find(ptr) == _stack.end()) {
            _stack[ptr] = _stackPointer;
            _stackPointer += size * 4;
        }
        return _stack.at(ptr);
    }

    int getStackSize() const { return _stackPointer; }
};


class LIRGlobalVariable : public LIRLabel {
private:
    int _num_elem;
    std::vector<int> _initial;
    LIRGlobalVariable(std::string name, Type *ty, Constant *init = nullptr, const std::vector<int> &flat={});
public:
    static LIRGlobalVariable *create(std::string name, Type *ty, Constant *init = nullptr, const std::vector<int> &flat={}) {
        return new LIRGlobalVariable(name, ty, init, flat);
    }
    std::string getLabelName() const final { return getName() + ".glo"; }
    int getNumElem() const { return _num_elem; }
    const std::vector<int> &getInitialValue() const { return _initial; }
    std::string print() const final;
};


class ConstantPool : public LIRLabel {
private:
    inline static int pool_id = 0;
    std::map<void *, int> _posMap;
    std::vector<void *> _literalList;
    std::set<LIRConstantOperand *> cSet;
    std::set<LIRLabel *> lSet;
    int topPos = 0;
    int curPoolID;
    ConstantPool(): LIRLabel(std::to_string(pool_id), LConstantPoolTy), curPoolID(pool_id++) {}

public:
    static ConstantPool *create() { return new ConstantPool(); }
    std::string print() const final;
    std::string getLabelName() const final;
    int getPoolOffset(LIRConstantOperand * c);
    int getPoolOffset(LIRLabel *l);
    bool empty() const { return _literalList.empty(); }
};
#endif //BAZINGA_COMPILER_LIRBASICBLOCK_H
