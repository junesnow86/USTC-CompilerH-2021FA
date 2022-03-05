; ModuleID = 'sysy2021_bzcompiler'
source_filename = "test.sy"

@maxn = constant i32 18
@mod = constant i32 1000000007
@dp = global [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]] zeroinitializer
@list = global [200 x i32] zeroinitializer
@cns = global [20 x i32] zeroinitializer
declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @memset(i32*, i32, i32)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @_sysy_starttime()

declare void @_sysy_stoptime()

declare void @putf()

define i32 @equal(i32 %arg0, i32 %arg1) {
label_entry:
  %op2 = icmp eq i32 %arg0, %arg1
  br i1 %op2, label %label_lb0, label %label_lb1
label_lb0:                                                ; preds = %label_entry
  ret i32 1
label_lb1:                                                ; preds = %label_entry
  ret i32 0
}
define i32 @dfs(i32 %arg0, i32 %arg1, i32 %arg2, i32 %arg3, i32 %arg4, i32 %arg5) {
label_entry:
  %op6 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp, i32 0, i32 %arg0, i32 %arg1, i32 %arg2, i32 %arg3, i32 %arg4, i32 %arg5
  %op7 = load i32, i32* %op6
  %op8 = icmp ne i32 %op7, -1
  br i1 %op8, label %label_lb4, label %label_lb5
label_lb4:                                                ; preds = %label_entry
  %op9 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp, i32 0, i32 %arg0, i32 %arg1, i32 %arg2, i32 %arg3, i32 %arg4, i32 %arg5
  %op10 = load i32, i32* %op9
  ret i32 %op10
label_lb5:                                                ; preds = %label_entry
  %op11 = add i32 %arg0, %arg1
  %op12 = add i32 %op11, %arg2
  %op13 = add i32 %op12, %arg3
  %op14 = add i32 %op13, %arg4
  %op15 = icmp eq i32 %op14, 0
  br i1 %op15, label %label_lb8, label %label_lb9
label_lb8:                                                ; preds = %label_lb5
  ret i32 1
label_lb9:                                                ; preds = %label_lb5
  %op16 = icmp ne i32 0, %arg0
  br i1 %op16, label %label_lb12, label %label_lb13
label_lb12:                                                ; preds = %label_lb9
  %op17 = call i32 @equal(i32 %arg5, i32 2)
  %op18 = sub i32 %arg0, %op17
  %op19 = sub i32 %arg0, 1
  %op20 = call i32 @dfs(i32 %op19, i32 %arg1, i32 %arg2, i32 %arg3, i32 %arg4, i32 1)
  %op21 = mul i32 %op18, %op20
  %op22 = add i32 0, %op21
  %op23 = load i32, i32* @mod
  %op24 = srem i32 %op22, %op23
  br label %label_lb13
label_lb13:                                                ; preds = %label_lb9, %label_lb12
  %op25 = phi i32 [ 0, %label_lb9 ], [ %op24, %label_lb12 ]
  %op26 = icmp ne i32 0, %arg1
  br i1 %op26, label %label_lb16, label %label_lb17
label_lb16:                                                ; preds = %label_lb13
  %op27 = call i32 @equal(i32 %arg5, i32 3)
  %op28 = sub i32 %arg1, %op27
  %op29 = add i32 %arg0, 1
  %op30 = sub i32 %arg1, 1
  %op31 = call i32 @dfs(i32 %op29, i32 %op30, i32 %arg2, i32 %arg3, i32 %arg4, i32 2)
  %op32 = mul i32 %op28, %op31
  %op33 = add i32 %op25, %op32
  %op34 = load i32, i32* @mod
  %op35 = srem i32 %op33, %op34
  br label %label_lb17
label_lb17:                                                ; preds = %label_lb13, %label_lb16
  %op36 = phi i32 [ %op25, %label_lb13 ], [ %op35, %label_lb16 ]
  %op37 = icmp ne i32 0, %arg2
  br i1 %op37, label %label_lb20, label %label_lb21
label_lb20:                                                ; preds = %label_lb17
  %op38 = call i32 @equal(i32 %arg5, i32 4)
  %op39 = sub i32 %arg2, %op38
  %op40 = add i32 %arg1, 1
  %op41 = sub i32 %arg2, 1
  %op42 = call i32 @dfs(i32 %arg0, i32 %op40, i32 %op41, i32 %arg3, i32 %arg4, i32 3)
  %op43 = mul i32 %op39, %op42
  %op44 = add i32 %op36, %op43
  %op45 = load i32, i32* @mod
  %op46 = srem i32 %op44, %op45
  br label %label_lb21
label_lb21:                                                ; preds = %label_lb17, %label_lb20
  %op47 = phi i32 [ %op36, %label_lb17 ], [ %op46, %label_lb20 ]
  %op48 = icmp ne i32 0, %arg3
  br i1 %op48, label %label_lb24, label %label_lb25
label_lb24:                                                ; preds = %label_lb21
  %op49 = call i32 @equal(i32 %arg5, i32 5)
  %op50 = sub i32 %arg3, %op49
  %op51 = add i32 %arg2, 1
  %op52 = sub i32 %arg3, 1
  %op53 = call i32 @dfs(i32 %arg0, i32 %arg1, i32 %op51, i32 %op52, i32 %arg4, i32 4)
  %op54 = mul i32 %op50, %op53
  %op55 = add i32 %op47, %op54
  %op56 = load i32, i32* @mod
  %op57 = srem i32 %op55, %op56
  br label %label_lb25
label_lb25:                                                ; preds = %label_lb21, %label_lb24
  %op58 = phi i32 [ %op47, %label_lb21 ], [ %op57, %label_lb24 ]
  %op59 = icmp ne i32 0, %arg4
  br i1 %op59, label %label_lb28, label %label_lb29
label_lb28:                                                ; preds = %label_lb25
  %op60 = add i32 %arg3, 1
  %op61 = sub i32 %arg4, 1
  %op62 = call i32 @dfs(i32 %arg0, i32 %arg1, i32 %arg2, i32 %op60, i32 %op61, i32 5)
  %op63 = mul i32 %arg4, %op62
  %op64 = add i32 %op58, %op63
  %op65 = load i32, i32* @mod
  %op66 = srem i32 %op64, %op65
  br label %label_lb29
label_lb29:                                                ; preds = %label_lb25, %label_lb28
  %op67 = phi i32 [ %op58, %label_lb25 ], [ %op66, %label_lb28 ]
  %op68 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp, i32 0, i32 %arg0, i32 %arg1, i32 %arg2, i32 %arg3, i32 %arg4, i32 %arg5
  %op69 = load i32, i32* @mod
  %op70 = srem i32 %op67, %op69
  store i32 %op70, i32* %op68
  %op71 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp, i32 0, i32 %arg0, i32 %arg1, i32 %arg2, i32 %arg3, i32 %arg4, i32 %arg5
  %op72 = load i32, i32* %op71
  ret i32 %op72
}
define i32 @main() {
label_entry:
  %op0 = call i32 @getint()
  br label %label_lb32
label_lb32:                                                ; preds = %label_entry, %label_lb39
  %op1 = phi i32 [ %op9, %label_lb39 ], [ undef, %label_entry ]
  %op2 = phi i32 [ %op10, %label_lb39 ], [ undef, %label_entry ]
  %op3 = phi i32 [ %op11, %label_lb39 ], [ undef, %label_entry ]
  %op4 = phi i32 [ %op12, %label_lb39 ], [ undef, %label_entry ]
  %op6 = phi i32 [ 0, %label_entry ], [ %op16, %label_lb39 ]
  %op7 = load i32, i32* @maxn
  %op8 = icmp slt i32 %op6, %op7
  br i1 %op8, label %label_lb37, label %label_lb62
label_lb37:                                                ; preds = %label_lb32, %label_lb44
  %op9 = phi i32 [ %op1, %label_lb32 ], [ %op17, %label_lb44 ]
  %op10 = phi i32 [ %op2, %label_lb32 ], [ %op18, %label_lb44 ]
  %op11 = phi i32 [ %op3, %label_lb32 ], [ %op19, %label_lb44 ]
  %op12 = phi i32 [ %op4, %label_lb32 ], [ %op20, %label_lb44 ]
  %op13 = phi i32 [ 0, %label_lb32 ], [ %op23, %label_lb44 ]
  %op14 = load i32, i32* @maxn
  %op15 = icmp slt i32 %op13, %op14
  br i1 %op15, label %label_lb42, label %label_lb39
label_lb39:                                                ; preds = %label_lb37
  %op16 = add i32 %op6, 1
  br label %label_lb32
label_lb42:                                                ; preds = %label_lb37, %label_lb49
  %op17 = phi i32 [ %op9, %label_lb37 ], [ %op24, %label_lb49 ]
  %op18 = phi i32 [ %op10, %label_lb37 ], [ %op25, %label_lb49 ]
  %op19 = phi i32 [ %op11, %label_lb37 ], [ %op26, %label_lb49 ]
  %op20 = phi i32 [ 0, %label_lb37 ], [ %op29, %label_lb49 ]
  %op21 = load i32, i32* @maxn
  %op22 = icmp slt i32 %op20, %op21
  br i1 %op22, label %label_lb47, label %label_lb44
label_lb44:                                                ; preds = %label_lb42
  %op23 = add i32 %op13, 1
  br label %label_lb37
label_lb47:                                                ; preds = %label_lb42, %label_lb54
  %op24 = phi i32 [ %op17, %label_lb42 ], [ %op30, %label_lb54 ]
  %op25 = phi i32 [ %op18, %label_lb42 ], [ %op31, %label_lb54 ]
  %op26 = phi i32 [ 0, %label_lb42 ], [ %op34, %label_lb54 ]
  %op27 = load i32, i32* @maxn
  %op28 = icmp slt i32 %op26, %op27
  br i1 %op28, label %label_lb52, label %label_lb49
label_lb49:                                                ; preds = %label_lb47
  %op29 = add i32 %op20, 1
  br label %label_lb42
label_lb52:                                                ; preds = %label_lb47, %label_lb59
  %op30 = phi i32 [ %op24, %label_lb47 ], [ %op35, %label_lb59 ]
  %op31 = phi i32 [ 0, %label_lb47 ], [ %op39, %label_lb59 ]
  %op32 = load i32, i32* @maxn
  %op33 = icmp slt i32 %op31, %op32
  br i1 %op33, label %label_lb57, label %label_lb54
label_lb54:                                                ; preds = %label_lb52
  %op34 = add i32 %op26, 1
  br label %label_lb47
label_lb57:                                                ; preds = %label_lb52, %label_lb58
  %op35 = phi i32 [ 0, %label_lb52 ], [ %op38, %label_lb58 ]
  %op36 = icmp slt i32 %op35, 7
  br i1 %op36, label %label_lb58, label %label_lb59
label_lb58:                                                ; preds = %label_lb57
  %op37 = getelementptr [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]], [18 x [18 x [18 x [18 x [18 x [7 x i32]]]]]]* @dp, i32 0, i32 %op6, i32 %op13, i32 %op20, i32 %op26, i32 %op31, i32 %op35
  store i32 -1, i32* %op37
  %op38 = add i32 %op35, 1
  br label %label_lb57
