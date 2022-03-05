/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "syntax_tree.h"
#include "ast_typedef.h"

// external functions from lex
extern int yylex();
extern void yyrestart(FILE* fp);

// external variables from lexical_analyzer module
extern int lines;
extern char *yytext;
extern int pos_end;
extern int pos_start;
extern FILE* yyin;
// Global syntax tree
SyntaxTree *syntax_tree;

// Error reporting
void yyerror(const char *s);

// Helper functions written for you with love
TreeNode *node(const char *node_name, LL_AST_TYPE type, int children_num, ...);

#line 100 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bs_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_CONST = 3,                  /* INT_CONST  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_RETURN = 7,                     /* RETURN  */
  YYSYMBOL_VOID = 8,                       /* VOID  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_ARRAY = 10,                     /* ARRAY  */
  YYSYMBOL_EQ = 11,                        /* EQ  */
  YYSYMBOL_NEQ = 12,                       /* NEQ  */
  YYSYMBOL_GTE = 13,                       /* GTE  */
  YYSYMBOL_LTE = 14,                       /* LTE  */
  YYSYMBOL_ADD = 15,                       /* ADD  */
  YYSYMBOL_SUB = 16,                       /* SUB  */
  YYSYMBOL_MUL = 17,                       /* MUL  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_LT = 19,                        /* LT  */
  YYSYMBOL_GT = 20,                        /* GT  */
  YYSYMBOL_ASSIN = 21,                     /* ASSIN  */
  YYSYMBOL_SEMICOLON = 22,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_LPARENTHESE = 24,               /* LPARENTHESE  */
  YYSYMBOL_RPARENTHESE = 25,               /* RPARENTHESE  */
  YYSYMBOL_LBRACKET = 26,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 27,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 28,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 29,                    /* RBRACE  */
  YYSYMBOL_ID = 30,                        /* ID  */
  YYSYMBOL_COMMENT = 31,                   /* COMMENT  */
  YYSYMBOL_BLANK = 32,                     /* BLANK  */
  YYSYMBOL_EOL = 33,                       /* EOL  */
  YYSYMBOL_CONTINUE = 34,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 35,                     /* BREAK  */
  YYSYMBOL_POS = 36,                       /* POS  */
  YYSYMBOL_NEG = 37,                       /* NEG  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_MOD = 39,                       /* MOD  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_OR = 41,                        /* OR  */
  YYSYMBOL_CONST = 42,                     /* CONST  */
  YYSYMBOL_IDENT = 43,                     /* IDENT  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_comp_unit = 46,                 /* comp_unit  */
  YYSYMBOL_decl = 47,                      /* decl  */
  YYSYMBOL_const_decl = 48,                /* const_decl  */
  YYSYMBOL_const_defs = 49,                /* const_defs  */
  YYSYMBOL_const_def = 50,                 /* const_def  */
  YYSYMBOL_const_pointer = 51,             /* const_pointer  */
  YYSYMBOL_const_init_val = 52,            /* const_init_val  */
  YYSYMBOL_const_init_vals = 53,           /* const_init_vals  */
  YYSYMBOL_var_decl = 54,                  /* var_decl  */
  YYSYMBOL_var_defs = 55,                  /* var_defs  */
  YYSYMBOL_var_def = 56,                   /* var_def  */
  YYSYMBOL_init_val = 57,                  /* init_val  */
  YYSYMBOL_init_vals = 58,                 /* init_vals  */
  YYSYMBOL_func_def = 59,                  /* func_def  */
  YYSYMBOL_funcf_params = 60,              /* funcf_params  */
  YYSYMBOL_funcf_param = 61,               /* funcf_param  */
  YYSYMBOL_block = 62,                     /* block  */
  YYSYMBOL_block_items = 63,               /* block_items  */
  YYSYMBOL_block_item = 64,                /* block_item  */
  YYSYMBOL_stmt = 65,                      /* stmt  */
  YYSYMBOL_assign_stmt = 66,               /* assign_stmt  */
  YYSYMBOL_lval_addr = 67,                 /* lval_addr  */
  YYSYMBOL_exp_stmt = 68,                  /* exp_stmt  */
  YYSYMBOL_if_stmt = 69,                   /* if_stmt  */
  YYSYMBOL_iter_stmt = 70,                 /* iter_stmt  */
  YYSYMBOL_break_stmt = 71,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 72,             /* continue_stmt  */
  YYSYMBOL_return_stmt = 73,               /* return_stmt  */
  YYSYMBOL_exp = 74,                       /* exp  */
  YYSYMBOL_cond = 75,                      /* cond  */
  YYSYMBOL_lval = 76,                      /* lval  */
  YYSYMBOL_pointer = 77,                   /* pointer  */
  YYSYMBOL_primary_exp = 78,               /* primary_exp  */
  YYSYMBOL_number = 79,                    /* number  */
  YYSYMBOL_unary_op = 80,                  /* unary_op  */
  YYSYMBOL_unary_exp = 81,                 /* unary_exp  */
  YYSYMBOL_func_call = 82,                 /* func_call  */
  YYSYMBOL_func_rparams = 83,              /* func_rparams  */
  YYSYMBOL_mulexp = 84,                    /* mulexp  */
  YYSYMBOL_addexp = 85,                    /* addexp  */
  YYSYMBOL_relexp = 86,                    /* relexp  */
  YYSYMBOL_eqexp = 87,                     /* eqexp  */
  YYSYMBOL_landexp = 88,                   /* landexp  */
  YYSYMBOL_lorexp = 89,                    /* lorexp  */
  YYSYMBOL_const_exp = 90                  /* const_exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  184

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    51,    54,    57,    60,    64,    67,    71,
      76,    79,    83,    86,    90,    93,    96,    99,   102,   106,
     109,   113,   117,   120,   124,   127,   130,   133,   137,   140,
     143,   147,   150,   154,   157,   160,   163,   167,   170,   174,
     177,   180,   184,   187,   191,   194,   198,   201,   205,   208,
     211,   214,   217,   220,   223,   226,   229,   233,   236,   239,
     242,   245,   248,   251,   254,   257,   260,   263,   266,   270,
     274,   277,   281,   284,   288,   291,   294,   298,   302,   303,
     304,   306,   309,   312,   315,   318,   322,   325,   329,   332,
     335,   338,   342,   345,   348,   352,   355,   358,   361,   364,
     368,   371,   374,   378,   381,   385,   388,   392
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT_CONST", "ELSE",
  "IF", "INT", "RETURN", "VOID", "WHILE", "ARRAY", "EQ", "NEQ", "GTE",
  "LTE", "ADD", "SUB", "MUL", "DIV", "LT", "GT", "ASSIN", "SEMICOLON",
  "COMMA", "LPARENTHESE", "RPARENTHESE", "LBRACKET", "RBRACKET", "LBRACE",
  "RBRACE", "ID", "COMMENT", "BLANK", "EOL", "CONTINUE", "BREAK", "POS",
  "NEG", "NOT", "MOD", "AND", "OR", "CONST", "IDENT", "$accept", "program",
  "comp_unit", "decl", "const_decl", "const_defs", "const_def",
  "const_pointer", "const_init_val", "const_init_vals", "var_decl",
  "var_defs", "var_def", "init_val", "init_vals", "func_def",
  "funcf_params", "funcf_param", "block", "block_items", "block_item",
  "stmt", "assign_stmt", "lval_addr", "exp_stmt", "if_stmt", "iter_stmt",
  "break_stmt", "continue_stmt", "return_stmt", "exp", "cond", "lval",
  "pointer", "primary_exp", "number", "unary_op", "unary_exp", "func_call",
  "func_rparams", "mulexp", "addexp", "relexp", "eqexp", "landexp",
  "lorexp", "const_exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
#endif

#define YYPACT_NINF (-127)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,   -30,   -22,    23,    43,    18,  -127,  -127,  -127,  -127,
     110,   107,  -127,    26,   -10,  -127,  -127,  -127,   180,     5,
      37,    42,  -127,    11,    33,    71,   145,  -127,  -127,  -127,
    -127,    37,    83,  -127,    40,  -127,  -127,  -127,  -127,  -127,
      37,  -127,  -127,    51,   157,    38,    56,    99,  -127,   157,
      87,   180,    82,  -127,    56,   100,   183,    96,  -127,   -10,
      79,  -127,  -127,    -6,   200,    37,  -127,  -127,    37,    37,
      37,    37,    37,   127,     3,  -127,   152,    56,   125,  -127,
    -127,    56,   150,  -127,  -127,   183,  -127,  -127,   180,  -127,
    -127,  -127,   134,   137,  -127,  -127,  -127,    51,    51,   135,
     146,    11,   117,   156,  -127,  -127,   162,   167,   114,  -127,
    -127,    67,  -127,  -127,  -127,   166,  -127,  -127,  -127,  -127,
    -127,  -127,   172,  -127,  -127,  -127,  -127,  -127,  -127,    77,
    -127,  -127,    37,  -127,   135,  -127,    37,  -127,   175,    37,
    -127,  -127,   181,  -127,  -127,    37,  -127,   183,  -127,  -127,
    -127,   184,   157,    74,   165,   170,   164,  -127,   187,   191,
    -127,   147,    37,    37,    37,    37,    37,    37,    37,    37,
     147,  -127,   202,   157,   157,   157,   157,    74,    74,   165,
     170,  -127,   147,  -127
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     2,     5,     7,     8,     6,
      24,     0,    22,     0,     0,     1,     3,     4,     0,     0,
       0,    26,    21,     0,     0,     0,     0,    11,    77,    78,
      79,     0,     0,    80,    70,    25,    28,    75,    81,    76,
       0,    88,    83,    92,    68,     0,     0,     0,    37,   107,
       0,     0,    24,    23,     0,     0,     0,     0,     9,     0,
       0,    29,    31,     0,     0,     0,    71,    82,     0,     0,
       0,     0,     0,    39,     0,    34,     0,     0,    15,    27,
      33,     0,     0,    12,    16,     0,    10,    74,     0,    30,
      84,    86,     0,     0,    89,    90,    91,    93,    94,    40,
       0,     0,     0,     0,    59,    42,     0,     0,    70,    46,
      50,     0,    44,    47,    48,     0,    49,    51,    52,    53,
      54,    55,     0,    38,    36,    14,    35,    17,    19,     0,
      13,    32,     0,    85,    72,    41,     0,    66,     0,     0,
      65,    64,    71,    43,    45,     0,    60,     0,    18,    87,
      73,     0,    95,   100,   103,   105,    69,    67,     0,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,    61,    97,    99,    98,    96,   101,   102,   104,
     106,    63,     0,    62
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,  -127,  -127,   113,  -127,  -127,   155,   -21,   -80,  -127,
    -127,  -127,   194,   -29,  -127,   214,   196,   151,   -26,  -127,
     111,  -126,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
     -17,    89,  -127,   -92,  -127,  -127,  -127,     9,  -127,  -127,
     120,   -20,    34,    61,    62,  -127,   210
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,   109,     7,    26,    27,    21,    83,   129,
       8,    11,    12,    35,    63,     9,    47,    48,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   151,    37,    66,    38,    39,    40,    41,    42,    92,
      43,    44,   153,   154,   155,   156,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    36,   128,    62,    57,   130,    28,   135,   100,   101,
     102,    45,   103,    10,    60,    36,   142,    88,    29,    30,
      75,    13,    79,    89,     1,   104,     2,    31,    80,    14,
      46,    74,   105,    25,    36,   172,    49,   106,   107,    45,
      28,    33,   150,    15,   181,     3,   108,    91,    93,    67,
      24,   124,    29,    30,    52,   126,   183,   125,    54,   131,
       3,    31,    49,    51,    64,    49,    65,   160,    68,    69,
      28,    36,   100,   101,   102,    33,   103,    94,    95,    96,
      34,    73,    29,    30,    74,   138,    28,   162,   163,   104,
      70,    31,    56,   164,   165,    74,   143,    20,    29,    30,
     147,   106,   107,    18,    87,    33,   148,    31,    20,     3,
     108,    32,    61,     6,    78,   149,   152,    85,    16,   152,
      28,    33,    76,    76,    77,    81,    34,    49,   159,    22,
      23,    18,    29,    30,    19,   -57,    20,    99,    64,   137,
      65,    31,   173,   174,   175,   176,   152,   152,   152,   152,
      28,    20,   100,    28,   102,    33,   103,   132,    45,   133,
      34,    65,    29,    30,   134,    29,    30,    58,    59,   104,
     136,    31,    71,    72,    31,    74,   166,   167,    82,   127,
     139,   106,   107,    28,   140,    33,    28,   145,    33,   141,
     108,    97,    98,    34,   146,    29,    30,   157,    29,    30,
     177,   178,   -58,    28,    31,   169,   182,    31,    32,   161,
     168,    82,   170,   171,    86,    29,    30,    53,    33,    17,
      55,    33,   144,    34,    31,    90,    34,   123,   158,   179,
      50,   180,     0,     0,     0,     0,     0,     0,    33,     0,
       0,     0,     0,    34
};

static const yytype_int16 yycheck[] =
{
      20,    18,    82,    32,    25,    85,     3,    99,     5,     6,
       7,     6,     9,    43,    31,    32,   108,    23,    15,    16,
      46,    43,    51,    29,     6,    22,     8,    24,    54,     6,
      25,    28,    29,    43,    51,   161,    56,    34,    35,     6,
       3,    38,   134,     0,   170,    42,    43,    64,    65,    40,
      24,    77,    15,    16,    43,    81,   182,    78,    25,    88,
      42,    24,    82,    21,    24,    85,    26,   147,    17,    18,
       3,    88,     5,     6,     7,    38,     9,    68,    69,    70,
      43,    43,    15,    16,    28,   102,     3,    13,    14,    22,
      39,    24,    21,    19,    20,    28,    29,    26,    15,    16,
      23,    34,    35,    21,    25,    38,    29,    24,    26,    42,
      43,    28,    29,     0,    27,   132,   136,    21,     5,   139,
       3,    38,    23,    23,    25,    25,    43,   147,   145,    22,
      23,    21,    15,    16,    24,    21,    26,    10,    24,    22,
      26,    24,   162,   163,   164,   165,   166,   167,   168,   169,
       3,    26,     5,     3,     7,    38,     9,    23,     6,    25,
      43,    26,    15,    16,    27,    15,    16,    22,    23,    22,
      24,    24,    15,    16,    24,    28,    11,    12,    28,    29,
      24,    34,    35,     3,    22,    38,     3,    21,    38,    22,
      43,    71,    72,    43,    22,    15,    16,    22,    15,    16,
     166,   167,    21,     3,    24,    41,     4,    24,    28,    25,
      40,    28,    25,    22,    59,    15,    16,    23,    38,     5,
      24,    38,   111,    43,    24,    25,    43,    76,   139,   168,
      20,   169,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     8,    42,    45,    46,    47,    48,    54,    59,
      43,    55,    56,    43,     6,     0,    47,    59,    21,    24,
      26,    51,    22,    23,    24,    43,    49,    50,     3,    15,
      16,    24,    28,    38,    43,    57,    74,    76,    78,    79,
      80,    81,    82,    84,    85,     6,    25,    60,    61,    85,
      90,    21,    43,    56,    25,    60,    21,    51,    22,    23,
      74,    29,    57,    58,    24,    26,    77,    81,    17,    18,
      39,    15,    16,    43,    28,    62,    23,    25,    27,    57,
      62,    25,    28,    52,    90,    21,    50,    25,    23,    29,
      25,    74,    83,    74,    81,    81,    81,    84,    84,    10,
       5,     6,     7,     9,    22,    29,    34,    35,    43,    47,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    61,    62,    51,    62,    29,    52,    53,
      52,    57,    23,    25,    27,    77,    24,    22,    74,    24,
      22,    22,    77,    29,    64,    21,    22,    23,    29,    74,
      77,    75,    85,    86,    87,    88,    89,    22,    75,    74,
      52,    25,    13,    14,    19,    20,    11,    12,    40,    41,
      25,    22,    65,    85,    85,    85,    85,    86,    86,    87,
      88,    65,     4,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    46,    46,    47,    47,    48,
      49,    49,    50,    50,    51,    51,    52,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    59,    59,    60,    60,    61,
      61,    61,    62,    62,    63,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    66,    67,    67,    68,
      68,    69,    69,    70,    71,    72,    73,    73,    74,    75,
      76,    76,    77,    77,    78,    78,    78,    79,    80,    80,
      80,    81,    81,    81,    82,    82,    83,    83,    84,    84,
      84,    84,    85,    85,    85,    86,    86,    86,    86,    86,
      87,    87,    87,    88,    88,    89,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     1,     4,
       3,     1,     3,     4,     4,     3,     1,     2,     3,     1,
       3,     3,     1,     3,     1,     3,     2,     4,     1,     2,
       3,     1,     3,     5,     5,     6,     6,     1,     3,     2,
       3,     4,     2,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     2,     1,
       2,     5,     7,     5,     2,     2,     2,     3,     1,     1,
       1,     2,     3,     4,     3,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     3,     4,     1,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: comp_unit  */
