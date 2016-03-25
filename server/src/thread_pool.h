#ifndef CL_THREAD_POOL_H
#define CL_THREAD_POOL_H

#include <pthread.h>
#include <stdbool.h>

struct thread_pool_data
{
	pthread_t tid;

	size_t thread_count_min;
	size_t thread_count_max;
	size_t thread_count_cur;

	void* (*thread_func)(void* arg);

	pthread_cond_t thread_ready;
	pthread_mutex_t thread_lock;
};

typedef struct thread_pool_data thread_pool_t;

bool thread_pool_init(thread_pool_t* tp);
bool thread_pool_destroy(thread_pool_t* tp);

bool thread_pool_run(thread_pool_t* tp);

static void* thread_pool_func(void* arg);

#endif /* !CL_THREAD_POOL_H */
