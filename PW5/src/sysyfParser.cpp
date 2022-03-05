// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "sysyfParser.h"


// Unqualified %code blocks.
#line 35 "/data/workspace/myshixun/grammar/sysyfParser.yy"

#include "sysyfDriver.h"
#define yylex driver.lexer.yylex

#line 51 "/data/workspace/myshixun/build/sysyfParser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 143 "/data/workspace/myshixun/build/sysyfParser.cpp"

  /// Build a parser object.
  sysyfParser::sysyfParser (sysyfDriver& driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  sysyfParser::~sysyfParser ()
  {}

  sysyfParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  sysyfParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  sysyfParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  sysyfParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  sysyfParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  sysyfParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  sysyfParser::symbol_kind_type
  sysyfParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  sysyfParser::stack_symbol_type::stack_symbol_type ()
  {}

  sysyfParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.YY_MOVE_OR_COPY< SyntaxTree::Assembly* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Block: // Block
        value.YY_MOVE_OR_COPY< SyntaxTree::BlockStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_OptionRet: // OptionRet
      case symbol_kind::S_Exp: // Exp
      case symbol_kind::S_RelExp: // RelExp
      case symbol_kind::S_EqExp: // EqExp
      case symbol_kind::S_LAndExp: // LAndExp
      case symbol_kind::S_LOrExp: // LOrExp
      case symbol_kind::S_CondExp: // CondExp
        value.YY_MOVE_OR_COPY< SyntaxTree::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.YY_MOVE_OR_COPY< SyntaxTree::FuncDef* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.YY_MOVE_OR_COPY< SyntaxTree::FuncParam* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitVal: // InitVal
      case symbol_kind::S_InitValList: // InitValList
      case symbol_kind::S_CommaInitValList: // CommaInitValList
        value.YY_MOVE_OR_COPY< SyntaxTree::InitVal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LVal: // LVal
        value.YY_MOVE_OR_COPY< SyntaxTree::LVal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Number: // Number
        value.YY_MOVE_OR_COPY< SyntaxTree::Literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ExpList: // ExpList
      case symbol_kind::S_CommaExpList: // CommaExpList
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FParamList: // FParamList
      case symbol_kind::S_CommaFParamList: // CommaFParamList
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_ConstDefList: // ConstDefList
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.YY_MOVE_OR_COPY< SyntaxTree::PtrList<SyntaxTree::VarDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_IfStmt: // IfStmt
        value.YY_MOVE_OR_COPY< SyntaxTree::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BType: // BType
        value.YY_MOVE_OR_COPY< SyntaxTree::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConstDef: // ConstDef
      case symbol_kind::S_VarDef: // VarDef
        value.YY_MOVE_OR_COPY< SyntaxTree::VarDef* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  sysyfParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.move< SyntaxTree::Assembly* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Block: // Block
        value.move< SyntaxTree::BlockStmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_OptionRet: // OptionRet
      case symbol_kind::S_Exp: // Exp
      case symbol_kind::S_RelExp: // RelExp
      case symbol_kind::S_EqExp: // EqExp
      case symbol_kind::S_LAndExp: // LAndExp
      case symbol_kind::S_LOrExp: // LOrExp
      case symbol_kind::S_CondExp: // CondExp
        value.move< SyntaxTree::Expr* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.move< SyntaxTree::FuncDef* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.move< SyntaxTree::FuncParam* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitVal: // InitVal
      case symbol_kind::S_InitValList: // InitValList
      case symbol_kind::S_CommaInitValList: // CommaInitValList
        value.move< SyntaxTree::InitVal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LVal: // LVal
        value.move< SyntaxTree::LVal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Number: // Number
        value.move< SyntaxTree::Literal* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ExpList: // ExpList
      case symbol_kind::S_CommaExpList: // CommaExpList
        value.move< SyntaxTree::PtrList<SyntaxTree::Expr> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FParamList: // FParamList
      case symbol_kind::S_CommaFParamList: // CommaFParamList
        value.move< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.move< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.move< SyntaxTree::PtrList<SyntaxTree::Stmt> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_ConstDefList: // ConstDefList
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.move< SyntaxTree::PtrList<SyntaxTree::VarDef> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_IfStmt: // IfStmt
        value.move< SyntaxTree::Stmt* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BType: // BType
        value.move< SyntaxTree::Type > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConstDef: // ConstDef
      case symbol_kind::S_VarDef: // VarDef
        value.move< SyntaxTree::VarDef* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  sysyfParser::stack_symbol_type&
  sysyfParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.copy< SyntaxTree::Assembly* > (that.value);
        break;

      case symbol_kind::S_Block: // Block
        value.copy< SyntaxTree::BlockStmt* > (that.value);
        break;

      case symbol_kind::S_OptionRet: // OptionRet
      case symbol_kind::S_Exp: // Exp
      case symbol_kind::S_RelExp: // RelExp
      case symbol_kind::S_EqExp: // EqExp
      case symbol_kind::S_LAndExp: // LAndExp
      case symbol_kind::S_LOrExp: // LOrExp
      case symbol_kind::S_CondExp: // CondExp
        value.copy< SyntaxTree::Expr* > (that.value);
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.copy< SyntaxTree::FuncDef* > (that.value);
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.copy< SyntaxTree::FuncParam* > (that.value);
        break;

      case symbol_kind::S_InitVal: // InitVal
      case symbol_kind::S_InitValList: // InitValList
      case symbol_kind::S_CommaInitValList: // CommaInitValList
        value.copy< SyntaxTree::InitVal* > (that.value);
        break;

      case symbol_kind::S_LVal: // LVal
        value.copy< SyntaxTree::LVal* > (that.value);
        break;

      case symbol_kind::S_Number: // Number
        value.copy< SyntaxTree::Literal* > (that.value);
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ExpList: // ExpList
      case symbol_kind::S_CommaExpList: // CommaExpList
        value.copy< SyntaxTree::PtrList<SyntaxTree::Expr> > (that.value);
        break;

      case symbol_kind::S_FParamList: // FParamList
      case symbol_kind::S_CommaFParamList: // CommaFParamList
        value.copy< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (that.value);
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.copy< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (that.value);
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.copy< SyntaxTree::PtrList<SyntaxTree::Stmt> > (that.value);
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_ConstDefList: // ConstDefList
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.copy< SyntaxTree::PtrList<SyntaxTree::VarDef> > (that.value);
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_IfStmt: // IfStmt
        value.copy< SyntaxTree::Stmt* > (that.value);
        break;

      case symbol_kind::S_BType: // BType
        value.copy< SyntaxTree::Type > (that.value);
        break;

      case symbol_kind::S_ConstDef: // ConstDef
      case symbol_kind::S_VarDef: // VarDef
        value.copy< SyntaxTree::VarDef* > (that.value);
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  sysyfParser::stack_symbol_type&
  sysyfParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_CompUnit: // CompUnit
        value.move< SyntaxTree::Assembly* > (that.value);
        break;

      case symbol_kind::S_Block: // Block
        value.move< SyntaxTree::BlockStmt* > (that.value);
        break;

      case symbol_kind::S_OptionRet: // OptionRet
      case symbol_kind::S_Exp: // Exp
      case symbol_kind::S_RelExp: // RelExp
      case symbol_kind::S_EqExp: // EqExp
      case symbol_kind::S_LAndExp: // LAndExp
      case symbol_kind::S_LOrExp: // LOrExp
      case symbol_kind::S_CondExp: // CondExp
        value.move< SyntaxTree::Expr* > (that.value);
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        value.move< SyntaxTree::FuncDef* > (that.value);
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        value.move< SyntaxTree::FuncParam* > (that.value);
        break;

      case symbol_kind::S_InitVal: // InitVal
      case symbol_kind::S_InitValList: // InitValList
      case symbol_kind::S_CommaInitValList: // CommaInitValList
        value.move< SyntaxTree::InitVal* > (that.value);
        break;

      case symbol_kind::S_LVal: // LVal
        value.move< SyntaxTree::LVal* > (that.value);
        break;

      case symbol_kind::S_Number: // Number
        value.move< SyntaxTree::Literal* > (that.value);
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ExpList: // ExpList
      case symbol_kind::S_CommaExpList: // CommaExpList
        value.move< SyntaxTree::PtrList<SyntaxTree::Expr> > (that.value);
        break;

      case symbol_kind::S_FParamList: // FParamList
      case symbol_kind::S_CommaFParamList: // CommaFParamList
        value.move< SyntaxTree::PtrList<SyntaxTree::FuncParam> > (that.value);
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        value.move< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > (that.value);
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        value.move< SyntaxTree::PtrList<SyntaxTree::Stmt> > (that.value);
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_ConstDefList: // ConstDefList
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        value.move< SyntaxTree::PtrList<SyntaxTree::VarDef> > (that.value);
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_IfStmt: // IfStmt
        value.move< SyntaxTree::Stmt* > (that.value);
        break;

      case symbol_kind::S_BType: // BType
        value.move< SyntaxTree::Type > (that.value);
        break;

      case symbol_kind::S_ConstDef: // ConstDef
      case symbol_kind::S_VarDef: // VarDef
        value.move< SyntaxTree::VarDef* > (that.value);
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        value.move< float > (that.value);
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        value.move< int > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  sysyfParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  sysyfParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  sysyfParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  sysyfParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  sysyfParser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  sysyfParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  sysyfParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  sysyfParser::debug_level_type
  sysyfParser::debug_level () const
  {
    return yydebug_;
  }

  void
  sysyfParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  sysyfParser::state_type
  sysyfParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  sysyfParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  sysyfParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  sysyfParser::operator() ()
  {
    return parse ();
  }

  int
  sysyfParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 24 "/data/workspace/myshixun/grammar/sysyfParser.yy"
{
// Initialize the initial location.
yyla.location.begin.filename = yyla.location.end.filename = &driver.file;
}

#line 785 "/data/workspace/myshixun/build/sysyfParser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_CompUnit: // CompUnit
        yylhs.value.emplace< SyntaxTree::Assembly* > ();
        break;

      case symbol_kind::S_Block: // Block
        yylhs.value.emplace< SyntaxTree::BlockStmt* > ();
        break;

      case symbol_kind::S_OptionRet: // OptionRet
      case symbol_kind::S_Exp: // Exp
      case symbol_kind::S_RelExp: // RelExp
      case symbol_kind::S_EqExp: // EqExp
      case symbol_kind::S_LAndExp: // LAndExp
      case symbol_kind::S_LOrExp: // LOrExp
      case symbol_kind::S_CondExp: // CondExp
        yylhs.value.emplace< SyntaxTree::Expr* > ();
        break;

      case symbol_kind::S_FuncDef: // FuncDef
        yylhs.value.emplace< SyntaxTree::FuncDef* > ();
        break;

      case symbol_kind::S_FuncFParam: // FuncFParam
        yylhs.value.emplace< SyntaxTree::FuncParam* > ();
        break;

      case symbol_kind::S_InitVal: // InitVal
      case symbol_kind::S_InitValList: // InitValList
      case symbol_kind::S_CommaInitValList: // CommaInitValList
        yylhs.value.emplace< SyntaxTree::InitVal* > ();
        break;

      case symbol_kind::S_LVal: // LVal
        yylhs.value.emplace< SyntaxTree::LVal* > ();
        break;

      case symbol_kind::S_Number: // Number
        yylhs.value.emplace< SyntaxTree::Literal* > ();
        break;

      case symbol_kind::S_ArrayExpList: // ArrayExpList
      case symbol_kind::S_ExpList: // ExpList
      case symbol_kind::S_CommaExpList: // CommaExpList
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::Expr> > ();
        break;

      case symbol_kind::S_FParamList: // FParamList
      case symbol_kind::S_CommaFParamList: // CommaFParamList
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
        break;

      case symbol_kind::S_GlobalDecl: // GlobalDecl
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ();
        break;

      case symbol_kind::S_BlockItemList: // BlockItemList
      case symbol_kind::S_BlockItem: // BlockItem
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::Stmt> > ();
        break;

      case symbol_kind::S_ConstDecl: // ConstDecl
      case symbol_kind::S_ConstDefList: // ConstDefList
      case symbol_kind::S_VarDecl: // VarDecl
      case symbol_kind::S_VarDefList: // VarDefList
        yylhs.value.emplace< SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
        break;

      case symbol_kind::S_Stmt: // Stmt
      case symbol_kind::S_IfStmt: // IfStmt
        yylhs.value.emplace< SyntaxTree::Stmt* > ();
        break;

      case symbol_kind::S_BType: // BType
        yylhs.value.emplace< SyntaxTree::Type > ();
        break;

      case symbol_kind::S_ConstDef: // ConstDef
      case symbol_kind::S_VarDef: // VarDef
        yylhs.value.emplace< SyntaxTree::VarDef* > ();
        break;

      case symbol_kind::S_FLOATCONST: // FLOATCONST
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_INTCONST: // INTCONST
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRINGCONST: // STRINGCONST
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // Begin: CompUnit END
#line 106 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                    {
    yystack_[1].value.as < SyntaxTree::Assembly* > ()->loc = yylhs.location;
    driver.root = yystack_[1].value.as < SyntaxTree::Assembly* > ();
    return 0;
  }
