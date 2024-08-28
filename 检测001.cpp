#include <stdio.h>
#include <string.h>
#include <io.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <windows.h>

int  main()
{
    // 打开SunnyRun.exe
    ShellExecute(0, "open", "C:/Users/86147/Desktop/ygty/SunnyRun.exe", NULL, NULL, SW_SHOWNORMAL);
    time_t current_time = time(NULL);
    struct tm *local_time_info = localtime(&current_time);

    int year = local_time_info->tm_year + 1900;
    int month = local_time_info->tm_mon + 1;
    int day = local_time_info->tm_mday;
        // 等待6秒
    Sleep(6000);

    // 输出结果
    printf("结果如下\n");
   

    

    // 转换日期为时间戳，以便进行比较
    struct tm input_date = {0};
    input_date.tm_year = year - 1900;
    input_date.tm_mon = month - 1;
    input_date.tm_mday = day;
    time_t input_date_timestamp = mktime(&input_date);

    char folder[] = "C:\\Users\\86147\\Desktop\\ygty\\Log\\";
    char target[1000] = {0};

    // 查找最新建立的文本文档
    struct _finddata_t file_info;
    intptr_t file_handle;
    time_t latest_timestamp = 0;

    strcat(folder, "*.txt"); // 只查找文本文件
    file_handle = _findfirst(folder, &file_info);
    if (file_handle == -1)
    {
        printf("\n找不到任何日志文件\n");
        return 0;
    }

    do
    {
        char filename[260] = "C:\\Users\\86147\\Desktop\\ygty\\Log\\";
        strcat(filename, file_info.name);
        struct stat file_stat;
        stat(filename, &file_stat);
        if (file_stat.st_mtime > latest_timestamp)
        {
            latest_timestamp = file_stat.st_mtime;
            strcpy(target, filename);
        }
    }
    while (_findnext(file_handle, &file_info) == 0);

    printf("\n最新建立的文本文档:s\n", target);

    // 读取第一行和最后六行
    FILE *fp;
    char lines[7][1000] = {{0}};
    int line_count = 0;
    fp = fopen(target, "r");
    if (fp != NULL)
    {
        while (!feof(fp))
        {
            fgets(lines[line_count], 1000, fp);
            if (line_count == 0) // 输出第一行
            {
                printf("\n第一行:%s\n", lines[line_count]);
            }
            line_count++;
            if (line_count > 6) // 移动数组元素，保留最后六行
            {
                for (int k = 0; k < 6; k++)
                {
                    strcpy(lines[k], lines[k + 1]);
                }
                line_count--;
            }
        }
    }
    fclose(fp);

    printf("\n最后六行: \n");
    for (int i = 0; i < 6 && *lines[i] != '\0'; i++)
    {
        printf("%s", lines[i]);
    }

    _findclose(file_handle);
}

