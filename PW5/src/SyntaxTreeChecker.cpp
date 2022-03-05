#include "SyntaxTreeChecker.h"

#include <iostream>
#include <string>
#include <vector>

using namespace SyntaxTree;

bool SymbolTable::isexist(std::string key) {
    if (table.find(key) == table.end())
        return false;
    else
        return true;
}

struct attr SymbolTable::lookup(std::string key) {
    return table[key];
}

void SymbolTable::addItem(std::string key, struct attr value) {
    table[key] = value;
}

std::vector<SymbolTable> TableVec;
int currentfield = 0;

void SyntaxTreeChecker::visit(Assembly &node) {
    SymbolTable newtbl(currentfield);
    TableVec.push_back(newtbl);
    for (auto def : node.global_defs) {
        def->accept(*this);
    }
}

void SyntaxTreeChecker::visit(FuncDef &node) {
    // FuncDef: ret_type, param_list, name, body
    if (TableVec[currentfield].isexist(node.name)) {
        err.error(node.loc, "Function duplicated.");
        exit(int(ErrorType::FuncDuplicated));
    }
    struct attr value;
    value.isVar = false;
    value.isFunc = true;
    value.type = node.ret_type;
    // 记录各个形参的类型，实参匹配检查时需要
    for (auto param : node.param_list->params) {
        value.FParamList.push_back(param->param_type);
    }
    TableVec[currentfield].addItem(node.name, value);

    node.param_list->accept(*this);  // 遍历函数形参列表来对其进行检查
    node.body->accept(*this);        // 遍历函数体来对其进行检查
}

void SyntaxTreeChecker::visit(BinaryExpr &node) {
    node.lhs->accept(*this);
    bool lhs_int = this->Expr_int;
    Type lhs_type = this->Expr_type;  // 左操作数类型
    node.rhs->accept(*this);
    bool rhs_int = this->Expr_int;
    Type rhs_type = this->Expr_type;  // 右操作数类型
    if (node.op == SyntaxTree::BinOp::MODULO) {
        if (!lhs_int || !rhs_int) {
            err.error(node.loc, "Operands of modulo should be integers.");
            exit(int(ErrorType::Modulo));
        }
    }
    this->Expr_int = lhs_int & rhs_int;
    // 判断该表达式类型
    if (lhs_type == Type::FLOAT || rhs_type == Type::FLOAT)
        this->Expr_type = Type::FLOAT;
    else
        this->Expr_type = Type::INT;
}

void SyntaxTreeChecker::visit(UnaryExpr &node) { node.rhs->accept(*this); }

void SyntaxTreeChecker::visit(LVal &node) {
    int save = currentfield;
    while (currentfield >= 0 && !TableVec[currentfield].isexist(node.name)) {
        currentfield--;
    }
    if (currentfield < 0) {
        currentfield = save;
        err.error(node.loc, "Variable unknown.");
        exit(int(ErrorType::VarUnknown));
    }
    this->Expr_int =
        (TableVec[currentfield].lookup(node.name).type == Type::INT);
    this->Expr_type = TableVec[currentfield].lookup(node.name).type;
    currentfield = save;
}

void SyntaxTreeChecker::visit(Literal &node) {
    this->Expr_int = (node.literal_type == SyntaxTree::Type::INT);
    this->Expr_type = node.literal_type;
}

void SyntaxTreeChecker::visit(ReturnStmt &node) { node.ret->accept(*this); }

void SyntaxTreeChecker::visit(VarDef &node) {
    if (node.is_inited) {
        node.initializers->accept(*this);
    }
    if (TableVec[currentfield].isexist(node.name)) {
        err.error(node.loc, "Variable duplicated.");
        exit(int(ErrorType::VarDuplicated));
    }

    struct attr value;
    value.isVar = true;
    value.isFunc = false;
    value.type = node.btype;
    TableVec[currentfield].addItem(node.name, value);
}