#line 1021 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 3: // CompUnit: CompUnit GlobalDecl
#line 113 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                            {
		yystack_[1].value.as < SyntaxTree::Assembly* > ()->global_defs.insert(yystack_[1].value.as < SyntaxTree::Assembly* > ()->global_defs.end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end());
		yylhs.value.as < SyntaxTree::Assembly* > ()=yystack_[1].value.as < SyntaxTree::Assembly* > ();
	}
#line 1030 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 4: // CompUnit: GlobalDecl
#line 117 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                    {
		yylhs.value.as < SyntaxTree::Assembly* > ()=new SyntaxTree::Assembly();
		yylhs.value.as < SyntaxTree::Assembly* > ()->global_defs.insert(yylhs.value.as < SyntaxTree::Assembly* > ()->global_defs.end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end());
  }
#line 1039 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 5: // GlobalDecl: ConstDecl
#line 123 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                    {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ()=SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1048 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 6: // GlobalDecl: VarDecl
#line 127 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                 {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ()=SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1057 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 7: // GlobalDecl: FuncDef
#line 131 "/data/workspace/myshixun/grammar/sysyfParser.yy"
           {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ()=SyntaxTree::PtrList<SyntaxTree::GlobalDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::GlobalDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::GlobalDef>(yystack_[0].value.as < SyntaxTree::FuncDef* > ()));
  }
