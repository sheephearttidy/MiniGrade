#include "command.h"
#include "student.h"
#include "input.h"
#include "error.h"
#include "log.h"
#include <string.h>
#include <stdlib.h>

static ErrCode cmd_help(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    printf("支持的命令:\n");
    printf("  add  <id> <name> <score>  - 添加学生\n");
    printf("  list                      - 列出所有学生\n");
    printf("  find <id>                 - 查找学生\n");
    printf("  sort <id|name|score>      - 排序\n");
    printf("  sum  <s1> <s2> ...        - 求和\n");
    printf("  log  <on|off>             - 日志开关\n");
    printf("  quit / exit               - 退出\n");
    return OK;
}

static ErrCode cmd_add(int argc, char** argv)
{
    if (argc != 4) return ERR_ARG;

    int id;
    ErrCode e = read_int(argv[1], &id);
    if (e != OK) return e;

    char name[32];
    e = read_str(argv[2], name, sizeof(name));
    if (e != OK) return e;

    int score;
    e = read_score(argv[3], &score);
    if (e != OK) return e;

    return student_add(id, name, score);
}

static void print_student(Student* s, void* ctx)
{
    (void)ctx;
    const char* pass = s->flags.is_pass ? "及格" : "不及格";
    printf("ID: %d  姓名: %s  成绩: %d  %s\n",
           s->id, s->name, s->score.i, pass);
}

static ErrCode cmd_list(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    if (global_student_count == 0) {
        printf("暂无学生\n");
        return OK;
    }
    student_foreach(print_student, NULL);
    return OK;
}

static ErrCode cmd_find(int argc, char** argv)
{
    if (argc != 2) return ERR_ARG;

    int id;
    ErrCode e = read_int(argv[1], &id);
    if (e != OK) return e;

    Student* s = student_find_by_id(id);
    if (s == NULL) return ERR_NOT_FOUND;

    print_student(s, NULL);
    return OK;
}

static ErrCode cmd_sort(int argc, char** argv)
{
    if (argc != 2) return ERR_ARG;

    if (strcmp(argv[1], "id") == 0)
        student_sort(cmp_by_id);
    else if (strcmp(argv[1], "name") == 0)
        student_sort(cmp_by_name);
    else if (strcmp(argv[1], "score") == 0)
        student_sort(cmp_by_score);
    else
        return ERR_ARG;

    printf("排序完成\n");
    return OK;
}

static ErrCode cmd_sum(int argc, char** argv)
{
    if (argc < 2) return ERR_ARG;

    int total = 0;
    for (int i = 1; i < argc; i++) {
        int val;
        ErrCode e = read_score(argv[i], &val);
        if (e != OK) return e;
        total += val;
    }

    printf("总和: %d\n", total);
    return OK;
}

static ErrCode cmd_log(int argc, char** argv)
{
    if (argc != 2) return ERR_ARG;

    if (strcmp(argv[1], "on") == 0) {
        is_log_open = 1;
        printf("日志已开启\n");
    } else if (strcmp(argv[1], "off") == 0) {
        is_log_open = 0;
        printf("日志已关闭\n");
    } else {
        return ERR_ARG;
    }
    return OK;
}

static ErrCode cmd_quit(int argc, char** argv)
{
    printf("再见!\n");
    exit(0);
    return OK;
}

static const struct {
    const char* name;
    CmdFn fn; // 命令的 函数指针(利用typedef定义)
} cmd_table[] = {
    {"help",  cmd_help}, // 这里存的函数地址
    {"add",   cmd_add},
    {"list",  cmd_list},
    {"find",  cmd_find},
    {"sort",  cmd_sort},
    {"sum",   cmd_sum},
    {"log",   cmd_log},
    {"quit",  cmd_quit},
    {"exit",  cmd_quit},
};

ErrCode dispatch(int argc, char** argv) // 分发命令
{
    if (argc < 1 || argv[0] == NULL) // 如果用户输入为空 ，则返回错误
        return ERR_UNKNOWN_CMD;  // 返回未知命令错误

    int n = sizeof(cmd_table) / sizeof(cmd_table[0]); // 命令表的大小

    for (int i = 0; i < n; i++) {
        if (strcmp(argv[0], cmd_table[i].name) == 0) // 如果用户输入的命令与命令表中的命令匹配
            return cmd_table[i].fn(argc, argv); // 调用命令函数
            /* 
            fn是结构体成员，指向命令函数的指针。
            cmd_table[i].fn(argc, argv) 这个是结构体，直接获得到fn函数的地址，
            调用fn函数，传入argc和argv。
            */
    }

    return ERR_UNKNOWN_CMD; // 如果用户输入的命令与命令表中的命令都不匹配 ，则返回错误
}