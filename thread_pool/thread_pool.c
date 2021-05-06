#include "thread_pool.h"
#include <stdlib.h>
#include <stdio.h>

static void *thread_pool_routine(void *arg)
{
    struct thread_pool *pool = (struct thread_pool *)arg;
    struct thread_worker *worker;

    while (1)
    {
        pthread_mutex_lock(&pool->lock);   //加锁
        
        if (pool->worker_count == 0 && pool->shutdown == 0)     //任务队列无任务
        {
            pthread_cond_wait(&pool->cond, &pool->lock);      //等待条件变量
        } 

        if (pool->worker_count == 0 && pool->shutdown)          //任务数为0才能销毁线程池
        {
            pthread_mutex_unlock(&pool->lock);               //解锁
            pthread_exit(NULL);
        }

        worker = pool->list.next;    // 获取任务队列第一个任务
        pool->list.next = pool->list.next->next;
        pool->worker_count--;
        pthread_mutex_unlock(&pool->lock);

        if (worker->work)
        {
            worker->work(worker->arg);
        }
        free(worker);        //执行结束释放内存
        worker = NULL;       //指针释放结束置NULL是个好习惯
    }
}


int thread_pool_init(struct thread_pool *pool, int thread_count)
{
    if (pool == NULL)
    {
        printf("error : pool is null\n");
        return -1;
    }
        
    if (thread_count <= 0)
    {
        printf("error : thread number is negative\n");
        return -2;
    }
        
    pool->tids = (pthread_t *)malloc(thread_count * sizeof(pthread_t));
    if (pool->tids == NULL)
    {
        printf("error : tids is null\n");
        return -3;
    }
    
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cond, NULL);

    pool->shutdown = 0;
    pool->worker_count = 0;
    pool->thread_count = thread_count;
    for (int i = 0; i < pool->thread_count; i++)
    {
        int ret = pthread_create(&(pool->tids[i]), NULL, thread_pool_routine, (void *)pool);    
        if (ret < 0)
        {
            printf("create thread error: %d\n", ret);
            return -4;
        }
    }

    return 0;
}

int thread_pool_add_worker(struct thread_pool *pool, void (*work)(void *arg), void *arg)
{
    if (pool == NULL)
    {
        printf("%s thread pool is null\r\n", __FUNCTION__);
        return -1;
    }

    if (work == NULL || arg == NULL)
    {
        printf("%s work is null\r\n", __FUNCTION__);
        return -2;
    }

    struct thread_worker *worker = (struct thread_worker *)malloc(sizeof(struct thread_worker));
    if (worker == NULL)
    {
        printf("%s work malloc failed\r\n", __FUNCTION__);
        return -3;
    }
    worker->work = work;
    worker->arg = arg;
    worker->next = NULL;

    pthread_mutex_lock(&pool->lock);
    struct thread_worker *tmp;
    for (tmp = &pool->list; tmp->next != NULL; tmp = tmp->next);
    tmp->next = worker;
    pool->worker_count++;
    pthread_mutex_unlock(&pool->lock);

    pthread_cond_signal(&pool->cond);    

    return 0;
}

int thread_pool_deinit(struct thread_pool *pool)
{
    if (pool == NULL)
        return -1;

    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->cond);          //唤醒所有线程

    for (int i = 0; i < pool->thread_count; i++)
    {
        int ret = pthread_join(pool->tids[i], NULL);
        if (ret < 0)
        {
            printf("pthread join error: %d\n", i);
        }
    }

    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->cond);

    free(pool->tids);

    return 0;
}

int thread_pool_destroy(struct thread_pool *pool)
{
    if (pool == NULL)
        return -1;

    pool->shutdown = 1;
    pthread_cond_broadcast(&pool->cond);          //环形所有线程

    for (int i = 0; i < pool->thread_count; i++)
    {
        int ret = pthread_join(pool->tids[i], NULL);
        if (ret < 0)
        {
            printf("pthread join error: %d\n", i);
        }
    }

    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->cond);

    free(pool->tids);
    free(pool);

    return 0;
}