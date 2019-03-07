rand.o: rand.c rand.h
	gcc -c rand.c

test1.o: test1.c
	gcc -c test1.c

test_rand: test1.o rand.o
	gcc test1.o rand.o -o test_rand