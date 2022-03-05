sort: sort.o
	clang sort.o -o sort

sort.o: sort.s
	clang -c sort.s -o sort.o

sort.s: sort.i
	clang -S sort.i -o sort.s

sort.i: sort.c
	clang -E sort.c -o sort.i
clean:
    rm -rf sort.i sort.s sort.o sort