#include<error.h>
#include"common.h"

// switch 语句，根据错误码返回对应的错误信息
const char* err_msg(ErrCode e){
    // 之所以用const char* 是因为错误代码通常是只读的字面量。
    /*
    C/C++ 里函数不能直接返回数组，而字符串字面量 "Success" 本身就是一个字符数组。
    所以只能返回指向这个数组首元素的指针，也就是 const char*。
    */
    switch(e){
        /*
        OK = 0,
        ERR_ARG, // 错误的参数
        ERR_FORMAT, // 错误的格式
        ERR_RANGE, // 超出范围 
        ERR_FULL, // 容器已满
        ERR_NOT_FOUND, // 未找到
        ERR_DUP, // 重复
        ERR_UNKNOWN_CMD // 未知的命令
        */
       case OK:
           return "OK";
       case ERR_ARG:
           return "ERR_ARG";
       case ERR_FORMAT:
           return "ERR_FORMAT";
       case ERR_RANGE:
           return "ERR_RANGE";
       case ERR_FULL:
           return "ERR_FULL";
       case ERR_NOT_FOUND:
           return "ERR_NOT_FOUND";
       case ERR_DUP:
           return "ERR_DUP";
       case ERR_UNKNOWN_CMD:
           return "ERR_UNKNOWN_CMD";
        default:
            return "Unknown error";
}
}