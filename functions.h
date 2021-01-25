#include<stdio.h>

typedef struct
{
	char name[40];
	char gender[40];
	char adress[40];
	char notes[200];
}CONTACT;

CONTACT creatContact();
void addContactToList(CONTACT *contactList, int listSize);
void printList(CONTACT *contactList);
void linha();
void limpaInput();
int listSizeFinder(CONTACT *contactlist);
