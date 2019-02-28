util.o: util.h util.c
	gcc -c -Wall util.c

trout.o: trout.h trout.c
	gcc -c -Wall trout.c

main.o: main.c 
	gcc -c -Wall main.c

trout: main.o trout.o util.o
	gcc main.o trout.o util.o -o trout

# trout: main.c trout.h trout.c util.h util.c
# 	gcc -g -o trout main.c trout.c util.c

