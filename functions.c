#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void limpaInput()
{
    while (getchar() != '\n');
}

void linha()
{
    printf("____________________________________________\n");
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

void inicializeHead(CONTACT **contact)
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

void listContacts(CONTACT *head)
{

    CONTACT *temp = head;
    if (head == NULL)
        printf("Empty list.\n");
    
    else
    {
        while (temp != NULL)
        {
            linha();
            printf("%s\n", temp->name);
            printf("%s\n", temp->gender);
            printf("%s\n", temp->adress);
            printf("%s\n", temp->notes);

            temp = temp->next;
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