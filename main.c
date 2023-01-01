#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct word {
	char* eng;
	char* kor;
	struct word* next;
};

int reload_word(struct word **list, int cnt);
void show_word(struct word* list);
void Test(struct word** list, int cnt);

int main() {
	struct word* list = NULL;

	int in, cnt = 0;

	cnt = reload_word(&list, cnt);
	printf("\n");
	printf("*****TOEIC Word Test Program*****\n\n");
	printf("Reloaded [%d]words from \"word_list.txt\"\n", cnt);

	while (1) {
		printf("\n");
		printf("*****Menu*****\n\n");
		printf("[1] Show word\n");
		printf("[2] Test Start\n");
		printf("[other input] Exit\n\n");
		printf("[Input] >> ");
		scanf("%d", &in);
		printf("\n");

		switch (in) {
		case 1: show_word(list);
			break;
		case 2: Test(&list, cnt);
			break;
		default:
			break;
		}
		if (!(in > 0 && in < 3))
			break;
	}

	return 0;
}

int reload_word(struct word** list, int cnt) {
	char eng[101], kor[101];
	struct word* new_node;

	FILE* fp = fopen("word_list.txt", "r");

	while (1) {
		fscanf(fp, "%s %s", eng, kor);

		if ((feof(fp) != 0))
			break;

		++cnt;

		new_node = (struct word*)malloc(sizeof(struct word));

		new_node->eng = (char*)malloc((strlen(eng) + 1) * sizeof(char));
		strcpy(new_node->eng, eng);
		new_node->kor = (char*)malloc((strlen(kor) + 1) * sizeof(char));
		strcpy(new_node->kor, kor);

		new_node->next = *list;
		*list = new_node;

		//free(new_node);
	}

	fclose(fp);

	return cnt;
}

void show_word(struct word* list) {
	struct word* p;

	printf("[Word List]\n\n");

	for (p = list; p != NULL; p = p->next)
		printf("%s %s\n", p->eng, p->kor);

}

void Test(struct word** list, int cnt) {
	struct word* words, *p;
	int i, j, *num, o = 0, x = 0;
	char in[101];

	srand(time(NULL));

	words = (struct word*)malloc(cnt*sizeof(struct word));
	num = (int*)malloc(cnt * sizeof(int));

	for (p = *list, i = 0; p != NULL; p = p->next, ++i) {
		words[i].eng = (char*)malloc((strlen(p->eng) + 1) * sizeof(char));
		strcpy(words[i].eng, p->eng);
		words[i].kor = (char*)malloc((strlen(p->kor) + 1) * sizeof(char));
		strcpy(words[i].kor, p->kor);
	}

	for (i = 0; i < cnt; ++i) {
		num[i] = (rand() % cnt);
		for (j = 0; j < i; ++j) {
			if (num[i] == num[j]) {
				--i;
				break;
			}
		}
	}

	printf("Test start!\n\n");

	for (i = 0; i < cnt; ++i) {
		printf("%s  > ", words[num[i]].eng);
		scanf("%s", in);
		if (strcmp(in, words[num[i]].kor) == 0) {
			printf("Correct!\n");
			++o;
		}
		else {
			printf("Wrong!  The answer is [ %s ]\n", words[num[i]].kor);
			++x;
		}
	}
	printf("Test End!\n");
	printf("Correct : %d	Wrong : %d\n\n", o, x);
}