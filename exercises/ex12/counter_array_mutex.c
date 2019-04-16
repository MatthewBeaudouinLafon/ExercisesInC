/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

2. There are 29887 errors. So yes. There seem to be sync errors.
3. Wow seems to work!
4. 
Results
___________________________________________________________
matthews-mbp:ex12 mattbl$ time ./counter_array
181620 errors.

real    0m0.054s
user    0m0.085s
sys     0m0.005s

matthews-mbp:ex12 mattbl$ time ./counter_array_mutex
0 errors.

real    0m0.065s
user    0m0.044s
sys     0m0.054s
___________________________________________________________

Looks like sys time jumped from 0.005 to 0.054, which is rather significant overhead time.
user-time is better, so it seems like running in parallel was effective.
However it did take more real time so, that's unfortunate.
    Not to mention that counter_array has to make about 20% more calculations due to sync errors.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mutex.h"

#define NUM_CHILDREN 2
Mutex *mutex = NULL;

void perror_exit(char *s)
{
    perror(s);
    exit(-1);
}

void *check_malloc(int size)
{
    void *p = malloc(size);
    if (p == NULL) {
        perror_exit("malloc failed");
    }
    return p;
}

typedef struct {
    int counter;
    int end;
    int *array;
} Shared;

Shared *make_shared(int end)
{
    int i;
    Shared *shared = check_malloc(sizeof(Shared));

    shared->counter = 0;
    shared->end = end;

    shared->array = check_malloc(shared->end * sizeof(int));
    for (i=0; i<shared->end; i++) {
        shared->array[i] = 0;
    }
    return shared;
}

pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

void child_code(Shared *shared)
{
    // printf("Starting child at counter %d\n", shared->counter);

    while (1) {
        if (shared->counter >= shared->end) {
            return;
        }
        mutex_lock(mutex);
        shared->array[shared->counter]++;
        shared->counter++;
        mutex_unlock(mutex);

        // if (shared->counter % 10000 == 0) {
        //     printf("%d\n", shared->counter);
        // }
    }
}

void *entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    child_code(shared);
    // printf("Child done.\n");
    pthread_exit(NULL);
}

void check_array(Shared *shared)
{
    int i, errors=0;

    // printf("Checking...\n");

    for (i=0; i<shared->end; i++) {
        if (shared->array[i] != 1) errors++;  // YOU MANIACS!
                                              // YOU BLEW IT UP!
    }
    printf("%d errors.\n", errors);
}

int main()
{
    int i;
    pthread_t child[NUM_CHILDREN];

    mutex = make_mutex();

    Shared *shared = make_shared(1000000);

    for (i=0; i<NUM_CHILDREN; i++) {
        child[i] = make_thread(entry, shared);
    }

    for (i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }

    check_array(shared);
    return 0;
}
