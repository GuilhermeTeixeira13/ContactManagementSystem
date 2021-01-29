#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>

int main()
{
	int op=1, res=0;

	char name[40];
	char gender[40];
	char adress[40];
	char notes[200];

    CONTACT *head;
    inicialize(&head);

	CONTACT *current;
	inicialize(&current);

	FILE *file;
    char line[128];

	file = openFile("contacts.txt", "r");

    while(fscanf(file, "NAME:%[^|]|GENDER:%[^|]|ADRESS:%[^|]|NOTES:%[^|]|\n", name, gender, adress, notes) == 4)
	{
        CONTACT *contact = malloc(sizeof(CONTACT));

		strcpy(contact->name, name);
		strcpy(contact->gender, gender);
		strcpy(contact->adress, adress);
		strcpy(contact->notes, notes);

        contact->next =NULL;

        if(head == NULL)
            current = head = contact;   
		else 
            current = current->next = contact;
    }
	closeFile(file, "contacts.txt");

    while (op != 0)
    {
        linha();
        printf("1 - ADD CONTACT\n");
        printf("2 - DELETE CONTACT\n");
        printf("3 - SHOW CONTACTS\n");
        printf("\n0 - LEAVE\n");
		printf("OPTION --> ");
        while (scanf("%d", &op) != 1) 
        {
            limpaInput();
            printf("Invalid input, please choose an option --> ");
        }
		while(op>3 ||op<0)
		{
			printf("That option isn't avaiable, please pick other --> ");
			scanf("%d", &op);
		}
        switch (op)
        {
        case 1:
			linha();
			limpaInput();
            printf("NAME: ");
			fgets(name, 40, stdin);
			char *pos1 = strchr(name,'\n');
			*pos1 = '\0';

			printf("GENDER: ");
			fgets(gender, 40, stdin);
			char *pos2 = strchr(gender,'\n');
			*pos2 = '\0';

			printf("ADRESS: ");
			fgets(adress, 40, stdin);
			char *pos3 = strchr(adress,'\n');
			*pos3 = '\0';

			printf("EXTRA NOTES: ");
			fgets(notes, 200, stdin);
			char *pos4 = strchr(notes,'\n');
			*pos4 = '\0';

            if (addContact(&head, name, gender, adress, notes) == -1)
                printf("Failed to add contact.\n");
            else
                printf("Contact has been added.\n");

			saveTXT(&head, "contacts.txt");
            break;

        case 2:
			linha();
			limpaInput();
            printf("Contact NAME to be removed: \n");
			fgets(name, 40, stdin);
			char *pos5 = strchr(name,'\n');
			*pos5 = '\0';

			res = removeContact(&head, name);

			if(res == -1)
                printf("Name not founded.");
			if(res == 1)
				printf("Contact has been sucessfly removed.");

			saveTXT(&head, "contacts.txt");

            break;
        case 3:
			linha();
            listContacts(head);
            break;
        case 0:
            printf("xau\n");
            break;
        }
    }

    return 0;
}