label_lb59:                                                ; preds = %label_lb57
  %op39 = add i32 %op31, 1
  br label %label_lb52
label_lb62:                                                ; preds = %label_lb32, %label_lb63
  %op40 = phi i32 [ 0, %label_lb32 ], [ %op52, %label_lb63 ]
  %op41 = icmp slt i32 %op40, %op0
  br i1 %op41, label %label_lb63, label %label_lb64
label_lb63:                                                ; preds = %label_lb62
  %op42 = getelementptr [200 x i32], [200 x i32]* @list, i32 0, i32 %op40
  %op43 = call i32 @getint()
  store i32 %op43, i32* %op42
  %op44 = getelementptr [200 x i32], [200 x i32]* @list, i32 0, i32 %op40
  %op45 = load i32, i32* %op44
  %op46 = getelementptr [20 x i32], [20 x i32]* @cns, i32 0, i32 %op45
  %op47 = getelementptr [200 x i32], [200 x i32]* @list, i32 0, i32 %op40
  %op48 = load i32, i32* %op47
  %op49 = getelementptr [20 x i32], [20 x i32]* @cns, i32 0, i32 %op48
  %op50 = load i32, i32* %op49
  %op51 = add i32 %op50, 1
  store i32 %op51, i32* %op46
  %op52 = add i32 %op40, 1
  br label %label_lb62
label_lb64:                                                ; preds = %label_lb62
  %op53 = getelementptr [20 x i32], [20 x i32]* @cns, i32 0, i32 1
  %op54 = load i32, i32* %op53
  %op55 = getelementptr [20 x i32], [20 x i32]* @cns, i32 0, i32 2
  %op56 = load i32, i32* %op55
  %op57 = getelementptr [20 x i32], [20 x i32]* @cns, i32 0, i32 3
  %op58 = load i32, i32* %op57
  %op59 = getelementptr [20 x i32], [20 x i32]* @cns, i32 0, i32 4
  %op60 = load i32, i32* %op59
  %op61 = getelementptr [20 x i32], [20 x i32]* @cns, i32 0, i32 5
  %op62 = load i32, i32* %op61
  %op63 = call i32 @dfs(i32 %op54, i32 %op56, i32 %op58, i32 %op60, i32 %op62, i32 0)
  call void @putint(i32 %op63)
  ret i32 %op63
}
