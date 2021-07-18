#include <stdio.h>
#include "s_log_safe.h"

void* thread_1_exec(void* arg)
{
    int* count =  (int*)arg;
    s_safe_tag("thread_1", S_LOG_SAFE_OPT_DEBUG);

    do {
        s_log_safe_a("%s %d","测试1",*count);
        usleep(5000);
    } while (*count -= 1);

    return s_log_safe_null;
}

void* thread_2_exec(void* arg)
{
    int* count =  (int*)arg;
    s_safe_tag("thread_2", S_LOG_SAFE_OPT_DEBUG);

    do {
        s_log_safe_v("%s %d","测试2",*count);
        usleep(5000);
    } while (*count -= 1);

    return s_log_safe_null;
}

void* thread_3_exec(void* arg)
{
    int* count =  (int*)arg;
    s_safe_tag("thread_3", S_LOG_SAFE_OPT_DEBUG);

    do {
        s_log_safe_e("%s %d","测试3",*count);
        usleep(5000);
    } while (*count -= 1);

    return s_log_safe_null;
}

void* thread_4_exec(void* arg)
{
    int* count =  (int*)arg;
    s_safe_tag("thread_4", S_LOG_SAFE_OPT_DEBUG);

    do {
        s_log_safe_w("%s %d","测试4",*count);
        usleep(5000);
    } while (*count -= 1);

    return s_log_safe_null;
}

void* thread_5_exec(void* arg)
{
    int* count =  (int*)arg;
    s_safe_tag("thread_5", S_LOG_SAFE_OPT_DEBUG);

    do {
        s_log_safe_t("%s %d","测试5",*count);
        usleep(5000);
    } while (*count -= 1);

    return s_log_safe_null;
}

void* thread_6_exec(void* arg)
{
    int* count =  (int*)arg;
    s_safe_tag("thread_6", S_LOG_SAFE_OPT_DEBUG);

    do {
        s_log_safe_i("%s %d","测试6",*count);
        usleep(5000);
    } while (*count -= 1);

    return s_log_safe_null;
}

void* thread_7_exec(void* arg)
{
    int* count =  (int*)arg;
    s_safe_tag("thread_7", S_LOG_SAFE_OPT_TRACE);

    do {
        s_log_safe_d("%s %d","测试7",*count);
        if((*count)%8 == 0) {
            s_safe_tag_log_level_limit_set(S_LOG_SAFE_OPT_DEBUG);
        } else {
            s_safe_tag_log_level_limit_set(S_LOG_SAFE_OPT_TRACE);
        }
        usleep(5000);
    } while (*count -= 1);

    return s_log_safe_null;
}

void* thread_main_exec(void* arg)
{
    int count = 0;
    unsigned int log_safe_pool_cap = 0;
    unsigned int log_safe_pool_used = 0;
    s_safe_tag("main", S_LOG_SAFE_OPT_DEBUG);

    log_safe_pool_cap = s_log_safe_output_pool_cap_get();
    while(1) {
        log_safe_pool_used = s_log_safe_output_pool_used_get();
        s_log_safe_i("%s log_safe_pool_cap:%d log_safe_pool_used:%d count:%d","main", log_safe_pool_cap, log_safe_pool_used, count++);
        usleep(5000);
    }

    return s_log_safe_null;
}

int main(void)
{
    int                  ret = 0;
    s_log_safe_thread_t* s_log_safe_thread_1_p;
    s_log_safe_thread_t* s_log_safe_thread_2_p;
    s_log_safe_thread_t* s_log_safe_thread_3_p;
    s_log_safe_thread_t* s_log_safe_thread_4_p;
    s_log_safe_thread_t* s_log_safe_thread_5_p;
    s_log_safe_thread_t* s_log_safe_thread_6_p;
    s_log_safe_thread_t* s_log_safe_thread_7_p;
    s_log_safe_thread_t* s_log_safe_thread_main_p;
    int                  count_1 = 777777;
    int                  count_2 = 666666;
    int                  count_3 = 555555;
    int                  count_4 = 444444;
    int                  count_5 = 333333;
    int                  count_6 = 222222;
    int                  count_7 = 111111;

    ret = s_log_safe_init();
    if(ret != 0) {
        return 0;
    }
    s_log_safe_thread_7_p = s_log_safe_thread_create(thread_main_exec, (void*)s_log_safe_null, "", S_LOG_SAFE_THREAD_PRIORITY, 1024);
    s_log_safe_thread_1_p = s_log_safe_thread_create(thread_1_exec, (void*)&count_1, "", 10, 1024);
    s_log_safe_thread_2_p = s_log_safe_thread_create(thread_2_exec, (void*)&count_2, "", 10, 1024);
    s_log_safe_thread_3_p = s_log_safe_thread_create(thread_3_exec, (void*)&count_3, "", 12, 1024);
    s_log_safe_thread_4_p = s_log_safe_thread_create(thread_4_exec, (void*)&count_4, "", 12, 1024);
    s_log_safe_thread_5_p = s_log_safe_thread_create(thread_5_exec, (void*)&count_5, "", 11, 1024);
    s_log_safe_thread_6_p = s_log_safe_thread_create(thread_6_exec, (void*)&count_6, "", 11, 1024);
    s_log_safe_thread_7_p = s_log_safe_thread_create(thread_7_exec, (void*)&count_7, "", 10, 1024);

    while(1) {
        sleep(1);
    }
    return 0;
}