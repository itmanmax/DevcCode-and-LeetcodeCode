
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char directory[] = "your_directory";  // 替换为实际目录路径
    FILE *file;

    chdir(directory);

    int num1, num2;
    char id[100];
    printf("请输入两个数字和ID：");
    scanf("%d %d %s", &num1, &num2, id);

    file = fopen("time.txt", "w");
    if (!file) {
        printf("无法打开文件：time.txt\n");
        return 1;
    }
    fprintf(file,"%d\n", num1);
    fclose(file);

    file = fopen("log.txt", "w");
    if (!file) {
        printf("无法打开文件：log.txt\n");
        return 1;
    }
    fprintf(file,"%d\n\n", num2, id);
    fclose(file);

    system("\"./sun.exe\""); // 运行sun.exe，确认该程序兼容您的系统

    char log_directory[] = "log";
    chdir(log_directory);

    file = fopen("hestiy.txt", "r");
    if (!file) {
        printf("无法打开文件：hestiy.txt\n");
        return 1;
    }

    char line[1000];
    printf("\nhestiy.txt的内容：\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);

    return 0;
}

