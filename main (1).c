//Documentation
/*
Name       : Shreya D N
student id : 26018_229
batch id   : 26018D
start Date : 08/09/2026
End Date   : 18/09/2026


Description : The following functions are implemented in the Address Book project to manage contact information.

createContact()      -> Adds a new contact to the address book by collecting name, phone number and email from the user.

searchContact        -> Searches for contacts using name, phone number or email and displays the matching contact details.

editContact()        -> Allows the user to modify the details of an existing contact after validation.

deleteContact()      -> Deletes a selected contact from the address book and reorganizes the remaining contacts.

listContacts()       -> Displays all contacts in a tabular format and sorts them based on the selected criteria.

initialize()         -> Initializes the address book and loads previously saved contacts from the file.

saveContactsToFile() -> Saves all contacts from the address book into a file for permanent storage.

loadContactsFromFile()-> Loads previously saved contacts from the file into the address book when the program starts.

*/


/*
Sample Output
Contacts loaded successfully

+-----------------------------------------------------------+
|                    ADDRESS BOOK                           |
+-----------------------------------------------------------+
|                                                           |
|    1.  ➕    Create Contact                               |
|    2.  🔍   Search Contact                                |
|    3.  ✏️    Edit Contact                                 |
|    4.  🗑️    Delete Contact                               |
|    5.  📋   List Contacts                                 |
|    6.  💾   Save & Exit                                   |
|                                                           |
+-----------------------------------------------------------+

Enter your choice : 1       
Enter Name: Shreya D N
Enter Phone Number: 7204305715
Enter Email: shre@gmail.com
Creating contact.................................................................................................... 100%
Contact created successfully



Enter your choice : 2

Search by:
1. Name
2. Phone number
3. Email
4. Exit
Enter your choice: 1
Enter name: shreya

Name  : shreya
Phone : 7204305716
Email : shreya@gmail.com

Name  : Shreya D N
Phone : 7204305715
Email : shre@gmail.com


Enter your choice : 6
Saving and Exiting.................................................. 100%
Contacts saved successfully

*/

#include <stdio.h>
#include<stdlib.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
        printf("\n");
        printf("+-----------------------------------------------------------+\n");
        printf("|                    ADDRESS BOOK                           |\n");
        printf("+-----------------------------------------------------------+\n");
        printf("|                                                           |\n");
        printf("|    1.  ➕   Create Contact                                |\n");
        printf("|    2.  🔍   Search Contact                                |\n");
        printf("|    3.  ✏️    Edit Contact                                  |\n");
        printf("|    4.  🗑️    Delete Contact                                |\n");
        printf("|    5.  📋   List Contacts                                 |\n");
        printf("|    6.  💾   Save & Exit                                   |\n");
        printf("|                                                           |\n");
        printf("+-----------------------------------------------------------+\n");
        printf("\nEnter your choice : ");

        if(scanf("%d", &choice) != 1)
        {
            printf("Invalid choice. Please enter a number from 1 to 6.\n");

            // Clear invalid input from input buffer
            while(getchar() != '\n');

            continue;
        }




        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);//calling function for create new contact
                break;
            case 2:
                searchContact(&addressBook);//calling function for search contact
                break;
            case 3:
                editContact(&addressBook);//calling function for edit contact
                break;
            case 4:
                deleteContact(&addressBook);//calling function for delete  contact
                break;
            case 5:
                printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);//calling function for list the contacts
                break;
            case 6:
                
                saveContactsToFile(&addressBook);//calling function for save contacts to file
                exit(EXIT_SUCCESS);
                
            default:
                printf("Invalid choice. Please enter a number from 1 to 6.\n");
        }
    }while (choice != 6);
    
    return 0;
}
