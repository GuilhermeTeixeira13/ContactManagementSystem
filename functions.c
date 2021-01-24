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

CONTACT creatContact()
{
    CONTACT contact;

    printf("NAME: ");
    fgets(contact.name, 20, stdin);
    //scanf("%[^\n]s", contact.name);
    //limpaInput();
    printf("GENDER: ");
    fgets(contact.gender, 15, stdin);
    //scanf("%[^\n]s", contact.gender);
    //limpaInput();
    printf("%s", contact.gender);
    printf("ADRESS: ");
    fgets(contact.adress, 25, stdin);
    //scanf("%[^\n]s", contact.adress);
    //limpaInput();
    printf("%s", contact.adress);
    printf("EXTRA NOTES: ");
    fgets(contact.notes, 200, stdin);
    //scanf("%[^\n]s", contact.notes);
    //limpaInput();

    return contact;
}

int listSizeFinder(CONTACT *contactlist)
{
    int index=0, listSize;
    while(strlen(contactlist[index].name) != 0)
        index++;
    
    listSize = index;

    printf("O tamanho da lista é %d\n", listSize);
    return listSize;
}

void addContactToList(CONTACT *contactList)
{
    int addPos, listSize;
    CONTACT contact;

    listSize = listSizeFinder(contactList);

    addPos = listSize;

    if(listSize != 1)
        contactList = (CONTACT*)realloc(contactList, (sizeof(CONTACT))*(listSize+1));
    
    contact = creatContact();

    strcpy(contactList[addPos].name, contact.name);
    strcpy(contactList[addPos].gender, contact.gender);
    printf("%s vai para %s!!", contact.gender, contactList[addPos].gender);
    strcpy(contactList[addPos].adress, contact.adress);
    strcpy(contactList[addPos].notes, contact.notes);
    printf("%s vai para %s!!", contact.notes, contactList[addPos].notes);
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