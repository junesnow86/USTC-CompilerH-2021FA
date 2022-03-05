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
  %op1 = alloca i32
  store i32 1, i32* %op1
  %op2 = alloca i32
  %op3 = load i32, i32* %op1
  %op4 = mul i32 4, %op3
  store i32 %op4, i32* %op2
  %op5 = alloca i32
  %op6 = load i32, i32* %op1
  %op7 = mul i32 4, %op6
  store i32 %op7, i32* %op5
  %op8 = alloca i32
  %op9 = load i32, i32* %op2
  store i32 %op9, i32* %op8
  %op10 = load i32, i32* %op2
  %op11 = load i32, i32* %op5
  %op12 = sub i32 %op10, %op11
  store i32 %op12, i32* %op0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %op13 = load i32, i32* %op0
  ret i32 %op13
}