#line 1066 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 8: // ConstDecl: CONST BType ConstDefList SEMICOLON
#line 137 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                            {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
    for (auto &node : yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()) {
      node->btype = yystack_[2].value.as < SyntaxTree::Type > ();
    }
  }
#line 1077 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 9: // ConstDefList: ConstDefList COMMA ConstDef
#line 144 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                        {
    yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>(yystack_[0].value.as < SyntaxTree::VarDef* > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
  }
#line 1086 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 10: // ConstDefList: ConstDef
#line 148 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                  {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=SyntaxTree::PtrList<SyntaxTree::VarDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>(yystack_[0].value.as < SyntaxTree::VarDef* > ()));
  }
#line 1095 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 11: // BType: INT
#line 154 "/data/workspace/myshixun/grammar/sysyfParser.yy"
         {
  yylhs.value.as < SyntaxTree::Type > ()=SyntaxTree::Type::INT;
  }
#line 1103 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 12: // BType: FLOAT
#line 157 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
  yylhs.value.as < SyntaxTree::Type > ()=SyntaxTree::Type::FLOAT;
  }
#line 1111 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 13: // ConstDef: IDENTIFIER ArrayExpList ASSIGN InitVal
#line 163 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                               {//TODO:ADD ARRAY SUPPORT
    yylhs.value.as < SyntaxTree::VarDef* > ()=new SyntaxTree::VarDef();
    yylhs.value.as < SyntaxTree::VarDef* > ()->is_constant = true;
    yylhs.value.as < SyntaxTree::VarDef* > ()->is_inited = true;
    yylhs.value.as < SyntaxTree::VarDef* > ()->name=yystack_[3].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::VarDef* > ()->array_length = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::VarDef* > ()->initializers = SyntaxTree::Ptr<SyntaxTree::InitVal>(yystack_[0].value.as < SyntaxTree::InitVal* > ());
    yylhs.value.as < SyntaxTree::VarDef* > ()->loc = yylhs.location;
  }
#line 1125 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 14: // VarDecl: BType VarDefList SEMICOLON
#line 174 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                  {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
    for (auto &node : yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()) {
      node->btype = yystack_[2].value.as < SyntaxTree::Type > ();
    }
  }
#line 1136 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 15: // VarDefList: VarDefList COMMA VarDef
#line 182 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                  {
    yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>(yystack_[0].value.as < SyntaxTree::VarDef* > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ();
  }
#line 1145 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 16: // VarDefList: VarDef
#line 186 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ()=SyntaxTree::PtrList<SyntaxTree::VarDef>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().push_back(SyntaxTree::Ptr<SyntaxTree::VarDef>(yystack_[0].value.as < SyntaxTree::VarDef* > ()));
  }
#line 1154 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 17: // VarDef: IDENTIFIER ArrayExpList
#line 192 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                              {
    yylhs.value.as < SyntaxTree::VarDef* > ()=new SyntaxTree::VarDef();
    yylhs.value.as < SyntaxTree::VarDef* > ()->name=yystack_[1].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::VarDef* > ()->array_length = yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::VarDef* > ()->is_inited = false;
    yylhs.value.as < SyntaxTree::VarDef* > ()->loc = yylhs.location;
  }
#line 1166 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 18: // VarDef: IDENTIFIER ArrayExpList ASSIGN InitVal
#line 199 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                                {
    yylhs.value.as < SyntaxTree::VarDef* > () = new SyntaxTree::VarDef();
    yylhs.value.as < SyntaxTree::VarDef* > ()->name = yystack_[3].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::VarDef* > ()->array_length = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::VarDef* > ()->initializers = SyntaxTree::Ptr<SyntaxTree::InitVal>(yystack_[0].value.as < SyntaxTree::InitVal* > ());
    yylhs.value.as < SyntaxTree::VarDef* > ()->is_inited = true;
    yylhs.value.as < SyntaxTree::VarDef* > ()->loc = yylhs.location;
  }
#line 1179 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 19: // ArrayExpList: ArrayExpList LBRACKET Exp RBRACKET
#line 209 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                               {
    yystack_[3].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Expr* > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ()=yystack_[3].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  }
