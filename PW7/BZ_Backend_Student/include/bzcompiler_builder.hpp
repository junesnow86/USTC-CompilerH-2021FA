#ifndef _CMINUSF_BUILDER_HPP_
#define _CMINUSF_BUILDER_HPP_

#include <iostream>
#include "IR/BasicBlock.h"
#include "IR/Constant.h"
#include "IR/Function.h"
#include "IR/IRbuilder.h"
#include "IR/Module.h"
#include "IR/Type.h"
#include "ast.h"
#include <map>
#include <utility>


class Scope {
public:
    struct ValType {
        bool isConst;
        bool isArray;
        std::vector<int> dim;
        std::vector<int> init_values;
        std::vector<int> dim_offset;
        Value *val;

        ValType(bool i_const, const std::vector<int> &i_dim, std::vector<int> i_init, Value *i_value) :
                isConst(i_const), isArray(!i_dim.empty()), dim(i_dim), init_values(std::move(i_init)), val(i_value) {
            if (isArray) {
                dim_offset.resize(dim.size());
                dim_offset[dim.size() - 1] = 1;
                for (int i = dim.size() - 2; i >= 0; --i) {
                    dim_offset[i] = dim_offset[i + 1] * dim[i + 1];
                }
            }
        };
    };

private:


public:
    // enter a new scope
    void enter() {
        inner.emplace_back();
        array_param.emplace_back();
    }

    // exit a scope
    void exit() {
        inner.pop_back();
        array_param.pop_back();
    }

    bool in_global() {
        return inner.size() == 1;
    }

    // push a name to scope
    // return true if successful
    // return false if this name already exits
    bool pushVar(std::string name, Value *val, bool isConst = false, const std::vector<int> &dim = {},
              const std::vector<int> &initial_value = {}) {
        auto result = inner[inner.size() - 1].insert({name, new ValType(isConst, dim, initial_value, val)});
        return result.second;
    }

    bool pushFunction(std::string name, Value *val) {
        auto result = func.insert({name, val});
        return result.second;
    }

    bool push_params(std::string name, Value *val, std::vector<Value *> params) {
        auto result = array_param[array_param.size() - 1].insert({name, params});
        return result.second;
    }

    Value *find_params(std::string name, std::vector<Value *> &params) {
        for (auto s = array_param.rbegin(); s != array_param.rend(); s++) {
                auto iter = s->find(name);
            if (iter != s->end()) {
                params.assign(iter->second.begin(), iter->second.end());
                return iter->second[0];
            }
        }   
        return nullptr;
    }

    ValType *getRawType(std::string name) {
        for (auto s = inner.rbegin(); s != inner.rend(); s++) {
            auto iter = s->find(name);
            if (iter != s->end()) {
                return iter->second;
            }
        }
        return nullptr;
    }



    /**
     * 由常量数组或
     * @param name
     * @param dim
     * @return
     */
    int getValue(const std::string &name, const std::vector<int> &dim = {}) {
        ValType *val = getRawType(name);
        if (val == nullptr || !val->isConst) { ::exit(4); }
        assert(val != nullptr && "Can't find target variable in scope");
        assert(val->isConst && "Only const value can get variable");
        if (!(val->isArray ^ dim.empty())) {
            ::exit(5);
            assert(0 && "Variable Type mismatch params");
        }
        if (val->isArray) {
            int offset = 0;
            for (int i = 0; i < dim.size(); ++i) {
                offset += val->dim_offset[i] * dim[i];
            }
            return val->init_values[offset];
        } else {
            return val->init_values[0];
        }
    }

    Value *find_var(const std::string &name) {
        auto ret = getRawType(name);
        if (ret == nullptr) {
            return nullptr;
        }
        return ret->val;
    }

    Value *find_func(const std::string &name) {
        if (name == "putf") {
            ::exit(6);
        }
        assert(name != "putf" && "Use of un implement function 'putf'");
        if (func.find(name) == func.end()) {
            return nullptr;
        }
        return func.at(name);
    }

