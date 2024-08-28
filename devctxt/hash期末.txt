#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>

#define MAX_WORD_LENGTH 100
#define HASH_TABLE_SIZE 100

typedef struct {
    char word[MAX_WORD_LENGTH];
    int frequency;
} KeywordFrequency;

typedef struct HashNode {
    KeywordFrequency data;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *table[HASH_TABLE_SIZE];
} HashTable;

unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % HASH_TABLE_SIZE;
}

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

void insertKeyword(HashTable *hashTable, const char *word) {
    unsigned int index = hash(word);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }

    strcpy(newNode->data.word, word);
    newNode->data.frequency = 0;
    newNode->next = NULL;

    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

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

int main() {
    FILE *keywordFile, *textFile, *outputFile;
    char keywordFilename[] = "C:\\Users\\86147\\Desktop\\quest\\Key.txt";
    char textFilename[] = "C:\\Users\\86147\\Desktop\\quest\\InFile.txt";
    char outputFilename[] = "C:\\Users\\86147\\Desktop\\quest\\OutFile4.txt";
    char buffer[1000];
    HashTable hashTable;

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hashTable.table[i] = NULL;
    }

    keywordFile = fopen(keywordFilename, "r");

    if (keywordFile == NULL) {
        printf("无法打开关键词文件 %s\n", keywordFilename);
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), keywordFile) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertKeyword(&hashTable, buffer);
    }

    fclose(keywordFile);

    textFile = fopen(textFilename, "r");

    if (textFile == NULL) {
        printf("无法打开文本文件 %s\n", textFilename);
        return 1;
    }

    int c;
    char word[MAX_WORD_LENGTH];
    int wordIndex = 0;
    while ((c = fgetc(textFile)) != EOF) {
        if (isalpha(c) || c == '_') {
            word[wordIndex++] = (char)c;
        } else {
            if (wordIndex > 0) {
                word[wordIndex] = '\0';
                KeywordFrequency *keyword = findKeyword(&hashTable, word);
                if (keyword != NULL) {
                    keyword->frequency++;
                }
                wordIndex = 0;
            }
        }
    }

    fclose(textFile);

    KeywordFrequency sortedKeywords[HASH_TABLE_SIZE];
    int sortedCount = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode *current = hashTable.table[i];
        while (current != NULL) {
            if (current->data.frequency > 0) {
                sortedKeywords[sortedCount++] = current->data;
            }
            current = current->next;
        }
    }

    shellSort(sortedKeywords, sortedCount);

    outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("无法打开输出文件 %s\n", outputFilename);
        fclose(textFile);
        return 1;
    }

    for (int i = 0; i < sortedCount; i++) {
        fprintf(outputFile, "关键词 '%s' 出现的频率: %d\n", sortedKeywords[i].word, sortedKeywords[i].frequency);
    }

    fclose(outputFile);

    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode *current = hashTable.table[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}

