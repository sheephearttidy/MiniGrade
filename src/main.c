#include "common.h"
#include "command.h"
#include "error.h"
#include <string.h>

int main()
{
    printf("Welcome to MiniGrade\n");

    char line[256];
    while (1) {
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        // 去掉末尾的换行符
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0)
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
        ErrCode e = dispatch(argc, argv);
        if (e != OK)
            printf("错误: %s\n", err_msg(e));
    }

    return 0;
}