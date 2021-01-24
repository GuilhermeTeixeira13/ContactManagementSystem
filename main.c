#include<stdio.h>
#include"functions.h"
#include<stdlib.h>

int main(void)
{
	CONTACT *contacts;

	contacts = (CONTACT*)malloc(1*sizeof(CONTACT));

	addContactToList(contacts);
	addContactToList(contacts);
	printList(contacts);

	free(contacts);
	contacts = NULL;

	return 0;
}

