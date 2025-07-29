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
				printf("해시테이블이 가득찼습니다!\n");
				return;
			}
		}

		if (hTable[index].key == NULL || strcmp(hTable[index].key, DEL) == 0) {
			hTable[index].key = strdup(key);
		}
		hTable[index].value = value;
	}
}
int search(char* key) { //테이블 내 값 탐색 함수
	int index = hashFunction(key);
	int first = index;
	if (hTable[index].key == NULL) {
		return -1; // 키가 존재하지 않음
	}
	do {
		if (strcmp(hTable[index].key, key) == 0) {
			return hTable[index].value; // Return the value if key matches
		}
		index = (index + 1) % buketSize; // Wrap around if necessary
		if(index == first) {
			break; // 테이블 일순 시 종료
		}
	} while (hTable[index].key != NULL);
		
	return -1; //오류 인덱스
}
void deleteKey(char* key) {
	int index = hashFunction(key);
	int first = index;
	while (hTable[index].key != NULL) {
		if (strcmp(hTable[index].key, key) == 0) {
			free(hTable[index].key); // 메모리 해제
			hTable[index].key = DEL; // 삭제 마킹
			hTable[index].value = 0; // 값 초기화
			return;
		}
		index = (index + 1) % buketSize; // Wrap around if necessary
		if (index == first) {
			break; // 테이블 일순 시 종료
		}
	}
	printf("키값 '%s' 을 찾을 수 없습니다.\n", key);
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
	printf("key에 exit을 입력하면 종료합니다.\n");
	while (1) {
		printf("Enter key: ");
		scanf("%s", key);
		if (strcmp(key, "exit") == 0) {
			break; // 종료 조건
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
		printf("선택값을 입력해주세요(정수): ");
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
					printf("키와 값은 '%s': %d\n", key, result);
				} else {
					printf("키값 '%s' 을 찾을 수 없습니다.\n", key);
				}
				break;
			case 3:
				printf("지울 키값을 입력해주세요.: ");
				scanf("%s", key);
				deleteKey(key);
				break;
			case 4:
				printHashTable();
				break;
			case 5:
				exit(0);
			default:
				printf("올바르지 않은 선택입니다.\n");
		}
	}
}