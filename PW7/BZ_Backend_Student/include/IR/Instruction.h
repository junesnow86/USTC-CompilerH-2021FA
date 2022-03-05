#ifndef BAZINGA_COMPILER_INSTRUCTION_H
#define BAZINGA_COMPILER_INSTRUCTION_H

#include "User.h"
#include "Type.h"
#include "cassert"
#include "BasicBlock.h"
#include <map>

class BasicBlock;
class Function;

class Instruction : public User
{
public:
    enum OpID
    {
        ret,
        br,
        add,
        sub,
        mul,
        sdiv,
        mod,
        alloca,
        load,
        store,
        cmp,
        phi,
        call,
        getelementptr,
        zext,
    };
    Instruction(Type *ty, OpID id, unsigned num_ops,
                BasicBlock *parent);
    Instruction(Type *ty, OpID id, unsigned num_ops);
    inline const BasicBlock *get_parent() const { return parent_; }
    inline BasicBlock *get_parent() { return parent_; }
    void set_parent(BasicBlock *parent) { this->parent_ = parent; }
    // Return the function this instruction belongs to.
    Function *get_function();
    Module *get_module();

private:
    Instruction *_prev_inst = nullptr;
    Instruction *_next_inst = nullptr;
public:
    Instruction *getPrevInst() const { return _prev_inst; }
    Instruction *getSuccInst() const { return _next_inst; }
    void setPrevInst(Instruction *inst) { _prev_inst = inst; }
    void setSuccInst(Instruction *inst) { _next_inst = inst; }

    virtual Instruction* deepcopy(BasicBlock* parent) = 0;
    virtual void transplant(std::map<Value*, Value*> ptMap){
        auto it = use_list_.begin();
        auto ite = use_list_.end();
        while (it != ite)
        {
            auto u = *it;
            if(ptMap.find(u.val_) != ptMap.end()){
                *it = Use(ptMap[u.val_], u.arg_no_);
            }
            it++;
        }
        auto it1 = operands_.begin();
        auto ite1 = operands_.end();
        while(it1 != ite1){
            auto o =  *it1;
            if(ptMap.find(o) != ptMap.end()){
                *it1 = ptMap[o];
            }
            it1++;
        }

    };

    OpID get_instr_type() { return op_id_; }
    std::string get_instr_op_name() {
        switch (op_id_)
        {
            case ret: return "ret"; break;
            case br: return "br"; break;
            case add: return "add"; break;
            case sub: return "sub"; break;
            case mul: return "mul"; break;
            case sdiv: return "sdiv"; break;
            case alloca: return "alloca"; break;
            case load: return "load"; break;
            case store: return "store"; break;
            case cmp: return "cmp"; break;
            case phi: return "phi"; break;
            case call: return "call"; break;
            case getelementptr: return "getelementptr"; break;
            case zext: return "zext"; break;

        default: return ""; break;
        }
    }



    bool is_void() { return ((op_id_ == ret) || (op_id_ == br) || (op_id_ == store) || (op_id_ == call && this->get_type()->is_void_type())); }

    bool is_phi() { return op_id_ == phi; }
    bool is_store() { return op_id_ == store; }
    bool is_alloca() { return op_id_ == alloca; }
    bool is_ret() { return op_id_ == ret; }
    bool is_load() { return op_id_ == load; }
    bool is_br() { return op_id_ == br; }

    bool is_add() { return op_id_ == add; }
    bool is_sub() { return op_id_ == sub; }
    bool is_mul() { return op_id_ == mul; }
    bool is_div() { return op_id_ == sdiv; }
    bool is_rem() { return op_id_ == mod; }


    bool is_cmp() { return op_id_ == cmp; }

    bool is_call() { return op_id_ == call; }
    bool is_gep() { return op_id_ == getelementptr; }
    bool is_zext() { return op_id_ == zext; }


    bool isBinary()
    {
        return (is_add() || is_sub() || is_mul() || is_div()) &&
               (get_num_operand() == 2);
    }

    virtual bool isStaticCalculable();


    virtual int calculate()  { return 0; }

    bool isTerminator() { return is_br() || is_ret(); }

protected:
    BasicBlock *parent_;
    OpID op_id_;
    unsigned num_ops_;
};

class BinaryInst : public Instruction
{
private:
    BinaryInst(Type *ty, OpID id, Value *v1, Value *v2,
               BasicBlock *bb);
    BinaryInst(Type *ty, OpID id, BasicBlock *bb): Instruction(ty, id, 2, bb){};

public:
    static BinaryInst *create_add(Value *v1, Value *v2, BasicBlock *bb, Module *m);
    static BinaryInst *create_sub(Value *v1, Value *v2, BasicBlock *bb, Module *m);
    static BinaryInst *create_mul(Value *v1, Value *v2, BasicBlock *bb, Module *m);
    static BinaryInst *create_sdiv(Value *v1, Value *v2, BasicBlock *bb, Module *m);
    static BinaryInst *create_mod(Value *v1, Value *v2, BasicBlock *bb, Module *m);
    static BinaryInst *create_s_bin(Value *v1, Value *v2, OpID op, BasicBlock *bb, Module *m){
        return new BinaryInst(Type::get_int32_type(m), op, v1, v2, bb);
    };

