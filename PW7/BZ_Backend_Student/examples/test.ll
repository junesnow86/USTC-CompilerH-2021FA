; ModuleID = 'sysy2021_bzcompiler'
source_filename = "test.sy"

@ans = global [50 x i32] zeroinitializer
@sum = global i32 0
@n = global i32 0
@row = global [50 x i32] zeroinitializer
@line1 = global [50 x i32] zeroinitializer
@line2 = global [100 x i32] zeroinitializer
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

define void @printans() {
label_entry:
  %op0 = load i32, i32* @sum
  %op1 = add i32 %op0, 1
  store i32 %op1, i32* @sum
  br label %label_lb0
label_lb0:                                                ; preds = %label_entry, %label_lb6
  %op2 = phi i32 [ 1, %label_entry ], [ %op9, %label_lb6 ]
  %op3 = load i32, i32* @n
  %op4 = icmp sle i32 %op2, %op3
  br i1 %op4, label %label_lb1, label %label_lb2
label_lb1:                                                ; preds = %label_lb0
  %op5 = getelementptr [50 x i32], [50 x i32]* @ans, i32 0, i32 %op2
  %op6 = load i32, i32* %op5
  call void @putint(i32 %op6)
  %op7 = load i32, i32* @n
  %op8 = icmp eq i32 %op2, %op7
  br i1 %op8, label %label_lb5, label %label_lb6
label_lb2:                                                ; preds = %label_lb0
  ret void
label_lb5:                                                ; preds = %label_lb1
  call void @putch(i32 10)
  ret void
label_lb6:                                                ; preds = %label_lb1
  call void @putch(i32 32)
  %op9 = add i32 %op2, 1
  br label %label_lb0
}
define void @f(i32 %arg0) {
label_entry:
  br label %label_lb10
label_lb10:                                                ; preds = %label_entry, %label_lb16
  %op1 = phi i32 [ 1, %label_entry ], [ %op10, %label_lb16 ]
  %op2 = load i32, i32* @n
  %op3 = icmp sle i32 %op1, %op2
  br i1 %op3, label %label_lb11, label %label_lb12
label_lb11:                                                ; preds = %label_lb10
  %op4 = getelementptr [50 x i32], [50 x i32]* @row, i32 0, i32 %op1
  %op5 = load i32, i32* %op4
  %op6 = icmp ne i32 %op5, 1
  br i1 %op6, label %label_lb19, label %label_lb16
label_lb12:                                                ; preds = %label_lb10
  ret void
label_lb15:                                                ; preds = %label_lb22
  %op7 = getelementptr [50 x i32], [50 x i32]* @ans, i32 0, i32 %arg0
  store i32 %op1, i32* %op7
  %op8 = load i32, i32* @n
  %op9 = icmp eq i32 %arg0, %op8
  br i1 %op9, label %label_lb25, label %label_lb26
label_lb16:                                                ; preds = %label_lb11, %label_lb19, %label_lb22, %label_lb26
  %op10 = add i32 %op1, 1
  br label %label_lb10
label_lb19:                                                ; preds = %label_lb11
  %op11 = add i32 %arg0, %op1
  %op12 = getelementptr [50 x i32], [50 x i32]* @line1, i32 0, i32 %op11
  %op13 = load i32, i32* %op12
  %op14 = icmp eq i32 %op13, 0
  br i1 %op14, label %label_lb22, label %label_lb16
label_lb22:                                                ; preds = %label_lb19
  %op15 = load i32, i32* @n
  %op16 = add i32 %op15, %arg0
  %op17 = sub i32 %op16, %op1
  %op18 = getelementptr [100 x i32], [100 x i32]* @line2, i32 0, i32 %op17
  %op19 = load i32, i32* %op18
  %op20 = icmp eq i32 %op19, 0
  %op21 = icmp ne i32 0, i1 %op20
  br i1 %op21, label %label_lb15, label %label_lb16
label_lb25:                                                ; preds = %label_lb15
  call void @printans()
  br label %label_lb26
label_lb26:                                                ; preds = %label_lb15, %label_lb25
  %op22 = getelementptr [50 x i32], [50 x i32]* @row, i32 0, i32 %op1
  store i32 1, i32* %op22
  %op23 = add i32 %arg0, %op1
  %op24 = getelementptr [50 x i32], [50 x i32]* @line1, i32 0, i32 %op23
  store i32 1, i32* %op24
  %op25 = load i32, i32* @n
  %op26 = add i32 %op25, %arg0
  %op27 = sub i32 %op26, %op1
  %op28 = getelementptr [100 x i32], [100 x i32]* @line2, i32 0, i32 %op27
  store i32 1, i32* %op28
  %op29 = add i32 %arg0, 1
  call void @f(i32 %op29)
  %op30 = getelementptr [50 x i32], [50 x i32]* @row, i32 0, i32 %op1
  store i32 0, i32* %op30
  %op31 = add i32 %arg0, %op1
  %op32 = getelementptr [50 x i32], [50 x i32]* @line1, i32 0, i32 %op31
  store i32 0, i32* %op32
  %op33 = load i32, i32* @n
  %op34 = add i32 %op33, %arg0
  %op35 = sub i32 %op34, %op1
  %op36 = getelementptr [100 x i32], [100 x i32]* @line2, i32 0, i32 %op35
  store i32 0, i32* %op36
  br label %label_lb16
}
define i32 @main() {
label_entry:
  %op0 = call i32 @getint()
  br label %label_lb29
label_lb29:                                                ; preds = %label_entry, %label_lb30
  %op1 = phi i32 [ %op0, %label_entry ], [ %op4, %label_lb30 ]
  %op2 = icmp sgt i32 %op1, 0
  br i1 %op2, label %label_lb30, label %label_lb31
label_lb30:                                                ; preds = %label_lb29
  %op3 = call i32 @getint()
  store i32 %op3, i32* @n
  call void @f(i32 1)
  %op4 = sub i32 %op1, 1
  br label %label_lb29
label_lb31:                                                ; preds = %label_lb29
  %op5 = load i32, i32* @sum
  ret i32 %op5
}
