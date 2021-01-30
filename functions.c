#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <unistd.h>

void cleanInput()
{
    while (getchar() != '\n');
}

void cleanConsole()
{
    system("clear");
}

void linha()
{
    printf("----------------------------------------------------------------\n");
}

void leaving()
{
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
  	printf("┃ *\t\t>  THANKS FOR USING THIS PROGRAM  <          * ┃\n");
  	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

FILE *openFile(char *fnome, char *modo) 
{
    FILE *f = fopen(fnome, modo);

    if (f == NULL)
    {
        fprintf(stderr, "Failed to open %s.\n", fnome);
        exit(EXIT_FAILURE);
    }

    return f;
}

void closeFile(FILE *f, char *fnome)
{
    if (fclose(f) == EOF)
    {
        fprintf(stderr, "Failed to close %s.\n", fnome);
        exit(EXIT_FAILURE);
    }
}

void saveTXT(CONTACT **head, char *fileName)
{
    FILE *file = openFile(fileName, "w+");

    CONTACT *temp = *head;
    
    while(1)
    {
        fprintf(file, "NAME:%s|GENDER:%s|ADRESS:%s|NOTES:%s|\n", temp->name, temp->gender, temp->adress, temp->notes);
        temp = temp->next;
        if(temp == NULL)
            break;
    }

    closeFile(file, fileName);
}

void inicialize(CONTACT **contact)
{
    *contact = NULL;
}

CONTACT *createContact(char *name, char *gender, char *adress, char *notes)
{

    CONTACT *contact = malloc(sizeof(CONTACT));

    strcpy(contact->name, name);
    strcpy(contact->gender, gender);
    strcpy(contact->adress, adress);
    strcpy(contact->notes, notes);

    contact->next = NULL;
    return contact;
}

int addContact(CONTACT **head, char *name, char *gender, char *adress, char *notes)
{

    CONTACT *temp = *head;

    if (*head == NULL)
    {
        *head = (CONTACT *)malloc(sizeof(CONTACT));
        if (*head == NULL)
            return -1;

        (*head) = createContact(name, gender, adress, notes);
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = (CONTACT *)malloc(sizeof(CONTACT));

        if (temp->next == NULL)
            return -1;

        temp->next = createContact(name, gender, adress, notes);
    }
    return 0;
}

void listContacts(CONTACT **head)
{
    int i = 0, out=0, valid;
    char decison[12];
    char *pos;

    CONTACT *temp = *head;

    if (*head == NULL)
    {
        printf("\t\t     ☛    Empty list    ☚\n"); 
        sleep(2);
    }
    else
    {
        while (temp != NULL && out != 1)
        {
            printf("\n▹ NAME: %s\n", temp->name);
            printf("▹ GENDER: %s\n", temp->gender);
            printf("▹ ADRESS: %s\n", temp->adress);
            printf("▹ NOTES: %s\n\n", temp->notes);

            temp = temp->next;
            
            if ((i + 1) % 5 == 0)
            {
                valid=0;
                printf("- Press ENTER to see the next five or 'q'/'quit' to leave --> ");
                fgets(decison, 257, stdin);
                pos = strchr(decison, '\n');
                *pos = '\0';

                if(strcmp(decison, "q") == 0 || strcmp(decison, "quit") == 0)
                    out = 1;
                else if(decison[0] == '\0')
                    out = 0;
                else
                {
                    while(valid != 1)
                    {
                        printf(" ✘  Invalid option! Press ENTER to see the next five or 'q'/'quit' to leave --> ");

                        fgets(decison, 257, stdin);
                        pos = strchr(decison, '\n');
                        *pos = '\0';

                        if(strcmp(decison, "q") == 0 || strcmp(decison, "quit") == 0)
                        {
                            out = 1;
                            valid = 1;
                        }
                        else if(decison[0] == '\0')
                        {
                            out = 0;
                            valid = 1;
                        }
                        else
                            valid = 0; 
                    }
                }
                printf("\n");
            }
            
            if ((i + 1) % 5 != 0)
                linha(); 
            else
                printf("****************************************************************\n"); 
            i++;    
        }
        if((i+1)<5)
        {
            printf("  You will be redirected to the main page in about 5 seconds.\n");
            sleep(5);
        }        
    }
}

int removeContact(CONTACT **head, char *name)
{
    CONTACT *temp = *head;
    CONTACT *remove = NULL;
    int res = 0;

    if (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            temp = temp->next;
            free(*head);
            *head = temp;
            res = 1;
        }
        else 
        {
            while(temp->next != NULL && res != 1)
            {

                if (strcmp(temp->next->name, name) == 0)
                {
                    remove = temp->next; //1->2->56 .. 1->56
                    temp->next = remove->next;
                    free(remove);
                    remove = NULL;
                    res = 1;
                }
                else
                    temp = temp->next;
            }
        }
    }
    if (res == 0)
        res = -1;
    return res;
}