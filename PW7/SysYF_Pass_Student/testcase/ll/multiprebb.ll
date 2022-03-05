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
  %op4 = mul i32 1, 1
  %op7 = mul i32 2, 1
  %op11 = icmp eq i32 0, 1
  %op12 = zext i1 %op11 to i32
  %op13 = icmp ne i32 %op12, 0
  br i1 %op13, label %label16, label %label20
label_ret:                                                ; preds = %label25
  ret i32 %op31
label16:                                                ; preds = %label_entry
  %op19 = add i32 %op4, %op7
  br label %label25
label20:                                                ; preds = %label_entry
  %op23 = add i32 %op4, %op7
  %op24 = sub i32 %op23, 1
  br label %label25
label25:                                                ; preds = %label16, %label20
  %op32 = phi i32 [ %op24, %label20 ], [ %op19, %label16 ]
  %op28 = add i32 %op4, %op7
  ; %op28 = phi i32 [ %op23, %label20 ], [ %op19, %label16 ]
  %op31 = sub i32 %op28, %op32
  br label %label_ret
}
