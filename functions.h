#include<stdio.h>

typedef struct contact
{
	char name[40];
	char gender[40];
	char adress[40];
	char notes[200];
	struct contact *next;
}CONTACT;

/*
CONTACT creatContact();
void addContactToList(CONTACT *contactList, int listSize);
void printList(CONTACT *contactList);
void saveTXT(CONTACT *contacts, char *fileName);
int listSizeFinder(CONTACT *contactlist);
void readTXT(CONTACT *contacts, char *fileName);
int sumContactsInFile(char *fileName);
int returnsPositionsToRemove(char *name, CONTACT *contacts);
void minuscula(char *original, char *final);
void removeContactIO(CONTACT *contacts);*/


void linha();
void limpaInput();
void inicializeHead(CONTACT **contact);
CONTACT *createContact(char *name, char *gender, char *adress, char *notes);
int addContact(CONTACT **head, char *name, char *gender, char *adress, char *notes);
void listContacts(CONTACT *head);
int removeContact(CONTACT **head, char *name);
void saveTXT(CONTACT **head, char *fileName);
FILE *openFile(char *fnome, char *modo);
void closeFile(FILE *f, char *fnome);





