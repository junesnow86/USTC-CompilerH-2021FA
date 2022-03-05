@a = global i32 0, align 4						;global variable a

define i32 @main(){								;function main
	store i32 10, i32* @a, align 4				;a = 10
	%1 =alloca i32,align 4	
	store i32 0, i32* %1,align 4				;0
	%2 = load i32,i32 *@a, align 4				;a's value
	%3 = load i32,i32 *%1, align 4				;0's value
	%4 = icmp sgt i32 %2, %3					;a > 0
	br i1 %4, label %5, label %7

5:
	%6 = load i32,i32 *@a, align 4				;a's value
	ret i32 %6

7:
	%8 = load i32,i32 *%1, align 4				;0's value
	ret i32 %8
}