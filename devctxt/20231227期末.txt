#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYWORD_LENGTH 50
#define HASH_TABLE_SIZE 100

// 结构体表示哈希表中的节点
typedef struct {
    char keyword[MAX_KEYWORD_LENGTH];
    int frequency;
} HashNode;

// 初始化哈希表
void initializeHashTable(HashNode hashTable[]) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        hashTable[i].frequency = 0;
    }
}

// 哈希函数
int hashFunction(char *keyword) {
    int hash = 0;
    while (*keyword) {
        hash += *keyword++;
    }
    return hash % HASH_TABLE_SIZE;
}

// 在哈希表中查找关键字
int searchKeyword(HashNode hashTable[], char *keyword) {
    int hash = hashFunction(keyword);
    int initialHash = hash;

    while (hashTable[hash].frequency != 0) {
        if (strcmp(hashTable[hash].keyword, keyword) == 0) {
            return hash;
        }

        hash = (hash + 1) % HASH_TABLE_SIZE;

        // 防止无限循环
        if (hash == initialHash) {
            break;
        }
    }

    return -1; // 关键字未找到
}

// 更新哈希表中的关键字频度
void updateFrequency(HashNode hashTable[], char *keyword) {
    int index = searchKeyword(hashTable, keyword);
    if (index != -1) {
        hashTable[index].frequency++;
    }
}

int main() {
    // 打开文件
    FILE *inFile = fopen("C:\\Users\\86147\\Desktop\\quest\\InFile.txt", "r");
    FILE *keyFile = fopen("C:\\Users\\86147\\Desktop\\quest\\Key.txt", "r");
    FILE *outFile = fopen("C:\\Users\\86147\\Desktop\\quest\\OutFile1.txt", "w");

    if (inFile == NULL || keyFile == NULL || outFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // 初始化哈希表
    HashNode hashTable[HASH_TABLE_SIZE];
    initializeHashTable(hashTable);

    // 从关键字文件中读取关键字并插入哈希表
    char keyword[MAX_KEYWORD_LENGTH];
    while (fscanf(keyFile, "%s", keyword) != EOF) {
        int index = hashFunction(keyword);
        while (hashTable[index].frequency != 0) {
            index = (index + 1) % HASH_TABLE_SIZE;
        }
        strcpy(hashTable[index].keyword, keyword);
        hashTable[index].frequency = 0;
    }

    // 从代码文件中读取并统计关键字频度
    while (fscanf(inFile, "%s", keyword) != EOF) {
        updateFrequency(hashTable, keyword);
    }

    // 将结果写入输出文件
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        if (hashTable[i].frequency != 0) {
            fprintf(outFile, "%s: %d\n", hashTable[i].keyword, hashTable[i].frequency);
        }
    }

    // 关闭文件
    fclose(inFile);
    fclose(keyFile);
    fclose(outFile);

    return 0;
}

