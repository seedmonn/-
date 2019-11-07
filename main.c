#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define LEN 100
#define SPC 20

struct data
{
	char name[LEN];
	char spec[SPC];
	int num;
	int day;
	int st_vis;
	int end_vis;
	struct data* ptr;
};

struct data* init()
{
	struct data* lst;
	lst = (struct data*)malloc(sizeof(struct data));
	lst->ptr = NULL; 
	return (lst);
}

struct data* deleteHead(struct data* head)
{
	struct data* temp;
	temp = head->ptr;
	free(head);
	return(temp);
}

void deleteDoc(struct data* lst, struct data* head)
{
	struct data* temp;
	temp = head;
	while (temp->ptr != lst)
	{
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr;
	free(lst);
}
void freeStruct(struct data* head)
{
	struct data* current = head;
	struct data* next = NULL;
	do
	{
		next = current->ptr;
		free(current);
		current = next;
	} while (current != NULL);
}

struct data* appendlist(struct data** headRef)
{
	struct data* current = *headRef;
	struct data* lst;
	lst = (struct data*)malloc(sizeof(struct data));
	lst->ptr = NULL;
	
	if (current == NULL) {
		*headRef = lst;
	}
	else {
		
		while (current->ptr != NULL) {
			current = current->ptr;
		}
		current->ptr = lst;
	}
	return(lst);
}

void sort(struct data* headRef, int count)
{
	struct data* current;
	struct data* next;
	int noSwap;
	int iBuf;
	char cBuf[LEN];
	for (int i = count - 1; i >= 0; i--)
	{
		current = headRef;
		next = current->ptr;
		noSwap = 1;
		for (int j = 0; j < i; j++)
		{
			if (strcmp(current->name, next->name) > 0)
			{
				strcpy(cBuf, current->name);
				strcpy(current->name, next->name);
				strcpy(next->name, cBuf);
				strcpy(cBuf, current->spec);
				strcpy(current->spec, next->spec);
				strcpy(next->spec, cBuf);
				iBuf = current->num;
				current->num = next->num;
				next->num = iBuf;
				iBuf = current->day;
				current->day = next->day;
				next->day = iBuf;
				iBuf = current->st_vis;
				current->st_vis = next->st_vis;
				next->st_vis = iBuf;
				iBuf = current->end_vis;
				current->end_vis = next->end_vis;
				next->end_vis = iBuf;
				noSwap = 0;
			}
			current = current->ptr;
			next = current->ptr;
		}
		if (noSwap == 1)
			break;
	}
}
void input(struct data** headRef, int* cnt)
{
	FILE* fin;
	FILE* finit;
	char line[100];
	struct data* current;
	fin = fopen("test.txt", "r"); 
	if (fin == NULL)
	{
		finit = fopen("test.txt", "w");
		fclose(finit);
		fin = fopen("test.txt", "r");
	}
	while (!feof(fin))
	{
		if (!*cnt)
		{
			current = *headRef = init();
		}
		else
		{
			current = appendlist(headRef);
		}
		if (fscanf(fin, "%[^\n]\n", line) == -1)
		{
			break;
		}
		strcpy(current->name, line);
		fscanf(fin, "%[^\n]\n", line);
		strcpy(current->spec, line);
		fscanf(fin, "%d %d %d %d\n", &current->num, &current->day, &current->st_vis, &current->end_vis);
		(*cnt)++;
	}
	fclose(fin);
}
void save(struct data* head)
{
	FILE* fout;
	struct data* current = head;
	fout = fopen("test.txt", "w"); 
	while (current != NULL)
	{
		fprintf(fout, "%s\n", current->name);
		fprintf(fout, "%s\n", current->spec);
		fprintf(fout, "%d %d %d %d\n", current->num, current->day, current->st_vis, current->end_vis);
		current = current->ptr;
	}
	fclose(fout); 
}
