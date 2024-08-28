#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEYWORD_LENGTH 50
#define HASH_TABLE_SIZE 100

// �ṹ���ʾ��ϣ���еĽڵ�
typedef struct {
    char keyword[MAX_KEYWORD_LENGTH];
    int frequency;
} HashNode;

// ��ʼ����ϣ��
void initializeHashTable(HashNode hashTable[]) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        hashTable[i].frequency = 0;
    }
}

// ��ϣ����
int hashFunction(char *keyword) {
    int hash = 0;
    while (*keyword) {
        hash += *keyword++;
    }
    return hash % HASH_TABLE_SIZE;
}

// �ڹ�ϣ���в��ҹؼ���
int searchKeyword(HashNode hashTable[], char *keyword) {
    int hash = hashFunction(keyword);
    int initialHash = hash;

    while (hashTable[hash].frequency != 0) {
        if (strcmp(hashTable[hash].keyword, keyword) == 0) {
            return hash;
        }

        hash = (hash + 1) % HASH_TABLE_SIZE;

        // ��ֹ����ѭ��
        if (hash == initialHash) {
            break;
        }
    }

    return -1; // �ؼ���δ�ҵ�
}

// ���¹�ϣ���еĹؼ���Ƶ��
void updateFrequency(HashNode hashTable[], char *keyword) {
    int index = searchKeyword(hashTable, keyword);
    if (index != -1) {
        hashTable[index].frequency++;
    }
}

int main() {
    // ���ļ�
    FILE *inFile = fopen("C:\\Users\\86147\\Desktop\\quest\\InFile.txt", "r");
    FILE *keyFile = fopen("C:\\Users\\86147\\Desktop\\quest\\Key.txt", "r");
    FILE *outFile = fopen("C:\\Users\\86147\\Desktop\\quest\\OutFile1.txt", "w");

    if (inFile == NULL || keyFile == NULL || outFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    // ��ʼ����ϣ��
    HashNode hashTable[HASH_TABLE_SIZE];
    initializeHashTable(hashTable);

    // �ӹؼ����ļ��ж�ȡ�ؼ��ֲ������ϣ��
    char keyword[MAX_KEYWORD_LENGTH];
    while (fscanf(keyFile, "%s", keyword) != EOF) {
        int index = hashFunction(keyword);
        while (hashTable[index].frequency != 0) {
            index = (index + 1) % HASH_TABLE_SIZE;
        }
        strcpy(hashTable[index].keyword, keyword);
        hashTable[index].frequency = 0;
    }

    // �Ӵ����ļ��ж�ȡ��ͳ�ƹؼ���Ƶ��
    while (fscanf(inFile, "%s", keyword) != EOF) {
        updateFrequency(hashTable, keyword);
    }

    // �����д������ļ�
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        if (hashTable[i].frequency != 0) {
            fprintf(outFile, "%s: %d\n", hashTable[i].keyword, hashTable[i].frequency);
        }
    }

    // �ر��ļ�
    fclose(inFile);
    fclose(keyFile);
    fclose(outFile);

    return 0;
}

