CC = gcc
CFLAGS = -g -Wall -std=c99
GLIB_FLAGS = -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LIBS = -lglib-2.0

list_errors: list_errors.c
	$(CC) -o $@ $^ $(CFLAGS)

list_errors_soln: list_errors_soln.c
	$(CC) -o $@ $^ $(CFLAGS) $(GLIB_FLAGS) $(LIBS)

# # Different recipe for my os
# word_count: word_count.c
# 	$(CC) -o $@ $^ $(CFLAGS) $(GLIB_FLAGS) $(LIBS)

word_count.out: word_count.c
	gcc `pkg-config --cflags --libs glib-2.0` -g -o word_count.out word_count.c

word_count_soln: word_count_soln.c
	$(CC) -o $@ $^ $(CFLAGS) $(GLIB_FLAGS) $(LIBS)
