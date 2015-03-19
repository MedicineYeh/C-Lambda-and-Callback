#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#define ringBuffer_typedef(T, NAME) \
    typedef struct { \
        int size; \
        volatile int start; \
        volatile int end; \
        T* elems; \
    } NAME

#define bufferInit(BUF, S, T, B_T) \
    BUF = (B_T*)malloc(sizeof(B_T));\
    BUF->size = S+1; \
    BUF->start = 0; \
    BUF->end = 0; \
    BUF->elems = (T*)calloc(BUF->size, sizeof(T))


#define bufferDestroy(BUF) free(BUF->elems)
#define nextStartIndex(BUF) ((BUF->start + 1) % BUF->size)
#define nextEndIndex(BUF) ((BUF->end + 1) % BUF->size)
#define isBufferEmpty(BUF) (BUF->end == BUF->start)
#define isBufferFull(BUF) (nextEndIndex(BUF) == BUF->start)

#define bufferWrite(BUF, ELEM) \
    BUF->elems[BUF->end] = ELEM; \
    BUF->end = (BUF->end + 1) % BUF->size; \
    if (isBufferEmpty(BUF)) { \
        BUF->start = nextStartIndex(BUF); \
    }

#define bufferRead(BUF, ELEM) \
    ELEM = BUF->elems[BUF->start]; \
    BUF->start = nextStartIndex(BUF);

#endif

