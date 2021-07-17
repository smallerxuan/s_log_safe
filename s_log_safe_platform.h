#ifndef S_LOG_SAFE_PLATFORM_H__
#define S_LOG_SAFE_PLATFORM_H__

#include <stdio.h>          /* 标准输入输出 */
#include <stdlib.h>         /* 标准c库 */
#include <string.h>         /*  字符串处理库 */
#include <pthread.h>        /* 系统线程 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef s_log_safe_malloc
#define s_log_safe_malloc       malloc
#endif

#ifndef s_log_safe_free
#define s_log_safe_free         free
#endif

#ifndef s_log_safe_memcpy
#define s_log_safe_memcpy       memcpy
#endif

#ifndef s_log_safe_memset
#define s_log_safe_memset       memset
#endif

#ifndef s_log_safe_strlen
#define s_log_safe_strlen       strlen
#endif

#ifndef s_log_safe_null
#define s_log_safe_null         NULL
#endif

#define s_log_safe_usleep(x)    usleep(x)
#define s_log_safe_msleep(x)    s_log_safe_usleep(1000 * x)
#define s_log_safe_sleep(x)     s_log_safe_msleep(x)

/* 线程执行体类型定义 */
typedef void* (*s_log_safe_thread_func_t)(void *);
/* 线程类型定义 */
typedef struct s_log_safe_thread_s {
    pthread_t thread;
} s_log_safe_thread_t;
/**
 * 创建线程
 */
s_log_safe_thread_t *s_log_safe_thread_create(s_log_safe_thread_func_t     thread_func,
                                              void*                        thread_func_arg,
                                              __attribute__((unused))char* thread_name,
                                              int                          thread_priority,
                                              __attribute__((unused))int   thread_stack_size);
/**
 * 销毁线程
 */
void s_log_safe_thread_delete(s_log_safe_thread_t** s_log_safe_thread_pp);


/* 锁类型定义 */
typedef struct s_log_safe_mutex_s {
    pthread_mutex_t mutex;
} s_log_safe_mutex_t;
/**
 * 创建锁
 * 成功，返回锁地址；失败，返回 s_log_safe_null
 */
s_log_safe_mutex_t* s_log_safe_mutex_create(void);
/**
 * 销毁锁
 */
void s_log_safe_mutex_destroy(s_log_safe_mutex_t** mutex_pp);
/**
 * 上锁
 * 成功，返回1；失败，返回0
 */
int s_log_safe_mutex_lock(s_log_safe_mutex_t* mutex_p);
/**
 * 尝试上锁
 * 成功，返回1；失败，返回0
 */
int s_log_safe_mutex_try_lock(s_log_safe_mutex_t* mutex_p);
/**
 * 解锁
 * 成功，返回1；失败，返回0
 */
int s_log_safe_mutex_unlock(s_log_safe_mutex_t* mutex_p);

#ifdef __cplusplus
} /* "C" */
#endif

#endif /* S_LOG_SAFE_PLATFORM_H__ */