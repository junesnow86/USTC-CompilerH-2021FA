## SysYF

和 demo 都是 C 语言的子集

预期完成时的结果应是，在 sysyfParser 目录下执行以下指令

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

就会生成可执行文件(假设是 sysyf)，再使用

```
$ ./sysyf -h
```

就会有相应的"帮助"信息输出，然后使用

```
$ ./sysyf <input-file>
```

就会有一个输出文件，对照以下自己的输出文件和助教给的参考输出就可以知道自己的 ll 和 yy 文件有没有写对了。

## SysYF 文法

编译单元			声明/函数定义

声明					常量声明/变量声明

常量声明			"const" 基本类型 常量定义 { "," 常量定义 } ";"

基本类型			int 或 float

常量定义			标识符 { '['    常量表达式    ']' }    '='	常量初值

常量初值			常量表达式 或 " {**\* , \*\*\*\*} "

## 词法描述

```
// 这部分表示识别一个关键字后就执行后面的动作
int         {return yy::demoParser::make_INT(loc);}
return      {return yy::demoParser::make_RETURN(loc);}
void        {return yy::demoParser::make_VOID(loc);}

// 这部分表示一个[]中的符号就执行后面的动作
[+]         {return yy::demoParser::make_PLUS(loc);}
[-]         {return yy::demoParser::make_MINUS(loc);}
[*]         {return yy::demoParser::make_MULTIPLY(loc);}
[/]         {return yy::demoParser::make_DIVIDE(loc);}
[%]         {return yy::demoParser::make_MODULO(loc);}
[=]         {return yy::demoParser::make_ASSIGN(loc);}
[;]         {return yy::demoParser::make_SEMICOLON(loc);}
[,]         {return yy::demoParser::make_COMMA(loc);}
[(]         {return yy::demoParser::make_LPARENTHESE(loc);}
[)]         {return yy::demoParser::make_RPARENTHESE(loc);}
[{]         {return yy::demoParser::make_LBRACE(loc);}
[}]         {return yy::demoParser::make_RBRACE(loc);}

// 这部分表示识别{}中的正规式后就执行后面的动作
{Blank}+                {loc.step();}
{NewLine}+              {loc.lines(yyleng); loc.step();}
{DecConst}              {
                            std::string dec = yytext;
                            unsigned sum = 0;
                            int len = dec.size();
                            for(int i = 0;i < len;i++){
                                auto a = dec[i];
                                sum = sum * 10 + a - 48;
                            }
                            return yy::demoParser::make_INTCONST(int(sum),loc);
                        }
{OctConst}              {
                            std::string oct = yytext;
                            unsigned sum = 0;
                            int len = oct.size();
                            for(int i = 1;i < len;i++){
                                auto a = oct[i];
                                sum  = sum * 8 + a - 48;
                            }
                            return yy::demoParser::make_INTCONST(int(sum),loc);
                        }
{Identifier}            {return yy::demoParser::make_IDENTIFIER(yytext, loc);}
<<EOF>>                 {return yy::demoParser::make_END(loc);}
.
```

ll 文件中不能用库函数？！

## 语法描述

__%token部分要加哪些东西？__

1. 所有 [] 内的符号的记号名
2. 在词法中的 keyword
3. 在词法中定义的正规式，但是没有 NEWLINE

__%type部分要加哪些东西？__

__一个表达式要怎么存起来？__

__关于优先级和结合性__

* 声明结合性：%left、%right、%nonassoc
* 声明优先级：%precedence
* 记号的优先级约定：由记号的结合性声明所在行的先后次序决定，先出现的优先级较低，在同一行声明的记号具有相同的优先级

__关于初值的存放__

{ { 1, 2 }, { 3, 4 } }类型的初值要如何表示/存放？

__不能左递归？__

__如何保证有且仅有一个main函数？__

__GlobalDecl如何创建和维护？__

数组形参的第一维要不要存？如果存存在哪？

## 对 demoParser 的分析

86-96：只支持一种全局声明(即函数)，且该全局函数声明只能有一次。





int len = flo.size();
                                int i = 0;
                                for(; i < len; i++)
                                {
                                    auto a = flo[i];
                                    if(a == '.')
                                    {
                                        ++i;
                                        break;
                                    }
                                    sum = sum * 10 + a - 48; 
                                }
                                float frasum = 0;
                                for(int j = len - 1; j >= i; j--)
                                {
                                    auto a = flo[j];
                                    float temp = a - 48;
                                    frasum = frasum / 10 + temp;
                                }
                                sum = sum + frasum;

Exp产生式中为什么要用 temp？

make_xxx 是 Bison 根据语法描述文件里的 token 生成的。



__bugs__

![image-20211007190644525](/media/snowball/Data/USTC/CompilerH/Lab/Lab4/myshixun/PW/P2/image-20211007190644525.png)

这原本读的是21行，怎么一下子就跳到243行了？原因：

21行				/* ...

...						  ...

中间某行		*/

...

某一行			/* ...

...						 ...

243行			*/

所以按 "/*"(.|\n)\*"\*/"正规式的话，21行和243行之间的东西全当注释了！
