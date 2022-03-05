#ifndef _DEMO_SYNTAX_TREE_PRINTER_H_
#define _DEMO_SYNTAX_TREE_PRINTER_H_

#include "SyntaxTree.h"

class SyntaxTreePrinter : public SyntaxTree::Visitor
{
public:
    void visit(SyntaxTree::Assembly &node) override;
    void visit(SyntaxTree::FuncDef &node) override;
    void visit(SyntaxTree::BinaryExpr &node) override;
    void visit(SyntaxTree::UnaryExpr &node) override;
    void visit(SyntaxTree::LVal &node) override;
    void visit(SyntaxTree::Literal &node) override;
    void visit(SyntaxTree::ReturnStmt &node) override;
    void visit(SyntaxTree::VarDef &node) override;
    void visit(SyntaxTree::AssignStmt &node) override;
    void visit(SyntaxTree::BlockStmt &node) override;
    void visit(SyntaxTree::EmptyStmt &node) override;
    void visit(SyntaxTree::ExprStmt &node) override;
    void visit(SyntaxTree::InitVal &node) override;
    void print_indent();
private:
    int indent = 0;
};

#endif  // _DEMO_SYNTAX_TREE_PRINTER_H_
