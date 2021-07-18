#ifndef S_LOG_SAFE_CFG_H__
#define S_LOG_SAFE_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * s_log_safe是否开启
 */
#define S_LOG_SAFE_ENABLE						(1)

/**
 * s_log_safe是否启用色彩格式
 */
#define S_LOG_SAFE_COLOR_OPEN                   (1)

/**
 * s_log_safe输出方式，可选择多种方式同时开启
 */
#define S_LOG_SAFE_OUT_BY_PRINTF				(1)				/* 通过printf输出 */
#define S_LOG_SAFE_OUT_BY_FILE				    (0)				/* 保存到文件,暂未实现 */
#define S_LOG_SAFE_OUT_BY_NET				    (0)				/* 保存到网络,暂未实现 */

/* s_log_safe输出单个缓冲最大字节数 */
#define S_LOG_SAFE_BUFF_LIMIT                   (1024)
/* s_log_safe log缓冲 最大缓冲log条数 */
#define S_LOG_SAFE_POOL_LIMIT                   (512)

/* 空闲间隔时间（单位ms）*/
#define S_LOG_SAFE_OUTPUT_IDLE_TIME             (10)
/* 插入超时时间（单位ms）*/
#define S_LOG_SAFE_POOL_INSERT_TIME_LIMIT       (50)
/* 取出超时时间（单位ms）*/
#define S_LOG_SAFE_POOL_REMOVE_TIME_LIMIT       (5)

/**
 * S_LOG_SAFE输出选项
 */
#define S_LOG_SAFE_OPT_ASSERT                   (1<<0)	       /* 断言 */
#define S_LOG_SAFE_OPT_VERSION                  (1<<1)         /* 版本 */
#define S_LOG_SAFE_OPT_ERROR                    (1<<2)         /* 错误 */
#define S_LOG_SAFE_OPT_WARN                     (1<<3)         /* 警告 */
#define S_LOG_SAFE_OPT_TRACE                    (1<<4)	       /* 跟踪 */	 
#define S_LOG_SAFE_OPT_INFO                     (1<<5)         /* 信息 */
#define S_LOG_SAFE_OPT_DEBUG                    (1<<6)         /* 调试 */
/**
 * S_LOG_SAFE输出等级
 */
#define S_LOG_SAFE_OPT_LVL                      S_LOG_SAFE_OPT_DEBUG

/* s_log_safe 优先级 */
#define S_LOG_SAFE_THREAD_PRIORITY              (8)
/* s_log_safe 堆栈大小 */
#define S_LOG_SAFE_THREAD_STACK_SIZE            (8*1024)
/* s_log_safe 线程名 */
#define S_LOG_SAFE_THREAD_NAME                  "s_log_safe"

#ifdef __cplusplus
} /* "C" */
#endif

#endif /* S_LOG_SAFE_CFG_H__ */