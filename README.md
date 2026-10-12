# MiniGrade

命令行学生成绩管理器，一个用于巩固 C 语言核心知识点的练习项目。

## 快速开始

```bash
make
./mini_grade
```

## 支持的命令

```
add  <id> <name> <score>  - 添加学生
list                      - 列出所有学生
find <id>                 - 查找学生
sort <id|name|score>      - 排序
sum  <s1> <s2> ...        - 求和
log  <on|off>             - 日志开关
help                      - 显示帮助
quit / exit               - 退出
```

## 示例

```
> add 1001 小明 88
> add 1002 小红 95
> list
ID: 1001  姓名: 小明  成绩: 88  及格
ID: 1002  姓名: 小红  成绩: 95  及格
> sort score
排序完成
> find 1001
ID: 1001  姓名: 小明  成绩: 88  及格
> sum 80 90 85
总和: 255
> quit
再见!
```

## 项目结构

```
mini_grade/
├── Makefile
├── README.md
├── docs/
│   └── requirements.md
├── include/
│   ├── common.h       # 公共类型、错误码、函数指针 typedef
│   ├── error.h        # 错误信息接口
│   ├── input.h        # 安全输入解析接口
│   ├── student.h      # 学生结构体（union、位域）
│   ├── command.h      # 命令分发接口
│   └── log.h          # 日志与可变参数接口
└── src/
    ├── main.c         # 主循环
    ├── error.c        # 错误码转字符串
    ├── input.c        # 安全解析整数/字符串
    ├── student.c      # 学生增删查改排序
    ├── command.c      # 函数指针命令表
    └── log.c          # 可变参数日志与求和
```

## 涉及知识点

| 知识点 | 说明 |
|---|---|
| K1 指针与数组 | 用指针操作学生数组 |
| K2 static / extern | 内部链接、外部链接、跨文件共享变量 |
| K3 函数指针 | 命令表用函数指针分发 |
| K4 指针函数 | `student_find_by_id` 返回 `Student*` |
| K5 回调函数 | 排序比较器、遍历访问器作为参数传入 |
| K6 union 共用体 | `ScoreValue` 三种视角访问成绩 |
| K7 位域 | `valid`、`is_pass`、`gender` 各占 1 位 |
| K8 typedef | 结构体、函数指针、错误码的类型别名 |
| K9 错误处理 | 统一错误码，安全输入解析 |
| K10 可变参数 | `log_info`、`sum_int` 使用 `stdarg.h` |

## 构建

```bash
# 编译
make

# 清理（手动删除生成文件）
rm -f mini_grade.exe src/*.o
```