    virtual BinaryInst* deepcopy(BasicBlock* parent) override{
        BinaryInst* newInst = new BinaryInst(type_, op_id_, parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };

    virtual std::string print() override;

    int calculate() final;

    bool isStaticCalculable() final;

private:
    void assertValid();
};

class CmpInst : public Instruction
{
public:
    enum CmpOp
    {
        EQ, // ==
        NE, // !=
        GT, // >
        GE, // >=
        LT, // <
        LE  // <=
    };

private:
    CmpInst(Type *ty, CmpOp op, Value *lhs, Value *rhs,
            BasicBlock *bb);
    CmpInst(Type *ty, CmpOp op, BasicBlock* bb): Instruction(ty, Instruction::cmp, 2, bb), cmp_op_(op){};

public:
    static CmpInst *create_cmp(CmpOp op, Value *lhs, Value *rhs,
                               BasicBlock *bb, Module *m);

    CmpOp get_cmp_op() { return cmp_op_; }

    void setCmpOp(CmpOp op) { cmp_op_ = op; }

    void inverseCmpOp() {
        switch (get_cmp_op()) {
            case EQ:
                setCmpOp(NE);
                break;
            case NE:
                setCmpOp(EQ);
                break;
            case GT:
                setCmpOp(LE);
                break;
            case GE:
                setCmpOp(LT);
                break;
            case LT:
                setCmpOp(GE);
                break;
            case LE:
                setCmpOp(LT);
                break;
        }
    }

    bool isStaticCalculable() final;

    int calculate() final;

    virtual CmpInst* deepcopy(BasicBlock* parent) override{
        CmpInst* newInst = new CmpInst(type_, cmp_op_, parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };

    virtual std::string print() override;

private:
    CmpOp cmp_op_;

    void assertValid();
};

class CallInst : public Instruction
{
protected:
    CallInst(Function *func, std::vector<Value *> args, BasicBlock *bb);

    CallInst(Type* typ, size_t sz, BasicBlock *bb): Instruction(typ, Instruction::call, sz, bb){};

public:
    static CallInst *create(Function *func, std::vector<Value *> args, BasicBlock *bb);
    FunctionType *get_function_type() const;

    virtual std::string print() override;

    virtual CallInst* deepcopy(BasicBlock* parent) override{
        CallInst* newInst = new CallInst(type_, operands_.size(), parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };

    virtual void transplant(std::map<Value*, Value*> ptMap) override{
        auto it = use_list_.begin();
        auto ite = use_list_.end();
        while (it != ite)
        {
            auto u = *it;
            if(ptMap.find(u.val_) != ptMap.end()){
                *it = Use(ptMap[u.val_], u.arg_no_);
            }
        }
        auto it1 = operands_.begin();
        auto ite1 = operands_.end();
        it1++;
        while(it1 != ite1){
            auto o =  *it1;
            if(ptMap.find(o) != ptMap.end()){
                *it1 = ptMap[o];
            }
        }

    };
};

class BranchInst : public Instruction
{
private:
    BranchInst(Value *cond, BasicBlock *if_true, BasicBlock *if_false,
               BasicBlock *bb);
    BranchInst(BasicBlock *if_true, BasicBlock *bb);
    BranchInst(int op_num, BasicBlock *bb);

public:
    static BranchInst *create_cond_br(Value *cond, BasicBlock *if_true, BasicBlock *if_false,
                                      BasicBlock *bb);
    static BranchInst *create_br(BasicBlock *if_true, BasicBlock *bb);

    bool is_cond_br() const;

    Value *get_condition() const {
        assert(is_cond_br() && "Only condition branch have a condition");
        return get_operand(0);
    }

    BasicBlock *getTrueBB() const;
    BasicBlock *getFalseBB() const;

    virtual std::string print() override;

    virtual BranchInst* deepcopy(BasicBlock* parent) override{
        BranchInst* newInst = new BranchInst(num_ops_, parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };
};

class ReturnInst : public Instruction
{
private:
    ReturnInst(Value *val, BasicBlock *bb);
    ReturnInst(BasicBlock *bb);
    ReturnInst(BasicBlock *bb, size_t num_op);

public:
    static ReturnInst *create_ret(Value *val, BasicBlock *bb);
    static ReturnInst *create_void_ret(BasicBlock *bb);
    bool is_void_ret() const;

    virtual std::string print() override;

    virtual ReturnInst* deepcopy(BasicBlock* parent) override{
        ReturnInst* newInst = new ReturnInst(parent, num_ops_);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };
};

class GetElementPtrInst : public Instruction
{
private:
    GetElementPtrInst(Value *ptr, std::vector<Value *> idxs, BasicBlock *bb);
    GetElementPtrInst(Type* ty, size_t op_num, BasicBlock* bb): Instruction(ty, Instruction::getelementptr, op_num, bb), element_ty_(ty){};


public:
    static Type *get_element_type(Value *ptr, std::vector<Value *> idxs);
    static GetElementPtrInst *create_gep(Value *ptr, std::vector<Value *> idxs, BasicBlock *bb);
    Type *get_element_type() const;

