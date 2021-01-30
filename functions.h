/**
 * @file      "functions.h"
 * @brief     This file contains all the headers needed to the correct behavior of the program.
 * @author    Guilherme Teixeira
 * @version   1.0.
*/

#include<stdio.h>

typedef struct contact
{
	char name[40];
	char gender[40];
	char adress[40];
	char notes[200];
	struct contact *next;
}CONTACT;

void linha();

void cleanInput();

void cleanConsole();

void leaving();

void intro();

void inicialize(CONTACT **contact);

CONTACT *createContact(char *name, char *gender, char *adress, char *notes);

int addContact(CONTACT **head, char *name, char *gender, char *adress, char *notes);

void listContacts(CONTACT **head);

int removeContact(CONTACT **head, char *name);

void saveTXT(CONTACT **head, char *fileName);

FILE *openFile(char *fname, char *mode);

void closeFile(FILE *f, char *fname);





