#include "common.h"
#include "command.h"
#include "error.h"
#include <string.h>

int main()
{
    printf("Welcome to MiniGrade\n");

    char line[256];
    while (1) {
        printf("<MiniGrade@localhost:$> :"); // 模拟命令行提示
        if (fgets(line, sizeof(line), stdin) == NULL) // 读取用户输入 ，直到用户输入Ctrl+D
            break;
        // 去掉末尾的换行符
        line[strcspn(line, "\n")] = '\0'; // 去掉换行符 ，将换行符替换为字符串结束符
        if (strlen(line) == 0) // 如果用户输入为空 ，则跳过
            continue;

        // 分词
        char* argv[16];
        int argc = 0;
        char* token = strtok(line, " ");
        while (token != NULL && argc < 16) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        // 分发
        ErrCode e = dispatch(argc, argv); // 获取错误码，方便err_msg的调用
        if (e != OK)
            printf("错误: %s\n", err_msg(e));
    }

    return 0;
}