#line 1188 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 20: // ArrayExpList: %empty
#line 213 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ()=SyntaxTree::PtrList<SyntaxTree::Expr>();
  }
#line 1196 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 21: // InitVal: Exp
#line 218 "/data/workspace/myshixun/grammar/sysyfParser.yy"
            {//TODO:CHECK?
    //TODO:Initializer cheking for scalar to array
    yylhs.value.as < SyntaxTree::InitVal* > () = new SyntaxTree::InitVal();
    yylhs.value.as < SyntaxTree::InitVal* > ()->isExp = true;
    yylhs.value.as < SyntaxTree::InitVal* > ()->elementList = SyntaxTree::PtrList<SyntaxTree::InitVal>();
    //$$->elementList = std::vector<SyntaxTree::Ptr<SyntaxTree::InitVal>>();
    yylhs.value.as < SyntaxTree::InitVal* > ()->expr = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::InitVal* > ()->loc = yylhs.location;
  }
#line 1210 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 22: // InitVal: LBRACE InitValList RBRACE
#line 227 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                             {
    yylhs.value.as < SyntaxTree::InitVal* > () = yystack_[1].value.as < SyntaxTree::InitVal* > ();
  }
#line 1218 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 23: // InitValList: CommaInitValList InitVal
#line 232 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                     {
    yystack_[1].value.as < SyntaxTree::InitVal* > ()->elementList.push_back(SyntaxTree::Ptr<SyntaxTree::InitVal>(yystack_[0].value.as < SyntaxTree::InitVal* > ()));
    yylhs.value.as < SyntaxTree::InitVal* > () = yystack_[1].value.as < SyntaxTree::InitVal* > ();
  }
#line 1227 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 24: // InitValList: %empty
#line 236 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::InitVal* > () = new SyntaxTree::InitVal();
    yylhs.value.as < SyntaxTree::InitVal* > ()->isExp = false;
    yylhs.value.as < SyntaxTree::InitVal* > ()->elementList = SyntaxTree::PtrList<SyntaxTree::InitVal>();
    //$$->elementList = std::vector<SyntaxTree::Ptr<SyntaxTree::InitVal>>();
    yylhs.value.as < SyntaxTree::InitVal* > ()->expr = nullptr;
    yylhs.value.as < SyntaxTree::InitVal* > ()->loc = yylhs.location;
  }
#line 1240 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 25: // CommaInitValList: CommaInitValList InitVal COMMA
#line 246 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                                {
    yystack_[2].value.as < SyntaxTree::InitVal* > ()->elementList.push_back(SyntaxTree::Ptr<SyntaxTree::InitVal>(yystack_[1].value.as < SyntaxTree::InitVal* > ()));
    yylhs.value.as < SyntaxTree::InitVal* > () = yystack_[2].value.as < SyntaxTree::InitVal* > ();
  }
#line 1249 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 26: // CommaInitValList: %empty
#line 250 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::InitVal* > () = new SyntaxTree::InitVal();
    yylhs.value.as < SyntaxTree::InitVal* > ()->isExp = false;
    yylhs.value.as < SyntaxTree::InitVal* > ()->elementList = SyntaxTree::PtrList<SyntaxTree::InitVal>();
    //$$->elementList = std::vector<SyntaxTree::Ptr<SyntaxTree::InitVal>>();
    yylhs.value.as < SyntaxTree::InitVal* > ()->expr = nullptr;
    yylhs.value.as < SyntaxTree::InitVal* > ()->loc = yylhs.location;
  }
#line 1262 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 27: // ExpList: CommaExpList Exp
#line 260 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                        {
    yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  }
#line 1271 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 28: // ExpList: %empty
#line 264 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = SyntaxTree::PtrList<SyntaxTree::Expr>();
  }
#line 1279 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 29: // CommaExpList: CommaExpList Exp COMMA
#line 269 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                   {
    yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Expr* > ()));
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  }
#line 1288 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 30: // CommaExpList: %empty
#line 273 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > () = SyntaxTree::PtrList<SyntaxTree::Expr>();
  }
#line 1296 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 31: // FuncFParam: BType IDENTIFIER ArrayExpList
#line 279 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                        {
  yylhs.value.as < SyntaxTree::FuncParam* > () = new SyntaxTree::FuncParam();
  yylhs.value.as < SyntaxTree::FuncParam* > ()->param_type = yystack_[2].value.as < SyntaxTree::Type > ();
  yylhs.value.as < SyntaxTree::FuncParam* > ()->name = yystack_[1].value.as < std::string > ();
  yylhs.value.as < SyntaxTree::FuncParam* > ()->array_index = yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
  yylhs.value.as < SyntaxTree::FuncParam* > ()->loc = yylhs.location;
}
#line 1308 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 32: // FuncFParam: BType IDENTIFIER LRBRACKET ArrayExpList
#line 286 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                         {
   yylhs.value.as < SyntaxTree::FuncParam* > () = new SyntaxTree::FuncParam();
   yylhs.value.as < SyntaxTree::FuncParam* > ()->param_type = yystack_[3].value.as < SyntaxTree::Type > ();
   yylhs.value.as < SyntaxTree::FuncParam* > ()->name = yystack_[2].value.as < std::string > ();
   yylhs.value.as < SyntaxTree::FuncParam* > ()->array_index = yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
   yylhs.value.as < SyntaxTree::FuncParam* > ()->array_index.insert(yylhs.value.as < SyntaxTree::FuncParam* > ()->array_index.begin(),nullptr);
   yylhs.value.as < SyntaxTree::FuncParam* > ()->loc = yylhs.location;
}
#line 1321 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 33: // FParamList: CommaFParamList FuncFParam
#line 296 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                      {
  yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ().push_back(SyntaxTree::Ptr<SyntaxTree::FuncParam>(yystack_[0].value.as < SyntaxTree::FuncParam* > ()));
  yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > () = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
}
#line 1330 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 34: // FParamList: %empty
#line 300 "/data/workspace/myshixun/grammar/sysyfParser.yy"
        {
  yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > () = SyntaxTree::PtrList<SyntaxTree::FuncParam>();
}
#line 1338 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 35: // CommaFParamList: CommaFParamList FuncFParam COMMA
#line 305 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                                {
  yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ().push_back(SyntaxTree::Ptr<SyntaxTree::FuncParam>(yystack_[1].value.as < SyntaxTree::FuncParam* > ()));
  yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > () = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
}
#line 1347 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 36: // CommaFParamList: %empty
#line 309 "/data/workspace/myshixun/grammar/sysyfParser.yy"
        {
  yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > () = SyntaxTree::PtrList<SyntaxTree::FuncParam>();
}
#line 1355 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 37: // FuncDef: BType IDENTIFIER LPARENTHESE FParamList RPARENTHESE Block
#line 313 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                                                 {
    yylhs.value.as < SyntaxTree::FuncDef* > () = new SyntaxTree::FuncDef();
    yylhs.value.as < SyntaxTree::FuncDef* > ()->ret_type = yystack_[5].value.as < SyntaxTree::Type > ();
    yylhs.value.as < SyntaxTree::FuncDef* > ()->name = yystack_[4].value.as < std::string > ();
    auto tmp = new SyntaxTree::FuncFParamList();
    tmp->params = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
    yylhs.value.as < SyntaxTree::FuncDef* > ()->param_list = SyntaxTree::Ptr<SyntaxTree::FuncFParamList>(tmp);
    yylhs.value.as < SyntaxTree::FuncDef* > ()->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>(yystack_[0].value.as < SyntaxTree::BlockStmt* > ());
    yylhs.value.as < SyntaxTree::FuncDef* > ()->loc = yylhs.location;
  }
