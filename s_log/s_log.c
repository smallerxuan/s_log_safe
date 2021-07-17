#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "s_log.h"

#if (S_LOG_ENABLE == 1)

typedef int (*S_LOG_PRINTF)(const char *s_log_str);
#if (S_LOG_OUT_BY_PRINTF == 1)
	int s_log_out_by_printf(const char *s_log_str);
	S_LOG_PRINTF s_log_printf = s_log_out_by_printf;
#endif

#if (S_LOG_OUT_BY_FILE == 1)
	int s_log_out_by_printf(const char *s_log_str);
	S_LOG_PRINTF s_log_printf_file = s_log_out_by_printf;
#endif

#if (S_LOG_OUT_BY_NET == 1)
	int s_log_out_by_printf(const char *s_log_str);
	S_LOG_PRINTF s_log_printf_net = s_log_out_by_printf;
#endif

void s_log_print(_S_Log_OPT opt, const char *tag, const char *file, const char *func,const long line, const char *format, ...);
S_LOG_OUTPUT_T s_log_output = s_log_print;

#if (S_LOG_COLOR_OPEN == 1)
	static char fixed_format[FIX_FMT_BUFF_SIZE]     = "%s%s%s->{File:%s,Func:%s,Line:%ld}:%s%s%s%s %s";
#else
	static char fixed_format[FIX_FMT_BUFF_SIZE]     = "%s%s->{File:%s,Func:%s,Line:%ld}:%s %s";
#endif
static char change_format[CAG_FMT_BUFF_SIZE]    = {0};
static char s_log_buff[S_LOG_BUFF_SIZE]			= {0};

void s_log_print(_S_Log_OPT opt, const char *tag, const char *file, const char *func,const long line, const char *format, ...) {
	char 		*opt_str 		 = NULL;
	va_list 	args;
	int			len				 = 0;
#if (S_LOG_COLOR_OPEN == 1)
	char		*fixed_bfs_start = "";
	char		*fixed_bfs_end   = "";
#else
#endif

	memset(change_format, 0, CAG_FMT_BUFF_SIZE);

	switch(opt) {
		case S_LOG_OPT_ASSERT:
			opt_str = "[A]";
		#if (S_LOG_COLOR_OPEN == 1)
			fixed_bfs_start = ASSERT_FBCS_START; fixed_bfs_end = ASSERT_FBCS_END; 
		#else
		#endif
			break;
		case S_LOG_OPT_VERSION:
			opt_str = "[V]";
		#if (S_LOG_COLOR_OPEN == 1)
			fixed_bfs_start = VERSION_FBCS_START;fixed_bfs_end = VERSION_FBCS_END;
		#else
		#endif
			break;
        case S_LOG_OPT_ERROR: 
			opt_str = "[E]";
		#if (S_LOG_COLOR_OPEN == 1)
			fixed_bfs_start = ERROR_FBCS_START;  fixed_bfs_end = ERROR_FBCS_END;
		#else
		#endif
			break;
        case S_LOG_OPT_WARN:
			opt_str = "[W]";
		#if (S_LOG_COLOR_OPEN == 1)
			fixed_bfs_start = WARN_FBCS_START;   fixed_bfs_end = WARN_FBCS_END;
		#else
		#endif
			break;
        case S_LOG_OPT_TRACE:
			opt_str = "[T]";
		#if (S_LOG_COLOR_OPEN == 1)
			fixed_bfs_start = TRACE_FBCS_START;  fixed_bfs_end = TRACE_FBCS_END;   
		#else
		#endif
			break;
        case S_LOG_OPT_INFO:
			opt_str = "[I]";
		#if (S_LOG_COLOR_OPEN == 1)
			fixed_bfs_start = INFO_FBCS_START;   fixed_bfs_end = INFO_FBCS_END;
		#else
		#endif
			break;
        case S_LOG_OPT_DEBUG:
			opt_str = "[D]";
		#if (S_LOG_COLOR_OPEN == 1)
			fixed_bfs_start = DEBUG_FBCS_START;  fixed_bfs_end = DEBUG_FBCS_END;  
		#else
		#endif
			break;
        default:opt_str = "[undifine]"; break;
	}

	#if (S_LOG_COLOR_OPEN == 1)
		/* 如果启用色彩控制 */
		sprintf(change_format, fixed_format, fixed_bfs_start, opt_str, tag, file, func, line, fixed_bfs_end, USER_FBCS_START, format, USER_FBCS_END, S_LOG_NEWLINE_SWITCH);
	#else
		/* 如果不启用色彩控制 */
		sprintf(change_format, fixed_format, opt_str, tag, file, func, line, format, S_LOG_NEWLINE_SWITCH);
	#endif
	va_start(args, change_format);
	len = vsnprintf(s_log_buff, S_LOG_BUFF_SIZE, change_format, args);
	va_end(args); 
	s_log_buff[len] = 0;

#if (S_LOG_OUT_BY_PRINTF == 1)
	s_log_printf(s_log_buff);
#endif

#if (S_LOG_OUT_BY_FILE == 1)
	s_log_printf_file(s_log_buff);
#endif

#if (S_LOG_OUT_BY_NET == 1)
	s_log_printf_net(s_log_buff);
#endif

    return;
}

char* s_log_strrchr(const char *str, int c)
{
	return strrchr(str, c);
}

#if (S_LOG_OUT_BY_PRINTF == 1)
int s_log_out_by_printf(const char *s_log_str)
{
	printf("%s", s_log_str);
	return 0;
}
#endif

#endif  /* S_LOG_ENABLE == 1 */
