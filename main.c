#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 100
#define SPC 20

enum Doctors {

	Surgeon = 1,
	Ophthalmologist,
	Therapist,
	Pediatrician,
	ENT,
	Dentist
};
enum Days {
	Monday = 1,
	Thuesday,
	Wednesday,
	Thursday,
	Friday
};
enum Worktime {
	MIN_START_TIME = 8,
	MAX_START_TIME = 16,
	MIN_END_TIME = 16,
	MAX_END_TIME = 24
};
enum Cabinet {
	MIN_NUM_OF_CAB = 1,
	MAX_NUM_OF_CAB = 99
};

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

void savecurrent(struct data* head)
{
	FILE* fout;
	struct data* current = head;
	fout = fopen("test.txt", "a+");
	while (current != NULL)
	{
		fprintf(fout, "%s\n", current->name);
		fprintf(fout, "%s\n", current->spec);
		fprintf(fout, "%d %d %d %d\n", current->num, current->day, current->st_vis, current->end_vis);
		current = current->ptr;
	}
	fclose(fout);
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
void addDoc(struct data** head, int* cnt)
{
	char spec[6][20] = { "Surgeon", "Ophthalmologist", "Therapist", "Pediatrician", "ENT", "Dentist" };
	char days[5][20] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
	char* ptr;
	int i;
	int callback_int;
	char callback_char[10];
	int flag;

	struct data* current;

	if (!*cnt)
	{
		current = *head = init();
		(*cnt)++;
	}
	else
	{
		current = appendlist(head);
		(*cnt)++;
	}
	system("cls");
	printf("Enter a name in the format Name N.N. : ");
	flag = 0;
	do {
		if (flag)
			printf("The name you entered is incorrect. Enter a name in the format Name N.N. ");
		scanf("\n%[^\n]", &current->name);
		ptr = &current->name;
		while (*ptr != '\0')
		{
			if (!(*ptr >= 'a' && *ptr <= 'z' || *ptr == ' ' || *ptr == '.' || *ptr >= 'A' && *ptr <= 'Z'))
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}
			ptr++;
		}
	} while (flag);
	flag = 0;
	system("cls");
	printf("Enter your doctor's specialty:\n");
	for (i = 0; i < 6; i++)
	{
		printf("[%d]%s\n", i + 1, spec[i]);
	}
	printf("Select a doctor's specialty (1-6): ");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 1 to 6: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
	} while (callback_int < Surgeon || callback_int > Dentist);
	strcpy(current->spec, spec[callback_int - 1]);
	system("cls");
	printf("Enter the cabinet number (1-99): ");
	flag = 0;
	do {
		if (flag)
			printf("Enter correct the cabinet number (1-99): ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
		current->num = callback_int;
	} while (callback_int < MIN_NUM_OF_CAB || callback_int > MAX_NUM_OF_CAB);
	system("cls");
	for (i = 0; i < 5; i++)
	{
		printf("[%d]%s\n", i + 1, days[i]);
	}
	printf("Select a doctor's work day (1-5): \n");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 1 to 5: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
	} while (callback_int < Monday || callback_int > Friday);
	current->day = callback_int;
	system("cls");
	printf("Enter the work start time from 8 to 16:");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 8 to 16: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
		current->st_vis = callback_int;
	} while (callback_int < MIN_START_TIME || callback_int > MAX_START_TIME);
	system("cls");
	printf("Enter the work end time from 16 to 24: ");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 16 to 24: ");
		scanf("%s", &callback_char);
		flag = 1;
		callback_int = atoi(callback_char);
		current->end_vis = callback_int;
	} while (callback_int < MIN_END_TIME || callback_int > MAX_END_TIME);
	savecurrent(current);
}
void edit(struct data* current)
{
	int i;
	char vibor[3];
	int ivibor = 0;
	int flag;
	char* ptr;
	char spec[6][20] = { "Surgeon", "Ophthalmologist", "Therapist", "Pediatrician", "ENT", "Dentist" };
	char days[5][20] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
	system("cls");
	printf("Old name of the doctor: %s \n", current->name);
	printf("Enter a new name for the doctor:\nName: ");
	flag = 0;
	do {
		if (flag)
			printf("The name you entered is incorrect. Enter a name in the format Name N.N.");
		scanf("\n%[^\n]", &current->name);
		ptr = &current->name;
		while (*ptr != '\0')
		{
			if (!(*ptr >= 'a' && *ptr <= 'z' || *ptr == ' ' || *ptr == '.' || *ptr >= 'A' && *ptr <= 'Z'))
			{
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}
			ptr++;
		}
	} while (flag);
	system("cls");
	printf("Old specialty of the doctor: %s \n", current->spec);
	printf("Enter a new doctor's specialty:\n");
	for (i = 0; i < 6; i++)
	{
		printf("[%d]%s\n", i + 1, spec[i]);
	}
	printf("Select a doctor's specialty (1-6): ");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 1 to 6: ");
		scanf("%s", &vibor);
		ivibor = atoi(vibor);
		flag = 1;
	} while ((ivibor < 1) || (ivibor > 6));
	strcpy(current->spec, spec[ivibor - 1]);
	system("cls");
	printf("Old cabinet number: %d\n", current->num);
	printf("Enter the new cabinet number (1 - 99): ");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 1 to 99: ");
		scanf("%s", &vibor);
		ivibor = atoi(vibor);
		flag = 1;
	} while ((ivibor < MIN_NUM_OF_CAB) || (ivibor > MAX_NUM_OF_CAB));
	current->num = ivibor;
	system("cls");
	printf("Former doctor's work day: %s \n", days[current->day - 1]);
	for (i = 0; i < 5; i++)
	{
		printf("[%d]%s\n", i + 1, days[i]);
	}
	printf("Select a doctor's work day (1-5): ");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 1 to 5: ");
		scanf("%s", &vibor);;
		ivibor = atoi(vibor);
		flag = 1;
	} while ((ivibor < Monday) || (ivibor > Friday));
	current->day = ivibor;
	system("cls");
	printf("Former doctor's work start time: %d\n", current->st_vis);
	printf("Enter the new work start time (8-16): ");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 8 to 16: ");
		scanf("%s", &vibor);;
		ivibor = atoi(vibor);
		flag = 1;
	} while ((ivibor < MIN_START_TIME) || (ivibor > MAX_START_TIME));
	current->st_vis = ivibor;
	system("cls");
	printf("Former doctor's work end time: %d \n", current->end_vis);
	printf("Enter the new work end time from 16 to 24: ");
	flag = 0;
	do {
		if (flag)
			printf("Incorrect value entered. Enter from 16 to 24: ");
		scanf("%s", &vibor);;
		ivibor = atoi(vibor);
		flag = 1;
	} while ((ivibor < MIN_END_TIME) || (ivibor > MAX_END_TIME));
	current->end_vis = ivibor;
	system("cls");
	savecurrent(current);
}

