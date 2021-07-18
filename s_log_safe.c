#include "s_log_safe.h"

typedef struct s_log_safe_s {
    s_log_safe_thread_t* s_log_safe_thread_p;
    s_ring_buffer_t*     s_log_safe_output_pool_p;
    unsigned int         s_log_safe_output_pool_cap;
} s_log_safe_t;

typedef struct s_log_safe_log_element_s {
    char*           tag;
    unsigned char   log_level;
    char*           log_file;
    char*           log_func;
    long            log_line;
    char*           log_main_body;
} s_log_safe_log_element_t;

static s_log_safe_t* s_log_safe_g = s_log_safe_null;

static s_log_safe_t* s_log_safe_constructor(void)
{
    s_log_safe_t* s_log_safe_p = s_log_safe_null;

    s_log_safe_p = s_log_safe_malloc(sizeof(s_log_safe_t));
    if(s_log_safe_null == s_log_safe_p) {
        goto s_log_safe_constructor_out;
    }

    s_log_safe_p->s_log_safe_output_pool_p = s_ring_buffer_constructor(sizeof(s_log_safe_log_element_t*), S_LOG_SAFE_POOL_LIMIT, NULL, NULL);
    s_log_safe_p->s_log_safe_output_pool_cap = S_LOG_SAFE_POOL_LIMIT;
s_log_safe_constructor_out:
    return s_log_safe_p;
}

static void s_log_safe_destructor(s_log_safe_t* s_log_safe_p)
{
    if(s_log_safe_null == s_log_safe_p) {
        return;
    }
    return;
}

/**
 * 通过s_log输出
 */
static void s_log_safe_output(void)
{
    int err = 0;
    unsigned int read_count = 0;
    s_log_safe_log_element_t* s_log_safe_log_element_p = s_log_safe_null;

    /* 从s_log_safe 的 rb缓冲区中取出一个 s_log_safe_log_element_p，提取log相关数据，并通过s_log输出 */
    read_count = s_ring_buffer_read_elements(s_log_safe_g->s_log_safe_output_pool_p,
                                             (void*)&s_log_safe_log_element_p,
                                             1, S_LOG_SAFE_POOL_REMOVE_TIME_LIMIT, &err);
    if(read_count == 1 && s_log_safe_null != s_log_safe_log_element_p) {
        switch(s_log_safe_log_element_p->log_level) {
            case S_LOG_OPT_ASSERT:
                /* 断言 */
                s_log_safe_assert(s_log_safe_log_element_p->tag,\
                                  s_log_safe_log_element_p->log_file,\
                                  s_log_safe_log_element_p->log_func,\
                                  s_log_safe_log_element_p->log_line,"%s",s_log_safe_log_element_p->log_main_body);
                break;
            case S_LOG_OPT_VERSION:
                /* 版本 */
                s_log_safe_version(s_log_safe_log_element_p->tag,\
                                  s_log_safe_log_element_p->log_file,\
                                  s_log_safe_log_element_p->log_func,\
                                  s_log_safe_log_element_p->log_line,"%s",s_log_safe_log_element_p->log_main_body);
                break;
            case S_LOG_OPT_ERROR:
                /* 错误 */
                s_log_safe_error(s_log_safe_log_element_p->tag,\
                                  s_log_safe_log_element_p->log_file,\
                                  s_log_safe_log_element_p->log_func,\
                                  s_log_safe_log_element_p->log_line,"%s",s_log_safe_log_element_p->log_main_body);
                break;
            case S_LOG_OPT_WARN:
                /* 警告 */
                s_log_safe_warn(s_log_safe_log_element_p->tag,\
                                  s_log_safe_log_element_p->log_file,\
                                  s_log_safe_log_element_p->log_func,\
                                  s_log_safe_log_element_p->log_line,"%s",s_log_safe_log_element_p->log_main_body);
                break;
            case S_LOG_OPT_TRACE:
                /* 跟踪 */
                s_log_safe_trace(s_log_safe_log_element_p->tag,\
                                  s_log_safe_log_element_p->log_file,\
                                  s_log_safe_log_element_p->log_func,\
                                  s_log_safe_log_element_p->log_line,"%s",s_log_safe_log_element_p->log_main_body);
                break;
            case S_LOG_OPT_INFO:
                /* 信息 */
                s_log_safe_info(s_log_safe_log_element_p->tag,\
                                  s_log_safe_log_element_p->log_file,\
                                  s_log_safe_log_element_p->log_func,\
                                  s_log_safe_log_element_p->log_line,"%s",s_log_safe_log_element_p->log_main_body);
                break;
            case S_LOG_OPT_DEBUG:
            default :
                /* 调试 */ 
                s_log_safe_debug(s_log_safe_log_element_p->tag,\
                                  s_log_safe_log_element_p->log_file,\
                                  s_log_safe_log_element_p->log_func,\
                                  s_log_safe_log_element_p->log_line,"%s",s_log_safe_log_element_p->log_main_body);
                break;
        }
        
        if(s_log_safe_null != s_log_safe_log_element_p->tag)
            s_log_safe_free(s_log_safe_log_element_p->tag);
        if(s_log_safe_null != s_log_safe_log_element_p->log_file)
            s_log_safe_free(s_log_safe_log_element_p->log_file);
        if(s_log_safe_null != s_log_safe_log_element_p->log_func)
            s_log_safe_free(s_log_safe_log_element_p->log_func);
        if(s_log_safe_null != s_log_safe_log_element_p->log_main_body)
            s_log_safe_free(s_log_safe_log_element_p->log_main_body);
        s_log_safe_free(s_log_safe_log_element_p);
        s_log_safe_log_element_p = s_log_safe_null;
    }

    return;
}

