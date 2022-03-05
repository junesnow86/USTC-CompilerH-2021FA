; ModuleID = 'func_test.c'
source_filename = "func_test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @add(i32, i32) #0 {
    %3 = alloca i32, align 4
    %4 = alloca i32, align 4
    store i32 %0, i32* %3, align 4      ; store a
    store i32 %1, i32* %4, align 4      ; store b
    %5 = load i32, i32* %3, align 4
    %6 = load i32, i32* %4, align 4
    %7 = add nsw i32 %5, %6             ; a+b
    %8 = sub nsw i32 %7, 1              ; a+b-1
    ret i32 %8                          ; return a+b-1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
    %1 = alloca i32, align 4        ; a
    %2 = alloca i32, align 4        ; b
    %3 = alloca i32, align 4        ; c
    store i32 3, i32* %1, align 4   ; a = 3
    store i32 2, i32* %2, align 4   ; b = 2
    store i32 5, i32* %3, align 4   ; c = 5
    %4 = load i32, i32* %1, align 4
    %5 = load i32, i32* %2, align 4
    %6 = load i32, i32* %3, align 4
    %7 = call i32 @add(i32 %4, i32 %5)  ; add(a, b)
    %8 = add nsw i32 %6, %7             ; c+add(a,b)
    ret i32 %8
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 7.0.1-8 (tags/RELEASE_701/final)"}
