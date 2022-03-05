## 1-1

main 函数负责解析命令行参数，根据命令行参数设置好相应的 bool 变量(trace_parsing 等)或者打印 help 信息，然后调用 demoDriver 类的 parse 方法构建语法树并返回根节点的指针，之后如果输入命令要求打印通过 AST 复原后的代码则调用相应的方法 accept。

在 demoDriver 类中，parse 方法会先调用 scan_begin()，里面调用 demoFlexLexer 类的方法对输入文件(可以是标准输入)进行词法分析，然后调用 demoParser 类的方法进行语法分析，如果不能打开文件就输出错误信息。总的来说，demoDriver 类实例的作用就是驱动词法分析器(demoFlexLexer类实例)和语法分析器(demoParser类实例)工作：

```cpp
SyntaxTree::Node* demoDriver::parse(const std::string &f)
{
    file = f;

    // lexer begin
    scan_begin();	// 词法分析
    yy::demoParser parser(*this);
    parser.set_debug_level(trace_parsing);
    // parser begin
    parser.parse(); // 语法分析
    // lexer end
    scan_end();

    return this->root;
}
```

## 1-2

__词法部分__

在 `demoScanner.ll` 中的 /* keyword */ 下增加一个 "main"，即可以在95行处添加一行，这样当 "main" 出现在源代码文件中时将被词法分析当做一个关键字处理，而不是被归为 Identifier。

```
main {return yy::demoParser::make_MAIN(loc);}
```

__语法部分__

demo 的语法描述中会有与下列文法

```
CompUnit -> FuncDef
FuncDef -> FuncType Ident '(' ')' Block
FuncType -> 'void'
```

相关的描述，即 `demoParser.yy` 中的143~150行：

```
FuncDef: VOID IDENTIFIER LPARENTHESE RPARENTHESE BLOCK{
	$$ = new SyntaxTree::FuncDef();
	$$->ret_type = SyntaxTree::Type::VOID;
	$$->name = $2;
	$$->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>($5);
	$$->loc = @$;
};
```

这条规则是识别一个函数定义的，大意是：

1. 函数的返回类型必须是 void；
2. 函数名是上面的 IDENTIFIER；
3. 函数体是 Block 中的语句；

修改对于函数名的规则，将上面规则中的 "IDENTIFIER" 改成 "MAIN"并修改 $$ 的 name 属性 ，即

```
FuncDef: VOID MAIN LPARENTHESE RPARENTHESE BLOCK {
	$$ = new SyntaxTree::FuncDef();
	$$->ret_type = SyntaxTree::Type::VOID;
	$$->name = std::string("main");
	$$->body = SyntaxTree::Ptr<SyntaxTree::BlockStmt>($5);
	$$->loc = @$;
};
```

这样 demo 唯一能包含的函数名就必须是 "main"。并在 token 的相关声明中(48行)将

```
%token INT RETURN VOID
```

改成

```
%token INT RETURN VOID MAIN
```

