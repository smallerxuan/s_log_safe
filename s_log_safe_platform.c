#include "s_log_safe_platform.h"
#include "assert.h"

static int get_thread_policy(pthread_attr_t *attr, int *policy)
{
    int rs = 0;
        
    rs = pthread_attr_getschedpolicy(attr, policy);/* SCHED_FIFO、SCHED_RR、SCHED_OTHER、UNKNOWN */
    assert(rs == 0);
    switch (*policy) {
    case SCHED_FIFO:
            printf("policy = SCHED_FIFO\n");
            break;
    case SCHED_RR:
            printf("policy = SCHED_RR\n");
            break;
    case SCHED_OTHER:
            printf("policy = SCHED_OTHER\n");
            break;
    default:
            printf("policy = UNKNOWN\n");
            break;
    }
    return *policy;
}

/**
 * 创建线程
 */
s_log_safe_thread_t *s_log_safe_thread_create(s_log_safe_thread_func_t      thread_func,
                                              void*                         thread_func_arg,
                                              __attribute__((unused))char*  thread_name,
                                              int                           thread_priority,
                                              __attribute__((unused))int    thread_stack_size)
{
    int                ret = 0;
    pthread_attr_t     attr;        /* 线程属性 */
    struct sched_param sched;       /* 调度参数 */
    int policy = SCHED_RR;          /* 调度策略: SCHED_FIFO、SCHED_RR、SCHED_OTHER、UNKNOWN */
    int priority_max;               /* 当前调度策略，最高优先级 */
    int priority_min;               /* 当前调度策略，最高优先级 */

    s_log_safe_thread_t *s_log_safe_thread_p = (s_log_safe_thread_t *)s_log_safe_malloc(sizeof(s_log_safe_thread_t));
    if(s_log_safe_thread_p == s_log_safe_null) {
        goto s_log_safe_thread_create_out;
    }
    /* 线程属性初始化 */
    ret = pthread_attr_init(&attr);
    if(ret != 0) {
        goto s_log_safe_thread_create_free_out;
    }

    /* 设置调度策略 */
    pthread_attr_setschedpolicy(&attr, policy);   
    get_thread_policy(&attr, &policy);   

    /* 当前策略最高优先级 */
    priority_max = sched_get_priority_max(policy);
    /* 当前策略最低优先级 */
    priority_min = sched_get_priority_min(policy);
    /* 真实设置优先级 */
    sched.sched_priority = (thread_priority > priority_min)?((thread_priority > priority_max)?(priority_max):(thread_priority)):(priority_min);
    /* 设置调度参数 */
    pthread_attr_setschedparam(&attr, &sched);
    /* 设置线程分离 */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /* 创建线程 */
    ret = pthread_create(&(s_log_safe_thread_p->thread), &attr, thread_func, thread_func_arg);
    if (ret != 0) {
        goto s_log_safe_thread_create_free_out;
    }
    goto s_log_safe_thread_create_out;

s_log_safe_thread_create_free_out:
    if(s_log_safe_null != s_log_safe_thread_p) {
        s_log_safe_free(s_log_safe_thread_p);
        s_log_safe_thread_p = s_log_safe_null;
    }  

s_log_safe_thread_create_out:
    return s_log_safe_thread_p;
}

/**
 * 销毁线程
 */
void s_log_safe_thread_delete(s_log_safe_thread_t** s_log_safe_thread_pp)
{
    if (*s_log_safe_thread_pp != s_log_safe_null) {
        s_log_safe_free(*s_log_safe_thread_pp);
        *s_log_safe_thread_pp = s_log_safe_null;
    }
}

/**
 * 创建锁
 */
s_log_safe_mutex_t* s_log_safe_mutex_create(void)
{
    int ret = 0;
    s_log_safe_mutex_t* s_log_safe_mutex_p = s_log_safe_null;

    s_log_safe_mutex_p = (s_log_safe_mutex_t*)s_log_safe_malloc(sizeof(s_log_safe_mutex_t));
    if (s_log_safe_null == s_log_safe_mutex_p) {
        goto s_log_safe_mutex_create_out;
    }
    ret = pthread_mutex_init(&(s_log_safe_mutex_p->mutex), NULL);
    if (ret != 0) {
        s_log_safe_free(s_log_safe_mutex_p);
        s_log_safe_mutex_p = s_log_safe_null;
    }

s_log_safe_mutex_create_out:
    return s_log_safe_mutex_p;
}

/**
 * 销毁锁
 */
void s_log_safe_mutex_destroy(s_log_safe_mutex_t** mutex_pp)
{
    if (s_log_safe_null != mutex_pp && s_log_safe_null != *mutex_pp) {
        pthread_mutex_destroy(&((*mutex_pp)->mutex));
        s_log_safe_free(*mutex_pp);
        *mutex_pp = s_log_safe_null;
    }
}

/**
 * 上锁
 * 成功，返回1；失败，返回0
 */
int s_log_safe_mutex_lock(s_log_safe_mutex_t* mutex_p)
{
    int ret = 0;
    /* 阻塞调用，上锁 */
    ret = pthread_mutex_lock(&(mutex_p->mutex));
    if(0 == ret) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 尝试上锁
 * 成功，返回1；失败，返回0
 */
int s_log_safe_mutex_try_lock(s_log_safe_mutex_t* mutex_p)
{
    int ret = 0;
    /* 非阻塞调用，尝试上锁 */
    ret = pthread_mutex_trylock(&(mutex_p->mutex));
    if(0 == ret) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 解锁
 * 成功，返回1；失败，返回0
 */
int s_log_safe_mutex_unlock(s_log_safe_mutex_t* mutex_p)
{
    int ret = 0;
    ret = pthread_mutex_unlock(&(mutex_p->mutex));
    if(0 == ret) {
        return 1;
    } else {
        return 0;
    }
}
