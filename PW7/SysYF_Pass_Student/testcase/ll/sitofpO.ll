@f = global i32 1
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
  %op2 = load i32, i32* @f
  %op3 = sitofp i32 %op2 to float
  %op5 = load i32, i32* @f
  %op6 = sitofp i32 %op5 to float
  %op9 = fadd float %op3, %op6
  %op10 = fptosi float %op9 to i32
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret i32 %op10
}
