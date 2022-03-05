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
  %op2 = alloca [2 x i32]
  %op3 = getelementptr [2 x i32], [2 x i32]* %op2, i32 0, i32 0
  store i32 0, i32* %op3
  %op4 = getelementptr [2 x i32], [2 x i32]* %op2, i32 0, i32 1
  store i32 1, i32* %op4
  %op7 = icmp ne i32 0, 0
  br i1 %op7, label %label9, label %label12
label_ret:                                                ; preds = %label15
  ret i32 0
label9:                                                ; preds = %label_entry
  %op10 = getelementptr [2 x i32], [2 x i32]* %op2, i32 0, i32 0
  %op11 = load i32, i32* %op10
  br label %label15
label12:                                                ; preds = %label_entry
  %op13 = getelementptr [2 x i32], [2 x i32]* %op2, i32 0, i32 1
  %op14 = load i32, i32* %op13
  br label %label15
label15:                                                ; preds = %label9, %label12
  br label %label_ret
}
