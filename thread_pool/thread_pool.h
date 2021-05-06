#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <pthread.h>

struct thread_worker {
    void *arg;
    void (*work)(void *arg);
    struct thread_worker *next;
};

struct thread_pool {
    pthread_mutex_t lock;          //互斥锁 保护任务队列
	pthread_cond_t  cond;          //条件变量 同步所有线程

    pthread_t *tids;               //线程ID
    struct thread_worker list;     //任务队列

    int thread_count;             //线程个数
    int worker_count;             //任务个数

    char shutdown;                 //线程池是否销毁标志
};

int thread_pool_init(struct thread_pool *pool, int thread_count);
int thread_pool_add_worker(struct thread_pool *pool, void (*work)(void *arg), void *arg);
int thread_pool_destroy(struct thread_pool *pool);
int thread_pool_deinit(struct thread_pool *pool);

#endif