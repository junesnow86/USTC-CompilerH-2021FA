%skeleton "lalr1.cc" /* -*- c++ -*- */
%require "3.0"
%defines
//%define parser_class_name {sysyfParser}
%define api.parser.class {sysyfParser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include "SyntaxTree.h"
class sysyfDriver;
}

// The parsing context.
%param { sysyfDriver& driver }

// Location tracking
%locations
%initial-action
{
// Initialize the initial location.
@$.begin.filename = @$.end.filename = &driver.file;
};

// Enable tracing and verbose errors (which may be wrong!)
%define parse.trace
%define parse.error verbose

// Parser needs to know about the driver:
%code
{
#include "sysyfDriver.h"
#define yylex driver.lexer.yylex
}

// Tokens:
%define api.token.prefix {TOK_}

%token END
/*********TODO: add your token here*********/
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token ASSIGN
%token COMMA SEMICOLON
%token LPARENTHESE RPARENTHESE
%token LSQUARE RSQUARE
%token LBRACE RBRACE
%token LT GT LTE GTE EQ NEQ LAND LOR
%token INT FLOAT VOID
%token CONST
%token IF ELSE WHILE BREAK CONTINUE RETURN  
%token <std::string>IDENTIFIER
%token <int>INTCONST
%token <float>FLOATCONST
%token EOL COMMENT
%token BLANK NOT
%token AND OR


// Use variant-based semantic values: %type and %token expect genuine types
%type <SyntaxTree::Assembly*>CompUnit
%type <SyntaxTree::PtrList<SyntaxTree::GlobalDef>>GlobalDecl
/*********TODO: add semantic value definition here*********/
%type <SyntaxTree::Type>BType
%type <SyntaxTree::PtrList<SyntaxTree::VarDef>>VarDecl
%type <SyntaxTree::PtrList<SyntaxTree::VarDef>>VarDefList
%type <SyntaxTree::VarDef *>VarDef
%type <SyntaxTree::VarDef *>InitVarDef
%type <SyntaxTree::VarDef *>NotInitVarDef
%type <SyntaxTree::VarDef *>InitArrDef
%type <SyntaxTree::VarDef *>NotInitArrDef
%type <SyntaxTree::InitVal *>InitVal
%type <SyntaxTree::PtrList<SyntaxTree::InitVal>>InitValList
%type <SyntaxTree::FuncDef *>FuncDef
%type <SyntaxTree::FuncFParamList *>FuncFParamList
%type <SyntaxTree::FuncParam *>FuncParam
%type <SyntaxTree::FuncParam *>NormalFuncParam
%type <SyntaxTree::FuncParam *>ArrayFuncParam
%type <SyntaxTree::BlockStmt *>Block
%type <SyntaxTree::PtrList<SyntaxTree::Stmt>>BlockItemList
%type <SyntaxTree::PtrList<SyntaxTree::Stmt>>BlockItem
%type <SyntaxTree::Stmt *>Stmt
%type <SyntaxTree::LVal *>LVal
%type <SyntaxTree::Expr *>Exp
%type <SyntaxTree::Literal *>Number
%type <SyntaxTree::PtrList<SyntaxTree::Expr>>FuncRParams


// No %destructors are needed, since memory will be reclaimed by the
// regular destructors.

// Grammar:
%start Begin 

/*********TODO: add other semantic symbol definition here*********/
%%
Begin: CompUnit END {
    $1->loc = @$;
    driver.root = $1;
    return 0;
  }
  ;

CompUnit:CompUnit GlobalDecl{
		$1->global_defs.insert($1->global_defs.end(), $2.begin(), $2.end());
		$$=$1;
	} 
	| GlobalDecl{
		$$=new SyntaxTree::Assembly();
		$$->global_defs.insert($$->global_defs.end(), $1.begin(), $1.end());
  }
	;

GlobalDecl: FuncDef {
    $$ = SyntaxTree::PtrList<SyntaxTree::GlobalDef>(); 
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::GlobalDef>($1));
}
| VarDecl {
    $$ = SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    $$.insert($$.end(), $1.begin(), $1.end());
}
| COMMENT {
};

BType: INT {
    $$ = SyntaxTree::Type::INT;
}
| FLOAT {
    $$ = SyntaxTree::Type::FLOAT;
}
| VOID {
    $$ = SyntaxTree::Type::VOID;
};

VarDecl: BType VarDefList SEMICOLON {
    $$ = $2;
    for(auto &node : $$) {
        node->btype = $1;
        node->is_constant = false;
    }
}
| CONST BType VarDefList SEMICOLON {
    $$ = $3;
    for(auto &node : $$) {
        node->btype = $2;
        node->is_constant = true;
    }
};

VarDefList: VarDefList COMMA VarDef {
    $1.push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>($3));
    $$ = $1;
}
| VarDef {
    $$ = SyntaxTree::PtrList<SyntaxTree::VarDef>();
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>($1));
};


