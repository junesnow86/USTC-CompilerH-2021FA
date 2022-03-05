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
  %op1 = alloca float
  store float 0x3ff0000000000000, float* %op1
  %op2 = alloca float
  %op3 = load float, float* %op1
  %op4 = sitofp i32 1 to float
  %op5 = fadd float %op3, %op4
  store float %op5, float* %op2
  store i32 0, i32* %op0
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  %op6 = load i32, i32* %op0
  ret i32 %op6
}
