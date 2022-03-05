/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_USERS_GUCH8017_DOCUMENTS_BAZINGA_COMPILER_TMP_INCLUDE_BS_PARSER_H_INCLUDED
# define YY_YY_USERS_GUCH8017_DOCUMENTS_BAZINGA_COMPILER_TMP_INCLUDE_BS_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_CONST = 258,               /* INT_CONST  */
    ELSE = 259,                    /* ELSE  */
    IF = 260,                      /* IF  */
    INT = 261,                     /* INT  */
    RETURN = 262,                  /* RETURN  */
    VOID = 263,                    /* VOID  */
    WHILE = 264,                   /* WHILE  */
    ARRAY = 265,                   /* ARRAY  */
    EQ = 266,                      /* EQ  */
    NEQ = 267,                     /* NEQ  */
    GTE = 268,                     /* GTE  */
    LTE = 269,                     /* LTE  */
    ADD = 270,                     /* ADD  */
    SUB = 271,                     /* SUB  */
    MUL = 272,                     /* MUL  */
    DIV = 273,                     /* DIV  */
    LT = 274,                      /* LT  */
    GT = 275,                      /* GT  */
    ASSIN = 276,                   /* ASSIN  */
    SEMICOLON = 277,               /* SEMICOLON  */
    COMMA = 278,                   /* COMMA  */
    LPARENTHESE = 279,             /* LPARENTHESE  */
    RPARENTHESE = 280,             /* RPARENTHESE  */
    LBRACKET = 281,                /* LBRACKET  */
    RBRACKET = 282,                /* RBRACKET  */
    LBRACE = 283,                  /* LBRACE  */
    RBRACE = 284,                  /* RBRACE  */
    ID = 285,                      /* ID  */
    COMMENT = 286,                 /* COMMENT  */
    BLANK = 287,                   /* BLANK  */
    EOL = 288,                     /* EOL  */
    CONTINUE = 289,                /* CONTINUE  */
    BREAK = 290,                   /* BREAK  */
    POS = 291,                     /* POS  */
    NEG = 292,                     /* NEG  */
    NOT = 293,                     /* NOT  */
    MOD = 294,                     /* MOD  */
    AND = 295,                     /* AND  */
    OR = 296,                      /* OR  */
    CONST = 297,                   /* CONST  */
    IDENT = 298                    /* IDENT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 31 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"

    TreeNode* node;

#line 111 "/Users/guch8017/Documents/bazinga_compiler/tmp/include/bs_parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_USERS_GUCH8017_DOCUMENTS_BAZINGA_COMPILER_TMP_INCLUDE_BS_PARSER_H_INCLUDED  */
