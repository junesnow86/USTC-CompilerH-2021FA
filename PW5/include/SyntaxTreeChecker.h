#ifndef _C1_SYNTAX_TREE_CHECKER_H_
#define _C1_SYNTAX_TREE_CHECKER_H_

#include <cassert>
#include <map>

#include "ErrorReporter.h"
#include "SyntaxTree.h"

class SyntaxTreeChecker : public SyntaxTree::Visitor {
   public:
    SyntaxTreeChecker(ErrorReporter& e) : err(e) {}
    virtual void visit(SyntaxTree::Assembly& node) override;
    virtual void visit(SyntaxTree::FuncDef& node) override;
    virtual void visit(SyntaxTree::BinaryExpr& node) override;
    virtual void visit(SyntaxTree::UnaryExpr& node) override;
    virtual void visit(SyntaxTree::LVal& node) override;
    virtual void visit(SyntaxTree::Literal& node) override;
    virtual void visit(SyntaxTree::ReturnStmt& node) override;
    virtual void visit(SyntaxTree::VarDef& node) override;
    virtual void visit(SyntaxTree::AssignStmt& node) override;
    virtual void visit(SyntaxTree::FuncCallStmt& node) override;
    virtual void visit(SyntaxTree::BlockStmt& node) override;
    virtual void visit(SyntaxTree::EmptyStmt& node) override;
    virtual void visit(SyntaxTree::ExprStmt& node) override;
    virtual void visit(SyntaxTree::FuncParam& node) override;
    virtual void visit(SyntaxTree::FuncFParamList& node) override;
    virtual void visit(SyntaxTree::BinaryCondExpr& node) override;
    virtual void visit(SyntaxTree::UnaryCondExpr& node) override;
    virtual void visit(SyntaxTree::IfStmt& node) override;
    virtual void visit(SyntaxTree::WhileStmt& node) override;
    virtual void visit(SyntaxTree::BreakStmt& node) override;
    virtual void visit(SyntaxTree::ContinueStmt& node) override;
    virtual void visit(SyntaxTree::InitVal& node) override;

   private:
    ErrorReporter& err;
    bool Expr_int;
    SyntaxTree::Type Expr_type;
};

enum class ErrorType {
    Accepted = 0,
    Modulo,
    VarUnknown,
    VarDuplicated,
    FuncUnknown,
    FuncDuplicated,
    FuncParams
};

class SymbolTable;

struct attr {
    bool isVar;             // 该条目是否是一个变量
    bool isFunc;            // 该条目是否是一个函数
    SyntaxTree::Type type;  // 变量的数据类型或函数的返回值类型
    std::vector<SyntaxTree::Type> FParamList;
};

class SymbolTable {
   public:
    SymbolTable(int field) { _field = field; }
    bool isexist(std::string);
    struct attr lookup(std::string key);
    void addItem(std::string key, struct attr value);
    ~SymbolTable() {}

   private:
    int _field;  // 作用域标识
    std::map<std::string, attr> table;
};

#endif  // _C1_SYNTAX_TREE_CHECKER_H_