FILE?=test1

clean :
	-rm *.o $(objects) 

### Objects
rand.o: rand.c rand.h
	gcc -c rand.c

$(FILE).o: $(FILE).c
	gcc -c $(FILE).c

# test1.o: test1.c
# 	gcc -c test1.c

# test2.o: test2.c
# 	gcc -c test2.c

# test_rand.o: test_rand.c
# 	gcc -c test_rand.c

### Executables
target: $(FILE).o rand.o
	gcc $(FILE).o rand.o -o $(FILE); make clean

# test1: test1.o rand.o
# 	gcc test1.o rand.o -o test1; make clean

# test2: test2.o rand.o
# 	gcc test2.o rand.o -o test2; make clean

# time_rand: time_rand.o rand.o
# 	gcc time_rand.o rand.o -o time_rand; make clean
