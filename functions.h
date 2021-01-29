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
void saveTXT(CONTACT *contacts, char *fileName);
int listSizeFinder(CONTACT *contactlist);
void readTXT(CONTACT *contacts, char *fileName);
int sumContactsInFile(char *fileName);
int returnsPositionsToRemove(char *name, CONTACT *contacts);
void minuscula(char *original, char *final);
int removeContact(char *name, CONTACT *contacts);
void removeContactIO(CONTACT *contacts);