VarDef: NotInitArrDef {
    $$ = $1;
}
| InitArrDef {
    $$ = $1;
}
| NotInitVarDef {
    $$ = $1;
}
| InitVarDef {
    $$ = $1;
};

NotInitArrDef: NotInitVarDef LSQUARE Exp RSQUARE {
    $1->array_length.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>($3));
    $$ = $1;
}
| NotInitArrDef LSQUARE Exp RSQUARE {
    $1->array_length.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>($3));
    $$ = $1;
};

NotInitVarDef: IDENTIFIER {
    $$ = new SyntaxTree::VarDef();
    $$->name = $1;
    $$->is_inited = false;
    $$->loc = @$;
};

InitArrDef: NotInitArrDef ASSIGN InitVal {
    $1->is_inited = true;
    $1->initializers = SyntaxTree::Ptr<SyntaxTree::InitVal>($3);
    $$ = $1;
};

InitVarDef: IDENTIFIER ASSIGN InitVal {
    $$ = new SyntaxTree::VarDef();
    $$->name = $1;
    $$->is_inited = true;
    $$->initializers = SyntaxTree::Ptr<SyntaxTree::InitVal>($3);
    $$->loc = @$;
};

InitVal: Exp {
    $$ = new SyntaxTree::InitVal();
    $$->isExp = true;
    $$->expr = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    $$->loc = @$;
}
| LBRACE RBRACE {
    $$ = new SyntaxTree::InitVal();
    $$->isExp = false;
    $$->loc = @$;
}
| LBRACE InitValList RBRACE {
    $$ = new SyntaxTree::InitVal();
    $$->isExp = false;
    $$->elementList.insert($$->elementList.end(), $2.begin(), $2.end());
    $$->loc = @$;
};

InitValList: InitVal {
    $$ = SyntaxTree::PtrList<SyntaxTree::InitVal>();
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::InitVal>($1));
}
| InitValList COMMA InitVal {
    $1.push_back(SyntaxTree::Ptr<SyntaxTree::InitVal>($3));
    $$ = $1;
};

/*
FuncDef: BType IDENTIFIER LPARENTHESE RPARENTHESE Block {
    $$ = new SyntaxTree::FuncDef();
    $$->ret_type = $1;
    $$->name = $2;
    $$->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>($5);
    $$->loc = @$;
};
*/

FuncDef: BType IDENTIFIER LPARENTHESE FuncFParamList RPARENTHESE Block {
    $$ = new SyntaxTree::FuncDef();
    $$->ret_type = $1;
    $$->name = $2;
    $$->param_list = SyntaxTree::Ptr<SyntaxTree::FuncFParamList>($4);
    $$->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>($6); 
    $$->loc = @$;
};

FuncFParamList: FuncParam {
    $$ = new SyntaxTree::FuncFParamList();
    $$->params.push_back(SyntaxTree::Ptr<SyntaxTree::FuncParam>($1));
    $$->loc = @$;
}
| FuncFParamList COMMA FuncParam {
    $1->params.push_back(SyntaxTree::Ptr<SyntaxTree::FuncParam>($3));
    $$ = $1;
}
| %empty {
    $$ = new SyntaxTree::FuncFParamList();
    $$->loc = @$;
};

FuncParam: NormalFuncParam {
    $$ = $1;
}
| ArrayFuncParam {
    $$ = $1;
};

ArrayFuncParam: NormalFuncParam LSQUARE RSQUARE {
    $1->array_index.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>());
    $$ = $1;
}
| NormalFuncParam LSQUARE Exp RSQUARE {
    $1->array_index.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>($3));
    $$ = $1;
}
| ArrayFuncParam LSQUARE Exp RSQUARE {
    $1->array_index.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>($3));
    $$ = $1;
};

NormalFuncParam: BType IDENTIFIER {
    $$ = new SyntaxTree::FuncParam();
    $$->name = $2;
    $$->param_type = $1;
    $$->loc = @$;
};

Block: LBRACE BlockItemList RBRACE {
    $$ = new SyntaxTree::BlockStmt();
    $$->body = $2;
    $$->loc = @$;
};

BlockItemList: BlockItemList BlockItem {
    $1.insert($1.end(), $2.begin(), $2.end());
    $$ = $1;
}
| %empty {
    $$ = SyntaxTree::PtrList<SyntaxTree::Stmt>();
};

BlockItem: VarDecl {
    $$ = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    $$.insert($$.end(), $1.begin(), $1.end());
}
| Stmt {
    $$ = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::Stmt>($1));
}
| COMMENT {
};

