#pragma once

#include <stdio.h>
#include <stddef.h>

// 定义错误代码
typedef enum {
    OK = 0,
    ERR_ARG, // 错误的参数
    ERR_FORMAT, // 错误的格式
    ERR_RANGE, // 超出范围 
    ERR_FULL, // 容器已满
    ERR_NOT_FOUND, // 未找到
    ERR_DUP, // 重复
    ERR_UNKNOWN_CMD // 未知的命令
} ErrCode;

typedef struct Student Student; // 学生结构体的声明

typedef int (*CmpFn)(const Student*, const Student*); // 比较函数指针
typedef ErrCode (*CmdFn)(int argc, char** argv); // 命令函数指针