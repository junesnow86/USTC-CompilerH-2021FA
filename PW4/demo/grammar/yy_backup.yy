%skeleton "lalr1.cc" /* -*- c++ -*- */
%require "3.0"
%defines
//%define parser_class_name {demoParser}
%define api.parser.class {demoParser}

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include "../include/SyntaxTree.h"
class demoDriver;
}

// The parsing context.
%param { demoDriver& driver }

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
#include "demoDriver.h"
#define yylex driver.lexer.yylex
}

// Tokens:
%define api.token.prefix {TOK_}

%token END
%token PLUS MINUS MULTIPLY DIVIDE MODULO
%token ASSIGN SEMICOLON
%token COMMA LPARENTHESE RPARENTHESE
%token LBRACE RBRACE
%token INT RETURN VOID
%token <std::string>IDENTIFIER
%token <int>INTCONST
%token EOL COMMENT
%token BLANK NOT
// Use variant-based semantic values: %type and %token expect genuine types

%type <SyntaxTree::Assembly*>CompUnit
%type <SyntaxTree::PtrList<SyntaxTree::GlobalDef>>GlobalDecl
%type <SyntaxTree::Type>BType
%type <SyntaxTree::PtrList<SyntaxTree::VarDef>>VarDecl
%type <SyntaxTree::PtrList<SyntaxTree::VarDef>>VarDefList
%type <SyntaxTree::VarDef*>VarDef
%type <SyntaxTree::InitVal*>InitVal
%type <SyntaxTree::FuncDef*>FuncDef
%type <SyntaxTree::BlockStmt*>Block
%type <SyntaxTree::PtrList<SyntaxTree::Stmt>>BlockItemList
%type <SyntaxTree::PtrList<SyntaxTree::Stmt>>BlockItem
%type <SyntaxTree::Stmt*>Stmt
%type <SyntaxTree::LVal*>LVal
%type <SyntaxTree::Expr*>Exp
%type <SyntaxTree::Literal*>Number

// No %destructors are needed, since memory will be reclaimed by the
// regular destructors.
/* %printer { yyoutput << $$; } <*>;*/

// Grammar:
%start Begin 

%%
Begin: CompUnit END {
    $1->loc = @$;
    driver.root = $1;
    return 0;
  }
  ;

CompUnit: GlobalDecl{
		$$=new SyntaxTree::Assembly();
		$$->global_defs.insert($$->global_defs.end(), $1.begin(), $1.end());
  }
	;

GlobalDecl:FuncDef{
    $$=SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::GlobalDef>($1));
  }
;

BType:INT{
  $$=SyntaxTree::Type::INT;
  }
;

VarDecl:BType VarDefList SEMICOLON{
    $$=$2;
    for (auto &node : $$) {
      node->btype = $1;
    }
  }
;

VarDefList:VarDefList COMMA VarDef{
    $1.push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>($3));
    $$=$1;
  }
	| VarDef{
    $$=SyntaxTree::PtrList<SyntaxTree::VarDef>();
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>($1));
  }
;

VarDef:IDENTIFIER{
    $$=new SyntaxTree::VarDef();
    $$->name=$1;
    $$->is_inited = false;
    $$->loc = @$;
  }
	| IDENTIFIER ASSIGN InitVal{
    $$ = new SyntaxTree::VarDef();
    $$->name = $1;
    $$->initializers = SyntaxTree::Ptr<SyntaxTree::InitVal>($3);
    $$->is_inited = true;
    $$->loc = @$;
  }
;

InitVal: Exp{
    $$ = new SyntaxTree::InitVal();
    $$->expr = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    $$->loc = @$;
  }
;

FuncDef: VOID IDENTIFIER LPARENTHESE RPARENTHESE Block{
    $$ = new SyntaxTree::FuncDef();
    $$->ret_type = SyntaxTree::Type::VOID;
    $$->name = $2;
    $$->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>($5);
    $$->loc = @$;
  }
  ;

Block:LBRACE BlockItemList RBRACE{
    $$ = new SyntaxTree::BlockStmt();
    $$->body = $2;
    $$->loc = @$;
  }
  ;

BlockItemList:BlockItemList BlockItem{
    $1.insert($1.end(), $2.begin(), $2.end());
    $$ = $1;
  }
  | %empty{
    $$ = SyntaxTree::PtrList<SyntaxTree::Stmt>();
  }
  ;

BlockItem:VarDecl{
    $$ = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    $$.insert($$.end(), $1.begin(), $1.end());
  }
  | Stmt{
    $$ = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    $$.push_back(SyntaxTree::Ptr<SyntaxTree::Stmt>($1));
  }
  ;

Stmt:LVal ASSIGN Exp SEMICOLON{
    auto temp = new SyntaxTree::AssignStmt();
    temp->target = SyntaxTree::Ptr<SyntaxTree::LVal>($1);
    temp->value = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
  }
  | Exp SEMICOLON{
    auto temp = new SyntaxTree::ExprStmt();
    temp->exp = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    $$ = temp;
    $$->loc = @$;
  }
  | RETURN SEMICOLON{
    auto temp = new SyntaxTree::ReturnStmt();
    $$ = temp;
    $$->loc = @$;
  }
  | Block{
    $$ = $1;
  }
  | SEMICOLON{
    $$ = new SyntaxTree::EmptyStmt();
    $$->loc = @$;
  }
  ;

LVal:IDENTIFIER{
    $$ = new SyntaxTree::LVal();
    $$->name = $1;
    $$->loc = @$;
  }
  ;

%left PLUS MINUS;
%left MULTIPLY DIVIDE MODULO;
%precedence UPLUS UMINUS;

Exp:PLUS Exp %prec UPLUS{
    auto temp = new SyntaxTree::UnaryExpr();
    temp->op = SyntaxTree::UnaryOp::PLUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($2);
    $$ = temp;
    $$->loc = @$;
  }
  | MINUS Exp %prec UMINUS{
    auto temp = new SyntaxTree::UnaryExpr();
    temp->op = SyntaxTree::UnaryOp::MINUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($2);
    $$ = temp;
    $$->loc = @$;
  }
  | Exp PLUS Exp{
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::PLUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
  }
  | Exp MINUS Exp{
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MINUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
  }
  | Exp MULTIPLY Exp{
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MULTIPLY;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
  }
  | Exp DIVIDE Exp{
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::DIVIDE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
  }
  | Exp MODULO Exp{
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MODULO;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>($1);
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>($3);
    $$ = temp;
    $$->loc = @$;
  }
  | LPARENTHESE Exp RPARENTHESE{
    $$ = $2;
  }
  | LVal{
    $$ = $1;
  }
  | Number{
    $$ = $1;
  }
  ;

Number: INTCONST {
    $$ = new SyntaxTree::Literal();
    $$->literal_type = SyntaxTree::Type::INT;
    $$->int_const = $1;
    $$->loc = @$;
  }
  ;

%%

// Register errors to the driver:
void yy::demoParser::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
