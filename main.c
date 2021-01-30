/**
 * @file      "main.c"
 * @brief     This is the main file of the project called "Contact Management System". Was used mainly the C source code (Linked Lists, Strings, Functions, etc).
 * @details	  As the name suggests, in this project you can easily add, remove and list contacts and keep them updated in a txt file("contacts.txt").
 * @author    Guilherme Teixeira
 * @version   1.0.
*/

#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

int main()
{
	cleanConsole();
	int op=1, res=0, invalidName = 0;

	char name[40];
	char gender[40];
	char adress[40];
	char notes[200];
	char insideOption[5];

    CONTACT *head;
    inicialize(&head);

	CONTACT *current;
	inicialize(&current);

	FILE *file;
    char line[128];

	/* ↓   Open the file and save, in a linked list, all the contacts in it   ↓ */
	file = openFile("contacts.txt", "r");

    while(fscanf(file, "NAME:%[^|]|GENDER:%[^|]|ADRESS:%[^|]|NOTES:%[^|]|\n", name, gender, adress, notes) == 4) // Keep looping until fail to read a full contact
	{
        CONTACT *contact = malloc(sizeof(CONTACT));

		strcpy(contact->name, name);
		strcpy(contact->gender, gender);
		strcpy(contact->adress, adress);
		strcpy(contact->notes, notes);

        contact->next =NULL;

        if(head == NULL) // If doens't exist any contact in "contacts.txt"
            current = head = contact;   
		else 
            current = current->next = contact; // Travel to the next contact
    }
	closeFile(file, "contacts.txt");

    while (op != 0)
    {
		intro();
		/* ↓   Ask user for an option   ↓ */
        while (scanf("%d", &op) != 1) 
        {
            cleanInput();
            printf("Invalid input, please choose an option --> ");
        }
		while(op>3 ||op<0)
		{
			printf("That option isn't avaiable, please pick other one --> ");
			scanf("%d", &op);
		}
        switch (op)
        {
        case 1:
			system("clear");
			linha();
			printf("*\t\t\tADD NEW CONTACT                        *\n");
			linha();
			do
			{
				cleanInput();
				/* ↓   Asks user for NAME, GENDER, ADRESS and NOTES of the contact that he is adding   ↓ */
				do
				{
					printf("▹ NAME: ");
					fgets(name, 40, stdin);
					char *pos1 = strchr(name,'\n');
					*pos1 = '\0';
					if(strcmp(name, "\0") == 0)
					{
						invalidName = 1;
						printf(" - Error! The contact needs a name.\n");
					}
				} while(strcmp(name, "\0") == 0);

				printf("▹ GENDER: ");
				fgets(gender, 40, stdin);
				char *pos2 = strchr(gender,'\n');
				*pos2 = '\0';

				printf("▹ ADRESS: ");
				fgets(adress, 40, stdin);
				char *pos3 = strchr(adress,'\n');
				*pos3 = '\0';

				printf("▹ EXTRA NOTES: ");
				fgets(notes, 200, stdin);
				char *pos4 = strchr(notes,'\n');
				*pos4 = '\0';

				if (addContact(&head, name, gender, adress, notes) == -1)
					printf("\n✘ Failed to add contact.\n");
				else
					printf("\n✔ Contact has been added.\n");

				saveTXT(&head, "contacts.txt"); // Save all the changes in "contacts.txt"

				printf("\nWrite 'q'/'quit' to leave or press any other key to continue: ");
				scanf("%s", insideOption);
				if(strcmp(insideOption, "q") != 0 && strcmp(insideOption, "quit") != 0)
					linha();
			} while(strcmp(insideOption, "q") != 0 && strcmp(insideOption, "quit") != 0); // Asks user if he wants to keep adding contacts
			cleanConsole();
            break;
        case 2:
			cleanConsole();
			linha();
			printf("*\t\t\t DELETE CONTACT                        *\n");
			linha();

			do
			{
				cleanInput();
				printf("Contact NAME to be removed ✂  ");

				fgets(name, 40, stdin);
				char *pos5 = strchr(name,'\n');
				*pos5 = '\0';

				res = removeContact(&head, name);

				if(res == -1)
					printf("\n✘  Name not founded.\n");
				if(res == 1)
				{
					printf("\n✔  Contact has been sucessfly removed.\n");
					saveTXT(&head, "contacts.txt"); // Save all the changes in "contacts.txt"
				}

				printf("\nWrite 'q'/'quit' to leave or press any other key to continue: ");
				scanf("%s", insideOption);
				if(strcmp(insideOption, "q") != 0 && strcmp(insideOption, "quit") != 0)
					linha();
			} while(strcmp(insideOption, "q") != 0 && strcmp(insideOption, "quit") != 0); // Asks the user if he wants to keep removing contacts

			cleanConsole();
            break;
        case 3:
			cleanConsole();
			linha();
			printf("*\t\t\tLIST OF CONTACTS                       *\n");
			linha();
			cleanInput();
            listContacts(&head);
			cleanConsole();
            break;
        case 0:
			leaving();
            break;
        }
    }
    return 0;
}


