define i32 @main() {
label_entry:
  %op6 = add i32 806, 2
  %op16 = sitofp i32 806 to float
  %op17 = fmul float 0x3fd3333340000000, %op16
  %op19 = icmp ne i32 3, 0
  br i1 %op19, label %label21, label %label28
label_ret:                                                ; preds = %label39
  ret i32 %op42
label21:                                                ; preds = %label_entry
  %op24 = srem i32 806, 2
  br label %label39
label28:                                                ; preds = %label_entry
  %op32 = fdiv float %op16, %op17
  %op33 = fptosi float %op32 to i32
  %op37 = fdiv float %op16, %op17
  %op38 = fptosi float %op37 to i32
  br label %label39
label39:                                                ; preds = %label21, %label28
  %op43 = phi i32 [ %op38, %label28 ], [ %op24, %label21 ]
  %op44 = phi i32 [ %op33, %label28 ], [ %op24, %label21 ]
  %op42 = add i32 %op44, %op43
  br label %label_ret
}