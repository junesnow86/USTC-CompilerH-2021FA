#ifndef BAZINGA_COMPILER_SCPCOMBINEDCE_H
#define BAZINGA_COMPILER_SCPCOMBINEDCE_H

#include <map>
#include <queue>
#include "pass_manager.h"
#include "IR/Instruction.h"

/**
 * 常量传播 lattice
 */
class ValueLattice {
public:
    enum ValueConstantTy {
        TopTy,
        DownTy,
        ConstantTy,
        ZeroTy,
        EmptyTy         // 无返回值的语句 Value使用Empty标记，实际不参与计算
    };
private:
    ValueConstantTy _ty;
    int _value{};



public:
    /**
     * 初始化时，将所有变量置为 T 类型
     */
    ValueLattice() {
        _ty = TopTy;
    }

    explicit ValueLattice(ValueConstantTy ty, int val = 0) : _ty((ty == ConstantTy && val == 0) ? ZeroTy : ty),
                                                             _value(val) {}

    explicit ValueLattice(int val) : _ty(val == 0 ? ZeroTy : ConstantTy), _value(val) {}

    void setValue(int val) { _value = val; }

    int getValue() const {
        assert(_ty == ConstantTy || _ty == ZeroTy && "Only constant or zero type can use getValue method");
        return _value;
    }

    inline ValueConstantTy getType() const { return _ty; }

    bool isTopType() const { return getType() == TopTy; }

    bool isDownType() const { return getType() == DownTy; }

    bool isConstantType() const { return getType() == ConstantTy; }

    bool isZeroType() const { return getType() == ZeroTy; }

    bool isEmptyType() const { return getType() == EmptyTy; }

    bool isConstantOrZeroType() const { return getType() == ConstantTy || getType() == ZeroTy; }

    /**
     * Implement for phi node calculation
     * In the lattice calculation this means $$\cap L_c \times L_c \to L_c$$
     * @param lhs
     * @param rhs
     * @return
     */
    static ValueLattice meet(const ValueLattice &lhs, const ValueLattice &rhs) {
        assert(!lhs.isEmptyType() && !rhs.isEmptyType() && "Empty type is not calculable");
        if (lhs.isTopType() && rhs.isTopType()) {
            return ValueLattice(TopTy);
        }
        if (lhs.isDownType() || rhs.isDownType()) {
            return ValueLattice(DownTy);
        }
        if (lhs.isTopType()) {
            return ValueLattice(ConstantTy, rhs.getValue());
        }
        if (rhs.isTopType()) {
            return ValueLattice(ConstantTy, lhs.getValue());
        } else {
            if (lhs.getValue() == rhs.getValue()) {
                return ValueLattice(ConstantTy, lhs.getValue());
            } else {
                return ValueLattice(DownTy);
            }
        }
    }

    /**
     * Implement for binary instruction calculation
     * @param lhs
     * @param rhs
     * @param fp: the function to calculate $c_0 op c_1$
     * Note that in this implement we need to promise this function don't throw a exception such as Overflow / ZeroDivision
     * Just return zero when an exception happened as the inputs are promised to have no Undefined Behaviour
     * @param considerZero: Set true ti consider zero in calculation. Such as the $\times$ operand
     * @return
     */
    static ValueLattice operand(const ValueLattice &lhs, const ValueLattice &rhs,
                                int (*fp)(int lhs, int rhs),
                                bool considerZero) {
        assert(!lhs.isEmptyType() && !rhs.isEmptyType() && "Empty type is not calculable");
        if (lhs.isTopType() || rhs.isTopType()) {
            return ValueLattice(TopTy);
        }
        if (considerZero) {
            if (lhs.isZeroType() || rhs.isZeroType()) {
                return ValueLattice(ZeroTy, 0);
            }
            if (lhs.isDownType() || rhs.isDownType()) {
                return ValueLattice(DownTy);
            }
            return ValueLattice(ConstantTy, fp(lhs.getValue(), rhs.getValue()));
        } else {
            if (lhs.isDownType() || rhs.isDownType()) {
                return ValueLattice(DownTy);
            }
            return ValueLattice(ConstantTy, fp(lhs.getValue(), rhs.getValue()));
        }
    }

    friend bool operator== (const ValueLattice &lhs, const ValueLattice &rhs) {
        if (lhs.getType() != rhs.getType()) return false;
        if (lhs.isConstantOrZeroType()) {
            return lhs.getValue() == rhs.getValue();
        }
        return true;
    }

    friend bool operator!= (const ValueLattice &lhs, const ValueLattice &rhs) {
        return operator==(lhs, rhs);
    }
};


/**
 * 死代码删除 lattice
 */
class InstLattice {
public:
    friend class ValueLattice;
    enum InstReachableType {
        UnreachableTy,
        ReachableTy,
        EmptyTy
    };

    explicit InstLattice(InstReachableType ty = EmptyTy) : _ty(ty) {}

    InstReachableType getType() const { return _ty; }
    bool isReachable() const { return getType() == ReachableTy; }
    bool isUnreachable() const { return getType() == UnreachableTy; }
    bool isEmpty() const { return getType() == EmptyTy; }