#line 1370 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 38: // FuncDef: VOID IDENTIFIER LPARENTHESE FParamList RPARENTHESE Block
#line 323 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                                            {
    yylhs.value.as < SyntaxTree::FuncDef* > () = new SyntaxTree::FuncDef();
    yylhs.value.as < SyntaxTree::FuncDef* > ()->ret_type = SyntaxTree::Type::VOID;
    yylhs.value.as < SyntaxTree::FuncDef* > ()->name = yystack_[4].value.as < std::string > ();
    auto tmp = new SyntaxTree::FuncFParamList();
    tmp->params = yystack_[2].value.as < SyntaxTree::PtrList<SyntaxTree::FuncParam> > ();
    yylhs.value.as < SyntaxTree::FuncDef* > ()->param_list = SyntaxTree::Ptr<SyntaxTree::FuncFParamList>(tmp);
    yylhs.value.as < SyntaxTree::FuncDef* > ()->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>(yystack_[0].value.as < SyntaxTree::BlockStmt* > ());
    yylhs.value.as < SyntaxTree::FuncDef* > ()->loc = yylhs.location;
  }
#line 1385 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 39: // Block: LBRACE BlockItemList RBRACE
#line 335 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                 {
    yylhs.value.as < SyntaxTree::BlockStmt* > () = new SyntaxTree::BlockStmt();
    yylhs.value.as < SyntaxTree::BlockStmt* > ()->body = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ();
    yylhs.value.as < SyntaxTree::BlockStmt* > ()->loc = yylhs.location;
  }
#line 1395 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 40: // BlockItemList: BlockItemList BlockItem
#line 342 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                     {
    yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().insert(yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end());
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ();
  }
#line 1404 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 41: // BlockItemList: %empty
#line 346 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
  }
#line 1412 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 42: // BlockItem: VarDecl
#line 351 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                 {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1421 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 43: // BlockItem: ConstDecl
#line 355 "/data/workspace/myshixun/grammar/sysyfParser.yy"
             {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().insert(yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().end(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().begin(), yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::VarDef> > ().end());
  }
#line 1430 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 44: // BlockItem: Stmt
#line 359 "/data/workspace/myshixun/grammar/sysyfParser.yy"
        {
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > () = SyntaxTree::PtrList<SyntaxTree::Stmt>();
    yylhs.value.as < SyntaxTree::PtrList<SyntaxTree::Stmt> > ().push_back(SyntaxTree::Ptr<SyntaxTree::Stmt>(yystack_[0].value.as < SyntaxTree::Stmt* > ()));
  }
#line 1439 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 45: // Stmt: LVal ASSIGN Exp SEMICOLON
#line 365 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                              {
    auto temp = new SyntaxTree::AssignStmt();
    temp->target = SyntaxTree::Ptr<SyntaxTree::LVal>(yystack_[3].value.as < SyntaxTree::LVal* > ());
    temp->value = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Stmt* > () = temp;
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1451 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 46: // Stmt: Exp SEMICOLON
#line 372 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                 {
    auto temp = new SyntaxTree::ExprStmt();
    temp->exp = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Stmt* > () = temp;
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1462 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 47: // Stmt: RETURN OptionRet SEMICOLON
#line 378 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                              {
    auto temp = new SyntaxTree::ReturnStmt();
    temp->ret = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[1].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Stmt* > () = temp;
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1473 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 48: // Stmt: Block
#line 384 "/data/workspace/myshixun/grammar/sysyfParser.yy"
         {
    yylhs.value.as < SyntaxTree::Stmt* > () = yystack_[0].value.as < SyntaxTree::BlockStmt* > ();
  }
#line 1481 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 49: // Stmt: WHILE LPARENTHESE CondExp RPARENTHESE Stmt
#line 387 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                              {
    auto temp = new SyntaxTree::WhileStmt();
    temp->cond_exp = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->statement = SyntaxTree::Ptr<SyntaxTree::Stmt>(yystack_[0].value.as < SyntaxTree::Stmt* > ());
    yylhs.value.as < SyntaxTree::Stmt* > () = temp;
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1493 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 50: // Stmt: IfStmt
#line 394 "/data/workspace/myshixun/grammar/sysyfParser.yy"
           {
    yylhs.value.as < SyntaxTree::Stmt* > () = yystack_[0].value.as < SyntaxTree::Stmt* > ();
  }
#line 1501 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 51: // Stmt: BREAK SEMICOLON
#line 397 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                    {
    yylhs.value.as < SyntaxTree::Stmt* > () = new SyntaxTree::BreakStmt();
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1510 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 52: // Stmt: CONTINUE SEMICOLON
#line 401 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                       {
    yylhs.value.as < SyntaxTree::Stmt* > () = new SyntaxTree::ContinueStmt();
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1519 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 53: // Stmt: SEMICOLON
#line 405 "/data/workspace/myshixun/grammar/sysyfParser.yy"
             {
    yylhs.value.as < SyntaxTree::Stmt* > () = new SyntaxTree::EmptyStmt();
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1528 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 54: // IfStmt: IF LPARENTHESE CondExp RPARENTHESE Stmt
#line 411 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                               {
    auto temp = new SyntaxTree::IfStmt();
    temp->cond_exp = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->if_statement = SyntaxTree::Ptr<SyntaxTree::Stmt>(yystack_[0].value.as < SyntaxTree::Stmt* > ());
    temp->else_statement = nullptr;
    yylhs.value.as < SyntaxTree::Stmt* > () = temp;
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1541 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 55: // IfStmt: IF LPARENTHESE CondExp RPARENTHESE Stmt ELSE Stmt
#line 419 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                                      {
    auto temp = new SyntaxTree::IfStmt();
    temp->cond_exp = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[4].value.as < SyntaxTree::Expr* > ());
    temp->if_statement = SyntaxTree::Ptr<SyntaxTree::Stmt>(yystack_[2].value.as < SyntaxTree::Stmt* > ());
    temp->else_statement = SyntaxTree::Ptr<SyntaxTree::Stmt>(yystack_[0].value.as < SyntaxTree::Stmt* > ());
    yylhs.value.as < SyntaxTree::Stmt* > () = temp;
    yylhs.value.as < SyntaxTree::Stmt* > ()->loc = yylhs.location;
  }