int main(void)
{
	system("chcp 1251");
	system("cls");
	struct data* head = NULL;
	struct data* current = NULL;
	char vibor[3];
	int count = 0, i = 0, flag = 0, ivibor = 0, bufhour = 0;
	char spec[6][20] = { "Surgeon", "Ophthalmologist", "Therapist", "Pediatrician", "ENT", "Dentist" };
	char days[5][20] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
	char main;
	input(&head, &count);
	do
	{
		system("cls");
		printf("[0] Quit the program\n[1] Add a new doctor\n[2] Edit info about doctor\n[3] Dismiss a doctor\n[4] Sort doctors by alphabetical order\n[5] Sort by number of cabinet\n[6] Sort by specialization & alphabetical order\n[7] Sort by specialization & work time\n Select a number from the list: ");
		scanf("%c", &main);
		switch (main)
		{
		case '1':
			addDoc(&head, &count);
			break;
		case '2':
			system("cls");
			if (!count)
			{
				printf("No doctors\n");
				system("pause");
				break;
			}
			i = 0;
			current = head;
			while (current != NULL)
			{
				printf("[%d] %s - %s\n", i + 1, current->name, current->spec);
				i++;
				current = current->ptr;
			}
			printf("Select a doctor to change: ");
			flag = 0;
			do {
				if (flag)
					printf("Incorrect value entered. Enter again: ");
				scanf("%s", &vibor);
				ivibor = atoi(vibor);
				flag = 1;
			} while ((ivibor < 1) || (ivibor > count));
			current = head;
			for (i = 0; i < ivibor - 1; i++)
			{
				current = current->ptr;
			}
			edit(current);
			break;
		case '3':
			system("cls");
			if (!count)
			{
				printf("No doctors\n");
				system("pause");
				break;
			}
			current = head;
			i = 0;
			while (current != NULL)
			{
				printf("[%d] %s\n", i + 1, current->name);
				i++;
				current = current->ptr;
			}
			printf("Select a doctor to dismiss: ");
			flag = 0;
			do {
				if (flag)
					printf("Incorrect value entered. Enter again: ");
				scanf("%s", &vibor);
				ivibor = atoi(vibor);
				flag = 1;
			} while ((ivibor < 1) || (ivibor > count));
			current = head;
			for (i = 0; i < ivibor - 1; i++)
			{
				current = current->ptr;
			}
			if (ivibor == 1)
			{
				head = deleteHead(current);

			}
			else
			{
				deleteDoc(current, head);
			}
			count--;
			break;
		case '4':
			if (!count)
			{
				printf("No doctors\n");
				system("pause");
				break;
			}
			sort(head, count);
			current = head;
			i = 1;
			while (current != NULL)
			{
				printf("------[%d]------\n", i);
				printf("Specialty: %s\n", current->spec);
				printf("Name: %s\n", current->name);
				printf("Cabinet: %d\n", current->num);
				printf("Day: %s\n", days[(current->day) - 1]);
				printf("Start/End work time: from |%d:00 - %d:00|\n", current->st_vis, current->end_vis);
				i++;
				current = current->ptr;
			}
			system("pause");
			break;
		case '5':
			system("CLS");
			if (!count)
			{
				printf("No doctors\n");
				system("pause");
				break;
			}
			printf("Enter the cabinet number (1-99): ");
			flag = 0;
			do {
				if (flag)
					printf("Incorrect value entered. Enter again: ");
				scanf("%s", &vibor);
				ivibor = atoi(vibor);
				flag = 1;
			} while ((ivibor < MIN_NUM_OF_CAB) || (ivibor > MAX_NUM_OF_CAB));
			system("CLS");
			printf("==================================================\n");
			printf("Cabinet - %d\n", ivibor);
			printf("==================================================\n");
			for (i = 1; i < 6; i++)
			{
				printf("__________________________________________________\n");
				printf("%s\n", days[--i]);
				printf("__________________________________________________\n");
				current = head;
				i++;
				while (current != NULL)
				{
					if (current->num == ivibor && current->day == i)
						printf("\n%s - %s |%d:00 - %d:00|\n", current->name, current->spec,current->st_vis, current->end_vis);
					current = current->ptr;
				}
				printf("\n");
			}
			system("pause");
			break;
		case '6':
			system("CLS");
			if (!count)
			{
				printf("No doctors\n");
				system("pause");
				break;
			}
			for (i = 0; i < 6; i++)
			{
				printf("[%d]%s\n", i + 1, spec[i]);
			}
			printf("Select a doctor's specialty (1-6): ");
			flag = 0;
			do {
				if (flag)
					printf("Incorrect value entered. Enter from 1 to 6: ");
				scanf("%s", &vibor);
				ivibor = atoi(vibor);
				flag = 1;
			} while ((ivibor < Surgeon) || (ivibor > Dentist));
			system("CLS");
			current = head;
			i = 1;
			while (current != NULL)
			{
				if (!strcmp(current->spec, spec[ivibor - 1]))
				{
					printf("------[%d]------\n", i);
					printf("Specialty: %s\n", current->spec);
					printf("Name: %s\n", current->name);
					printf("Cabinet: %d\n", current->num);
					printf("Day: %s\n", days[(current->day) - 1]);
					printf("Start/End work time from |%d:00 - %d:00|\n\n", current->st_vis, current->end_vis);
					i++;
				}
				current = current->ptr;
			}
			system("pause");
			break;
		case '7':
			system("CLS");
			if (!count)
			{
				printf("No doctors\n");
				system("pause");
				break;
			}
			printf("Enter your visitng hours (8-24):\n");
			flag = 0;
			do {
				if (flag)
					printf("Incorrect value entered. Enter again (8-24): ");
				scanf("%s", &vibor);
				bufhour = atoi(vibor);
				flag = 1;
			} while ((bufhour < MIN_START_TIME) || (bufhour > MAX_END_TIME));
			system("CLS");
			for (i = 0; i < 6; i++)
			{
				printf("[%d]%s\n", i + 1, spec[i]);
			}
			printf("Select a doctor's specialty (1-6): ");
			flag = 0;
			do {
				if (flag)
					printf("Incorrect value entered. Enter from 1 to 6: ");
				scanf("%s", &vibor);
				flag = 1;
				ivibor = atoi(vibor);
			} while (ivibor < Surgeon || ivibor > Dentist);
			system("cls");
			printf("==================================================\n");
			printf("Specialization - %s | Cab. - %d\n", spec[--ivibor], bufhour);
			printf("==================================================\n");
				for (i = 1; i < 6; i++)
			{
				printf("__________________________________________________\n");
				printf("%s\n", days[--i]);
				printf("__________________________________________________\n");
				current = head;
				i++;
				while (current != NULL)
				{
					if ((strcmp(current->spec, spec[ivibor]) == 0) && (bufhour >= current->st_vis && bufhour <= current->end_vis) && (current->day == i))
						printf("\n%s - %s |%d:00 - %d:00| Cab.:%d\n", current->name, current->spec, current->st_vis, current->end_vis, current->num);
					current = current->ptr;
				}
				printf("\n");
			}
			system("pause");
			break;
		default:
			break;
		}
	} while (main != '0');
	save(head);
	freeStruct(head);
	return 0;
}
