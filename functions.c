#include<stdio.h>
#include"functions.h"
#include<stdlib.h>
#include<string.h>

void limpaInput()
{
    while (getchar() != '\n');
}

void linha()
{
    printf("____________________________________________\n");
}

FILE *abreFicheiro(char *fnome, char *modo) 
{
    FILE *f = fopen(fnome, modo);

    if (f == NULL)
    {
        fprintf(stderr, "Falhou abertura de %s.\n", fnome);
        exit(EXIT_FAILURE);
    }

    return f;
}

void fechaFicheiro(FILE *f, char *fnome)
{
    if (fclose(f) == EOF)
    {
        fprintf(stderr, "Falhou o fecho de %s.\n", fnome);
        exit(EXIT_FAILURE);
    }
}

void gravaTXT(CONTACT *contacts, char *fileName)
{
    FILE *file = abreFicheiro(fileName, "w");

    for(int i=0; strlen(contacts[i].name) != 0; i++)
    {
        fprintf(file, "NAME:%sGENDER:%sADRESS:%sNOTES:%s\n", contacts[i].name, contacts[i].gender, contacts[i].adress, contacts[i].notes);
    }

    fechaFicheiro(file, fileName);
}

/*void leTXT(CONTACT *contacts, char *fileName)
{

}/*


CONTACT creatContact()
{
    CONTACT contact;

    printf("NAME: ");
    fgets(contact.name, 40, stdin);
    printf("GENDER: ");
    fgets(contact.gender, 40, stdin);
    printf("%s", contact.gender);
    printf("ADRESS: ");
    fgets(contact.adress, 40, stdin);
    printf("%s", contact.adress);
    printf("EXTRA NOTES: ");
    fgets(contact.notes, 200, stdin);

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
        printf("%s", contactList[index].name);
        printf("%s", contactList[index].gender);
        printf("%s", contactList[index].adress);
        printf("%s", contactList[index].notes);
    }
}