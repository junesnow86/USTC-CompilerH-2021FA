sort: sort.o
	gcc sort.o -o sort

sort.o: sort.s
	gcc -c sort.s -o sort.o

sort.s: sort.i
	gcc -S sort.i -o sort.s

sort.i: sort.c
	gcc -E sort.c -o sort.i

clean:
	rm -rf sort.i sort.s sort.o sort