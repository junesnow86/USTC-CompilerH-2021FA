#ifndef BAZINGA_COMPILER_LIRBUILDER_H
#define BAZINGA_COMPILER_LIRBUILDER_H

#include <map>
#include <vector>
#include <cassert>
#include <list>
#include <set>
#include <cmath>

#define NUM_REG 11
#define LITERAL_POOL_LINE 1000

class Value;
class Argument;
class Module;
class BasicBlock;
class Function;
class Instruction;
class AllocaInst;
class GlobalVariable;
class LIRInstruction;
class LIROperand;
class LIRFunction;
class LIRBasicBlock;
class LIRAlloca;
class LIRGlobalVariable;

class CFG;
class LoopSearch;
class dominator;

class LIRBuilder {
private:
    std::map<Instruction *, LIROperand *> _regMap;
    std::map<BasicBlock *, LIRBasicBlock *> _bbMap;
    std::map<Function *, LIRFunction *> _funcMap;
    std::map<AllocaInst *, LIRAlloca *> _allocaMap;
    std::map<Argument *, LIROperand *> _argMap;
    std::map<GlobalVariable *, LIRGlobalVariable *> _gvMap;
    std::map<Value *, std::set<Value *>> _phiCongruenceClass;
    std::map<Value *, std::set<Value *>> _unresolvedNeighborMap;
    std::map<Function *, std::vector<BasicBlock *>> _blockOrder;
    std::list<LIRFunction *> _funcList;

    std::vector<BasicBlock *> computeBasicBlockOrder(Function *f, CFG *cfg, LoopSearch *lp, dominator *dom) const;
    void setFunctionMap(Function *ori, LIRFunction *mp) { _funcMap[ori] = mp; }
    void setBlockMap(BasicBlock *ori, LIRBasicBlock *mp) { _bbMap[ori] = mp; }
    void setRegister(Instruction *ori, LIROperand *opr) { _regMap[ori] = opr; }
    void setArgument(Argument *arg, LIROperand *opr) { _argMap[arg] = opr; }
    void setAlloca(AllocaInst *ori, LIRAlloca *al) { _allocaMap[ori] = al; }
    void setGlobalVariable(GlobalVariable *ori, LIRGlobalVariable *gv) { _gvMap[ori] = gv; }
    bool existInRegMap(Instruction *i) const { return (_regMap.find(i) != _regMap.end()); }
    LIRFunction *getLFunction(Function *ori) {
        assert(_funcMap.find(ori) != _funcMap.end() && "Can't get function mapping");
        return _funcMap.at(ori);
    }
    LIRBasicBlock *getLBB(BasicBlock *bb) {
        assert(_bbMap.find(bb) != _bbMap.end() && "Can't get basic block mapping");
        return _bbMap.at(bb);
    }
    LIROperand *getReg(Instruction *i) {
        assert(_regMap.find(i) != _regMap.end() && "Can't get register mapping");
        return _regMap.at(i);
    }
    LIROperand *getArg(Argument *arg) {
        assert(_argMap.find(arg) != _argMap.end() && "Can't get argument mapping");
        return _argMap.at(arg);
    }
    LIRAlloca *getAlloca(AllocaInst *i) {
        assert(_allocaMap.find(i) != _allocaMap.end() && "Can't get alloca mapping");
        return _allocaMap.at(i);
    }
    LIRGlobalVariable *getGlobalVar(GlobalVariable *gv) {
        assert(_gvMap.find(gv) != _gvMap.end() && "Can't get global variable mapping");
        return _gvMap.at(gv);
    }
    LIROperand *getRegOrConstant(Value *v);

    void addInstruction(LIRInstruction *inst);
    void addBasicBlock(LIRBasicBlock *bb);
    void addFunction(LIRFunction *f);
    LIRBasicBlock *getExitBlock();

    Module *_m;
    LIRFunction *_currentFunc = nullptr;
    LIRBasicBlock *_currentBB = nullptr;

    void setCurrentBasicBlock(LIRBasicBlock *bb) { _currentBB = bb; }
    void setCurrentFunction(LIRFunction *ff) { _currentFunc = ff; }
    void buildInstr(Instruction *i);
public:
    explicit LIRBuilder(Module *m) : _m(m) {}
    void build();
    std::list<LIRFunction *> &getFunctionList() { return _funcList; }
    std::string print();
};

#endif //BAZINGA_COMPILER_LIRBUILDER_H
