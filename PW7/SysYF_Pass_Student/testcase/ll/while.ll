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
  br label %label4
label_ret:                                                ; preds = %label11
  ret i32 %op13
label4:                                                ; preds = %label_entry, %label8
  %op13 = phi i32 [ 0, %label_entry ], [ %op10, %label8 ]
  %op6 = sub i32 10, 1
  %op7 = icmp ne i32 %op6, 0
  br i1 %op7, label %label8, label %label11
label8:                                                ; preds = %label4
  %op10 = add i32 %op13, 1
  br label %label4
label11:                                                ; preds = %label4
  br label %label_ret
}
