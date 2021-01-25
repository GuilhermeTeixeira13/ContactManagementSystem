#include<stdio.h>
#include"functions.h"
#include<stdlib.h>

int main(void)
{
	CONTACT *contacts;
	int listSize;

	contacts = (CONTACT*)malloc(sizeof(CONTACT));
	

	listSize = listSizeFinder(contacts);
	contacts = (CONTACT*)realloc(contacts, (sizeof(CONTACT))*(listSize+1));
	addContactToList(contacts, listSize);

	listSize = listSizeFinder(contacts);
	contacts = (CONTACT*)realloc(contacts, (sizeof(CONTACT))*(listSize+1));
	addContactToList(contacts, listSize);

	saveTXT(contacts, "contacts.txt");

	listSize = listSizeFinder(contacts);
	contacts = (CONTACT*)realloc(contacts, (sizeof(CONTACT))*(listSize+1));
	addContactToList(contacts, listSize);

	saveTXT(contacts, "contacts.txt");

	printList(contacts);

	free(contacts);
	contacts = NULL;

	return 0;
}