static void* s_log_safe_thread_exec_func(void* arg)
{
    int used = 0;

    while(1) {
        /* 查看当前缓冲区使用量 */ 
        used = s_ring_buffer_could_read_num_get(s_log_safe_g->s_log_safe_output_pool_p);
        if(used > 0) {
            s_log_safe_output();
        } else {
            s_ring_buff_sleep(S_LOG_SAFE_OUTPUT_IDLE_TIME);
        }
    }
    return s_log_safe_null;
}

/*************************************** 外部接口 *************************************/

/**
 * 获取 s_log_safe 版本号
 */
const char* s_log_safe_version_get(void)
{
    return S_LOG_SAFE_VERSION;
}
/**
 * s_log_safe 初始化
 */
int s_log_safe_init(void)
{
    s_log_safe_g = s_log_safe_constructor();
    if(s_log_safe_null == s_log_safe_g) {
        return -1;
    }
    s_log_safe_g->s_log_safe_thread_p = s_log_safe_thread_create(s_log_safe_thread_exec_func,
                                                                 (void*)s_log_safe_null,
                                                                  S_LOG_SAFE_THREAD_NAME,
                                                                  S_LOG_SAFE_THREAD_PRIORITY,
                                                                  S_LOG_SAFE_THREAD_STACK_SIZE);

    return 0;
}

/**
 * s_log_safe 反初始化
 */
int s_log_safe_deinit(void)
{
    return 0;
}

/**
 * 获取s_log_safe log缓冲池容量
 */
unsigned int s_log_safe_output_pool_cap_get(void) {
    if(s_log_safe_null == s_log_safe_g || s_log_safe_null == s_log_safe_g->s_log_safe_output_pool_p) {
        return 0;
    }
    return s_log_safe_g->s_log_safe_output_pool_cap;
}

/**
 * 获取s_log_safe log缓冲池使用量
 */
unsigned int s_log_safe_output_pool_used_get(void) {
    if(s_log_safe_null == s_log_safe_g || s_log_safe_null == s_log_safe_g->s_log_safe_output_pool_p) {
        return 0;
    }
    return s_ring_buffer_could_read_num_get(s_log_safe_g->s_log_safe_output_pool_p);
}

/**
 * 输出log到s_log_safe的rb缓冲区
 */
int s_log_safe_out(const char*         tag,
                   const unsigned char log_level,
                   const unsigned char log_level_limit,
                   const char*         log_file,
                   const char*         log_func,
                   const long          log_line,
                   const char*         log_main_body)
{
    int ret = 0;
    int err = 0;
    unsigned int write_count = 0;
    unsigned char log_level_limit_temp = log_level_limit;
    char*         log_main_body_temp   = log_main_body;

    log_level_limit_temp = (log_level_limit_temp > S_LOG_SAFE_OPT_DEBUG) ? (S_LOG_SAFE_OPT_DEBUG) : (log_level_limit_temp);
    if(log_level > log_level_limit_temp) {
        goto s_log_safe_out_out;
    }

    s_log_safe_log_element_t* s_log_safe_log_element_p = s_log_safe_null;
    s_log_safe_log_element_p = s_log_safe_malloc(sizeof(s_log_safe_log_element_t));
    if(s_log_safe_null == s_log_safe_log_element_p) {
        ret = -1;
        goto s_log_safe_out_out;
    }

    s_log_safe_log_element_p->tag = s_log_safe_malloc(sizeof(char)*(s_log_safe_strlen(tag)+1));
    s_log_safe_memset(s_log_safe_log_element_p->tag, 0, (s_log_safe_strlen(tag)+1));
    s_log_safe_memcpy(s_log_safe_log_element_p->tag, tag, s_log_safe_strlen(tag));

    s_log_safe_log_element_p->log_file = s_log_safe_malloc(sizeof(char)*(s_log_safe_strlen(log_file)+1));
    s_log_safe_memset(s_log_safe_log_element_p->log_file, 0, (s_log_safe_strlen(log_file)+1));
    s_log_safe_memcpy(s_log_safe_log_element_p->log_file, log_file, s_log_safe_strlen(log_file));

    s_log_safe_log_element_p->log_func = s_log_safe_malloc(sizeof(char)*(s_log_safe_strlen(log_func)+1));
    s_log_safe_memset(s_log_safe_log_element_p->log_func, 0, (s_log_safe_strlen(log_func)+1));
    s_log_safe_memcpy(s_log_safe_log_element_p->log_func, log_func, s_log_safe_strlen(log_func));

    s_log_safe_log_element_p->log_main_body = log_main_body_temp;
    log_main_body_temp = s_log_safe_null;

    s_log_safe_log_element_p->log_level = log_level;
    s_log_safe_log_element_p->log_line  = log_line;

    /* 将s_log_safe_log_element_p存入 s_log_safe 的 rb缓冲区 */
s_log_safe_out_retry:
    
    write_count = s_ring_buffer_write_elements(s_log_safe_g->s_log_safe_output_pool_p,
                                               (void*)&s_log_safe_log_element_p,
                                               1, S_LOG_SAFE_POOL_INSERT_TIME_LIMIT, &err);
    if(write_count != 1) {
        if(err != -1) {
            goto s_log_safe_out_retry;
        }
        ret = -1;
    }

s_log_safe_out_out:
    if(s_log_safe_null != log_main_body_temp) {
        s_log_safe_free(log_main_body_temp);
        log_main_body_temp = s_log_safe_null;
    }
    return ret;
}