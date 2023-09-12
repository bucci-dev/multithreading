#include <stdio.h>
#include <stdbool.h>
#include <threads.h>

#define MAX_THREADS 8
#define MIN_BLOCK_SIZE 100

typedef struct {
    float *start;
    int len;
    int block_size;
    double sum;
} Sum_arg;

int parallel_sum(void *arg);

bool sum(float arr[], int len, double *sumPtr) 
{
    int block_size = len / MAX_THREADS;
    
    if (block_size < MIN_BLOCK_SIZE) 
    {
        block_size = len;
    }

    Sum_arg args = {arr, len, block_size, 0.0};

    if (parallel_sum(&args))
    {
        *sumPtr = args.sum;
        return true;
    }
    else 
    {
        return false;
    }
}

int parallel_sum(void *arg)
{
    Sum_arg *argp = (Sum_arg *)arg;

    if (argp->len <= argp->block_size)
    {
        for (int i = 0; i < argp->len; ++i)
        {
            argp->sum += argp->start[i];
        }
        return 1;
    }
    else
    {
        int mid = argp->len / 2;
        Sum_arg arg2 = {argp->start+mid, argp->len-mid, argp->block_size, 0};
        argp->len = mid;

        thrd_t th;
        int res = 0;
        if (thrd_create(&th, parallel_sum, arg) != thrd_success)
        {
            return 0;
        }

        if (!parallel_sum(&arg2))
        {
            thrd_detach(th);
            return 0;
        }

        thrd_join(th, &res);
        
        if (!res)
        {
            return 0;
        }

        argp->sum += arg2.sum;
        return 1;
    } 
}

int main(){
    float test[] = {5, 4, 5, 3, 5, 2, 1, 2};
    int size = 8;
    double store;
    double *result = &store;

    sum(test, size, result);
    printf("result: %f\n", store);

    return 0;
}