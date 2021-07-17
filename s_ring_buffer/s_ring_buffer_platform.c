#include <stdio.h>
#include <stdlib.h>
#include "s_ring_buffer_platform.h"

/**
 * s_ring_buffer锁创建
 */
void s_ring_buffer_lock_create(s_ring_buffer_lock_t** s_ring_buffer_lock_pp)
{
    *s_ring_buffer_lock_pp = s_log_safe_mutex_create();

    return;
}

/**
 * s_ring_buffer锁销毁
 */
void s_ring_buffer_lock_destroy(s_ring_buffer_lock_t** s_ring_buffer_lock_pp)
{
    s_log_safe_mutex_destroy(s_ring_buffer_lock_pp);

    return;
}

/**
 * s_ring_buffer上锁
 */
void s_ring_buffer_lock(s_ring_buffer_lock_t* s_ring_buffer_lock_p)
{
    s_log_safe_mutex_lock(s_ring_buffer_lock_p);

    return;
}

/**
 * s_ring_buffer尝试上锁
 */
int s_ring_buffer_try_lock(s_ring_buffer_lock_t* s_ring_buffer_lock_p)
{
    return s_log_safe_mutex_try_lock(s_ring_buffer_lock_p);
}

/**
 * s_ring_buffer解锁
 */
void s_ring_buffer_unlock(s_ring_buffer_lock_t* s_ring_buffer_lock_p)
{
    s_log_safe_mutex_unlock(s_ring_buffer_lock_p);

    return;
}