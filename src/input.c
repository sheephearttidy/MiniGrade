/*
安全模块：检查字符串是否符合要求
*/
#include "input.h"
#include "error.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"common.h"
#include<limits.h>
#include "log.h"

/* read_int：把字符串安全转成整数
   返回 OK 表示成功，out 指向解析结果
   返回 ERR_FORMAT 表示不是合法整数
   返回 ERR_RANGE 表示超出 int 范围
   返回 ERR_ARG 表示传了空指针
*/
ErrCode read_int(const char* s, int* out)
{
    if (s == NULL || out == NULL) // 检查是否传了空指针
        return ERR_ARG; // 返回错误码
    if (strlen(s) == 0 ) // 检查是否为空字符串
        return ERR_FORMAT; // 返回错误码

    char* endptr;
    long val = strtol(s, &endptr, 10); 
    // "你停下的地方，是字符串结尾吗？"

    if (*endptr != '\0')
        return ERR_FORMAT;

    if (val > INT_MAX || val < INT_MIN) // 检查是否超出 int 范围
        return ERR_RANGE;
    // 调用者准备好容器，函数往里面装东西
    *out = (int)val; // 转换为 int 类型 ，并赋值给 out 指向的内存。存成绩。long转int
    return OK;
}

/* read_str：安全拷贝字符串
   检查是否为空、是否超长、是否含空格   */
ErrCode read_str(const char* s, char* out, size_t max_len)
{
    // 检查通过后，把字符串拷贝到 out 指向的内存。存字符串
    if (s == NULL || out == NULL) // 检查是否传了空指针
        return ERR_ARG; // 返回错误码

    size_t len = strlen(s); // 计算字符串长度
    if (len == 0 || len >= max_len)
        return ERR_FORMAT; // 返回错误码

    for (size_t i = 0; i < len; i++) {
        if (s[i] == ' ')
            return ERR_FORMAT; // 返回错误码
    }

    // 调用者准备好容器，函数往里面装东西
    strcpy(out, s); // 拷贝字符串到 out 指向的内存
    
    out[len] = '\0'; // 给字符串添加结束符
    // 检查通过后，返回 OK
    log_info("read_str: %s", out); // 日志信息
    return OK;
}

/* read_score：解析成绩，复用 read_int 再做范围检查 */
ErrCode read_score(const char* s, int* out)
{
    ErrCode err = read_int(s, out);
    if (err != OK)
        return err;

    if (*out < 0 || *out > 100)
        return ERR_RANGE; // 返回错误码

    return OK;
}
/*
标准库函数<string.h>
strlen：计算字符串长度
strcpy：拷贝字符串
strcmp：比较字符串
strncmp：比较字符串前n个字符
*/