#line 1554 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 56: // OptionRet: Exp
#line 429 "/data/workspace/myshixun/grammar/sysyfParser.yy"
             {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::Expr* > ();
  }
#line 1562 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 57: // OptionRet: %empty
#line 432 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::Expr* > () = nullptr;
  }
#line 1570 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 58: // LVal: IDENTIFIER ArrayExpList
#line 437 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                            {
    yylhs.value.as < SyntaxTree::LVal* > () = new SyntaxTree::LVal();
    yylhs.value.as < SyntaxTree::LVal* > ()->name = yystack_[1].value.as < std::string > ();
    yylhs.value.as < SyntaxTree::LVal* > ()->array_index = yystack_[0].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::LVal* > ()->loc = yylhs.location;
  }
#line 1581 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 59: // Exp: PLUS Exp
#line 449 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                        {
    auto temp = new SyntaxTree::UnaryExpr();
    temp->op = SyntaxTree::UnaryOp::PLUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1593 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 60: // Exp: MINUS Exp
#line 456 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                          {
    auto temp = new SyntaxTree::UnaryExpr();
    temp->op = SyntaxTree::UnaryOp::MINUS;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1605 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 61: // Exp: NOT Exp
#line 463 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                      {
    auto temp = new SyntaxTree::UnaryCondExpr();
    temp->op = SyntaxTree::UnaryCondOp::NOT;
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1617 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 62: // Exp: Exp PLUS Exp
#line 470 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::PLUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1630 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 63: // Exp: Exp MINUS Exp
#line 478 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                 {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MINUS;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1643 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 64: // Exp: Exp MULTIPLY Exp
#line 486 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                    {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MULTIPLY;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1656 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 65: // Exp: Exp DIVIDE Exp
#line 494 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                  {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::DIVIDE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1669 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 66: // Exp: Exp MODULO Exp
#line 502 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                  {
    auto temp = new SyntaxTree::BinaryExpr();
    temp->op = SyntaxTree::BinOp::MODULO;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1682 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 67: // Exp: LPARENTHESE Exp RPARENTHESE
#line 510 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                               {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[1].value.as < SyntaxTree::Expr* > ();
  }
#line 1690 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 68: // Exp: IDENTIFIER LPARENTHESE ExpList RPARENTHESE
#line 513 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                                               {
    auto temp = new SyntaxTree::FuncCallStmt();
    temp->name = yystack_[3].value.as < std::string > ();
    temp->params = yystack_[1].value.as < SyntaxTree::PtrList<SyntaxTree::Expr> > ();
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1702 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 69: // Exp: LVal
#line 520 "/data/workspace/myshixun/grammar/sysyfParser.yy"
        {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::LVal* > ();
  }
#line 1710 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 70: // Exp: Number
#line 523 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::Literal* > ();
  }
#line 1718 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 71: // RelExp: RelExp LT Exp
#line 528 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                    {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LT;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1731 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 72: // RelExp: RelExp LTE Exp
#line 536 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                 {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LTE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1744 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 73: // RelExp: RelExp GT Exp
#line 544 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::GT;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1757 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 74: // RelExp: RelExp GTE Exp
#line 552 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                 {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::GTE;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1770 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 75: // RelExp: Exp
#line 560 "/data/workspace/myshixun/grammar/sysyfParser.yy"
       {//FIXME:type transfer
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::Expr* > ();
  }
#line 1778 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 76: // EqExp: EqExp EQ RelExp
#line 565 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                     {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::EQ;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1791 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 77: // EqExp: EqExp NEQ RelExp
#line 573 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                   {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::NEQ;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1804 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 78: // EqExp: RelExp
#line 581 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::Expr* > ();
  }
#line 1812 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 79: // LAndExp: LAndExp LOGICAND EqExp
#line 586 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                               {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LAND;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1825 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 80: // LAndExp: EqExp
#line 594 "/data/workspace/myshixun/grammar/sysyfParser.yy"
        {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::Expr* > ();
  }
#line 1833 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 81: // LOrExp: LOrExp LOGICOR LAndExp
#line 599 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                              {
    auto temp = new SyntaxTree::BinaryCondExpr();
    temp->op = SyntaxTree::BinaryCondOp::LOR;
    temp->lhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[2].value.as < SyntaxTree::Expr* > ());
    temp->rhs = SyntaxTree::Ptr<SyntaxTree::Expr>(yystack_[0].value.as < SyntaxTree::Expr* > ());
    yylhs.value.as < SyntaxTree::Expr* > () = temp;
    yylhs.value.as < SyntaxTree::Expr* > ()->loc = yylhs.location;
  }
#line 1846 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 82: // LOrExp: LAndExp
#line 607 "/data/workspace/myshixun/grammar/sysyfParser.yy"
          {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::Expr* > ();
  }
#line 1854 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 83: // CondExp: LOrExp
#line 612 "/data/workspace/myshixun/grammar/sysyfParser.yy"
              {
    yylhs.value.as < SyntaxTree::Expr* > () = yystack_[0].value.as < SyntaxTree::Expr* > ();
  }
