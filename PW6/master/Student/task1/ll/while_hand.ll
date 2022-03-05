@a = common global i32 0        ;int a
@b = common global i32 0        ;int b

define i32 @main() {            ;int main()
    %1 = alloca i32 
    store i32 0, i32* @b        ;b = 0
    store i32 3, i32* @a        ;a = 3
    br label %2

2:                              ;while condition
    %3 = load i32, i32* @a      ;%3 = a
    %4 = icmp sgt i32 %3, 0     ;if (a > 0)
    br i1 %4, label %5, label %10

5:                              ;while (a > 0) here: while body
    %6 = load i32, i32* @b      ;%6 = b
    %7 = load i32, i32* @a      ;%7 = a
    %8 = add i32 %6, %7         ;%8 = b + a
    store i32 %8, i32* @b       ;b = b + a
    %9 = sub i32 %7, 1          ;%9 = a - 1
    store i32 %9, i32* @a       ;a = a - 1
    br label %2

10:                             ;if (a <= 0) here: after while
    %11 = load i32, i32* @b     ;%11 = b
    store i32 %11, i32* %1      ;return_val = b
    %12 = load i32, i32* %1     ;%12 = return_val
    ret i32 %12                 ;return return_val
}