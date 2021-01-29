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

void saveTXT(CONTACT *contacts, char *fileName)
{
    FILE *file = openFile(fileName, "r+");
    
    int listSize = listSizeFinder(contacts);

    for(int i=0; i<listSize && strlen(contacts[i].name) > 0; i++)
    {
        fprintf(file, "NAME:%s|GENDER:%s|ADRESS:%s|NOTES:%s|\n", contacts[i].name, contacts[i].gender, contacts[i].adress, contacts[i].notes);
    }

    closeFile(file, fileName);
}

int sumContactsInFile(char *fileName)
{
    char frase[256];
    int linhas = 0;

    FILE *file = openFile(fileName, "r");

    while(fgets(frase, 256, file) != NULL)
        linhas++;

    return linhas;
}

void readTXT(CONTACT *contacts, char *fileName)
{
    FILE *file = openFile(fileName, "r");

    int i = 0;

    while(fscanf(file,"NAME:%[^|]|GENDER:%[^|]|ADRESS:%[^|]|NOTES:%[^|]|\n", contacts[i].name, contacts[i].gender, contacts[i].adress, contacts[i].notes) == 4)
    {
        i++;
    }

    closeFile(file, fileName);
}


CONTACT creatContact()
{
    CONTACT contact;

    printf("NAME: ");
    fgets(contact.name, 40, stdin);
    char *pos1 = strchr(contact.name,'\n');
    *pos1 = '\0';

    printf("GENDER: ");
    fgets(contact.gender, 40, stdin);
    char *pos2 = strchr(contact.gender,'\n');
    *pos2 = '\0';

    printf("ADRESS: ");
    fgets(contact.adress, 40, stdin);
    char *pos3 = strchr(contact.adress,'\n');
    *pos3 = '\0';

    printf("EXTRA NOTES: ");
    fgets(contact.notes, 200, stdin);
    char *pos4 = strchr(contact.notes,'\n');
    *pos4 = '\0';

    return contact;
}

int listSizeFinder(CONTACT *contactlist)
{
    int index=0, listSize;
    while(strlen(contactlist[index].name) != 0)
        index++;
    
    listSize = index;

    return listSize;
}

void addContactToList(CONTACT *contactList, int listSize)
{
    int addPos = listSize;
    CONTACT contact;

    contact = creatContact();

    strcpy(contactList[addPos].name, contact.name);
    strcpy(contactList[addPos].gender, contact.gender);
    strcpy(contactList[addPos].adress, contact.adress);
    strcpy(contactList[addPos].notes, contact.notes);
}

void printList(CONTACT *contactList)
{
    int index=0, listSize;

    listSize = listSizeFinder(contactList);

    for(index=0; index<listSize; index++)
    {
        linha();
        printf("%s\n", contactList[index].name);
        printf("%s\n", contactList[index].gender);
        printf("%s\n", contactList[index].adress);
        printf("%s\n", contactList[index].notes);
    }
}

void minuscula(char *original, char *final)
{
    int i;
    for(i=0; original[i] != '\0'; i++)
        final[i] = tolower(original[i]);
    final[i] = '\0';
}

int returnsPositionsToRemove(char *name, CONTACT *contacts)
{
    int i = 0, res = -1;
    char listName[40], nameToRemove[40];

    int listSize = listSizeFinder(contacts);
    

    while(i < listSize && strlen(contacts[i].name) > 0)
    {
        minuscula(contacts[i].name, listName);
        minuscula(name, nameToRemove);
        if(strcmp(listName, nameToRemove) == 0)
        {
            res = i;
            break;
        }
        i++;
    }
    return res;
}

int removeContact(char *name, CONTACT *contacts)
{
    int i, ret = 0;

    int listSize = listSizeFinder(contacts);

    i = returnsPositionsToRemove(name, contacts);

    if(i>=0)
    {
        while(i<listSize && strlen(contacts[i].name)>0)
        {
            contacts[i] = contacts[i+1];
            i++;
        }
        CONTACT contact = {};
        contacts[i] = contact;
        ret = 0;
    }
    else
    {
        ret = 1;
    }
    return ret;  
}

void removeContactIO(CONTACT *contacts)
{
    int option;
    char ContactName[40];
    char *pos;

    
    printf("Contact NAME to be removed: ");
    fgets(ContactName, 40, stdin);
    pos = strchr(ContactName, '\n');
    *pos = '\0';

    if(removeContact(ContactName, contacts) == 1)
        printf(" This contact doesn't exist.\n");
    else
        printf(" %s has been sucessfly removed.\n", ContactName); 
    printf("\n");
    limpaInput(); 
}
    