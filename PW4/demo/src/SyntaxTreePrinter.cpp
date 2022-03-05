#include "SyntaxTreePrinter.h"
#include "ErrorReporter.h"
#include <map>
#include <string>
#include <iostream>

using namespace SyntaxTree;

std::map<Type, std::string> type2str = {
    {Type::INT, "int"},
    {Type::VOID, "void"}
};

std::map<BinOp, std::string> binop2str = {
    {BinOp::PLUS, "+"},
    {BinOp::MINUS, "-"},
    {BinOp::MULTIPLY, "*"},
    {BinOp::DIVIDE, "/"},
    {BinOp::MODULO, "%"}
};

std::map<UnaryOp, std::string> unaryop2str = {
    {UnaryOp::PLUS, "+"},
    {UnaryOp::MINUS, "-"}
};

void SyntaxTreePrinter::print_indent()
{
    for (int i = 0; i < indent; i++)
        std::cout << " ";
}

void SyntaxTreePrinter::visit(Assembly &node)
{
    indent = 0;
    for (auto def : node.global_defs) {
        def->accept(*this);
    }
}

void SyntaxTreePrinter::visit(FuncDef &node)
{
    std::cout << type2str[node.ret_type] << " " 
        << node.name << "(";
    std::cout << ")" << std::endl;
    node.body->accept(*this);
    indent = 0;
}

void SyntaxTreePrinter::visit(BlockStmt &node)
{
    print_indent();
    std::cout << "{" << std::endl;
    indent += 4;
    for (auto stmt : node.body) {
        stmt->accept(*this);
    }
    indent -= 4;
    print_indent();
    std::cout << "}" << std::endl;
}

void SyntaxTreePrinter::visit(VarDef &node)
{
    print_indent();
    if (node.is_constant)
        std::cout << "const ";
    std::cout << type2str[node.btype] << " " << node.name;
    for (auto length : node.array_length) {
        std::cout << "[";
        length->accept(*this);
        std::cout << "]";
    }
    if (node.is_inited) {
        int tmp = indent;
        indent = 0;
        std::cout << " = ";
        node.initializers->accept(*this);
        indent = tmp;
    }
    std::cout << ";" << std::endl;
}

void SyntaxTreePrinter::visit(InitVal &node){
    node.expr->accept(*this);
    return;
}

void SyntaxTreePrinter::visit(BinaryExpr &node)
{
    std::cout << "(";
    node.lhs->accept(*this);
    std::cout << binop2str[node.op];
    node.rhs->accept(*this);
    std::cout << ")";
}

void SyntaxTreePrinter::visit(UnaryExpr &node)
{
    std::cout << "(";
    std::cout << unaryop2str[node.op];
    node.rhs->accept(*this);
    std::cout << ")";
}

void SyntaxTreePrinter::visit(LVal &node)
{
    std::cout << node.name;
    for (auto index : node.array_index) {
        std::cout << "[";
        index->accept(*this);
        std::cout << "]";
    }
}

void SyntaxTreePrinter::visit(Literal &node)
{
    if (node.literal_type == Type::INT)
        std::cout << node.int_const;
    else {
        ErrorReporter error(std::cerr);
        error.error(node.loc,"unsupported literal type!");
        abort(); 
    }
}

void SyntaxTreePrinter::visit(ReturnStmt &node)
{
    print_indent();
    std::cout << "return;" << std::endl;
}

void SyntaxTreePrinter::visit(AssignStmt &node)
{
    print_indent();
    node.target->accept(*this);
    std::cout << " = ";
    node.value->accept(*this);
    std::cout << ";" << std::endl;
}


void SyntaxTreePrinter::visit(EmptyStmt &)
{
    print_indent();
    std::cout << ";" << std::endl;
}

void SyntaxTreePrinter::visit(ExprStmt &node)
{
    print_indent();
    node.exp->accept(*this);
    std::cout << ";" << std::endl;
}

