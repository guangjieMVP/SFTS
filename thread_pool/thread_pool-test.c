#include "thread_pool.h"
#include <stdio.h>
#include <unistd.h>

struct thread_pool thread_pool;

void mywork(void *arg)
{
    int n = *(int*)arg;

	printf("[%u][%s] ==> job will be done in %d sec...\n",
		(unsigned)pthread_self(), __FUNCTION__, n);

	sleep(n);

	printf("[%u][%s] ==> job done!\n",
		(unsigned)pthread_self(), __FUNCTION__);
}

void *thread_count_time(void *arg)
{
    int i = 0;

    while (1)
    {
        sleep(1);
        printf("sec : %d\r\n", i++);    
    }
}

int main(int argc, char **argv)
{
    int a = 10;
    int b = 15;
    int c = 20;

    pthread_t threadtime;
	pthread_create(&threadtime, NULL, thread_count_time, NULL);

    int ret =  thread_pool_init(&thread_pool, 3);
    if (ret < 0)
    {
        printf("failed to init thread pool\r\n");
        return -1;
    }

    thread_pool_add_worker(&thread_pool, mywork, &a);
    thread_pool_add_worker(&thread_pool, mywork, &b);
    thread_pool_add_worker(&thread_pool, mywork, &c);

    thread_pool_deinit(&thread_pool);

    return 0;
}