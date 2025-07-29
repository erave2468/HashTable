#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define buketSize 13
#define MALLOC(p,s)\
	if (!((p) = malloc(s))) {\
		fprintf(stderr, "Insufficient memory");\
		exit(EXIT_FAILURE);\
	}
#define DEL "DELETED"
typedef struct {
	char* key;
	int value;
} HashTable;
HashTable hTable[buketSize];

int hashFunction(char* key) {
	int hash = key[0] - 'a';
	return hash % buketSize;
}
void insert(char* key, int value) {
	int index = hashFunction(key);
	int first = index;

	if (hTable[index].key == NULL) {
		hTable[index].key = strdup(key);
		hTable[index].value = value;
		return;
	}
	else if (strcmp(hTable[index].key, key) == 0) {
		hTable[index].value = value;
		return;
	}
	else {
		while (hTable[index].key != NULL &&
			strcmp(hTable[index].key, key) != 0 &&
			strcmp(hTable[index].key, DEL) != 0) {
			index = (index + 1) % buketSize;
			if (first == index) {
				printf("�ؽ����̺��� ����á���ϴ�!\n");
				return;
			}
		}

		if (hTable[index].key == NULL || strcmp(hTable[index].key, DEL) == 0) {
			hTable[index].key = strdup(key);
		}
		hTable[index].value = value;
	}
}
int search(char* key) { //���̺� �� �� Ž�� �Լ�
	int index = hashFunction(key);
	int first = index;
	if (hTable[index].key == NULL) {
		return -1; // Ű�� �������� ����
	}
	do {
		if (strcmp(hTable[index].key, key) == 0) {
			return hTable[index].value; // Return the value if key matches
		}
		index = (index + 1) % buketSize; // Wrap around if necessary
		if(index == first) {
			break; // ���̺� �ϼ� �� ����
		}
	} while (hTable[index].key != NULL);
		
	return -1; //���� �ε���
}
void deleteKey(char* key) {
	int index = hashFunction(key);
	int first = index;
	while (hTable[index].key != NULL) {
		if (strcmp(hTable[index].key, key) == 0) {
			free(hTable[index].key); // �޸� ����
			hTable[index].key = DEL; // ���� ��ŷ
			hTable[index].value = 0; // �� �ʱ�ȭ
			return;
		}
		index = (index + 1) % buketSize; // Wrap around if necessary
		if (index == first) {
			break; // ���̺� �ϼ� �� ����
		}
	}
	printf("Ű�� '%s' �� ã�� �� �����ϴ�.\n", key);
}
void printHashTable() {
	for (int i = 0; i < buketSize; i++) {
		if (hTable[i].key != NULL && strcmp(hTable[i].key, DEL) != 0) {
			printf("Index %d: Key = %s, Value = %d\n", i, hTable[i].key, hTable[i].value);
		} else {
			printf("Index %d: Empty\n", i);
		}
	}
}
void enterKey() {
	int value;
	char key[100];
	printf("key�� exit�� �Է��ϸ� �����մϴ�.\n");
	while (1) {
		printf("Enter key: ");
		scanf("%s", key);
		if (strcmp(key, "exit") == 0) {
			break; // ���� ����
		}
		printf("Enter value: ");
		scanf("%d", &value);
		insert(key, value);
	}
}
int main() {
	int choice, value;
	char key[100];
	while (1) {
		printf("1. Insert 2. Search 3. Delete 4. Print Hash Table 5. Exit");
		printf("���ð��� �Է����ּ���(����): ");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1:
				enterKey();
				break;
			case 2:
				printf("Enter key to search: ");
				scanf("%s", key);
				int result = search(key);
				if (result != -1) {
					printf("Ű�� ���� '%s': %d\n", key, result);
				} else {
					printf("Ű�� '%s' �� ã�� �� �����ϴ�.\n", key);
				}
				break;
			case 3:
				printf("���� Ű���� �Է����ּ���.: ");
				scanf("%s", key);
				deleteKey(key);
				break;
			case 4:
				printHashTable();
				break;
			case 5:
				exit(0);
			default:
				printf("�ùٸ��� ���� �����Դϴ�.\n");
		}
	}
}