# s_log_safe
一个采用MIT License协议开源的、小巧的、基于s_log ( https://github.com/smallerxuan/s_log.git ) 开源库和s_ring_buffer ( https://github.com/smallerxuan/s_ring_buffer.git ) 开源库打造的一款线程安全的嵌入式log库，纯C语言实现，移植、使用方便、快捷。在s_log原有的输出等级控制功能、log重定向功能、彩色log输出功能基础之上提供了线程安全支持。

## 文件结构
s_log_safe中使用到了s_log和s_ring_buffer，整体文件结构如下：  
```
.  
├── LICENSE  
├── main.c  
├── Makefile  
├── README.md  
├── s_log  
│   ├── LICENSE  
│   ├── README.md  
│   ├── s_log.c  
│   ├── s_log_cfg.h  
│   └── s_log.h  
├── s_log_safe.c  
├── s_log_safe_cfg.h  
├── s_log_safe.h  
├── s_log_safe_platform.c  
├── s_log_safe_platform.h  
└── s_ring_buffer  
    ├── LICENSE  
    ├── README.md  
    ├── s_ring_buffer.c  
    ├── s_ring_buffer.h  
    ├── s_ring_buffer_platform.c  
    └── s_ring_buffer_platform.h  
```

## 用户接口
s_log_safe的用户接口包括:  
`s_log_safe_init()`  
`s_log_safe_deinit()`  
`s_log_safe_output_pool_cap_get()`  
`s_log_safe_output_pool_used_get()`  
`s_log_safe_tag()`  
`s_log_safe_a()`  
`s_log_safe_v()`  
`s_log_safe_e()`  
`s_log_safe_w()`  
`s_log_safe_t()`  
`s_log_safe_i()`  
`s_log_safe_d()`  
`s_log_safe_out()`

## 使用方式
在需要使用s_log_safe的文件、模块中包含头文件 s_log_safe.h即可使用。

## 如何移植、适配
s_log_safe中与平台相关的接口实现均在`s_log_safe_platform.h`和`s_log_safe_platform.c`，用户主要需要适配实现的包括：  
宏 `s_log_safe_malloc`、`s_log_safe_free`、`s_log_safe_memcpy`、`s_log_safe_memset`、`s_log_safe_strlen`、`s_log_safe_null`  
接口 `s_log_safe_thread_create()`、`s_log_safe_thread_delete()`、`s_log_safe_mutex_create()`、`s_log_safe_mutex_destroy()`、`s_log_safe_mutex_lock()`、`s_log_safe_mutex_try_lock()`、`s_log_safe_mutex_unlock()`

## github仓库
https://github.com/smallerxuan/s_log_safe.git

## 更新日志
V0.0.1(first commit):  
        首次发布，基础功能支持
V0.0.2:  
        支持tag log输出级别限制自定义，支持不同的tag设置不同的 log输出级别限制        

