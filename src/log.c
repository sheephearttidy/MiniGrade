// 日志模块
#include"log.h"
#include"common.h"
#include<stdarg.h> // 可变参数定义的位置

int is_log_open = 0; // 日志开关

void log_info(const char* fmt, ...){
    // 如果日志开关关闭，直接返回，退出函数
    if (!is_log_open) return; // 其实一直都在调用，只是没有打印日志。
    // 如果日志开关开启，打印日志
    va_list args;
    va_start(args, fmt); // 把游标放在第一个可变参数上。
    vprintf(fmt, args); // 对于这个函数，我目前还不了解。
    va_end(args); // 结束使用可变参数，释放内存

    /*
    这个函数就是让main.c调用的函数，程序员选择打印日志。
    */
}

int sum_int(int count, ...){
    int total = 0; // 总分
    va_list args; // 创建了一个可以迭代的对象，（python中的迭代器）。
    va_start(args, count); // 把游标放在第一个可变参数上。
    for (int i = 0; i < count; i++){
        total += va_arg(args, int);
    }
    va_end(args); // 结束使用可变参数，释放内存
    return total; // 返回总分
}