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
  %op1 = alloca i32             ; a
  store i32 1, i32* %op1        ; 1存入a
  %op2 = alloca i32             ; b
  %op3 = load i32, i32* %op1    ; 从a取出1
  store i32 %op3, i32* %op2     ; 存到b
  %op4 = alloca i32             ; c
  %op5 = load i32, i32* %op1
  %op6 = add i32 %op5, 3
  store i32 %op6, i32* %op4
  %op7 = load i32, i32* %op4
  %op8 = load i32, i32* %op1
  %op9 = sub i32 %op7, %op8
  %op10 = load i32, i32* %op2
  %op11 = sub i32 %op9, %op10
  %op12 = sub i32 %op11, 1
  store i32 %op12, i32* %op0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %op13 = load i32, i32* %op0
  ret i32 %op13
}
