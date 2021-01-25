#include<stdio.h>
#include"functions.h"
#include<stdlib.h>

int main(void)
{
	CONTACT *contacts;
	int listSize;

	contacts = (CONTACT*)malloc(sizeof(CONTACT));
	if(contacts==NULL)
	{
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	listSize = listSizeFinder(contacts);
	contacts = (CONTACT*)realloc(contacts, (sizeof(CONTACT))*(listSize+1));
	addContactToList(contacts, listSize);

	listSize = listSizeFinder(contacts);
	contacts = (CONTACT*)realloc(contacts, (sizeof(CONTACT))*(listSize+1));
	addContactToList(contacts, listSize);

	printList(contacts);

	free(contacts);
	contacts = NULL;

	return 0;
}

