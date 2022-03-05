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
  %op6 = add i32 1, 3       ; c
  %op9 = sub i32 %op6, 1    ; c-a
  %op11 = sub i32 %op9, 1   ; c-a-b
  %op12 = sub i32 %op11, 1  ; c-a-b-1
  br label %label_ret
label_ret:                                                ; preds = %label_entry
  ret i32 %op12
}
