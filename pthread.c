/* Copyright (c) 2015 Medicine Yeh */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */
#include "ringbuffer.h" /* Ultra fast ringbuffer */

/* inline function with lambda macro definition */
#define PUSH_JOB(sem_mutex_t, call_back_function) do {\
    call_back_function;\
    sem_post(sem_mutex_t);       /* up semaphore */\
}while(0)
#define POP_JOB(sem_mutex_t, call_back_function) do {\
    sem_wait(sem_mutex_t);       /* down semaphore */\
    call_back_function;\
}while(0)

/* structure definition */
typedef struct POINT{
    int x;
    int y;
} POINT;

/* ring buffer structure definition */
ringBuffer_typedef(POINT, TraceBuffer);

/* prototype for thread routine */
void *slave(void *ptr);
void *master(void *ptr);

/* global vars */
sem_t *job_semaphore;
TraceBuffer* buffer_t;

void *slave(void *ptr)
{
    POINT p;

    while(1) {
        //Pop a job and do lambda function
        POP_JOB(job_semaphore, 
                //This is for double check, preventing unexpeted bug
                while(isBufferEmpty(buffer_t));
                bufferRead(buffer_t, p);
                printf("\tpop %d, %d\n", p.x, p.y); //Print message
                );
        sleep(2);//Sleep longer
    }
}

void *master(void *ptr)
{
    POINT p;
    p.x = 0;
    p.y = 1;

    while(1) {
        //Push a job after lambda function
        PUSH_JOB(job_semaphore, 
                while(isBufferFull(buffer_t));
                bufferWrite(buffer_t, p);
                printf("push>\n"); //Print message
                // Generate trace
                p.y++;
                p.x = p.y % 2;
                );
        sleep(1);
    }
}

int main()
{
    pthread_t thread_a;
    pthread_t thread_b;

    job_semaphore = (sem_t *)malloc(sizeof(sem_t));
    sem_init(job_semaphore, 0, 0); //Initialize mutex to 0
    bufferInit(buffer_t, 10, POINT, TraceBuffer); //Initialize ring buffer

    pthread_create (&thread_a, NULL, (void *) &master, NULL);
    pthread_create (&thread_b, NULL, (void *) &slave, NULL);

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    sem_destroy(job_semaphore); //Destroy semaphore
    free(job_semaphore);

    exit(0);
}


