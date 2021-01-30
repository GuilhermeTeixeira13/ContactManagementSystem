/**
 * @file      "functions.c"
 * @brief     This file contains all the functions needed to the correct behavior of the program.
 * @author    Guilherme Teixeira
 * @version   1.0.
*/

#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <unistd.h>

/**
 * This function just clears the buffer to avoid "garbage" in stdin.
*/
void cleanInput()
{
    while (getchar() != '\n');
}

/**
 * This function clears the terminal. With her, the appearance of the program looks clean.
*/
void cleanConsole()
{
    system("clear");
}

/**
 * This function helps in "front-end" stuff.
*/
void linha()
{
    printf("----------------------------------------------------------------\n");
}

/**
 * This function helps in "front-end" stuff. Appears when the user decides to leave the program.
*/
void leaving()
{
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
  	printf("┃ *\t\t>  THANKS FOR USING THIS PROGRAM  <          * ┃\n");
  	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

/**
 * This function helps in "front-end" stuff. Shows the available options that the user has.
*/
void intro()
{
    linha();
	printf("*\t\t    CONTACT MANAGEMENT SYSTEM                  *\n");
    linha();
    printf("\n1 - ADD CONTACT\n");
    printf("2 - DELETE CONTACT\n");
    printf("3 - SHOW CONTACTS\n");
    printf("\n0 - LEAVE\n");
	printf("\n↳ OPTION > ");
}

/**
 * Simple function that opens a file.
 * 
 * @param char *fname - Name of the file that we want to open.
 * @param char *mode - The mode that will be used when the file is opened.
 * 
 * @return a file of type FILE.
*/
FILE *openFile(char *fname, char *mode) 
{
    FILE *f = fopen(fname, mode);

    if (f == NULL)
    {
        fprintf(stderr, "Failed to open %s.\n", fname);
        exit(EXIT_FAILURE);
    }

    return f;
}

/**
 * Simple function that closes a file.
 * 
 * @param FILE *f - The file that we want to be closed.
 * @param char *fname - The name of the file that we want to be closed.

*/
void closeFile(FILE *f, char *fname)
{
    if (fclose(f) == EOF)
    {
        fprintf(stderr, "Failed to close %s.\n", fname);
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
        printf("  You will be redirected to the main page in about 5 seconds.\n"); 
        sleep(5);
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