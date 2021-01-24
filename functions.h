#include<stdio.h>

typedef struct
{
	char name[20];
	char gender[15];
	char adress[25];
	char notes[200];
}CONTACT;

CONTACT creatContact();
void addContactToList(CONTACT *contactList);
void printList(CONTACT *contactList);
void linha();
void limpaInput();
int listSizeFinder(CONTACT *contactlist);