%precedence RPARENTHESE;
%precedence ELSE;
Stmt: LVal ASSIGN Exp SEMICOLON {
    auto temp = new SyntaxTree::AssignStmt();
    temp->target = SyntaxTree::Ptr<SyntaxTree::LVal>($1);
    temp->value = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp SEMICOLON {
    auto temp = new SyntaxTree::ExprStmt();
    temp->exp = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    $$ = temp;
    $$->loc = @$;
}
| SEMICOLON {
    $$ = new SyntaxTree::EmptyStmt();
    $$->loc = @$;
}
| Block {
    $$ = $1;
}
| IF LPARENTHESE Exp RPARENTHESE Stmt {
    auto temp = new SyntaxTree::IfStmt();
    temp->cond_exp = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    temp->if_statement = SyntaxTree::Ptr<SyntaxTree::Stmt>($5);
    $$ = temp;
    $$->loc = @$;
}
| IF LPARENTHESE Exp RPARENTHESE Stmt ELSE Stmt {
    auto temp = new SyntaxTree::IfStmt();
    temp->cond_exp = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    temp->if_statement = SyntaxTree::Ptr<SyntaxTree::Stmt>($5);
    temp->else_statement = SyntaxTree::Ptr<SyntaxTree::Stmt>($7);
    $$ = temp;
    $$->loc = @$;
}
| WHILE LPARENTHESE Exp RPARENTHESE Stmt {
    auto temp = new SyntaxTree::WhileStmt();
    temp->cond_exp = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    temp->statement = SyntaxTree::Ptr<SyntaxTree::Stmt>($5);
    $$ = temp;
    $$->loc = @$;
}
| BREAK SEMICOLON {
    $$ = new SyntaxTree::BreakStmt();
    $$->loc = @$;
}
| CONTINUE SEMICOLON {
    $$ = new SyntaxTree::ContinueStmt();
    $$->loc = @$;
}
| RETURN Exp SEMICOLON {
    auto temp = new SyntaxTree::ReturnStmt();
    temp->ret = SyntaxTree::Ptr<SyntaxTree::Expr>($2);
    $$ = temp;
    $$->loc = @$;
}
| RETURN SEMICOLON {
    auto temp = new SyntaxTree::ReturnStmt();
    $$ = temp;
    $$->loc = @$;
};

LVal: IDENTIFIER {
    $$ = new SyntaxTree::LVal();
    $$->name = $1;
    $$->loc = @$;
}
| LVal LSQUARE Exp RSQUARE {
    $1->array_index.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>($3));
    $$ = $1;
}

%left LOR;
%left LAND;
%left EQ NEQ;
%left LT LTE GT GTE;
%left PLUS MINUS;
%left MULTIPLY DIVIDE MODULO;
%precedence NOT;
%precedence UPLUS UMINUS;
Exp: NOT Exp {
    auto temp = new SyntaxTree::UnaryCondExpr();
    temp->op = SyntaxTree::UnaryCondOp::NOT;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($2);
    $$ = temp;
    $$->loc = @$;
} 
| Exp LT Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LT;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp GT Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::GT;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
} 
| Exp LTE Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LTE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp GTE Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::GTE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp EQ Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::EQ;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp NEQ Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::NEQ;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp LAND Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LAND;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp LOR Exp {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LOR;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp PLUS Exp {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::PLUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp MINUS Exp {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MINUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp MULTIPLY Exp {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MULTIPLY;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp DIVIDE Exp {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::DIVIDE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| Exp MODULO Exp {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MODULO;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
}
| PLUS Exp %prec UPLUS {
    auto temp = new SyntaxTree::UnaryExpr();
    temp->op = SyntaxTree::UnaryOp::PLUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($2);
    $$ = temp;
    $$->loc = @$;
}
| MINUS Exp %prec UMINUS {
    auto temp = new SyntaxTree::UnaryExpr();
    temp->op = SyntaxTree::UnaryOp::MINUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($2);
    $$ = temp;
    $$->loc = @$;
}
| IDENTIFIER LPARENTHESE RPARENTHESE {
    auto temp = new SyntaxTree::FuncCallStmt();
    temp->name = $1;
    $$ = temp;
    $$->loc = @$;
}
| IDENTIFIER LPARENTHESE FuncRParams RPARENTHESE {
    auto temp = new SyntaxTree::FuncCallStmt();
    temp->name = $1;
    temp->params = $3;
    $$ = temp;
    $$->loc = @$;
}
| LPARENTHESE Exp RPARENTHESE {
    $$ = $2;
}
| LVal {
    $$ = $1;
}
| Number {
    $$ = $1;
};

FuncRParams: Exp {
    $$ = SyntaxTree::PtrList<SyntaxTree::Expr>();
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>($1));
}
| FuncRParams COMMA Exp {
    $1.push_back(SyntaxTree::Ptr<SyntaxTree::Expr>($3));
    $$ = $1;
};

Number: INTCONST {
    $$ = new SyntaxTree::Literal();
    $$->literal_type = SyntaxTree::Type::INT;
    $$->int_const = $1;
    $$->loc = @$;
}
| FLOATCONST {
    $$ = new SyntaxTree::Literal();
    $$->literal_type = SyntaxTree::Type::FLOAT;
    $$->float_const = $1;
    $$->loc = @$;
};

%%

// Register errors to the driver:
void yy::sysyfParser::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
