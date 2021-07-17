#ifndef __S_LOG_H__
#define __S_LOG_H__
#include "s_log_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (S_LOG_ENABLE == 1)

/**
 * s_log版本号（V主版本号.次版本号.版本内修改序号）
 */
#define S_LOG_VERSION						"V0.0.1"

/**
 * s_log固定格式缓冲区大小（单位Byte）
 */
#define FIX_FMT_BUFF_SIZE	                (48)
#define CAG_FMT_BUFF_SIZE                   (512)

#define __FILENAME__ (s_log_strrchr(__FILE__, '/') ? s_log_strrchr(__FILE__, '/') + 1 : __FILE__)

#if S_LOG_OPT_LVL >= S_LOG_OPT_ASSERT
    #define s_log_assert(tag, fmt, ...) \
        s_log_output(S_LOG_OPT_ASSERT,tag,__FILENAME__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
	#else
        #define s_log_assert(tag, fmt, ...)
#endif /* S_LOG_OPT_LVL >= S_LOG_OPT_ASSERT */

#if S_LOG_OPT_LVL >= S_LOG_OPT_VERSION
        #define s_log_version(tag, fmt, ...) \
                s_log_output(S_LOG_OPT_VERSION,tag,__FILENAME__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
    #else
        #define s_log_version(tag, fmt, ...)
#endif /* S_LOG_OPT_LVL >= S_LOG_OPT_VERSION */

#if S_LOG_OPT_LVL >= S_LOG_OPT_ERROR
    #define s_log_error(tag, fmt, ...) \
        s_log_output(S_LOG_OPT_ERROR,tag,__FILENAME__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
    #else
        #define s_log_error(tag, fmt, ...)
#endif /* S_LOG_OPT_LVL >= S_LOG_OPT_ERROR */

#if S_LOG_OPT_LVL >= S_LOG_OPT_WARN
    #define s_log_warn(tag, fmt, ...) \
        s_log_output(S_LOG_OPT_WARN,tag,__FILENAME__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
    #else
        #define s_log_warn(tag, fmt, ...)
#endif /* S_LOG_OPT_LVL >= S_LOG_OPT_WARN */

#if S_LOG_OPT_LVL >= S_LOG_OPT_TRACE
    #define s_log_trace(tag, fmt, ...) \
        s_log_output(S_LOG_OPT_TRACE,tag,__FILENAME__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
    #else
        #define s_log_trace(tag, fmt, ...)
#endif /* S_LOG_OPT_LVL >= S_LOG_OPT_TRACE */ 

#if S_LOG_OPT_LVL >= S_LOG_OPT_INFO
    #define s_log_info(tag, fmt, ...) \
        s_log_output(S_LOG_OPT_INFO,tag,__FILENAME__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
    #else
        #define s_log_info(tag,fmt,...)
#endif /* S_LOG_OPT_LVL >= S_LOG_OPT_INFO */

#if S_LOG_OPT_LVL == S_LOG_OPT_DEBUG
    #define s_log_debug(tag, fmt, ...) \
        s_log_output(S_LOG_OPT_DEBUG,tag,__FILENAME__,__FUNCTION__,__LINE__,fmt,__VA_ARGS__)
    #else
        #define s_log_debug(tag, fmt, ...)
#endif /* S_LOG_OPT_LVL == S_LOG_OPT_DEBUG */

/**
 * s_log换行
 */
#define S_LOG_NEWLINE_SWITCH     "\r\n"

/**
 * s_log 固定格式部分
 */
#define ASSERT_FBCS_START		 FBCS_START FS_BOLD ";" FC_BLUE "m"
#define ASSERT_FBCS_END			 FBCS_END
#define VERSION_FBCS_START		 FBCS_START FS_BOLD ";" FC_MAGENTA "m"
#define VERSION_FBCS_END		 FBCS_END
#define ERROR_FBCS_START		 FBCS_START FS_BOLD ";" FC_RED "m"
#define ERROR_FBCS_END			 FBCS_END
#define WARN_FBCS_START			 FBCS_START FS_BOLD ";" FC_YELLOW "m"
#define WARN_FBCS_END		     FBCS_END
#define TRACE_FBCS_START	     FBCS_START FS_BOLD ";" FC_CYAN "m"
#define TRACE_FBCS_END			 FBCS_END
#define INFO_FBCS_START			 FBCS_START FS_BOLD ";" FC_GREEN "m"
#define INFO_FBCS_END			 FBCS_END
#define DEBUG_FBCS_START		 FBCS_START FS_BOLD ";" FC_WHITE "m"
#define DEBUG_FBCS_END			 FBCS_END
#define USER_FBCS_START			 FBCS_START FS_NORMAL ";" FC_WHITE ";" BC_BLACK "m"
#define USER_FBCS_END			 FBCS_END

#define s_tag(const_str)	     static char* tag = const_str    
#define s_log_a(fmt,...)     	 s_log_assert(tag,fmt,__VA_ARGS__)
#define s_log_e(fmt,...)     	 s_log_error(tag,fmt,__VA_ARGS__)
#define s_log_w(fmt,...)     	 s_log_warn(tag,fmt,__VA_ARGS__)
#define s_log_t(fmt,...)	 	 s_log_trace(tag,fmt,__VA_ARGS__)
#define s_log_i(fmt,...)     	 s_log_info(tag,fmt,__VA_ARGS__)
#define s_log_d(fmt,...)     	 s_log_debug(tag,fmt,__VA_ARGS__)
#define s_log_v(fmt,...)     	 s_log_version(tag,fmt,__VA_ARGS__)

/**
 * s_log输出选项类型
 */
typedef unsigned char _S_Log_OPT;

typedef void (*S_LOG_OUTPUT_T)(_S_Log_OPT opt, const char *tag, const char *file, const char *func,const long line, const char *format, ...);
extern S_LOG_OUTPUT_T s_log_output;

char* s_log_strrchr(const char *str, int c);

#else
	#define s_tag(const_str)
	#define s_log_a(fmt, ...)
	#define s_log_e(fmt, ...)
	#define s_log_w(fmt, ...)
	#define s_log_t(fmt, ...)
	#define s_log_i(fmt, ...)
	#define s_log_d(fmt, ...)
	#define s_log_v(fmt, ...)
#endif /* S_LOG_ENABLE == 1 */


/**
 * s_log 字体设置
 */
#define FBCS_START               "\e["
#define FBCS_END                 "\e[0m"
/**
 * s_log 字体风格
 */
#define FS_BOLD                  "1"
#define FS_UNDERLINE             "4"
#define FS_BLINK                 "5"
#define FS_NORMAL                "22"
/**
 * s_log 字体色彩
 */
#define FC_BLACK                 "30"
#define FC_RED                   "31"
#define FC_GREEN                 "32"
#define FC_YELLOW                "33"
#define FC_BLUE                  "34"
#define FC_MAGENTA               "35"
#define FC_CYAN                  "36"
#define FC_WHITE                 "37"
/**
 * s_log 背景色彩
 */
#define BC_NULL					 ""
#define BC_BLACK                 "40"
#define BC_RED                   "41"
#define BC_GREEN                 "42"
#define BC_YELLOW                "43"
#define BC_BLUE                  "44"
#define BC_MAGENTA               "45"
#define BC_CYAN                  "46"
#define BC_WHITE                 "47"

#ifdef __cplusplus
}
#endif

#endif /* __S_LOG_H__ */