void SyntaxTreeChecker::visit(AssignStmt &node) { node.value->accept(*this); }
void SyntaxTreeChecker::visit(FuncCallStmt &node) {
    int save = currentfield;
    while (currentfield >= 0 && (!TableVec[currentfield].isexist(node.name))) {
        currentfield--;
    }
    if (currentfield < 0) {
        err.error(node.loc, "Function unknown.");
        exit(int(ErrorType::FuncUnknown));
    }
    this->Expr_int = (TableVec[currentfield].lookup(node.name).type ==
                      Type::INT);  // 检查函数的返回类型
    auto TableItem = TableVec[currentfield].lookup(node.name);
    int length = TableItem.FParamList.size();
    if (node.params.size() != 0) {  // 检查实参列表
        int index = 0;
        for (auto param : node.params) {
            param->accept(*this);  // 检查该参数时记录该参数的类型
            auto ParamType = this->Expr_type;
            if (index >= length || ParamType != TableItem.FParamList[index]) {
                err.error(node.loc, "FuncParams error.");
                exit(int(ErrorType::FuncParams));
            }
            index++;
        }
    } else if (node.params.size() == 0 && length > 0) {
        err.error(node.loc, "FuncParams error.");
        exit(int(ErrorType::FuncParams));
    }
    currentfield = save;
    this->Expr_type = TableVec[currentfield].lookup(node.name).type;
}
void SyntaxTreeChecker::visit(BlockStmt &node) {
    currentfield++;
    if (int(TableVec.size()) <= currentfield) {
        TableVec.push_back(SymbolTable(currentfield));
    }
    for (auto stmt : node.body) {
        stmt->accept(*this);  // 遍历语句块中的每个语句来对其进行检查
    }
    TableVec.pop_back();
    currentfield--;
}
void SyntaxTreeChecker::visit(EmptyStmt &node) {}
void SyntaxTreeChecker::visit(SyntaxTree::ExprStmt &node) {
    node.exp->accept(*this);
}
void SyntaxTreeChecker::visit(SyntaxTree::FuncParam &node) {
    if (TableVec[currentfield].isexist(node.name)) {
        err.error(node.loc, "FuncParam duplicated.");
        exit(int(ErrorType::VarDuplicated));
    }
    struct attr value;
    value.isVar = true;
    value.isFunc = false;
    value.type = node.param_type;
    TableVec[currentfield].addItem(node.name, value);
}
void SyntaxTreeChecker::visit(SyntaxTree::FuncFParamList &node) {
    currentfield++;
    if (node.params.size() != 0) {
        TableVec.push_back(SymbolTable(currentfield));
        for (auto funcparam : node.params) {
            funcparam->accept(
                *this);  // 遍历形参表中的每个形参边建立符号表边检查
        }
    }
    currentfield--;
}
void SyntaxTreeChecker::visit(SyntaxTree::BinaryCondExpr &node) {
    node.lhs->accept(*this);
    node.rhs->accept(*this);
    this->Expr_type = Type::BOOL;
}
void SyntaxTreeChecker::visit(SyntaxTree::UnaryCondExpr &node) {
    node.rhs->accept(*this);
}
void SyntaxTreeChecker::visit(SyntaxTree::IfStmt &node) {
    node.cond_exp->accept(*this);
    node.if_statement->accept(*this);
    if (node.else_statement != 0) {
        node.else_statement->accept(*this);
    }
}
void SyntaxTreeChecker::visit(SyntaxTree::WhileStmt &node) {
    node.cond_exp->accept(*this);
    node.statement->accept(*this);
}
void SyntaxTreeChecker::visit(SyntaxTree::BreakStmt &node) {}
void SyntaxTreeChecker::visit(SyntaxTree::ContinueStmt &node) {}

void SyntaxTreeChecker::visit(SyntaxTree::InitVal &node) {
    if (node.isExp) {
        node.expr->accept(*this);
    } else {
        for (auto element : node.elementList) {
            element->accept(*this);
        }
    }
}