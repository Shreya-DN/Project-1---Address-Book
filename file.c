#include <stdio.h>
#include <unistd.h>
#include "file.h"

//Saves all contacts from the address book into a file for permanent storage.
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    int i,j,dots;
    // Opens the contacts file in write mode
    fp = fopen("contacts.txt", "w");


    // Checks whether the file was opened successfully
    if(fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    // Writes each contact into the file
    for(i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    // Closes the file after saving
    fclose(fp);
    for(i = 1; i <= 100; i++)// Displays saving progress from 1% to 100%
    {
        dots = i / 2;

        printf("\rSaving and Exiting");

        for(int j = 0; j < dots; j++)// Displays dots according to the progress
        {
            printf(".");
        }

        printf(" %d%%", i);

        fflush(stdout);

        usleep(30000);
    }

    printf("\n");

    printf("Contacts saved successfully\n");
}


//Loads previously saved contacts from the file into the address book.
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("contacts.txt", "r");

    addressBook->contactCount = 0;// Initializes the contact count

    if(fp == NULL)// If the file does not exist, return to the program
    {
        return;
    }

    
    // Reads contact details from the file
    while(fscanf(fp, "%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;// Increments the contact count after reading a contact

        if(addressBook->contactCount == MAX_CONTACTS)// Stops reading when the address book reaches maximum capacity
        {
            break;
        }
    }

    fclose(fp);// Closes the file after loading

    printf("Contacts loaded successfully\n");
}