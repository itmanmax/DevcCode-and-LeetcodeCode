#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#define MAX_WORD_LENGTH 100
#define HASH_TABLE_SIZE 100

// 结构体用于保存关键词和对应的频率
typedef struct {
    char word[MAX_WORD_LENGTH];
    int frequency;
} KeywordFrequency;

// 哈希表节点
typedef struct HashNode {
    KeywordFrequency data;
    struct HashNode *next;
} HashNode;

// 哈希表
typedef struct {
    HashNode *table[HASH_TABLE_SIZE];
} HashTable;

// 函数声明
unsigned int hash(const char *str); // 计算字符串的哈希值
KeywordFrequency *findKeyword(HashTable *hashTable, const char *word); // 在哈希表中查找关键词
void insertKeyword(HashTable *hashTable, const char *word); // 在哈希表中插入关键词
void shellSort(KeywordFrequency *array, int size); // 希尔排序
void writeToFileSorted(KeywordFrequency *keywords, int keywordCount, const char *filename, int includeZeroFrequency); // 将排序后的关键词频率写入文件

int main() {
   // 文件指针，用于打开关键词文件和文本文件
FILE *keywordFile, *textFile;

// 存储文件路径的字符串数组，分别表示关键词文件、文本文件、以及三个输出文件的路径
char keywordFilename[] = "C:\\Users\\86147\\Desktop\\quest\\Key.txt";
char textFilename[] = "C:\\Users\\86147\\Desktop\\quest\\InFile.txt";
char outFile1[] = "C:\\Users\\86147\\Desktop\\quest\\OutFile1.txt";
char outFile2[] = "C:\\Users\\86147\\Desktop\\quest\\OutFile2.txt";
char outFile3[] = "C:\\Users\\86147\\Desktop\\quest\\OutFile3.txt";

// 缓冲区，用于读取文件内容
char buffer[1000];

// 哈希表和关键词数组的声明
HashTable hashTable;
KeywordFrequency *keywords1, *keywords2, *sortedKeywords;

// 用于统计关键词数量的变量
int keywordCount1 = 0, keywordCount2 = 0;

    // 初始化哈希表
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable.table[i] = NULL;
    }

    int methodChoice;

    // 用户选择哪种方法
    printf("请选择使用的方法 (1 或 2):\n方法1:顺序查找\n方法2:基于开放地址法的哈希查找\n ");
    scanf("%d", &methodChoice);

    // 方法1：基于数组的方法
    if (methodChoice == 1) {
        keywordFile = fopen(keywordFilename, "r");

        if (keywordFile == NULL) {
            printf("无法打开关键词文件 %s\n", keywordFilename);
            return 1;
        }

        // 统计关键词数量
        while (fgets(buffer, sizeof(buffer), keywordFile) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            keywordCount1++;
        }

        rewind(keywordFile);

        // 分配内存存储关键词数组
        keywords1 = (KeywordFrequency *)malloc(keywordCount1 * sizeof(KeywordFrequency));

        // 读取关键词和初始化频率为0
        for (int i = 0; i < keywordCount1; i++) {
            fgets(keywords1[i].word, sizeof(keywords1[i].word), keywordFile);
            keywords1[i].word[strcspn(keywords1[i].word, "\n")] = '\0';
            keywords1[i].frequency = 0;
        }

      // 关闭关键词文件
fclose(keywordFile);

// 打开文本文件以供读取
textFile = fopen(textFilename, "r");

// 检查文本文件是否成功打开
if (textFile == NULL) {
    printf("无法打开文本文件 %s\n", textFilename);

    // 释放动态分配的内存并返回错误码
    free(keywords1);
    return 1;
}


      // 统计文本中关键词出现的频率
while (fgets(buffer, sizeof(buffer), textFile) != NULL) {
    // 遍历关键词数组
    for (int i = 0; i < keywordCount1; i++) {
        char *pos = buffer;

        // 在文本中搜索关键词并更新频率
        while ((pos = strstr(pos, keywords1[i].word)) != NULL) {
            keywords1[i].frequency++;
            pos += strlen(keywords1[i].word);
        }
    }
}

// 关闭文本文件
fclose(textFile);


        // 将结果写入OutFile1
        writeToFileSorted(keywords1, keywordCount1, outFile1, 1);

        free(keywords1);
    }
    // 方法2：基于哈希表的方法
    else if (methodChoice == 2) {
        keywordFile = fopen(keywordFilename, "r");

        if (keywordFile == NULL) {
            printf("无法打开关键词文件 %s\n", keywordFilename);
            return 1;
        }

        // 统计关键词数量
        while (fgets(buffer, sizeof(buffer), keywordFile) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            keywordCount2++;
        }

        rewind(keywordFile);

        // 分配内存存储关键词数组
        keywords2 = (KeywordFrequency *)malloc(keywordCount2 * sizeof(KeywordFrequency));

        // 读取关键词和初始化频率为0
        for (int i = 0; i < keywordCount2; i++) {
            fgets(keywords2[i].word, sizeof(keywords2[i].word), keywordFile);
            keywords2[i].word[strcspn(keywords2[i].word, "\n")] = '\0';
            keywords2[i].frequency = 0;
        }

        fclose(keywordFile);

        textFile = fopen(textFilename, "r");

        if (textFile == NULL) {
            printf("无法打开文本文件 %s\n", textFilename);
            free(keywords2);
            return 1;
        }

        // 统计文本中关键词出现的频率
        while (fgets(buffer, sizeof(buffer), textFile) != NULL) {
            for (int i = 0; i < keywordCount2; i++) {
                char *pos = buffer;
                while ((pos = strstr(pos, keywords2[i].word)) != NULL) {
                    keywords2[i].frequency++;
                    pos += strlen(keywords2[i].word);
                }
            }
        }

        fclose(textFile);

        // 将结果写入OutFile2
        writeToFileSorted(keywords2, keywordCount2, outFile2, 1);

        free(keywords2);
    } else {
        printf("无效的选择\n");
        return 1;
    }

    // 统一排序后写入OutFile3
    sortedKeywords = (KeywordFrequency *)malloc((keywordCount1 + keywordCount2) * sizeof(KeywordFrequency));
    int sortedCount = 0;

    if (methodChoice == 1) {
        for (int i = 0; i < keywordCount1; i++) {
            sortedKeywords[sortedCount++] = keywords1[i];
        }
    } else if (methodChoice == 2) {
        for (int i = 0; i < keywordCount2; i++) {
            sortedKeywords[sortedCount++] = keywords2[i];
        }
    }

    // 使用希尔排序对关键词进行排序
    shellSort(sortedKeywords, sortedCount);

    // 将排序后的结果写入OutFile3（包括频率为0的关键字）
    writeToFileSorted(sortedKeywords, sortedCount, outFile3, 0);

    free(sortedKeywords);

    return 0;
}

