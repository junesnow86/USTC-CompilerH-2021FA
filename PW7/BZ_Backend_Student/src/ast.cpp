#include "ast.h"
#include "syntax_tree.h"

// ============  BEGIN OF METHODS IMPLEMENT =================

void ASTProgram::runVisitor(ASTvisitor &node){
    accept(node);
}
ASTUnaryOp::ASTUnaryOp(TreeNode *t) : ASTInstruction(AST_UNARY_EXP) {
    assert(t != nullptr && t->node_type == AST_unary_exp && t->children.size() == 2 &&
           "ASTUnaryOp got invalid TreeNode pointer");
    switch (t->children[0]->children[0]->node_type) {
        case AST_ADD:
            _op_type = AST_OP_POSITIVE;
            break;
        case AST_SUB:
            _op_type = AST_OP_NEGATIVE;
            break;
        case AST_NOT:
            _op_type = AST_OP_INVERSE;
            break;
        default:
            assert(0 && "ASTUnaryOp got unknown node type");
    }
    _sub_exp = getUnaryOp(t->children[1]);
}

ASTInstruction *ASTUnaryOp::getUnaryOp(TreeNode *t) {
    switch (t->children.size()) {
        case 2:
            // Unary Expression
            return new ASTUnaryOp(t);
        case 1:
            // Primary Expression
        {
            // node 为 PrimaryExp结点
            TreeNode *node = t->children[0];
            switch (node->children[0]->node_type) {
                case AST_LPARENTHESE:
                    // PrimaryExp->( Exp )->AddExp
                    return new ASTAddOp(node->children[1]->children[0]);
                case AST_lval:
                    // PrimaryExp->LVal->Indent (Pointer ?)
                    return new ASTLVal(node->children[0]);
                case AST_number:
                    return new ASTConstant(node->children[0]->children[0]);
                case AST_IDENT:
                    return new ASTFuncCall(node);
                default:
                    assert(0 && "ASTPrimaryExp got unknown child node type");
            }
        }
            break;
        case 3:
            // func()
        case 4:
            // func(a,...)
            return new ASTFuncCall(t->children[1]);
            break;
        default:
            assert(0 && "ASTUnaryOp got unknown sub node type");
    }
}

ASTStatement *ASTStatement::getASTStatement(TreeNode *t) {
    assert(t != nullptr && (t->node_type == AST_stmt || t->node_type == AST_decl) && "AST Statement got invalid TreeNode.");
    t = t->children[0];
    switch (t->node_type) {
        case AST_block:
            return new ASTBlock(t);
        case AST_if_stmt:
            return new ASTIfStmt(t);
        case AST_iter_stmt:
            return new ASTWhileStmt(t);
        case AST_continue_stmt:
            return new ASTContinueStmt(t);
        case AST_break_stmt:
            return new ASTBreakStmt(t);
        case AST_return_stmt:
            return new ASTReturnStmt(t);
        case AST_exp_stmt:
            return new ASTExpressionStmt(t);
        case AST_assign_stmt:
            return new ASTAssignStmt(t);
        case AST_var_decl:
        case AST_const_decl:
            return new ASTVarDecl(t);
        default:
            assert(0 && "AST Statement got unrecognizable node type.");
    }
}

// ============  END OF METHODS IMPLEMENT =================



// ============  BEGIN OF VISITOR PATTERN =================
void ASTConstant::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTUnaryOp::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTMulOp::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTAddOp::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTRelOp::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTEqOp::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTAndOp::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTOrOp::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTLVal::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTFuncCall::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTVarDecl::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTAssignStmt::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTExpressionStmt::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTIfStmt::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTWhileStmt::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTBreakStmt::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTContinueStmt::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTReturnStmt::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTParam::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTBlock::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTFuncDecl::accept(ASTvisitor &visitor) { visitor.visit(*this); }
void ASTProgram::accept(ASTvisitor &visitor) { visitor.visit(*this); }