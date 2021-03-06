#ifndef S_LOG_SAFE_H__
#define S_LOG_SAFE_H__

#include "s_log_safe_cfg.h"
#include "s_log_safe_platform.h"
#include "s_log.h"
#include "s_ring_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * s_log_safe版本号（V主版本号.次版本号.版本内修改序号）
 */
#define S_LOG_SAFE_VERSION						"V0.0.4"

#if S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_ASSERT
    #define s_log_safe_assert(tag, file, func,line, fmt, ...) \
        s_log_output(S_LOG_SAFE_OPT_ASSERT,tag,(s_log_strrchr(file, '/') ? s_log_strrchr(file, '/') + 1 : file),func,line,fmt,__VA_ARGS__)
#else
    #define s_log_safe_assert(tag, file, func,line, fmt, ...)
#endif /* S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_ASSERT */

#if S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_VERSION
        #define s_log_safe_version(tag, file, func,line, fmt, ...) \
                s_log_output(S_LOG_SAFE_OPT_VERSION,tag,(s_log_strrchr(file, '/') ? s_log_strrchr(file, '/') + 1 : file),func,line,fmt,__VA_ARGS__)
#else
    #define s_log_safe_version(tag, file, func,line, fmt, ...)
#endif /* S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_VERSION */

#if S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_ERROR
    #define s_log_safe_error(tag, file, func,line, fmt, ...) \
        s_log_output(S_LOG_SAFE_OPT_ERROR,tag,(s_log_strrchr(file, '/') ? s_log_strrchr(file, '/') + 1 : file),func,line,fmt,__VA_ARGS__)
#else
    #define s_log_safe_error(tag, file, func,line, fmt, ...)
#endif /* S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_ERROR */

#if S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_WARN
    #define s_log_safe_warn(tag, file, func,line, fmt, ...) \
        s_log_output(S_LOG_SAFE_OPT_WARN,tag,(s_log_strrchr(file, '/') ? s_log_strrchr(file, '/') + 1 : file),func,line,fmt,__VA_ARGS__)
#else
    #define s_log_safe_warn(tag, file, func,line, fmt, ...)
#endif /* S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_WARN */

#if S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_TRACE
    #define s_log_safe_trace(tag, file, func,line, fmt, ...) \
        s_log_output(S_LOG_SAFE_OPT_TRACE,tag,(s_log_strrchr(file, '/') ? s_log_strrchr(file, '/') + 1 : file),func,line,fmt,__VA_ARGS__)
#else
    #define s_log_safe_trace(tag, file, func,line, fmt, ...)
#endif /* S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_TRACE */ 

#if S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_INFO
    #define s_log_safe_info(tag, file, func,line, fmt, ...) \
        s_log_output(S_LOG_SAFE_OPT_INFO,tag,(s_log_strrchr(file, '/') ? s_log_strrchr(file, '/') + 1 : file),func,line,fmt,__VA_ARGS__)
#else
    #define s_log_safe_info(tag, file, func,line, fmt, ...)
#endif /* S_LOG_SAFE_OPT_LVL >= S_LOG_SAFE_OPT_INFO */

#if S_LOG_SAFE_OPT_LVL == S_LOG_SAFE_OPT_DEBUG
    #define s_log_safe_debug(tag, file, func,line, fmt, ...) \
        s_log_output(S_LOG_SAFE_OPT_DEBUG,tag,(s_log_strrchr(file, '/') ? s_log_strrchr(file, '/') + 1 : file),func,line,fmt,__VA_ARGS__)
#else
    #define s_log_safe_debug(tag, file, func,line, fmt, ...)
#endif /* S_LOG_SAFE_OPT_LVL == S_LOG_SAFE_OPT_DEBUG */

/**
 * s_safe_tag 类型定义
 */
typedef struct s_safe_tag_s {
    char*         tag_name;
    unsigned char log_level_limit;
} s_safe_tag_t;
/**
 * s_safe_tag对象定义宏
 */
#define s_safe_tag(const_tag_name, log_level_limit)	 static s_safe_tag_t tag = {const_tag_name, log_level_limit}

/**
 * s_safe_tag对象输出级别限制设置
 */
#define s_safe_tag_log_level_limit_set(log_level_limit_new) do {tag.log_level_limit = log_level_limit_new;}while(0)

#define  s_safe_log_fmt_par(fmt,...) \
char* __str__ = (char*)s_log_safe_malloc(sizeof(char)*S_LOG_SAFE_BUFF_LIMIT);\
snprintf(__str__,(S_LOG_SAFE_BUFF_LIMIT-1),fmt,__VA_ARGS__)

#define  s_safe_log_out_par(__log_level__) \
s_log_safe_out(tag.tag_name,__log_level__,tag.log_level_limit,__FILE__,__FUNCTION__,__LINE__,__str__);

#define s_log_safe_a(fmt,...) do{s_safe_log_fmt_par(fmt,__VA_ARGS__);s_safe_log_out_par(S_LOG_SAFE_OPT_ASSERT)}while(0)
#define s_log_safe_v(fmt,...) do{s_safe_log_fmt_par(fmt,__VA_ARGS__);s_safe_log_out_par(S_LOG_SAFE_OPT_VERSION)}while(0)
#define s_log_safe_e(fmt,...) do{s_safe_log_fmt_par(fmt,__VA_ARGS__);s_safe_log_out_par(S_LOG_SAFE_OPT_ERROR)}while(0)
#define s_log_safe_w(fmt,...) do{s_safe_log_fmt_par(fmt,__VA_ARGS__);s_safe_log_out_par(S_LOG_SAFE_OPT_WARN)}while(0)
#define s_log_safe_t(fmt,...) do{s_safe_log_fmt_par(fmt,__VA_ARGS__);s_safe_log_out_par(S_LOG_SAFE_OPT_TRACE)}while(0)
#define s_log_safe_i(fmt,...) do{s_safe_log_fmt_par(fmt,__VA_ARGS__);s_safe_log_out_par(S_LOG_SAFE_OPT_INFO)}while(0)
#define s_log_safe_d(fmt,...) do{s_safe_log_fmt_par(fmt,__VA_ARGS__);s_safe_log_out_par(S_LOG_SAFE_OPT_DEBUG)}while(0)

/**
 * 获取 s_log_safe 版本号
 */
const char* s_log_safe_version_get(void);

/**
 * s_log_safe 初始化
 */
int s_log_safe_init(void);
/**
 * s_log_safe 反初始化
 */
int s_log_safe_deinit(void);

/**
 * 获取s_log_safe log缓冲池容量
 */
unsigned int s_log_safe_output_pool_cap_get(void);
/**
 * 获取s_log_safe log缓冲池使用量
 */
unsigned int s_log_safe_output_pool_used_get(void);

/**
 * 输出log到s_log_safe的rb缓冲区
 */
int s_log_safe_out(const char*         tag,
                   const unsigned char log_level,
                   const unsigned char log_level_limit,
                   const char*         log_file,
                   const char*         log_func,
                   const long          log_line,
                   const char*         log_main_body);

#ifdef __cplusplus
} /* "C" */
#endif

#endif /* S_LOG_SAFE_H__ */