    /**
     * Implement of operator [<=]
     * @param lhs
     * @param rhs
     * @return
     */
    static InstLattice testing(const ValueLattice &lhs, bool rhs) {
        assert(!lhs.isEmptyType() && "Empty type is not calculable");
        if (lhs.isTopType()) return InstLattice(UnreachableTy);
        if (lhs.isDownType()) return InstLattice(ReachableTy);
        if (lhs.getValue() != 0) {
            if (rhs) return InstLattice(ReachableTy);
            else return InstLattice(UnreachableTy);
        } else {
            if (rhs) return InstLattice(UnreachableTy);
            else return InstLattice(ReachableTy);
        }
    }

    /**
     * Implement of operator [=>]
     * @param lhs
     * @param rhs
     * @return
     */
    static ValueLattice unreached(const InstLattice &lhs, const ValueLattice &rhs) {
        assert(!rhs.isEmptyType() && "Empty type is not calculable");
        if (lhs.isUnreachable()) return ValueLattice(ValueLattice::TopTy);
        return rhs;
    }

    friend InstLattice operator* (const InstLattice &lhs, const InstLattice &rhs) {
        if (lhs.isUnreachable() || rhs.isUnreachable()) {
            return InstLattice(UnreachableTy);
        } else {
            return InstLattice(ReachableTy);
        }
    }

    friend InstLattice operator+ (const InstLattice &lhs, const InstLattice &rhs) {
        if (lhs.isEmpty()) return rhs;
        if (rhs.isEmpty()) return lhs;
        if (lhs.isReachable() || rhs.isReachable()) {
            return InstLattice(ReachableTy);
        } else {
            return InstLattice(UnreachableTy);
        }
    }

    friend bool operator== (const InstLattice &lhs, const InstLattice &rhs) {
        return lhs._ty == rhs._ty;
    }

private:
    InstReachableType _ty;
};


typedef struct Lattice {
public:
    ValueLattice val;
    InstLattice inst;

    friend bool operator== (const Lattice &lhs, const Lattice &rhs) {
        return lhs.val == rhs.val && lhs.inst == rhs.inst;
    }

    friend bool operator!= (const Lattice &lhs, const Lattice &rhs) {
        return !(lhs == rhs);
    }

    explicit Lattice(const InstLattice &l) : inst(l), val(ValueLattice(ValueLattice::EmptyTy)) {}

    explicit Lattice(const ValueLattice &v) : inst(InstLattice(InstLattice::UnreachableTy)), val(v) {}

    Lattice(const ValueLattice &v, const InstLattice &l) : inst(l), val(v) {}

    Lattice() : inst(InstLattice(InstLattice::UnreachableTy)), val(ValueLattice(ValueLattice::EmptyTy)) {}
} Lattice;

struct ConditionLink {
    enum CondTy {
        NoCond,
        TrueCond,
        FalseCond
    };

    CondTy type;
    Instruction *from;
    Value *condition;

    ConditionLink(Instruction* i, Value *v, CondTy ty) : from(i), type(ty), condition(v) {}
    explicit ConditionLink(Instruction* i) : from(i), type(NoCond), condition(nullptr) {}
};

class ConstFoldingDCEliminating : public Pass {
private:

    std::map<Value *, Lattice> _map;
    std::queue<Instruction *> _worklist;
    std::map<Value *, std::vector<ConditionLink>> _linking;
    void addLink(Value *v, const ConditionLink &link) {
        _linking[v].push_back(link);
    }
    std::vector<ConditionLink> getLink(Value *v) {return _linking[v]; }
    void clearLink() { _linking.clear(); }
    bool existInMap(Value *v) { return _map.find(v) != _map.end(); }
    /**
     * 由值获取Lattice\n
     * 注意：不会检查值是否在map中存在，若不存在返回不可预测
     * @param v
     * @return
     */
    Lattice getLatticeByValue(Value *v) {
        if (existInMap(v)) {
            auto ret = _map[v];
            return ret;
        } else {
            auto const_int = dynamic_cast<ConstantInt *>(v);
            if (const_int != nullptr) {
                return Lattice(ValueLattice(const_int->get_value()));
            }
            return {};
        }
    }
    void setLattice(Value *v, const Lattice &l) {
        _map[v] = l;
    }

    void clearLattice() {
        _map.clear();
    }
    void pushWorkList(Instruction *v) {
        if (v == nullptr) return;
        _worklist.push(v);
    }
    Instruction *popWorkList() {
        if(_worklist.empty()) {
            return nullptr;
        }
        else {
            Instruction *ret = _worklist.front();
            _worklist.pop();
            return ret;
        }
    }

    void clearWorkList() {
        std::queue<Instruction *> empty;
        std::swap(empty, _worklist);
    }
public:
    explicit ConstFoldingDCEliminating(Module *m) : Pass(m) {}
    void run() final;
};

#endif //BAZINGA_COMPILER_SCPCOMBINEDCE_H