#line 49 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                   {(yyval.node)=node("program",AST_program,1,(yyvsp[0].node)); syntax_tree->root=(yyval.node);}
#line 1319 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 3: /* comp_unit: comp_unit decl  */
#line 51 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                           {
                (yyval.node)=node("comp_unit",AST_comp_unit,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1327 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 4: /* comp_unit: comp_unit func_def  */
#line 54 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                               {
                (yyval.node)=node("comp_unit",AST_comp_unit,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1335 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 5: /* comp_unit: decl  */
#line 57 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                 {
                (yyval.node)=node("comp_unit",AST_comp_unit,1,(yyvsp[0].node));
            }
#line 1343 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 6: /* comp_unit: func_def  */
#line 60 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                    {
                (yyval.node)=node("comp_unit",AST_comp_unit,1,(yyvsp[0].node));
            }
#line 1351 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 7: /* decl: const_decl  */
#line 64 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                       {
                (yyval.node)=node("decl",AST_decl,1,(yyvsp[0].node));
            }
#line 1359 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 8: /* decl: var_decl  */
#line 67 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("decl",AST_decl,1,(yyvsp[0].node));
            }
#line 1367 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 9: /* const_decl: CONST INT const_defs SEMICOLON  */
#line 71 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                          {
                (yyval.node)=node("const_decl",AST_const_decl,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1375 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 10: /* const_defs: const_defs COMMA const_def  */
#line 76 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                      {
                (yyval.node)=node("const_defs",AST_const_defs,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1383 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 11: /* const_defs: const_def  */
#line 79 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                      {
                (yyval.node)=node("const_defs",AST_const_defs,1,(yyvsp[0].node));
            }
#line 1391 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 12: /* const_def: IDENT ASSIN const_init_val  */
#line 83 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                      {
                (yyval.node)=node("const_def",AST_const_def,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1399 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 13: /* const_def: IDENT const_pointer ASSIN const_init_val  */
#line 86 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                    {
                (yyval.node)=node("const_def",AST_const_def,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1407 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 14: /* const_pointer: LBRACKET const_exp RBRACKET const_pointer  */
#line 90 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                       {
                (yyval.node)=node("const_pointer",AST_const_pointer,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1415 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 15: /* const_pointer: LBRACKET const_exp RBRACKET  */
#line 93 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                       {
                (yyval.node)=node("const_pointer",AST_const_pointer,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1423 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 16: /* const_init_val: const_exp  */
#line 96 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("const_init_val",AST_const_init_val,1,(yyvsp[0].node));
            }
#line 1431 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 17: /* const_init_val: LBRACE RBRACE  */
#line 99 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("const_init_val",AST_const_init_val,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1439 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 18: /* const_init_val: LBRACE const_init_vals RBRACE  */
#line 102 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                         {
                (yyval.node)=node("const_init_val",AST_const_init_val,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1447 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 19: /* const_init_vals: const_init_val  */
#line 106 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                {
                (yyval.node)=node("const_init_vals",AST_const_init_vals,1,(yyvsp[0].node));
            }
#line 1455 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 20: /* const_init_vals: const_init_vals COMMA const_init_val  */
#line 109 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                {
                (yyval.node)=node("const_init_vals",AST_const_init_vals,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1463 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 21: /* var_decl: INT var_defs SEMICOLON  */
#line 113 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                  {
                (yyval.node)=node("var_decl",AST_var_decl,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1471 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 22: /* var_defs: var_def  */
#line 117 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                    {
                (yyval.node)=node("var_defs",AST_var_defs,1,(yyvsp[0].node));
            }
#line 1479 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 23: /* var_defs: var_defs COMMA var_def  */
#line 120 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                  {
                (yyval.node)=node("var_defs",AST_var_defs,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1487 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 24: /* var_def: IDENT  */
#line 124 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("var_def",AST_var_def,1,(yyvsp[0].node));
            }
#line 1495 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 25: /* var_def: IDENT ASSIN init_val  */
#line 127 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                 {
            	(yyval.node)=node("var_def",AST_var_def,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1503 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 26: /* var_def: IDENT const_pointer  */
#line 130 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                {
                (yyval.node)=node("var_def",AST_var_def,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1511 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 27: /* var_def: IDENT const_pointer ASSIN init_val  */
#line 133 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                              {
                (yyval.node)=node("var_def",AST_var_def,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1519 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 28: /* init_val: exp  */
#line 137 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
               {
                (yyval.node)=node("init_val",AST_init_val,1,(yyvsp[0].node));
            }
#line 1527 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 29: /* init_val: LBRACE RBRACE  */
#line 140 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("init_val",AST_init_val,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1535 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 30: /* init_val: LBRACE init_vals RBRACE  */
#line 143 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                   {
                (yyval.node)=node("init_val",AST_init_val,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1543 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 31: /* init_vals: init_val  */
#line 147 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("init_vals",AST_init_vals,1,(yyvsp[0].node));
            }
#line 1551 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 32: /* init_vals: init_vals COMMA init_val  */
#line 150 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                    {
                (yyval.node)=node("const_init_vals",AST_const_init_vals,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1559 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 33: /* func_def: VOID IDENT LPARENTHESE RPARENTHESE block  */
#line 154 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                    {
                (yyval.node)=node("func_def",AST_func_def,5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1567 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 34: /* func_def: INT IDENT LPARENTHESE RPARENTHESE block  */
#line 157 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                   {
                (yyval.node)=node("func_def",AST_func_def,5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1575 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 35: /* func_def: VOID IDENT LPARENTHESE funcf_params RPARENTHESE block  */
#line 160 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                                 {
                (yyval.node)=node("func_def",AST_func_def,6,(yyvsp[-5].node),(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1583 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 36: /* func_def: INT IDENT LPARENTHESE funcf_params RPARENTHESE block  */
#line 163 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                                {
                (yyval.node)=node("func_def",AST_func_def,6,(yyvsp[-5].node),(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1591 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 37: /* funcf_params: funcf_param  */
#line 167 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("funcf_params",AST_funcf_params,1,(yyvsp[0].node));
            }
#line 1599 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 38: /* funcf_params: funcf_params COMMA funcf_param  */
#line 170 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                          {
                (yyval.node)=node("funcf_params",AST_funcf_params,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1607 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 39: /* funcf_param: INT IDENT  */
#line 174 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("funcf_param",AST_funcf_param,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1615 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 40: /* funcf_param: INT IDENT ARRAY  */
#line 177 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                            {
                (yyval.node)=node("funcf_param",AST_funcf_param,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1623 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 41: /* funcf_param: INT IDENT ARRAY pointer  */
#line 180 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                   {
                (yyval.node)=node("funcf_param",AST_funcf_param,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1631 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 42: /* block: LBRACE RBRACE  */
#line 184 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("block",AST_block,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1639 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 43: /* block: LBRACE block_items RBRACE  */
#line 187 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                     {
                (yyval.node)=node("block",AST_block,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1647 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 44: /* block_items: block_item  */
#line 191 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                      {
                (yyval.node)=node("block_items",AST_block_items,1,(yyvsp[0].node));
            }
#line 1655 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 45: /* block_items: block_items block_item  */
#line 194 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                  {
                (yyval.node)=node("block_items",AST_block_items,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1663 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 46: /* block_item: decl  */
#line 198 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                {
                (yyval.node)=node("block_item",AST_block_item,1,(yyvsp[0].node));
            }
#line 1671 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 47: /* block_item: stmt  */
#line 201 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                {
                (yyval.node)=node("block_item",AST_block_item,1,(yyvsp[0].node));
            }
#line 1679 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 48: /* stmt: assign_stmt  */
#line 205 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                       {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1687 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 49: /* stmt: exp_stmt  */
#line 208 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                    {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1695 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 50: /* stmt: block  */
#line 211 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                 {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1703 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 51: /* stmt: if_stmt  */
#line 214 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                   {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1711 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 52: /* stmt: iter_stmt  */
#line 217 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1719 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 53: /* stmt: break_stmt  */
#line 220 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                      {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1727 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 54: /* stmt: continue_stmt  */
#line 223 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1735 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 55: /* stmt: return_stmt  */
#line 226 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                       {
                (yyval.node)=node("stmt",AST_stmt,1,(yyvsp[0].node));
            }
#line 1743 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 56: /* assign_stmt: lval_addr ASSIN exp SEMICOLON  */
#line 229 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                         {
                (yyval.node)=node("assign_stmt",AST_assign_stmt,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1751 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 57: /* lval_addr: IDENT  */
#line 233 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                 {
                (yyval.node)=node("lval",AST_lval,1,(yyvsp[0].node));
            }
#line 1759 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 58: /* lval_addr: IDENT pointer  */
#line 236 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("lval",AST_lval,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1767 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 59: /* exp_stmt: SEMICOLON  */
#line 239 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("exp_stmt",AST_exp_stmt,1,(yyvsp[0].node));
            }
#line 1775 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 60: /* exp_stmt: exp SEMICOLON  */
#line 242 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("exp_stmt",AST_exp_stmt,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1783 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 61: /* if_stmt: IF LPARENTHESE cond RPARENTHESE stmt  */
#line 245 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                {
                (yyval.node)=node("if_stmt",AST_if_stmt,5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1791 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 62: /* if_stmt: IF LPARENTHESE cond RPARENTHESE stmt ELSE stmt  */
#line 248 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                          {
                (yyval.node)=node("if_else_stmt",AST_if_stmt,7,(yyvsp[-6].node),(yyvsp[-5].node),(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1799 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 63: /* iter_stmt: WHILE LPARENTHESE cond RPARENTHESE stmt  */
#line 251 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                   {
                (yyval.node)=node("iter_stmt",AST_iter_stmt,5,(yyvsp[-4].node),(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1807 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 64: /* break_stmt: BREAK SEMICOLON  */
#line 254 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                           {
                (yyval.node)=node("break_stmt",AST_break_stmt,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1815 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 65: /* continue_stmt: CONTINUE SEMICOLON  */
#line 257 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                {
                (yyval.node)=node("continue_stmt",AST_continue_stmt,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1823 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 66: /* return_stmt: RETURN SEMICOLON  */
#line 260 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                            {
                (yyval.node)=node("return_stmt",AST_return_stmt,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1831 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 67: /* return_stmt: RETURN exp SEMICOLON  */
#line 263 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                {
                (yyval.node)=node("return_stmt",AST_return_stmt,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1839 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 68: /* exp: addexp  */
#line 266 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("exp",AST_exp,1,(yyvsp[0].node));
            }
#line 1847 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 69: /* cond: lorexp  */
#line 270 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("cond",AST_cond,1,(yyvsp[0].node));
            }
#line 1855 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 70: /* lval: IDENT  */
#line 274 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                 {
                (yyval.node)=node("lval",AST_lval,1,(yyvsp[0].node));
            }
#line 1863 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 71: /* lval: IDENT pointer  */
#line 277 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                         {
                (yyval.node)=node("lval",AST_lval,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1871 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 72: /* pointer: LBRACKET exp RBRACKET  */
#line 281 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                 {
                (yyval.node)=node("pointer",AST_pointer,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1879 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 73: /* pointer: LBRACKET exp RBRACKET pointer  */
#line 284 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                         {
                (yyval.node)=node("pointer",AST_pointer,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1887 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 74: /* primary_exp: LPARENTHESE exp RPARENTHESE  */
#line 288 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                       {
                (yyval.node)=node("primary_exp",AST_primary_exp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1895 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 75: /* primary_exp: lval  */
#line 291 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                {
                (yyval.node)=node("primary_exp",AST_primary_exp,1,(yyvsp[0].node));
            }
#line 1903 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 76: /* primary_exp: number  */
#line 294 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("primary_exp",AST_primary_exp,1,(yyvsp[0].node));
            }
#line 1911 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 77: /* number: INT_CONST  */
#line 298 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("number",AST_number,1,(yyvsp[0].node));
            }
#line 1919 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 78: /* unary_op: ADD  */
#line 302 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                { (yyval.node)=node("unary_op", AST_unary_op, 1, (yyvsp[0].node)); }
#line 1925 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 79: /* unary_op: SUB  */
#line 303 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                { (yyval.node)=node("unary_op", AST_unary_op, 1, (yyvsp[0].node)); }
#line 1931 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 80: /* unary_op: NOT  */
#line 304 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                { (yyval.node)=node("unary_op", AST_unary_op, 1, (yyvsp[0].node)); }
#line 1937 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 81: /* unary_exp: primary_exp  */
#line 306 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                       {
                (yyval.node)=node("unary_exp",AST_unary_exp,1,(yyvsp[0].node));
            }
#line 1945 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 82: /* unary_exp: unary_op unary_exp  */
#line 309 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                              {
                (yyval.node)=node("unary_exp",AST_unary_exp,2,(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1953 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 83: /* unary_exp: func_call  */
#line 312 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("unary_exp", AST_unary_exp, 1, (yyvsp[0].node));
            }
#line 1961 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 84: /* func_call: IDENT LPARENTHESE RPARENTHESE  */
#line 315 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                         {
                (yyval.node)=node("func_call",AST_func_call,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1969 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 85: /* func_call: IDENT LPARENTHESE func_rparams RPARENTHESE  */
#line 318 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                                      {
                (yyval.node)=node("func_call",AST_func_call,4,(yyvsp[-3].node),(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1977 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 86: /* func_rparams: exp  */
#line 322 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                 {
                (yyval.node)=node("func_rparams",AST_func_rparams,1,(yyvsp[0].node));
            }
#line 1985 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 87: /* func_rparams: func_rparams COMMA exp  */
#line 325 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                  {
                (yyval.node)=node("func_rparams",AST_func_rparams,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 1993 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 88: /* mulexp: unary_exp  */
#line 329 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                     {
                (yyval.node)=node("mulexp",AST_mulexp,1,(yyvsp[0].node));
            }
#line 2001 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 89: /* mulexp: mulexp MUL unary_exp  */
#line 332 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                {
                (yyval.node)=node("mulexp",AST_mulexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2009 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 90: /* mulexp: mulexp DIV unary_exp  */
#line 335 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                {
                (yyval.node)=node("mulexp",AST_mulexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2017 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 91: /* mulexp: mulexp MOD unary_exp  */
#line 338 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                                {
                (yyval.node)=node("mulexp",AST_mulexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2025 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 92: /* addexp: mulexp  */
#line 342 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("addexp",AST_addexp,1,(yyvsp[0].node));
            }
#line 2033 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 93: /* addexp: addexp ADD mulexp  */
#line 345 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                             {
                (yyval.node)=node("addexp",AST_addexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2041 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 94: /* addexp: addexp SUB mulexp  */
#line 348 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                             {
                (yyval.node)=node("addexp",AST_addexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2049 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 95: /* relexp: addexp  */
#line 352 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("relexp",AST_relexp,1,(yyvsp[0].node));
            }
#line 2057 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 96: /* relexp: relexp GT addexp  */
#line 355 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                            {
                (yyval.node)=node("relexp",AST_relexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2065 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 97: /* relexp: relexp GTE addexp  */
#line 358 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                             {
                (yyval.node)=node("relexp",AST_relexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2073 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 98: /* relexp: relexp LT addexp  */
#line 361 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                            {
                (yyval.node)=node("relexp",AST_relexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2081 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 99: /* relexp: relexp LTE addexp  */
#line 364 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                             {
                (yyval.node)=node("relexp",AST_relexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2089 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 100: /* eqexp: relexp  */
#line 368 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("eqexp",AST_eqexp,1,(yyvsp[0].node));
            }
#line 2097 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 101: /* eqexp: eqexp EQ relexp  */
#line 371 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                           {
                (yyval.node)=node("eqexp",AST_eqexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2105 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 102: /* eqexp: eqexp NEQ relexp  */
#line 374 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                            {
                (yyval.node)=node("eqexp",AST_eqexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2113 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 103: /* landexp: eqexp  */
#line 378 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                 {
                (yyval.node)=node("landexp",AST_landexp,1,(yyvsp[0].node));
            }
#line 2121 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 104: /* landexp: landexp AND eqexp  */
#line 381 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                             {
                (yyval.node)=node("landexp",AST_landexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2129 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 105: /* lorexp: landexp  */
#line 385 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                   {
                (yyval.node)=node("lorexp",AST_lorexp,1,(yyvsp[0].node));
            }
#line 2137 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 106: /* lorexp: lorexp OR landexp  */
#line 388 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                             {
                (yyval.node)=node("lorexp",AST_lorexp,3,(yyvsp[-2].node),(yyvsp[-1].node),(yyvsp[0].node));
            }
#line 2145 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;

  case 107: /* const_exp: addexp  */
#line 392 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"
                  {
                (yyval.node)=node("const_exp",AST_const_exp,1,(yyvsp[0].node));
            }
#line 2153 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"
    break;


#line 2157 "/Users/guch8017/Documents/bazinga_compiler/tmp/bs_parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 395 "/Users/guch8017/Documents/bazinga_compiler/src/parser/parser.y"

/// The error reporting function.
void yyerror(const char *s)
{
    fprintf(stderr, "error at line %d column %d: %s, yytext = %s\n", lines, pos_start, s, yytext);
}

/// Parse input from file `input_path`, and prints the parsing results
/// to stdout.  If input_path is NULL, read from stdin.
///
/// This function initializes essential states before running yyparse().
SyntaxTree *parse(const char *input_path)
{
    yydebug = 0;
    if (input_path != NULL) {
        if (!(yyin = fopen(input_path, "r"))) {
            fprintf(stderr, "[ERR] Open input file %s failed.\n", input_path);
            exit(1);
        }
    } else {
        yyin = stdin;
    }

    lines = pos_start = pos_end = 1;
    syntax_tree = new SyntaxTree();
    yyrestart(yyin);
    yyparse();
    return syntax_tree;
}

/// A helper function to quickly construct a tree node.
///
/// e.g.
///     $$ = node("program", 1, $1);
///     $$ = node("local-declarations", 0);
TreeNode *node(const char *name, LL_AST_TYPE type, int children_num, ...)
{
    TreeNode *p = new TreeNode(name, type);
    TreeNode *child;
    if (children_num == 0) {
        child = new TreeNode("epsilon", AST_EMPTY);
        p->add_child(child);
    } else {
        va_list ap;
        va_start(ap, children_num);
        for (int i = 0; i < children_num; ++i) {
            child = va_arg(ap, TreeNode *);
            p->add_child(child);
        }
        va_end(ap);
    }
    return p;
}
