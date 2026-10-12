// 定义学生结构体
#pragma once
#include "common.h"

// 三个视角来看成绩
typedef union{
    int i;
    float f;
    char grade;
} ScoreValue;
// 学生标志，标记学生的成绩是否有效、是否及格、性别
typedef struct {
    unsigned valid:1; // 如果学生作弊呢。。:)
    unsigned is_pass:1; // 是否及格
    unsigned gender:1; // 性别 0:男 1:女
} ScoreFlags;
// 学生结构体，包含学生的学号、姓名、成绩、标志
typedef struct Student{
    int id;
    char name[32];
    ScoreValue score;
    ScoreFlags flags;
}Student;

/* ===== 全局数据 ===== */
extern Student global_students[100];   // 学生数组，最多100个
extern size_t  global_student_count;   // 当前学生数量

/* ===== 函数声明 ===== */
ErrCode   student_add(int id, const char* name, int score);
Student*  student_find_by_id(int id);
void      student_sort(CmpFn cmp);
void      student_foreach(void (*visit)(Student*, void*), void* ctx);

int cmp_by_id(const Student* a, const Student* b);
int cmp_by_name(const Student* a, const Student* b);
int cmp_by_score(const Student* a, const Student* b);