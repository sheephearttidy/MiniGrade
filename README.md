# MiniGrade 命令行学生成绩管理器——需求文档

## 1. 文档信息

| 项目 | 内容 |
|---|---|
| 项目名称 | MiniGrade |
| 文档类型 | 软件需求文档 |
| 目标 | 巩固 10-9、10-10、10-11 三天 C 语言学习内容 |
| 运行形式 | 命令行程序 |
| 编程语言 | C99 |
| 构建方式 | Makefile 多文件编译 |

---

## 2. 项目概述

### 2.1 背景

已学习：

- 10-9：用指针重新理解数组、指针操作与移动数组、内部/外部链接、`static` 与 `extern`、分文件编写。
- 10-10：函数指针、指针函数、回调函数、共用体、位域、`typedef`。
- 10-11：C 语言错误处理、可变参数。

本项目用一个“学生成绩管理器”串起以上知识点，避免只写单文件 demo。

### 2.2 目标

实现一个命令行程序，支持学生信息的添加、查找、排序、列出、求和、日志开关等功能，并强制使用：

- 多文件结构
- 函数指针命令表
- 指针函数查找
- 回调函数排序/遍历
- `union`、位域、`typedef`
- 统一错误码与错误处理
- 可变参数函数
- `static` / `extern` 跨文件控制

### 2.3 范围

本期只做内存内管理，不涉及数据库、文件持久化、图形界面、网络。

---

## 3. 运行环境与约束

| 项 | 要求 |
|---|---|
| 系统 | Windows / Linux / macOS 均可 |
| 编译器 | GCC / Clang / MSVC，支持 C99 |
| 构建 | `make` 或等价命令 |
| 第三方库 | 不依赖第三方库 |
| 数据存储 | 静态数组，最大 100 个学生 |
| 输入方式 | 标准输入逐行命令 |
| 输出方式 | 标准输出打印结果与错误 |

---

## 4. 目录结构

```text
mini_grade/
├── Makefile
├── README.md
├── docs/
│   └── requirements.md          # 本文档
├── include/
│   ├── common.h                 # 公共类型、错误码、函数指针 typedef
│   ├── error.h                  # 错误码与错误信息接口
│   ├── input.h                  # 安全输入解析接口
│   ├── student.h                # 学生数据、union、位域、查找、排序
│   ├── command.h                # 命令表与命令处理函数声明
│   └── log.h                    # 日志开关与可变参数日志
├── src/
│   ├── main.c                   # 命令循环、extern/static 示例
│   ├── error.c                  # 错误码到字符串
│   ├── input.c                  # 整数/字符串解析，错误处理
│   ├── student.c                # 数组指针操作、查找、排序、回调
│   ├── command.c                # 函数指针命令分发
│   └── log.c                    # 可变参数日志、全局日志开关
└── tests/
    ├── test_input.c
    ├── test_student.c
    └── test_sum.c
```

---

## 5. 模块职责与知识点链接