    virtual std::string print() override;

    virtual GetElementPtrInst* deepcopy(BasicBlock* parent) override{
        GetElementPtrInst* newInst = new GetElementPtrInst(element_ty_, num_ops_, parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };

private:
    Type *element_ty_;
};

class StoreInst : public Instruction
{
private:
    StoreInst(Value *val, Value *ptr, BasicBlock *bb);
    StoreInst(BasicBlock *bb);

public:
    static StoreInst *create_store(Value *val, Value *ptr, BasicBlock *bb);

    Value *get_rval() { return this->get_operand(0); }
    Value *get_lval() { return this->get_operand(1); }

    virtual std::string print() override;

    virtual StoreInst* deepcopy(BasicBlock* parent) override{
        StoreInst* newInst = new StoreInst(parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };
};

class LoadInst : public Instruction
{
private:
    LoadInst(Type *ty, Value *ptr, BasicBlock *bb);
    LoadInst(Type *ty, BasicBlock *bb): Instruction(ty, Instruction::load, 1, bb){};
public:
    static LoadInst *create_load(Type *ty, Value *ptr, BasicBlock *bb);
    Value *get_lval() { return this->get_operand(0); }

    Type *get_load_type() const;

    virtual std::string print() override;

    virtual LoadInst* deepcopy(BasicBlock* parent) override{
        LoadInst* newInst = new LoadInst(type_, parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };
};


class AllocaInst : public Instruction
{
private:
    AllocaInst(Type *ty, BasicBlock *bb);

public:
    static AllocaInst *create_alloca(Type *ty, BasicBlock *bb);

    Type *get_alloca_type() const;

    virtual std::string print() override;

    virtual AllocaInst* deepcopy(BasicBlock* parent) override{
        AllocaInst* newInst = new AllocaInst(alloca_ty_, parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        return newInst;
    };
    void set_init() {init=true;}
    bool get_init() {return init;}

private:
    Type *alloca_ty_;
    bool init;
};

class ZextInst : public Instruction
{
private:
    ZextInst(OpID op, Value *val, Type *ty, BasicBlock *bb);
    ZextInst(Type* ty, BasicBlock* bb): Instruction(ty, Instruction::zext, 1, bb), dest_ty_(ty){};

public:
    static ZextInst *create_zext(Value *val, Type *ty, BasicBlock *bb);

    Type *get_dest_type() const;

    virtual std::string print() override;

    virtual ZextInst* deepcopy(BasicBlock* parent) override{
        ZextInst* newInst = new ZextInst(type_, parent);
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };

private:
    Type *dest_ty_;
};

class PhiInst : public Instruction
{
private:
    PhiInst(OpID op, std::vector<Value *> vals, std::vector<BasicBlock *> val_bbs, Type *ty, BasicBlock *bb);
    PhiInst(Type *ty, unsigned num_ops, BasicBlock *bb)
        : Instruction(ty, Instruction::phi, num_ops, bb) {}
    Value *l_val_;

public:
    static PhiInst *create_phi(Type *ty, BasicBlock *bb);
    std::list<std::pair<Value *, BasicBlock *>> getValueBBPair();
    Value *get_lval() { return l_val_; }
    void set_lval(Value *l_val) { l_val_ = l_val; }
    void add_phi_pair_operand(Value *val, Value *pre_bb)
    {
        this->add_operand(val);
        this->add_operand(pre_bb);
    }
    void remove_source(BasicBlock *bb) {
        for (int i = 1; i < get_num_operand(); i+=2) {
            if ((Value *)bb == get_operand(i)) {
                remove_operands(i - 1, i);
            }
        }
    }
    virtual std::string print() override;

    virtual PhiInst* deepcopy(BasicBlock* parent) override{
        PhiInst* newInst = new PhiInst(type_, num_ops_, parent);
        newInst->l_val_ = l_val_;
        newInst->use_list_.clear();
        for(auto u: use_list_){
            newInst->use_list_.push_back(u);
        }
        newInst->operands_.clear();
        for(auto o: operands_){
            newInst->operands_.push_back(o);
        }
        return newInst;
    };

    virtual void transplant(std::map<Value*, Value*> ptMap) override{
        auto it = use_list_.begin();
        auto ite = use_list_.end();
        while (it != ite)
        {
            auto u = *it;
            if(ptMap.find(u.val_) != ptMap.end()){
                *it = Use(ptMap[u.val_], u.arg_no_);
            }
        }
        auto it1 = operands_.begin();
        auto ite1 = operands_.end();
        while(it1 != ite1){
            auto o =  *it1;
            if(ptMap.find(o) != ptMap.end()){
                *it1 = ptMap[o];
            }
        }
        if(ptMap.find(l_val_) != ptMap.end())
            l_val_ = ptMap[l_val_];
    };
};


#endif
