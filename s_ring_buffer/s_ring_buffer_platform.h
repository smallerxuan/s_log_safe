#ifndef S_RING_BUFFER_PLATFORM_H__
#define S_RING_BUFFER_PLATFORM_H__

#include "s_log_safe_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef s_ring_buff_malloc
#define s_ring_buff_malloc s_log_safe_malloc
#endif

#ifndef s_ring_buff_free
#define s_ring_buff_free   s_log_safe_free
#endif

#ifndef s_ring_buff_memcpy
#define s_ring_buff_memcpy s_log_safe_memcpy
#endif

#define s_ring_buff_usleep(x) s_log_safe_usleep(x)
#define s_ring_buff_msleep(x) s_log_safe_msleep(1000 * x)
#define s_ring_buff_sleep(x)  s_log_safe_sleep(x)

/* s_ring_buffer锁类型 */
typedef s_log_safe_mutex_t s_ring_buffer_lock_t;

/**
 * s_ring_buffer锁创建
 */
void s_ring_buffer_lock_create(s_ring_buffer_lock_t** s_ring_buffer_lock_pp);

/**
 * s_ring_buffer锁销毁
 */
void s_ring_buffer_lock_destroy(s_ring_buffer_lock_t** s_ring_buffer_lock_pp);
/**
 * s_ring_buffer上锁
 */
void s_ring_buffer_lock(s_ring_buffer_lock_t* s_ring_buffer_lock_p);

/**
 * s_ring_buffer尝试上锁
 */
int s_ring_buffer_try_lock(s_ring_buffer_lock_t* s_ring_buffer_lock_p);

/**
 * s_ring_buffer解锁
 */
void s_ring_buffer_unlock(s_ring_buffer_lock_t* s_ring_buffer_lock_p);

#ifdef __cplusplus
} /* "C" */
#endif

#endif /* S_RING_BUFFER_PLATFORM_H__ */