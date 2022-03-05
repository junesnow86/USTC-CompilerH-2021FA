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

define i32 @func(i32 %arg0) {
label_entry:
  %op4 = add i32 %arg0, 1
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret i32 %op4
}
define i32 @main() {
label_entry:
  %op4 = call i32 @func(i32 1)
  %op7 = call i32 @func(i32 1)
  %op10 = add i32 %op4, %op7
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret i32 %op10
}