| 文件/目录 | 职责 | 涉及功能 | 知识点链接 |
|---|---|---|---|
| `include/common.h` | 公共类型、错误码、函数指针类型 | F9/F10/F11 | [K3](#k3)、[K8](#k8)、[K9](#k9) |
| `include/error.h`、`src/error.c` | 错误码与错误信息 | F9 | [K8](#k8)、[K9](#k9)、[K2](#k2) |
| `include/input.h`、`src/input.c` | 安全解析整数、字符串 | F2/F4/F5/F6/F9 | [K8](#k8)、[K9](#k9) |
| `include/student.h`、`src/student.c` | 学生数组、union、位域、查找、排序、遍历 | F2/F3/F4/F5/F11 | [K1](#k1)、[K4](#k4)、[K5](#k5)、[K6](#k6)、[K7](#k7)、[K8](#k8) |
| `include/command.h`、`src/command.c` | 命令表、函数指针分发 | F1/F10 | [K2](#k2)、[K3](#k3)、[K8](#k8) |
| `include/log.h`、`src/log.c` | 日志开关、可变参数日志 | F7 | [K2](#k2)、[K8](#k8)、[K10](#k10) |
| `src/main.c` | 主循环、`extern` 配置、`static` 辅助函数 | F1/F8 | [K2](#k2)、[K3](#k3)、[K9](#k9) |
| `Makefile` | 多文件编译与链接 | 全部 | [K2](#k2) |
| `tests/` | 单元测试与边界测试 | 全部 | [K9](#k9)、[K10](#k10) |

---

## 6. 知识点索引

<a id="k1"></a>
### K1 指针与数组

用指针形式重新理解数组，掌握指针操作、移动数组。对应 10-9 笔记。

<a id="k2"></a>
### K2 内外部链接、static 与 extern

掌握内部链接、外部链接、`static`、`extern`，用于分文件编写。对应 10-9 笔记。

<a id="k3"></a>
### K3 函数指针

用函数指针保存命令处理函数，实现命令表分发。对应 10-10 笔记。

<a id="k4"></a>
### K4 指针函数

返回指针的函数，例如按 ID 查找学生并返回 `Student*`。对应 10-10 笔记。

<a id="k5"></a>
### K5 回调函数

把比较函数、遍历访问函数作为参数传入。对应 10-10 笔记。

<a id="k6"></a>
### K6 共用体 union

用 `union` 表示成绩，可以用 `int`、`float`、`char grade` 等视角访问。对应 10-10 笔记。

<a id="k7"></a>
### K7 位域

用位域保存 `valid`、`passed`、`gender` 等标记。对应 10-10 笔记。

<a id="k8"></a>
### K8 typedef

给结构体、函数指针、错误码起别名。对应 10-10 笔记。

<a id="k9"></a>
### K9 C 语言错误处理

处理非法输入、错误参数、越界、格式错误等。对应 10-11 笔记。

<a id="k10"></a>
### K10 可变参数

使用 `stdarg.h` 实现可变参数求和与日志。对应 10-11 笔记。

---

## 7. 功能需求

### F1 命令循环与帮助

| 项 | 内容 |
|---|---|
| 命令 | `help`、空行、未知命令 |
| 描述 | 程序启动后循环读取命令行，解析并分发命令 |
| 输入 | 一行字符串，按空白分词 |
| 输出 | 执行结果或错误提示 |
| 规则 | 空行忽略；`help` 显示支持命令；未知命令提示错误 |
| 异常 | 输入过长时截断并提示 |
| 知识点链接 | [K2](#k2)、[K3](#k3)、[K9](#k9) |
| 验收 | 输入 `help` 能显示命令列表 |

### F2 添加学生

| 项 | 内容 |
|---|---|
| 命令 | `add <id> <name> <score>` |
| 描述 | 添加一个学生到静态数组 |
| 输入 | `id` 正整数；`name` 长度 1~31 且不含空格；`score` 0~100 |
| 输出 | 成功提示，或错误码对应提示 |
| 规则 | 数组最多 100 人；ID 不允许重复；`valid=1`；`passed = score >= 60` |
| 异常 | `ERR_ARG`、`ERR_FORMAT`、`ERR_RANGE`、`ERR_FULL`、`ERR_DUP` |
| 知识点链接 | [K1](#k1)、[K6](#k6)、[K7](#k7)、[K8](#k8)、[K9](#k9) |
| 验收 | `add 1001 Tom 88` 成功；`add abc Tom 88` 报格式错误；`add 1002 Tom 999` 报范围错误 |

### F3 列出学生

| 项 | 内容 |
|---|---|
| 命令 | `list` |
| 描述 | 列出全部有效学生 |
| 输出 | 表头与每行：ID、姓名、成绩、是否及格 |
| 规则 | 使用指针遍历数组；可调用遍历回调函数 |
| 异常 | 无学生时输出“暂无学生” |
| 知识点链接 | [K1](#k1)、[K5](#k5)、[K7](#k7) |
| 验收 | 添加后 `list` 能看到对应学生 |

### F4 查找学生

| 项 | 内容 |
|---|---|
| 命令 | `find <id>` |
| 描述 | 按 ID 查找学生 |
| 输入 | 合法整数 ID |
| 输出 | 找到则输出信息；找不到提示未找到 |
| 规则 | 查找函数返回 `Student*`，找不到返回 `NULL` |
| 异常 | `ERR_ARG`、`ERR_FORMAT`、`ERR_NOT_FOUND` |
| 知识点链接 | [K1](#k1)、[K4](#k4)、[K9](#k9) |
| 验收 | `find 1001` 找到；`find 9999` 报未找到 |

### F5 排序学生

| 项 | 内容 |
|---|---|
| 命令 | `sort id`、`sort name`、`sort score` |
| 描述 | 按 ID、姓名或成绩排序 |
| 规则 | 比较函数通过函数指针传入；排序使用回调比较 |
| 输出 | 排序成功提示 |
| 异常 | 不支持的排序字段返回 `ERR_ARG` |
| 知识点链接 | [K1](#k1)、[K3](#k3)、[K5](#k5)、[K8](#k8) |
| 验收 | `sort score` 后 `list` 按成绩升序显示 |

### F6 可变参数求和

| 项 | 内容 |
|---|---|
| 命令 | `sum <s1> <s2> ...` |
| 描述 | 对多个整数成绩求和 |
| 输入 | 至少 1 个，最多 20 个，取值 0~100 |
| 输出 | 总和 |
| 规则 | 使用 `stdarg.h` 实现 `sum_int(int count, ...)` |
| 异常 | 无参数、非数字、越界返回对应错误 |
| 知识点链接 | [K9](#k9)、[K10](#k10) |
| 验收 | `sum 80 90 85` 输出 `255` |

### F7 日志开关

| 项 | 内容 |
|---|---|
| 命令 | `log on`、`log off` |
| 描述 | 控制是否输出调试日志 |
| 规则 | 全局变量 `extern int g_verbose;` 跨文件控制；日志函数为可变参数 |
| 输出 | 开启/关闭提示 |
| 异常 | 参数不是 `on/off` 返回 `ERR_ARG` |
| 知识点链接 | [K2](#k2)、[K8](#k8)、[K10](#k10) |
| 验收 | `log on` 后 `add` 有日志；`log off` 后无日志 |

### F8 退出

| 项 | 内容 |
|---|---|
| 命令 | `quit`、`exit` |
| 描述 | 退出程序 |
| 输出 | 退出提示 |
| 规则 | 正常退出码 0 |
| 知识点链接 | [K3](#k3)、[K9](#k9) |
| 验收 | 输入 `quit` 后程序结束 |

### F9 输入解析与错误处理

| 项 | 内容 |
|---|---|
| 描述 | 所有命令参数必须先解析再使用，禁止直接 `atoi` 后不检查 |
| 错误码 | `OK`、`ERR_ARG`、`ERR_FORMAT`、`ERR_RANGE`、`ERR_FULL`、`ERR_NOT_FOUND`、`ERR_DUP`、`ERR_UNKNOWN_CMD` |
| 输出 | 统一通过 `err_msg(ErrCode)` 返回错误字符串 |
| 规则 | 非法输入不能导致崩溃 |
| 知识点链接 | [K2](#k2)、[K8](#k8)、[K9](#k9) |
| 验收 | 输入 `add`、`add abc Tom 88`、`find x` 均能友好报错 |

### F10 命令分发

| 项 | 内容 |
|---|---|
| 描述 | 使用函数指针数组/结构体数组保存命令名与处理函数 |
| 规则 | 命令表建议为 `static const struct { const char* name; CmdFn fn; }` |
| 扩展 | 新增命令只需增加处理函数与表项 |
| 知识点链接 | [K2](#k2)、[K3](#k3)、[K8](#k8) |
| 验收 | `add`、`list`、`find`、`sort`、`sum`、`log`、`quit` 均可分发 |

### F11 数据模型与状态标记

| 项 | 内容 |
|---|---|
| 描述 | 用 `typedef struct` 定义学生；用 `union` 表示成绩；用位域表示状态 |
| 规则 | `ScoreValue` 支持 `int i`、`float f`、`char grade`；`StudentFlags` 包含 `valid:1`、`passed:1`、`gender:1` |
| 知识点链接 | [K6](#k6)、[K7](#k7)、[K8](#k8) |
| 验收 | 能正确访问 union 成员与位域成员 |

---

## 8. 数据需求

### 8.1 学生数据

```c
typedef union {
    int i;
    float f;
    char grade;
} ScoreValue;

typedef struct {
    unsigned valid  : 1;
    unsigned passed : 1;
    unsigned gender : 1;
} StudentFlags;

typedef struct Student {
    int id;
    char name[32];
    ScoreValue score;
    StudentFlags flags;
} Student;
```

### 8.2 错误码

```c
typedef enum {
    OK = 0,
    ERR_ARG,
    ERR_FORMAT,
    ERR_RANGE,
    ERR_FULL,
    ERR_NOT_FOUND,
    ERR_DUP,
    ERR_UNKNOWN_CMD
} ErrCode;
```

### 8.3 全局配置

```c
extern int g_verbose;
```

用于跨文件控制日志输出。

---

## 9. 接口需求

以下接口为需求约束，具体实现可调整，但必须保留对应知识点。

```c
const char* err_msg(ErrCode e);                    // 指针函数
ErrCode read_int(const char* s, int* out);         // 错误处理
Student* student_find_by_id(Student* arr, size_t n, int id); // 指针函数
void student_sort(Student* arr, size_t n, CmpFn cmp);        // 函数指针/回调
void student_foreach(Student* arr, size_t n,
                     void (*visit)(Student*, void*), void* ctx); // 回调
int sum_int(int count, ...);                       // 可变参数
void log_info(const char* fmt, ...);               // 可变参数
```

函数指针类型：

```c
typedef int (*CmpFn)(const Student*, const Student*);
typedef ErrCode (*CmdFn)(int argc, char** argv);
```

---

## 10. 功能与知识点链接总表

| 功能 | 命令/接口 | 主要文件 | 知识点链接 |
|---|---|---|---|
| F1 命令循环与帮助 | `help` | `main.c`、`command.c` | [K2](#k2)、[K3](#k3)、[K9](#k9) |
| F2 添加学生 | `add` | `student.c`、`input.c` | [K1](#k1)、[K6](#k6)、[K7](#k7)、[K8](#k8)、[K9](#k9) |
| F3 列出学生 | `list` | `student.c` | [K1](#k1)、[K5](#k5)、[K7](#k7) |
| F4 查找学生 | `find` | `student.c` | [K1](#k1)、[K4](#k4)、[K9](#k9) |
| F5 排序学生 | `sort` | `student.c` | [K1](#k1)、[K3](#k3)、[K5](#k5)、[K8](#k8) |
| F6 可变参数求和 | `sum` | `log.c`、`command.c` | [K9](#k9)、[K10](#k10) |
| F7 日志开关 | `log` | `log.c`、`main.c` | [K2](#k2)、[K8](#k8)、[K10](#k10) |
| F8 退出 | `quit` | `main.c` | [K3](#k3)、[K9](#k9) |
| F9 错误处理 | 所有命令 | `error.c`、`input.c` | [K2](#k2)、[K8](#k8)、[K9](#k9) |
| F10 命令分发 | 命令表 | `command.c` | [K2](#k2)、[K3](#k3)、[K8](#k8) |
| F11 数据模型 | `Student` | `student.h` | [K6](#k6)、[K7](#k7)、[K8](#k8) |

---

## 11. 非功能需求

| 项 | 要求 |
|---|---|
| 可编译 | 执行 `make` 能生成 `mini_grade` |
| 可维护 | 头文件声明、源文件实现，禁止全部写在 `main.c` |
| 健壮性 | 非法输入不崩溃，不越界 |
| 可测试 | 至少提供 `test_input.c`、`test_student.c`、`test_sum.c` |
| 可读性 | 使用 `typedef` 简化类型；错误码统一 |
| 可扩展 | 新增命令只需修改命令表和处理函数 |
| 链接要求 | 辅助函数用 `static`；跨文件配置用 `extern` |

---

## 12. 验收测试用例

| 编号 | 输入 | 预期结果 |
|---|---|---|
| T1 | `help` | 显示命令帮助 |
| T2 | `add 1001 Tom 88` | 添加成功 |
| T3 | `list` | 显示 Tom，成绩 88，及格 |
| T4 | `add abc Tom 88` | 报格式错误 |
| T5 | `add 1001 Tom 999` | 报范围错误 |
| T6 | `find 1001` | 找到学生 |
| T7 | `find 9999` | 报未找到 |
| T8 | `sort score` | 按成绩排序 |
| T9 | `sum 80 90 85` | 输出 `255` |
| T10 | `log on` 后 `add 1002 Jerry 59` | 有日志输出 |
| T11 | `log off` 后 `add 1003 Lucy 90` | 无日志输出 |
| T12 | `unknown_cmd` | 报未知命令 |
| T13 | `quit` | 正常退出 |

---

## 13. 开发顺序建议

1. 建立目录结构与 `Makefile`。
2. 完成 `common.h`、`error.h`、`error.c`。
3. 完成 `input.c`，实现安全整数解析与错误处理。
4. 完成 `student.c`，实现数组、指针遍历、查找、排序、回调。
5. 完成 `command.c`，实现函数指针命令表。
6. 完成 `log.c`，实现可变参数日志与 `sum_int`。
7. 完成 `main.c`，串起命令循环、`extern`、`static`。
8. 编写 `tests/` 并疯狂测试非法输入。
9. 最后检查每个知识点是否都有落点。

---

## 14. 风险与限制

| 项 | 说明 |
|---|---|
| 容量限制 | 最多 100 个学生 |
| 姓名限制 | 暂不支持空格 |
| 持久化 | 退出后数据丢失 |
| 平台差异 | 命令行分词以空白字符为准 |
| 测试范围 | 以功能与边界为主，不追求完整覆盖率 |

---

## 附录 A：命令帮助

```text
add <id> <name> <score>   添加学生
list                      列出全部学生
find <id>                 按 ID 查找
sort id|name|score        排序
sum <s1> <s2> ...         可变参数求和
log on|off                开启/关闭日志
help                      显示帮助
quit                      退出
```

如果需要，我可以继续按这份需求文档生成完整的代码骨架和 `Makefile`。