#line 1862 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 84: // Number: INTCONST
#line 617 "/data/workspace/myshixun/grammar/sysyfParser.yy"
                 {
    yylhs.value.as < SyntaxTree::Literal* > () = new SyntaxTree::Literal();
    yylhs.value.as < SyntaxTree::Literal* > ()->literal_type = SyntaxTree::Type::INT;
    yylhs.value.as < SyntaxTree::Literal* > ()->int_const = yystack_[0].value.as < int > ();
    yylhs.value.as < SyntaxTree::Literal* > ()->loc = yylhs.location;
  }
#line 1873 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;

  case 85: // Number: FLOATCONST
#line 623 "/data/workspace/myshixun/grammar/sysyfParser.yy"
               {
    yylhs.value.as < SyntaxTree::Literal* > () = new SyntaxTree::Literal();
    yylhs.value.as < SyntaxTree::Literal* > ()->literal_type = SyntaxTree::Type::FLOAT;
    yylhs.value.as < SyntaxTree::Literal* > ()->float_const = yystack_[0].value.as < float > ();
    yylhs.value.as < SyntaxTree::Literal* > ()->loc = yylhs.location;
  }
#line 1884 "/data/workspace/myshixun/build/sysyfParser.cpp"
    break;


#line 1888 "/data/workspace/myshixun/build/sysyfParser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  sysyfParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  sysyfParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  sysyfParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // sysyfParser::context.
  sysyfParser::context::context (const sysyfParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  sysyfParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  sysyfParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  sysyfParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char sysyfParser::yypact_ninf_ = -116;

  const signed char sysyfParser::yytable_ninf_ = -35;

  const short
  sysyfParser::yypact_[] =
  {
      -8,  -116,   -25,   -18,  -116,     9,    20,  -116,  -116,    -3,
    -116,  -116,    -5,     5,  -116,  -116,  -116,    27,   136,  -116,
      28,  -116,   138,  -116,    28,    10,  -116,    30,    39,   -18,
      29,  -116,     5,    46,   116,   119,  -116,  -116,    52,    48,
      63,   116,  -116,    52,   119,   119,   119,    62,    71,  -116,
    -116,   119,  -116,  -116,   172,  -116,    47,  -116,  -116,    55,
    -116,  -116,  -116,  -116,  -116,   155,    85,   116,    95,    96,
    -116,   119,   119,   119,   119,   119,  -116,    61,  -116,    96,
    -116,  -116,   110,    99,   119,   135,   135,  -116,  -116,  -116,
    -116,  -116,   111,   119,   127,   154,   156,  -116,    30,  -116,
    -116,  -116,  -116,  -116,   158,   104,    96,  -116,  -116,    64,
     119,   159,   172,   119,  -116,  -116,   119,  -116,  -116,   172,
       4,   122,   126,   137,   163,  -116,   165,   160,   119,   119,
     119,   119,   119,   119,   119,   119,   101,   101,  -116,   172,
     172,   172,   172,     4,     4,   122,   126,   161,  -116,   101,
    -116
  };

  const signed char
  sysyfParser::yydefact_[] =
  {
       0,    11,     0,     0,    12,     0,     0,     4,     5,     0,
       6,     7,     0,     0,     1,     2,     3,    20,     0,    16,
      36,    20,     0,    10,    36,    17,    14,     0,     0,     0,
       0,     8,     0,     0,     0,     0,    20,    15,     0,     0,
      33,     0,     9,     0,     0,     0,     0,    26,    20,    85,
      84,     0,    18,    69,    21,    70,     0,    41,    38,    20,
      35,    13,    37,    59,    60,     0,     0,     0,    30,    58,
      61,     0,     0,     0,     0,     0,    19,     0,    20,    31,
      67,    22,    23,     0,     0,    62,    63,    64,    65,    66,
      53,    39,     0,    57,     0,     0,     0,    43,     0,    42,
      48,    40,    44,    50,    69,     0,    32,    25,    68,    27,
       0,     0,    56,     0,    51,    52,     0,    46,    29,    75,
      78,    80,    82,    83,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,    72,
      73,    74,    71,    76,    77,    79,    81,    54,    49,     0,
      55
  };

  const short
  sysyfParser::yypgoto_[] =
  {
    -116,  -116,  -116,   180,   112,  -116,    -1,   162,   113,  -116,
     164,   -17,   -35,  -116,  -116,  -116,  -116,  -116,   168,  -116,
    -116,   -19,  -116,  -116,  -115,  -116,  -116,   -74,   -34,    25,
      53,    58,  -116,    75,  -116
  };

  const signed char
  sysyfParser::yydefgoto_[] =
  {
       0,     5,     6,     7,     8,    22,     9,    23,    10,    18,
      19,    25,    52,    66,    67,    83,    84,    40,    28,    29,
      11,   100,    77,   101,   102,   103,   111,    53,   119,   120,
     121,   122,   123,   124,    55
  };

  const short
  sysyfParser::yytable_[] =
  {
      54,    56,    13,   104,    30,    12,    61,    54,     1,    14,
      63,    64,    65,    20,   128,   129,   130,    70,     1,    58,
       2,   147,   148,    15,    62,    34,     4,    17,    39,     3,
      35,    69,    82,    54,   150,    21,     4,    85,    86,    87,
      88,    89,    79,   105,    41,    24,     1,   -34,     2,    35,
     109,   131,    71,    72,    73,    74,    75,     3,    38,   112,
      36,   106,   104,   104,     4,    43,    44,    45,    76,    71,
      72,    73,    74,    75,    57,   104,    98,    90,    59,    46,
      60,   118,   127,    57,    91,   -24,    92,     1,    93,    68,
      94,    48,    49,    50,   139,   140,   141,   142,     3,    95,
      96,    51,   105,   105,    78,     4,    44,    45,    81,    71,
      72,    73,    74,    75,   -28,   105,    35,    90,   108,    46,
     117,    44,    45,    57,    44,    45,    92,   107,    93,   110,
      94,    48,    49,    50,    46,   132,   133,    46,    47,    95,
      96,    51,    73,    74,    75,   113,    48,    49,    50,    48,
      49,    50,    26,    27,    31,    32,    51,   143,   144,    51,
      71,    72,    73,    74,    75,    71,    72,    73,    74,    75,
     114,   134,   115,   116,    80,   125,   138,    71,    72,    73,
      74,    75,   136,   135,   137,   149,    16,   145,   126,    97,
      99,    37,    33,   146,    42
  };

  const unsigned char
  sysyfParser::yycheck_[] =
  {
      34,    35,     3,    77,    21,    30,    41,    41,    26,     0,
      44,    45,    46,    18,    10,    11,    12,    51,    26,    38,
      28,   136,   137,     3,    43,    15,    44,    30,    29,    37,
      20,    48,    67,    67,   149,    30,    44,    71,    72,    73,
      74,    75,    59,    77,    15,    18,    26,    19,    28,    20,
      84,    47,     5,     6,     7,     8,     9,    37,    19,    93,
      30,    78,   136,   137,    44,    19,     5,     6,    21,     5,
       6,     7,     8,     9,    22,   149,    77,    16,    30,    18,
      17,    17,   116,    22,    23,    23,    25,    26,    27,    18,
      29,    30,    31,    32,   128,   129,   130,   131,    37,    38,
      39,    40,   136,   137,    49,    44,     5,     6,    23,     5,
       6,     7,     8,     9,    19,   149,    20,    16,    19,    18,
      16,     5,     6,    22,     5,     6,    25,    17,    27,    18,
      29,    30,    31,    32,    18,    13,    14,    18,    22,    38,
      39,    40,     7,     8,     9,    18,    30,    31,    32,    30,
      31,    32,    16,    17,    16,    17,    40,   132,   133,    40,
       5,     6,     7,     8,     9,     5,     6,     7,     8,     9,
      16,    45,    16,    15,    19,    16,    16,     5,     6,     7,
       8,     9,    19,    46,    19,    24,     6,   134,   113,    77,
      77,    27,    24,   135,    32
  };

  const signed char
  sysyfParser::yystos_[] =
  {
       0,    26,    28,    37,    44,    54,    55,    56,    57,    59,
      61,    73,    30,    59,     0,     3,    56,    30,    62,    63,
      18,    30,    58,    60,    18,    64,    16,    17,    71,    72,
      64,    16,    17,    71,    15,    20,    30,    63,    19,    59,
      70,    15,    60,    19,     5,     6,    18,    22,    30,    31,
      32,    40,    65,    80,    81,    87,    81,    22,    74,    30,
      17,    65,    74,    81,    81,    81,    66,    67,    18,    64,
      81,     5,     6,     7,     8,     9,    21,    75,    49,    64,
      19,    23,    65,    68,    69,    81,    81,    81,    81,    81,
      16,    23,    25,    27,    29,    38,    39,    57,    59,    61,
      74,    76,    77,    78,    80,    81,    64,    17,    19,    81,
      18,    79,    81,    18,    16,    16,    15,    16,    17,    81,
      82,    83,    84,    85,    86,    16,    86,    81,    10,    11,
      12,    47,    13,    14,    45,    46,    19,    19,    16,    81,
      81,    81,    81,    82,    82,    83,    84,    77,    77,    24,
      77
  };

  const signed char
  sysyfParser::yyr1_[] =
  {
       0,    53,    54,    55,    55,    56,    56,    56,    57,    58,
      58,    59,    59,    60,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    70,    70,    71,    71,    72,    72,    73,    73,    74,
      75,    75,    76,    76,    76,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    78,    78,    79,    79,    80,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    82,    82,    82,    82,    82,    83,    83,    83,    84,
      84,    85,    85,    86,    87,    87
  };

  const signed char
  sysyfParser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     1,     1,     1,     4,     3,
       1,     1,     1,     4,     3,     3,     1,     2,     4,     4,
       0,     1,     3,     2,     0,     3,     0,     2,     0,     3,
       0,     3,     4,     2,     0,     3,     0,     6,     6,     3,
       2,     0,     1,     1,     1,     4,     2,     3,     1,     5,
       1,     2,     2,     1,     5,     7,     1,     0,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     4,     1,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const sysyfParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "END", "ERROR", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "LTE", "GT", "GTE", "EQ", "NEQ",
  "ASSIGN", "SEMICOLON", "COMMA", "LPARENTHESE", "RPARENTHESE", "LBRACKET",
  "RBRACKET", "LBRACE", "RBRACE", "ELSE", "IF", "INT", "RETURN", "VOID",
  "WHILE", "IDENTIFIER", "FLOATCONST", "INTCONST", "LETTER", "EOL",
  "COMMENT", "BLANK", "CONST", "BREAK", "CONTINUE", "NOT", "AND", "OR",
  "MOD", "FLOAT", "LOGICAND", "LOGICOR", "LT", "STRINGCONST", "LRBRACKET",
  "UPLUS", "UMINUS", "UNOT", "$accept", "Begin", "CompUnit", "GlobalDecl",
  "ConstDecl", "ConstDefList", "BType", "ConstDef", "VarDecl",
  "VarDefList", "VarDef", "ArrayExpList", "InitVal", "InitValList",
  "CommaInitValList", "ExpList", "CommaExpList", "FuncFParam",
  "FParamList", "CommaFParamList", "FuncDef", "Block", "BlockItemList",
  "BlockItem", "Stmt", "IfStmt", "OptionRet", "LVal", "Exp", "RelExp",
  "EqExp", "LAndExp", "LOrExp", "CondExp", "Number", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  sysyfParser::yyrline_[] =
  {
       0,   106,   106,   113,   117,   123,   127,   131,   137,   144,
     148,   154,   157,   163,   174,   182,   186,   192,   199,   209,
     213,   218,   227,   232,   236,   246,   250,   260,   264,   269,
     273,   279,   286,   296,   300,   305,   309,   313,   323,   335,
     342,   346,   351,   355,   359,   365,   372,   378,   384,   387,
     394,   397,   401,   405,   411,   419,   429,   432,   437,   449,
     456,   463,   470,   478,   486,   494,   502,   510,   513,   520,
     523,   528,   536,   544,   552,   560,   565,   573,   581,   586,
     594,   599,   607,   612,   617,   623
  };

  void
  sysyfParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  sysyfParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2469 "/data/workspace/myshixun/build/sysyfParser.cpp"

#line 631 "/data/workspace/myshixun/grammar/sysyfParser.yy"


// Register errors to the driver:
void yy::sysyfParser::error (const location_type& l,
                          const std::string& m)
{
    driver.error(l, m);
}
