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