// 哈希函数
unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % HASH_TABLE_SIZE;
}

// 在哈希表中查找关键词
KeywordFrequency *findKeyword(HashTable *hashTable, const char *word) {
    unsigned int index = hash(word);
    HashNode *current = hashTable->table[index];

    while (current != NULL) {
        if (strcmp(current->data.word, word) == 0) {
            return &(current->data);
        }
        current = current->next;
    }

    return NULL;
}

// 在哈希表中插入关键词
void insertKeyword(HashTable *hashTable, const char *word) {
    unsigned int index = hash(word);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }

    // 将关键词和频率初始化，并插入哈希表
    strcpy(newNode->data.word, word);
    newNode->data.frequency = 0;
    newNode->next = NULL;

    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

// 希尔排序
void shellSort(KeywordFrequency *array, int size) {
    int gap, i, j;
    KeywordFrequency temp;
    for (gap = size / 5; gap > 0; gap /= 5) {
        for (i = gap; i < size; ++i) {
            temp = array[i];
            for (j = i; j >= gap && ((temp.frequency > array[j - gap].frequency) ||
                                     (temp.frequency == array[j - gap].frequency && strcmp(temp.word, array[j - gap].word) < 0)); j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = temp;
        }
    }
}

// 将排序后的关键词频率写入文件
void writeToFileSorted(KeywordFrequency *keywords, int keywordCount, const char *filename, int includeZeroFrequency) {
    FILE *outfile = fopen(filename, "w");

    if (outfile == NULL) {
        printf("无法打开输出文件 %s\n", filename);
        return;
    }

    // 遍历关键词数组，将非零频率或按需包括零频率的关键词写入文件
    for (int i = 0; i < keywordCount; i++) {
        if (keywords[i].frequency > 0 || includeZeroFrequency) {
            fprintf(outfile, "关键词 '%s' 出现的频率: %d\n", keywords[i].word, keywords[i].frequency);
        }
    }

    fclose(outfile);
}

