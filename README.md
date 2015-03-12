# C-Lambda-and-Callback
Lambda expression has been supported by many programing languages. But it is not supported by standard C.
This problem is now solved by the combinations of some techniques. If you want to have the same functionality of lambda, your compiler needs to support __nested function__. The result would be something like this:

```C
my_qsort(values, 6, a, b, return (*(int*)a - *(int*)b););
```

If you only needs a callback function, there's no extra requirements. it can be compiled by almost every C compiler. The result is like this:

```C
pop_job(job_semaphore,
    //In callback function
    //This is for double check, preventing unexpeted bug
    while(isBufferEmpty(buffer_t));
    bufferRead(buffer_t, p);
    printf("\tpop %d, %d\n", p.x, p.y); //Print message
);
```

# Compilation
* gcc -lpthread ./pthread.c -o ./pthread
* gcc ./lambda.c -o ./lambda

# Usage and Description
Please reference to my [blog](https://medicineyeh.wordpress.com/2015/03/12/how-to-write-a-lambda-expression-and-callback-function-in-c/)

# Super Fast Ring Buffer
This is my version of Ring Buffer modified from [Philip Thrasher](https://github.com/pthrasher/c-generic-ring-buffer)
I made macros deal with only pointer type for easier to use.