    Scope() {
        inner.emplace_back();
        array_param.emplace_back();
    }

private:
    std::vector<std::map<std::string, ValType *>> inner;
    std::map<std::string, Value*> func;
    std::vector<std::map<std::string, std::vector<Value *>>> array_param;
};


class BZBuilder : public ASTvisitor {
public:
    BZBuilder() {
        module = new Module("bz_code");
        builder = new IRBuilder(nullptr, module);
        auto TyVoid = Type::get_void_type(module);
        auto TyInt32 = Type::get_int32_type(module);
        auto TyInt32Ptr = Type::get_int32_ptr_type(module);
        // 添加运行库函数
        scope.pushFunction("getint", Function::create(FunctionType::get(TyInt32, {}), "getint", getModule()));
        scope.pushFunction("getch", Function::create(FunctionType::get(TyInt32, {}), "getch", getModule()));
        scope.pushFunction("getarray", Function::create(FunctionType::get(TyInt32, {TyInt32Ptr}), "getarray", getModule()));
        scope.pushFunction("memset", Function::create(FunctionType::get(TyVoid, {TyInt32Ptr, TyInt32, TyInt32}), "memset", getModule()));
        scope.pushFunction("putint", Function::create(FunctionType::get(TyVoid, {TyInt32}), "putint", getModule()));
        scope.pushFunction("putch", Function::create(FunctionType::get(TyVoid, {TyInt32}), "putch", getModule()));
        scope.pushFunction("putarray", Function::create(FunctionType::get(TyVoid, {TyInt32, TyInt32Ptr}), "putarray", getModule()));
        scope.pushFunction("starttime", Function::create(FunctionType::get(TyVoid, {}), "_sysy_starttime", getModule()));
        scope.pushFunction("stoptime", Function::create(FunctionType::get(TyVoid, {}), "_sysy_stoptime", getModule()));
        scope.pushFunction("putf", Function::create(FunctionType::get(TyVoid, {}), "putf", getModule()));
    }

    Module *getModule() {
        return module;
    }
private:
    void visit(ASTProgram &) final;
    void visit(ASTConstant &) final;
    void visit(ASTUnaryOp &) final;
    void visit(ASTMulOp &)  final;
    void visit(ASTAddOp &)  final;
    void visit(ASTRelOp &) final;
    void visit(ASTEqOp &)  final;
    void visit(ASTAndOp &) final;
    void visit(ASTOrOp &) final;
    void visit(ASTLVal &) final;
    void visit(ASTFuncCall &) final;
    void visit(ASTVarDecl &)  final;
    void visit(ASTAssignStmt &)  final;
    void visit(ASTExpressionStmt &)  final;
    void visit(ASTIfStmt &)  final;
    void visit(ASTWhileStmt &)  final;
    void visit(ASTBreakStmt &)  final;
    void visit(ASTContinueStmt &)  final;
    void visit(ASTParam &node) final;
    void visit(ASTFuncDecl &node) final;
    void visit(ASTReturnStmt &node) final;
    void visit(ASTBlock &node) final;

    IRBuilder *builder;
    Scope scope;
    Module *module;

    int compute_ast_constant(ASTInstruction *inst);

    std::tuple<int, int> ConstInitialValueWalker(ASTVarDecl::ASTArrayList *l, const std::vector<int> &dim, int depth,
                                                 std::vector<int> &init_values);

    std::tuple<int, int> InitialValueWalker(ASTVarDecl::ASTArrayList *l, const std::vector<int> &offset, int depth,
                                            std::vector<Value *> &init_values, Module *m);

    void InitialValueBuilder(const std::vector<int> &dim, const std::vector<Value *> &val, Instruction *gep, int &offset, int depth, int totalSize);


    std::vector<Constant *> int2constant(const std::vector<int> &ori);

    std::vector<Value *> int2value(const std::vector<int> &ori);
};

#endif
