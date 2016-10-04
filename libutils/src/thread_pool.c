#include "thread_pool.h"

bool thread_pool_init(thread_pool_t* tp)
{
	pthread_cond_init(&tp->thread_ready, NULL);
	pthread_mutex_init(&tp->thread_lock, NULL);

	pthread_mutex_lock(&tp->thread_lock);

	for (tp->thread_count_cur = 0; tp->thread_count_cur <= tp->thread_count_min; tp->thread_count_cur++)
		if (pthread_create(&tp->tid, NULL, &thread_pool_func, NULL) != 0)
			return false;

	return true;
}

bool thread_pool_destroy(thread_pool_t* tp)
{
	return true;
}

bool thread_pool_run(thread_pool_t* tp)
{
	if (pthread_cond_signal(&tp->thread_ready) != 0)
		return false;
	else
		return true;
}

static void* thread_pool_func(void* arg)
{
	thread_pool_t *tp = (thread_pool_t*)arg;

	while (pthread_cond_wait(&tp->thread_ready, &tp->thread_lock) != 0)
		(*tp->thread_func)(NULL);

	return NULL;
}
