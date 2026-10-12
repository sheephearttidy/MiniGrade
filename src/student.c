#include "student.h"
#include "error.h"
#include"common.h"
#include "log.h"
#include<string.h>

// Student stu; // 定义学生结构体变量

Student global_students[100]; // 学生数组，最多100个
size_t global_student_count = 0; // 当前学生数量

ErrCode   student_add(int id, const char* name, int score)
{
    if (name == NULL) // 检查是否传了空指针
        return ERR_ARG; // 返回错误码
    if (id <= 0) // 检查是否为无效ID
        return ERR_FORMAT; // 返回错误码
    if (score < 0 || score > 100) // 检查是否超出成绩范围
        return ERR_RANGE; // 返回错误码
    if (global_student_count >= 100) // 检查是否已满
        return ERR_FULL; // 返回错误码
    // 检查是否重复添加
    for (size_t i = 0; i < global_student_count; i++) {
        if (global_students[i].id == id)
            return ERR_DUP; // 重复添加
    }

    Student* s = &global_students[global_student_count]; // 拿到空位的地址
    s->id = id; // 在空位填充ID
    strcpy(s->name, name); // 在空位填充姓名
    s->score.i = score; // 在空位填充成绩
    s->flags.valid = 1; // 标记为有效
    // 标记是否通过
    s->flags.is_pass = (score >= 60) ? 1 : 0; // 三目运算。条件?真:假。

    global_student_count++; // 全局变量;增加学生数量

    log_info("添加学生: id=%d, name=%s, score=%d\n", id, name, score);
    return OK;

};

Student*  student_find_by_id(int id);

void      student_sort(CmpFn cmp);

void      student_foreach(void (*visit)(Student*, void*), void* ctx);
