declare i32 @get_int()

declare float @get_float()

declare i32 @get_char()

declare i32 @get_int_array(i32*)

declare i32 @get_float_array(float*)

declare void @put_int(i32)

declare void @put_float(float)

declare void @put_char(i32)

declare void @put_int_array(i32, i32*)

declare void @put_float_array(i32, float*)

define i32 @main() {
label_entry:
  %op0 = alloca i32
  %op1 = alloca [3 x i32]
  %op2 = getelementptr [3 x i32], [3 x i32]* %op1, i32 0, i32 0
  store i32 1, i32* %op2
  %op3 = getelementptr [3 x i32], [3 x i32]* %op1, i32 0, i32 1
  store i32 2, i32* %op3
  %op4 = getelementptr [3 x i32], [3 x i32]* %op1, i32 0, i32 2
  store i32 3, i32* %op4
  %op5 = alloca i32
  %op6 = getelementptr [3 x i32], [3 x i32]* %op1, i32 0, i32 2
  %op7 = load i32, i32* %op6
  store i32 %op7, i32* %op5
  %op8 = alloca i32
  %op9 = getelementptr [3 x i32], [3 x i32]* %op1, i32 0, i32 2
  %op10 = load i32, i32* %op9
  store i32 %op10, i32* %op8
  %op11 = load i32, i32* %op5
  %op12 = load i32, i32* %op8
  %op13 = sub i32 %op11, %op12
  store i32 %op13, i32* %op0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %op14 = load i32, i32* %op0
  ret i32 %op14
}
