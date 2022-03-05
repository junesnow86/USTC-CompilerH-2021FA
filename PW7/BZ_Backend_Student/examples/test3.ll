; ModuleID = 'sysy2021_bzcompiler'
source_filename = "test.sy"

@TAPE_LEN = constant i32 65536
@BUFFER_LEN = constant i32 32768
@tape = global [65536 x i32] zeroinitializer
@program = global [32768 x i32] zeroinitializer
@ptr = global i32 0
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

define void @read_program() {
label_entry:
  %op0 = call i32 @getint()
  br label %label_lb0
label_lb0:                                                ; preds = %label_entry, %label_lb1
  %op1 = phi i32 [ 0, %label_entry ], [ %op5, %label_lb1 ]
  %op2 = icmp slt i32 %op1, %op0
  br i1 %op2, label %label_lb1, label %label_lb2
label_lb1:                                                ; preds = %label_lb0
  %op3 = getelementptr [32768 x i32], [32768 x i32]* @program, i32 0, i32 %op1
  %op4 = call i32 @getch()
  store i32 %op4, i32* %op3
  %op5 = add i32 %op1, 1
  br label %label_lb0
label_lb2:                                                ; preds = %label_lb0
  %op6 = getelementptr [32768 x i32], [32768 x i32]* @program, i32 0, i32 %op1
  store i32 0, i32* %op6
  ret void
}
define void @interpret(i32* %arg0) {
label_entry:
  br label %label_lb5
label_lb5:                                                ; preds = %label_entry, %label_lb12
  %op1 = phi i32 [ 0, %label_entry ], [ %op16, %label_lb12 ]
  %op2 = phi i32 [ %op14, %label_lb12 ], [ undef, %label_entry ]
  %op4 = getelementptr i32, i32* %arg0, i32 %op1
  %op5 = load i32, i32* %op4
  %op6 = icmp ne i32 0, %op5
  br i1 %op6, label %label_lb6, label %label_lb7
label_lb6:                                                ; preds = %label_lb5
  %op7 = getelementptr i32, i32* %arg0, i32 %op1
  %op8 = load i32, i32* %op7
  %op9 = icmp eq i32 %op8, 62
  br i1 %op9, label %label_lb10, label %label_lb11
label_lb7:                                                ; preds = %label_lb5
  ret void
label_lb10:                                                ; preds = %label_lb6
  %op10 = load i32, i32* @ptr
  %op11 = add i32 %op10, 1
  store i32 %op11, i32* @ptr
  br label %label_lb12
label_lb11:                                                ; preds = %label_lb6
  %op12 = icmp eq i32 %op8, 60
  br i1 %op12, label %label_lb15, label %label_lb16
label_lb12:                                                ; preds = %label_lb10, %label_lb15, %label_lb20, %label_lb25, %label_lb30, %label_lb35, %label_lb36, %label_lb44, %label_lb47
  %op13 = phi i32 [ %op1, %label_lb10 ], [ %op1, %label_lb15 ], [ %op1, %label_lb20 ], [ %op1, %label_lb25 ], [ %op1, %label_lb30 ], [ %op1, %label_lb35 ], [ %op1, %label_lb36 ], [ %op1, %label_lb44 ], [ %op46, %label_lb47 ]
  %op14 = phi i32 [ %op2, %label_lb10 ], [ %op2, %label_lb15 ], [ %op2, %label_lb20 ], [ %op2, %label_lb25 ], [ %op2, %label_lb30 ], [ %op2, %label_lb35 ], [ %op2, %label_lb36 ], [ %op2, %label_lb44 ], [ %op47, %label_lb47 ]
  %op16 = add i32 %op13, 1
  br label %label_lb5
label_lb15:                                                ; preds = %label_lb11
  %op17 = load i32, i32* @ptr
  %op18 = sub i32 %op17, 1
  store i32 %op18, i32* @ptr
  br label %label_lb12
label_lb16:                                                ; preds = %label_lb11
  %op19 = icmp eq i32 %op8, 43
  br i1 %op19, label %label_lb20, label %label_lb21
label_lb20:                                                ; preds = %label_lb16
  %op20 = load i32, i32* @ptr
  %op21 = getelementptr [65536 x i32], [65536 x i32]* @tape, i32 0, i32 %op20
  %op22 = load i32, i32* @ptr
  %op23 = getelementptr [65536 x i32], [65536 x i32]* @tape, i32 0, i32 %op22
  %op24 = load i32, i32* %op23
  %op25 = add i32 %op24, 1
  store i32 %op25, i32* %op21
  br label %label_lb12
label_lb21:                                                ; preds = %label_lb16
  %op26 = icmp eq i32 %op8, 45
  br i1 %op26, label %label_lb25, label %label_lb26
label_lb25:                                                ; preds = %label_lb21
  %op27 = load i32, i32* @ptr
  %op28 = getelementptr [65536 x i32], [65536 x i32]* @tape, i32 0, i32 %op27
  %op29 = load i32, i32* @ptr
  %op30 = getelementptr [65536 x i32], [65536 x i32]* @tape, i32 0, i32 %op29
  %op31 = load i32, i32* %op30
  %op32 = sub i32 %op31, 1
  store i32 %op32, i32* %op28
  br label %label_lb12
label_lb26:                                                ; preds = %label_lb21
  %op33 = icmp eq i32 %op8, 46
  br i1 %op33, label %label_lb30, label %label_lb31
label_lb30:                                                ; preds = %label_lb26
  %op34 = load i32, i32* @ptr
  %op35 = getelementptr [65536 x i32], [65536 x i32]* @tape, i32 0, i32 %op34
  %op36 = load i32, i32* %op35
  call void @putch(i32 %op36)
  br label %label_lb12
label_lb31:                                                ; preds = %label_lb26
  %op37 = icmp eq i32 %op8, 44
  br i1 %op37, label %label_lb35, label %label_lb36
label_lb35:                                                ; preds = %label_lb31
  %op38 = load i32, i32* @ptr
  %op39 = getelementptr [65536 x i32], [65536 x i32]* @tape, i32 0, i32 %op38
  %op40 = call i32 @getch()
  store i32 %op40, i32* %op39
  br label %label_lb12
label_lb36:                                                ; preds = %label_lb31
  %op41 = icmp eq i32 %op8, 93
  br i1 %op41, label %label_lb44, label %label_lb12
label_lb44:                                                ; preds = %label_lb36
  %op42 = load i32, i32* @ptr
  %op43 = getelementptr [65536 x i32], [65536 x i32]* @tape, i32 0, i32 %op42
  %op44 = load i32, i32* %op43
  %op45 = icmp ne i32 0, %op44
  br i1 %op45, label %label_lb47, label %label_lb12
label_lb47:                                                ; preds = %label_lb44, %label_lb52, %label_lb53, %label_lb57
  %op46 = phi i32 [ %op1, %label_lb44 ], [ %op50, %label_lb52 ], [ %op50, %label_lb53 ], [ %op50, %label_lb57 ]
  %op47 = phi i32 [ 1, %label_lb44 ], [ %op54, %label_lb52 ], [ %op47, %label_lb53 ], [ %op56, %label_lb57 ]
  %op49 = icmp sgt i32 %op47, 0
  br i1 %op49, label %label_lb48, label %label_lb12
label_lb48:                                                ; preds = %label_lb47
  %op50 = sub i32 %op46, 1
  %op51 = getelementptr i32, i32* %arg0, i32 %op50
  %op52 = load i32, i32* %op51
  %op53 = icmp eq i32 %op52, 91
  br i1 %op53, label %label_lb52, label %label_lb53
label_lb52:                                                ; preds = %label_lb48
  %op54 = sub i32 %op47, 1
  br label %label_lb47
label_lb53:                                                ; preds = %label_lb48
  %op55 = icmp eq i32 %op52, 93
  br i1 %op55, label %label_lb57, label %label_lb47
label_lb57:                                                ; preds = %label_lb53
  %op56 = add i32 %op47, 1
  br label %label_lb47
}
define i32 @main() {
label_entry:
  call void @read_program()
  %op0 = getelementptr [32768 x i32], [32768 x i32]* @program, i32 0
  %op1 = getelementptr [32768 x i32], [32768 x i32]* %op0, i32 0, i32 0
  call void @interpret(i32* %op1)
  ret i32 0
}
