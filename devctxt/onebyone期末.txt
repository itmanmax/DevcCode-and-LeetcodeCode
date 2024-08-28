#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 100

// 结构体用于保存关键词和对应的频率
typedef struct {
    char word[MAX_WORD_LENGTH];
    int frequency;
} KeywordFrequency;

// 函数声明
void shellSort(KeywordFrequency *keywords, int n);
void writeToFileSorted(KeywordFrequency *keywords, int keywordCount, const char *filename);

int main() {
    FILE *keywordFile, *textFile;
    char keywordFilename[] = "C:\\Users\\86147\\Desktop\\quest\\Key.txt";
    char textFilename[] = "C:\\Users\\86147\\Desktop\\quest\\InFile.txt";
    char outFile[] = "C:\\Users\\86147\\Desktop\\quest\\OutFile3.txt";
    char buffer[1000];
    KeywordFrequency *keywords;
    int keywordCount = 0;

    // 尝试打开关键词文件
    keywordFile = fopen(keywordFilename, "r");

    // 检查关键词文件是否成功打开
    if (keywordFile == NULL) {
        printf("无法打开关键词文件 %s\n", keywordFilename);
        return 1;
    }

    // 统计关键词的数量
    while (fgets(buffer, sizeof(buffer), keywordFile) != NULL) {
        keywordCount++;
    }

    // 回到文件开始处
    rewind(keywordFile);

    // 分配存储关键词和频率的数组
    keywords = (KeywordFrequency *)malloc(keywordCount * sizeof(KeywordFrequency));

    // 逐行读取关键词文件，保存关键词到数组中
    for (int i = 0; i < keywordCount; i++) {
        fgets(keywords[i].word, sizeof(keywords[i].word), keywordFile);
        // 移除末尾的换行符
        keywords[i].word[strcspn(keywords[i].word, "\n")] = '\0';
        keywords[i].frequency = 0;
    }

    // 关闭关键词文件
    fclose(keywordFile);

    // 尝试打开文本文件
    textFile = fopen(textFilename, "r");

    // 检查文本文件是否成功打开
    if (textFile == NULL) {
        printf("无法打开文本文件 %s\n", textFilename);
        free(keywords); // 释放关键词数组内存
        return 1;
    }

    // 逐行读取文本文件，统计关键词出现的频率
    while (fgets(buffer, sizeof(buffer), textFile) != NULL) {
        // 遍历每个关键词
        for (int i = 0; i < keywordCount; i++) {
            char *pos = buffer;
            // 在当前行查找关键词
            while ((pos = strstr(pos, keywords[i].word)) != NULL) {
                keywords[i].frequency++;
                pos += strlen(keywords[i].word);
            }
        }
    }

    // 关闭文本文件
    fclose(textFile);

    // 希尔排序，根据频度和关键字首字母排序
    shellSort(keywords, keywordCount);

    // 输出排序后的统计结果
    for (int i = 0; i < keywordCount; i++) {
        printf("关键词 '%s' 出现的频率: %d\n", keywords[i].word, keywords[i].frequency);
    }

    // 写入排序后的结果到文件（不包括频率为0的关键字）
    writeToFileSorted(keywords, keywordCount, outFile);

    // 释放关键词数组内存
    free(keywords);

    return 0;
}

// 希尔排序
void shellSort(KeywordFrequency *keywords, int n) {
    int gap, i, j;
    KeywordFrequency temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = keywords[i];
            for (j = i; j >= gap && (temp.frequency > keywords[j - gap].frequency ||
                                     (temp.frequency == keywords[j - gap].frequency && strcmp(temp.word, keywords[j - gap].word) < 0)); j -= gap) {
                keywords[j] = keywords[j - gap];
            }
            keywords[j] = temp;
        }
    }
}

// 将排序后的关键词频率写入文件（不包括频率为0的关键字）
void writeToFileSorted(KeywordFrequency *keywords, int keywordCount, const char *filename) {
    FILE *outfile = fopen(filename, "w");

    // 检查文件是否成功打开
    if (outfile == NULL) {
        printf("无法打开输出文件 %s\n", filename);
        return;
    }

    // 清空文件内容
    fclose(outfile);
    outfile = fopen(filename, "w");

    // 写入关键词频率到文件（不包括频率为0的关键字）
    for (int i = 0; i < keywordCount; i++) {
        if (keywords[i].frequency > 0) {
            fprintf(outfile, "关键词 '%s' 出现的频率: %d\n", keywords[i].word, keywords[i].frequency);
        }
    }

    // 关闭文件
    fclose(outfile);
}

