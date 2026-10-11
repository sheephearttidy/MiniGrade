// 日志模块
#pragma once

extern int is_log_open; // 是否开启日志开关 extern 声明一个全局变量
// extern int is_log_open; = "这个变量在别的文件里定义的，我只是告诉你它存在。"
void log_info(const char* fmt, ...); // 打印信息日志

int sum_int(int count, ...); 
