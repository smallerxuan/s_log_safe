#ifndef __S_LOG_CFG_H__
#define __S_LOG_CFG_H__

#include "s_log_safe_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * S_Log是否开启
 */
#define S_LOG_ENABLE						S_LOG_SAFE_ENABLE

/**
 * S_Log是否启用色彩格式
 */
#define S_LOG_COLOR_OPEN                    S_LOG_SAFE_COLOR_OPEN

/**
 * S_Log输出方式，可选择多种方式同时开启
 */
#define S_LOG_OUT_BY_PRINTF					S_LOG_SAFE_OUT_BY_PRINTF	/* 通过printf输出 */
#define S_LOG_OUT_BY_FILE				    S_LOG_SAFE_OUT_BY_FILE		/* 保存到文件,暂未实现 */
#define S_LOG_OUT_BY_NET				    S_LOG_SAFE_OUT_BY_NET 		/* 保存到网络,暂未实现 */

/**
 * S_Log输出长度限制（缓冲区大小，单位Byte）
 */
#define S_LOG_BUFF_SIZE		                (S_LOG_SAFE_BUFF_LIMIT + 256)

/**
 * S_Log输出选项
 */
#define S_LOG_OPT_ASSERT					S_LOG_SAFE_OPT_ASSERT		/* 断言 */
#define S_LOG_OPT_VERSION                   S_LOG_SAFE_OPT_VERSION		/* 版本 */
#define S_LOG_OPT_ERROR                   	S_LOG_SAFE_OPT_ERROR		/* 错误 */
#define S_LOG_OPT_WARN                     	S_LOG_SAFE_OPT_WARN			/* 警告 */
#define S_LOG_OPT_TRACE						S_LOG_SAFE_OPT_TRACE		/* 跟踪 */	 
#define S_LOG_OPT_INFO                     	S_LOG_SAFE_OPT_INFO			/* 信息 */
#define S_LOG_OPT_DEBUG                     S_LOG_SAFE_OPT_DEBUG		/* 调试 */ 

/**
 * S_Log输出选项等级
 */
#define S_LOG_OPT_LVL 						S_LOG_SAFE_OPT_LVL

#ifdef __cplusplus
}
#endif

#endif /* __S_LOG_CFG_H__ */
