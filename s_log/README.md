# s_log
一个小巧的嵌入式log库，纯C语言实现，可以方便的进行移植、使用。支持`log输出等级控制`功能、`log重定向`功能、`彩色log输出`功能，使用灵活方便、简单快捷。

## 文件结构
s_log源文件目前版本由：`s_log_cfg.h`、`s_log.h`、`s_log.c` 组成。

## 用户接口
s_log的用户接口包括：  
`s_tag()`、`s_log_a()`、`s_log_e()`、`s_log_w()`、`s_log_t()`、`s_log_i()`、`s_log_d()`、`s_log_v()`

## 使用方式
在需要使用s_log的文件、模块中包含头文件 s_log.h，并通过`s_tag()`接口定义一个tag，然后根据需要使用不同等级的log接口即可。

## 如何配置
s_log中的 `s_log_cfg.h`文件包含了用户的使用配置宏，主要包括：  
1、s_log使能 `S_LOG_ENABLE`  
2、s_log色彩控制使能`S_LOG_COLOR_OPEN`  
3、s_log通过printf输出`S_LOG_OUT_BY_PRINTF`  
4、s_log输出缓冲区大小`S_LOG_BUFF_SIZE`  
5、s_log输出级别控制`S_LOG_OPT_LVL`  

## 开源协议
s_log采用MIT License

## github仓库
https://github.com/smallerxuan/s_log.git