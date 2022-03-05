#ifndef BAZINGA_COMPILER_LIROPR_H
#define BAZINGA_COMPILER_LIROPR_H

#include <string>
#include <vector>
#include <cassert>
#include <map>

class LIRInstruction;

struct LIRUse {
    LIRInstruction *user;
    // idx>=0代表在OperandList内，idx=-1代表Result
    int idx;
    LIRUse(LIRInstruction *u, int id): user(u), idx(id) {}
};

class LIROperand {
public:
    enum LIROprTy {
        LOVirtualRegTy, // 虚拟寄存器
        LOPhysicRegTy,  // 物理寄存器
        LOConstantTy,   // 常量
    };
private:
    LIROprTy _ty;
    std::vector<LIRUse *> _use;
protected:
    explicit LIROperand(LIROprTy ty) : _ty(ty) {}

public:
    LIROprTy getOperandType() const { return _ty; }
    bool isVirtualRegTy() const { return _ty == LOVirtualRegTy; }
    bool isPhysicsRegTy() const { return _ty == LOPhysicRegTy; }
    bool isConstantTy() const { return _ty == LOConstantTy; }
    virtual std::string print() = 0;
    /**
     * These apis should be used iff it's a VirtualRegister Type
     * @return
     */
    virtual std::vector<LIRUse *> &getUseList() { return _use; }
    virtual void addUse(int idx, LIRInstruction *inst) {}
    virtual void removeUse(int idx, LIRInstruction *inst) {}
    virtual void replaceAllUseWith(LIROperand *opr) {}
    virtual void clearUse() {}
};

class LIRConstantOperand : public LIROperand {
private:
    int _value;
    inline static std::map<int, LIRConstantOperand *> _map;

protected:
    explicit LIRConstantOperand(int value): LIROperand(LOConstantTy) ,_value(value) {}

public:
    static LIRConstantOperand *create(int value) {
        if (_map.find(value) == _map.end()) {
            _map[value] = new LIRConstantOperand(value);
        }
        return _map.at(value);
    }

    int getValue() const { return _value; }

    std::string print() final { return "#" + std::to_string(getValue()); }
};


class LIRVirtualRegister : public LIROperand {
private:
    static int _totalRegId;
    int _rid;
    std::vector<LIRUse *> _useList;
    LIRVirtualRegister() : LIROperand(LOVirtualRegTy) {
        _rid = _totalRegId++;
        _vRegMap[_rid] = this;
    }
    inline static std::map<int, LIRVirtualRegister *> _vRegMap;
public:
    static LIRVirtualRegister *create() { return new LIRVirtualRegister(); }
    static LIRVirtualRegister *getVReg(int regNo) { return _vRegMap.at(regNo); }
    int getRegisterID() const { return _rid; }

    std::string print() final {
        return "v" + std::to_string(getRegisterID());
    }

    std::vector<LIRUse *> &getUseList() final { return _useList; }
    void addUse(int idx, LIRInstruction *inst) final {
        _useList.push_back(new LIRUse(inst, idx));
    }
    void removeUse(int idx, LIRInstruction *inst) final {
        auto it = _useList.begin();
        while (it != _useList.end()) {
            if ((*it)->user == inst && (*it)->idx == idx) {
                it = _useList.erase(it);
            } else {
                it++;
            }
        }
    }
    void replaceAllUseWith(LIROperand *opr) final;
    /**
     * 将引用该虚拟寄存器的指令中指令ID大于after的都替换为opr
     * @param opr
     * @param after
     */
    void replaceAllUseAfterID(LIROperand *opr, int after);
    void clearUse() final { _useList.clear(); }
};


class LIRPhysicsRegister : public LIROperand {
private:
    inline static std::map<int, LIRPhysicsRegister *> _map;
    const static std::map<int, std::string> _regNameMap;
    int _regId;
    explicit LIRPhysicsRegister(int regId) : LIROperand(LOPhysicRegTy), _regId(regId) {}
public:
    static LIRPhysicsRegister *create(int regId) {
        if (_map.find(regId) == _map.end()) {
            _map[regId] = new LIRPhysicsRegister(regId);
        }
        return _map.at(regId);
    }

    int getRegisterID() const { return _regId; }

    std::string print() final {
        return _regNameMap.at(getRegisterID());
    }
};


#endif //BAZINGA_COMPILER_LIROPR_H
