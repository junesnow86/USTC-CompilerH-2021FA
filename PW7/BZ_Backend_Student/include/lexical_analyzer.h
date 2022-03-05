#ifndef _LEXICAL_ANALYZER_H_
#define _LEXICAL_ANALYZER_H_

#include <stdio.h>
#include <vector>

// extern int fileno (FILE *__stream) __THROW __wur;

#ifndef YYTOKENTYPE
#define YYTOKENTYPE
typedef enum cminus_token_type {
    //运算
    ADD = 259,
    SUB = 260,
    MUL = 261,
    DIV = 262,
    LT = 263,
    LTE = 264,
    GT = 265,
    GTE = 266,
    EQ = 267,
    NEQ = 268,
    ASSIN = 269,
    MOD = 293,
    NOT = 296,
    AND = 297,
    OR = 298,
    //符号
    SEMICOLON = 270,
    COMMA = 271,
    LPARENTHESE = 272,
    RPARENTHESE = 273,
    LBRACKET = 274,
    RBRACKET = 275,
    LBRACE = 276,
    RBRACE = 277,
    //关键字
    ELSE = 278,
    IF = 279,
    INT = 280,
    CONTINUE = 281,
    RETURN = 282,
    VOID = 283,
    WHILE = 284,
    BREAK = 294,
    CONST = 295,
    //ID和NUM
    IDENT = 285,
    INT_CONST = 286,
    FLOATPOINT = 287,
    ARRAY = 288,
    LETTER = 289,
    //others
    EOL = 290,
    COMMENT = 291,
    BLANK = 292,
    ERROR = 258

} Token;


typedef struct{
    char text[256];
    int token;
    int lines;
    int pos_start;
    int pos_end;
} Token_Node;


void analyzer(char* input_file, std::vector<Token_Node>& token_stream);

#endif /* YYTOKENTYPE */
#endif /* lexical_analyzer.h */
