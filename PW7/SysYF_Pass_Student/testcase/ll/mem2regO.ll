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
  %op4 = mul i32 4, 1
  %op7 = mul i32 4, 1
  %op12 = mul i32 4, 6
  %op15 = sub i32 %op12, %op4
  %op17 = sub i32 %op15, %op7
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret i32 %op17
}
