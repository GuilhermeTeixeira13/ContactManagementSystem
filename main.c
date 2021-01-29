#include<stdio.h>
#include"functions.h"
#include<stdlib.h>

int main(void)
{
	CONTACT *contacts;
	int listSize, contactsInFile;

	contactsInFile = sumContactsInFile("contacts.txt");

	contacts = (CONTACT*)malloc((sizeof(CONTACT))*(contactsInFile));

	readTXT(contacts, "contacts.txt");

	listSize = listSizeFinder(contacts);
	contacts = (CONTACT*)realloc(contacts, (sizeof(CONTACT))*(listSize+1));
	addContactToList(contacts, listSize);

	listSize = listSizeFinder(contacts);
	contacts = (CONTACT*)realloc(contacts, (sizeof(CONTACT))*(listSize+1));
	addContactToList(contacts, listSize);

	saveTXT(contacts, "contacts.txt");

	printList(contacts);

	/*removeContactIO(contacts);
	printList(contacts);

	listSize = listSizeFinder(contacts);
	printf("Tamanho da lista atual --> %d", listSize);
	

	saveTXT(contacts, "contacts.txt");*/
	

	free(contacts);
	contacts = NULL;

	return 0;
}

