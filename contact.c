#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// To validate the name
int validateName(char name[])
{
    int i;
    int count = 0;

    // Checks each character of the name
    for(i = 0; name[i] != '\0'; i++)
    {
        // Checks whether the character is an alphabet or space
        if(isalpha(name[i]) || name[i] == ' ')
        {
            count++;
        }
        else
        {
            printf("Name should contain only alphabets\n");
            return 0;
        }
    }

    // Checks whether the name contains at least 3 characters
    if(count < 3)
    {
        printf("Name must contain atleast 3 characters\n");
        return 0;
    }

    // Returns 1 when the name is valid
    return 1;
}

//To find name is unique
int isNameUnique(AddressBook *addressBook, char name[])
{
    int i, j;
    char temp1[50];
    char temp2[50];

    // Checks the entered name with all existing contact names
    for(i = 0; i < addressBook->contactCount; i++)
    {
        // Copies the existing name and entered name into temporary arrays
        strcpy(temp1, addressBook->contacts[i].name);
        strcpy(temp2, name);

        // Convert both names to lowercase
        for(j = 0; temp1[j] != '\0'; j++)
        {
            temp1[j] = tolower(temp1[j]);
        }

        for(j = 0; temp2[j] != '\0'; j++)
        {
            temp2[j] = tolower(temp2[j]);
        }

        // Checks whether both names are the same
        if(strcmp(temp1, temp2) == 0)
        {
            return 0;
        }
    }

    // Returns 1 when the name is unique
    return 1;
}



// To validate phone number
int validatePhone(char phone[])
{
    int i;

    // Check only digits
    for(i = 0; phone[i] != '\0'; i++)
    {
        if(isdigit(phone[i]) == 0)
        {
            printf("Only digits are allowed\n");
            return 0;
        }
    }

    // Check exactly 10 digits
    if(i != 10)
    {
        printf("Phone number must contain exactly 10 digits\n");
        return 0;
    }

    // Check first digit
    if(phone[0] < '6' || phone[0] > '9')
    {
        printf("First digit must be between 6 and 9\n");
        return 0;
    }

    // Returns 1 when the phone number is valid
    return 1;
}


// To check whether phone number is unique or not
int isPhoneUnique(AddressBook *addressBook, char phone[])
{
    int i;

    // Checks the entered phone number with all existing contacts
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 0;
        }
    }

    // Returns 1 when the phone number is unique
    return 1;
}
// To validate email
int validateEmail(char email[])
{
    int i;
    int at_Count = 0;
    int dot_Count = 0;
    int at_position = 0;
    int dot_position = 0;

    // Checks each character of the email
    for(i = 0; email[i] != '\0'; i++)
    {
    
        // Check uppercase letters
        if(email[i] >= 'A' && email[i] <= 'Z')
        {
            printf("Email should contain lowercase letters only\n");
            return 0;
        }

        // Check lowercase letters, digits, @ and .
        if(!((email[i] >= 'a' && email[i] <= 'z') ||
             (email[i] >= '0' && email[i] <= '9') ||
             email[i] == '@' || email[i] == '.'))
        {
            printf("Invalid symbol\n");
            return 0;
        }

        // Count @ and store its position
        if(email[i] == '@')
        {
            at_Count++;
            at_position = i;
        }

        // Count dot and store its position
        if(email[i] == '.')
        {
            dot_Count++;
            dot_position = i;
        }
    }

    // Exactly one @
    if(at_Count != 1)
    {
        printf("Email must contain exactly one @\n");
        return 0;
    }

    // Exactly one dot
    if(dot_Count != 1)
    {
        printf("Email must contain exactly one dot\n");
        return 0;
    }

    // Dot must be after @
    if(dot_position < at_position)
    {
        printf("Dot must appear after @\n");
        return 0;
    }

    // At least one character between @ and dot
    if(dot_position == at_position + 1)
    {
        printf("There must be a character between @ and dot\n");
        return 0;
    }

    // Nothing after .com
    if(strcmp(&email[dot_position], ".com") != 0)
    {
        printf("Email must end with .com\n");
        return 0;
    }

    // Returns 1 when the email is valid
    return 1;
}


// To check whether email is unique
int isEmailUnique(AddressBook *addressBook, char email[])
{
    int i;

    // Checks the entered email with all existing contacts
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
        {
            return 0;
        }
    }

    // Returns 1 when the email is unique
    return 1;
}

// To display and sort all contacts
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    int i, j;
    Contact temp;

    // Check whether address book is empty
    if(addressBook->contactCount == 0)
    {
        printf("Address book is empty\n");
        return;
    }

    // Sort contacts
    for(i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            // Sort by name
            if(sortCriteria == 1)
            {
                char name1[50];
                char name2[50];

                // Copy names into temporary arrays
                strcpy(name1, addressBook->contacts[j].name);
                strcpy(name2, addressBook->contacts[j + 1].name);

                // Convert both names to lowercase
                int k;

                for(k = 0; name1[k] != '\0'; k++)
                {
                    name1[k] = tolower(name1[k]);
                }

                for(k = 0; name2[k] != '\0'; k++)
                {
                    name2[k] = tolower(name2[k]);
                }

                // Compare names and swap contacts if required
                if(strcmp(name1, name2) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }

            // Sort by phone
            else if(sortCriteria == 2)
            {
                // Compare phone numbers and swap contacts if required
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j + 1].phone) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }

            // Sort by email
            else if(sortCriteria == 3)
            {
                // Compare email addresses and swap contacts if required
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j + 1].email) > 0)
                {
                    temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }
    }

    // Display contacts
    printf("============================Contact List====================================\n");
    printf("+--------------------------------------------------------------------------+\n");
    printf("| No.   Name                 Phone          Email                          |\n");
    printf("+--------------------------------------------------------------------------+\n");

    for(i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-5d %-20s %-14s %-30s |\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    printf("+--------------------------------------------------------------------------+\n");
    printf("| Total contacts: %d / %d                                                 |\n",addressBook->contactCount, MAX_CONTACTS);
    printf("+--------------------------------------------------------------------------+\n");
}




// To initialize the address book
void initialize(AddressBook *addressBook)
{
    // Initialize contact count to zero
    addressBook->contactCount = 0;

    // Load previously saved contacts from the file
    loadContactsFromFile(addressBook);
}



// To save contacts and exit the program
void saveAndExit(AddressBook *addressBook)
{
    // Save contacts to file
    saveContactsToFile(addressBook);

    // Exit the program successfully
    exit(EXIT_SUCCESS);
}




// To create a new contact
void createContact(AddressBook *addressBook)
{
    char temp_name[100];
    char temp_phone[20];
    char temp_email[50];
    int i,j;

    // Check whether address book is full
    if(addressBook->contactCount == MAX_CONTACTS)
    {
        printf("Address book is full\n");
        return;
    }

    // Name
    while(1)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", temp_name);

        // Check name length
        if(strlen(temp_name) > 50)
        {
            printf("Name should not exceed 50 characters\n");
            continue;
        }

        // Validate name
        if(validateName(temp_name))
        {
            // Check whether name is unique
            if(isNameUnique(addressBook, temp_name))
            {
                // Store the valid name in the current contact
                strcpy(addressBook->contacts[addressBook->contactCount].name,temp_name);
                break;
            }
            else
            {
                printf("Name already exists. Enter another name.\n");
            }
        }
        else
        {
            printf("Invalid name. Try again.\n");
        }
    }

    // Phone number
    while(1)
    {
        printf("Enter Phone Number: ");
        scanf(" %[^\n]", temp_phone);

        // Validate phone number first
        if(validatePhone(temp_phone))
        {
            // Check whether phone number is unique
            if(isPhoneUnique(addressBook, temp_phone))
            {
                // Store the valid phone number in the current contact
                strcpy(addressBook->contacts[addressBook->contactCount].phone,temp_phone);
                break;
            }
            else
            {
                printf("Phone number already exists. Enter another number.\n");
            }
        }
        else
        {
            printf("Invalid phone number. Try again.\n");
        }
    }

    // Email
    while(1)
    {
        printf("Enter Email: ");
        scanf(" %[^\n]", temp_email);

        // Validate email first
        if(validateEmail(temp_email))
        {
            // Check whether email is unique
            if(isEmailUnique(addressBook, temp_email))
            {
                // Store the valid email in the current contact
                strcpy(addressBook->contacts[addressBook->contactCount].email,temp_email);
                break;
            }
            else
            {
                printf("Email already exists. Enter another email.\n");
            }
        }
        else
        {
            printf("Invalid email. Try again.\n");
        }
    }

    // Increase contact count after successfully creating the contact
    addressBook->contactCount++;

    for(i = 1; i <= 100; i++)
    {
        int dots = i / 2;

        // Clear the previous progress line and move to the beginning
        printf("\r\033[KCreating contact");

        // Display dots according to the progress
        for(j = 0; j < dots; j++)
        {
            printf(".");
        }

        // Display the current percentage
        printf(" %d%%", i);

        // Immediately display the updated progress
        fflush(stdout);

        // Add a small delay to show the progress
        usleep(30000);
    }

    // Display successful creation message
    printf("\nContact created successfully\n");

}

// To search for a contact
void searchContact(AddressBook *addressBook)
{
    int choice, i;
    char search[50];
    char temp[50];
    int found = 0;

    // Display search options
    printf("\nSearch by:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Select the search method
    switch(choice)
    {
        case 1:
            printf("Enter name: ");
            scanf(" %[^\n]", search);

            // Convert search name to lowercase
            for(i = 0; search[i] != '\0'; i++)
            {
                search[i] = tolower(search[i]);
            }
            break;

        case 2:
            printf("Enter phone number: ");
            scanf(" %[^\n]", search);
            break;

        case 3:
            printf("Enter Email: ");
            scanf(" %[^\n]", search);

            // Convert search email to lowercase
            for(i = 0; search[i] != '\0'; i++)
            {
                search[i] = tolower(search[i]);
            }
            break;

        case 4:
            // Exit from search operation
            printf("Exiting search...\n");
            return;

        default:
            // Handle invalid search choice
            printf("Enter valid choice\n");
            return;
    }

    // Check all contacts for a matching record
    for(i = 0; i < addressBook->contactCount; i++)
    {
        // Search by name
        if(choice == 1)
        {
            // Copy stored name into a temporary array
            strcpy(temp, addressBook->contacts[i].name);

            // Convert stored name to lowercase
            int j;
            for(j = 0; temp[j] != '\0'; j++)
            {
                temp[j] = tolower(temp[j]);
            }

            // Perform partial and case-insensitive name search
            if(strstr(temp, search) != NULL)
            {
                // Display the matching contact
                printf("\nName  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);

                // Mark that a contact was found
                found = 1;
            }
        }

        // Search by phone number
        else if(choice == 2)
        {
            // Perform exact phone number search
            if(strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                // Display the matching contact
                printf("\nName  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);

                // Mark that a contact was found
                found = 1;
            }
        }

        // Search by email
        else if(choice == 3)
        {
            // Copy stored email into a temporary array
            strcpy(temp, addressBook->contacts[i].email);

            // Convert stored email to lowercase
            int j;
            for(j = 0; temp[j] != '\0'; j++)
            {
                temp[j] = tolower(temp[j]);
            }

            // Perform partial and case-insensitive email search
            if(strstr(temp, search) != NULL)
            {
                // Display the matching contact
                printf("\nName  : %s\n", addressBook->contacts[i].name);
                printf("Phone : %s\n", addressBook->contacts[i].phone);
                printf("Email : %s\n", addressBook->contacts[i].email);

                // Mark that a contact was found
                found = 1;
            }
        }
    }

    // Display message when no contact matches the search
    if(found == 0)
    {
        printf("No contacts found\n");
    }
}



// To edit an existing contact
void editContact(AddressBook *addressBook)
{
    int searchChoice;
    int i,j;
    int matches[MAX_CONTACTS];
    int matchCount = 0;
    int selected;
    char search[50];

    // Search contact to edit
    printf("\nSearch contact by:\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);

    // Select the search method
    switch(searchChoice)
    {
        case 1:
            printf("Enter name: ");
            scanf(" %[^\n]", search);
            break;

        case 2:
            printf("Enter phone number: ");
            scanf(" %[^\n]", search);
            break;

        case 3:
            printf("Enter email: ");
            scanf(" %[^\n]", search);
            break;

        case 4:
            // Exit from edit operation
            return;

        default:
            // Handle invalid search choice
            printf("Enter valid choice\n");
            return;
    }

    // Convert search string to lowercase for case-insensitive search
    for(int j = 0; search[j] != '\0'; j++)
    {
        search[j] = tolower(search[j]);
    }

    // Find all contacts matching the search
    for(i = 0; i < addressBook->contactCount; i++)
    {
        // Search by name
        if(searchChoice == 1)
        {
            char temp[50];

            // Copy the contact name into a temporary array
            strcpy(temp, addressBook->contacts[i].name);

            // Convert the contact name to lowercase
            for(int j = 0; temp[j] != '\0'; j++)
            {
                temp[j] = tolower(temp[j]);
            }

            // Check whether the search text is present in the name
            if(strstr(temp, search) != NULL)
            {
                // Store the index of the matching contact
                matches[matchCount] = i;
                matchCount++;
            }
        }

        // Search by phone number
        else if(searchChoice == 2)
        {
            // Check whether the search number is present in the phone number
            if(strstr(addressBook->contacts[i].phone, search) != NULL)
            {
                // Store the index of the matching contact
                matches[matchCount] = i;
                matchCount++;
            }
        }

        // Search by email
        else if(searchChoice == 3)
        {
            char temp[50];

            // Copy the contact email into a temporary array
            strcpy(temp, addressBook->contacts[i].email);

            // Convert the contact email to lowercase
            for(j = 0; temp[j] != '\0'; j++)
            {
                temp[j] = tolower(temp[j]);
            }

            // Check whether the search text is present in the email
            if(strstr(temp, search) != NULL)
            {
                // Store the index of the matching contact
                matches[matchCount] = i;
                matchCount++;
            }
        }
    }

    // Check whether any matching contact was found
    if(matchCount == 0)
    {
        printf("No contacts found\n");
        return;
    }

    // Display matching contacts when more than one contact is found
    if(matchCount > 1)
    {
        printf("\nMatching contacts:\n");

        // Display all matching contacts
        for(i = 0; i < matchCount; i++)
        {
            printf("\n%d.\n", i + 1);
            printf("Name  : %s\n", addressBook->contacts[matches[i]].name);
            printf("Phone : %s\n", addressBook->contacts[matches[i]].phone);
            printf("Email : %s\n", addressBook->contacts[matches[i]].email);
        }

        // Ask the user to select one contact
        printf("\nSelect contact to edit: ");
        scanf("%d", &selected);

        // Check whether the selected number is valid
        if(selected < 1 || selected > matchCount)
        {
            printf("Invalid choice\n");
            return;
        }

        // Get the actual index of the selected contact
        selected = matches[selected - 1];
    }
    else
    {
        // Select the only matching contact
        selected = matches[0];
    }

    // Display the current contact details
    printf("\nCurrent contact details:\n");
    printf("Name  : %s\n", addressBook->contacts[selected].name);
    printf("Phone : %s\n", addressBook->contacts[selected].phone);
    printf("Email : %s\n", addressBook->contacts[selected].email);

    // Display edit options
    int editChoice;
    printf("\nEdit:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. All\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &editChoice);

    // Edit the contact according to the selected field
    switch(editChoice)
    {
        case 1:
        {
            char tempName[50];

            while(1)
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", tempName);

                // Validate the new name
                if(validateName(tempName) == 0)
                {
                    printf("Invalid name\n");
                    continue;
                }

                int duplicate = 0;

                // Check whether the new name already exists
                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(i == selected)
                    {
                        continue;
                    }

                    if(strcmp(addressBook->contacts[i].name, tempName) == 0)
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if(duplicate == 1)
                {
                    printf("Name already exists\n");
                    continue;
                }

                strcpy(addressBook->contacts[selected].name, tempName);
                printf("Contact updated successfully\n");
                break;
            }
        break;
        }


        case 2:
        {
            char tempPhone[20];

            while(1)
            {
                printf("Enter new phone number: ");
                scanf(" %[^\n]", tempPhone);

                // Validate the new phone number
                if(validatePhone(tempPhone) == 0)
                {
                    printf("Invalid phone number\n");
                    continue;
                }

                int duplicate = 0;

                // Check whether the new phone number already exists
                for(i = 0; i < addressBook->contactCount; i++)
                {
                    if(i == selected)
                    {
                        continue;
                    }

                    if(strcmp(addressBook->contacts[i].phone, tempPhone) == 0)
                    {
                        duplicate = 1;
                        break;
                    }
                }

                if(duplicate == 1)
                {
                    printf("Phone number already exists\n");
                    continue;
                }

                strcpy(addressBook->contacts[selected].phone, tempPhone);
                printf("Contact updated successfully\n");
                break;
            }
            break;
        }


    case 3:
    {
        char tempEmail[50];

        while(1)
        {
            printf("Enter new email: ");
            scanf(" %[^\n]", tempEmail);

            // Validate the new email
            if(validateEmail(tempEmail) == 0)
            {
                printf("Invalid email\n");
                continue;
            }

            int duplicate = 0;

            // Check whether the new email already exists
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(i == selected)
                {
                    continue;
                }

                if(strcmp(addressBook->contacts[i].email, tempEmail) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }

            if(duplicate == 1)
            {
                printf("Email already exists\n");
                continue;
            }

            strcpy(addressBook->contacts[selected].email, tempEmail);
            printf("Contact updated successfully\n");
            break;
        }
        break;
    }


    case 4:
    {
        char tempName[50];
        char tempPhone[20];
        char tempEmail[50];

        // Name
        while(1)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", tempName);

            if(validateName(tempName) == 0)
            {
                printf("Invalid name\n");
                continue;
            }

            int duplicate = 0;

            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(i == selected)
                {
                    continue;
                }

                if(strcmp(addressBook->contacts[i].name, tempName) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }

            if(duplicate == 1)
            {
                printf("Name already exists\n");
                continue;
            }

            break;
        }

        // Phone
        while(1)
        {
            printf("Enter new phone number: ");
            scanf(" %[^\n]", tempPhone);

            if(validatePhone(tempPhone) == 0)
            {
                printf("Invalid phone number\n");
                continue;
            }

            int duplicate = 0;

            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(i == selected)
                {
                    continue;
                }

                if(strcmp(addressBook->contacts[i].phone, tempPhone) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }

            if(duplicate == 1)
            {
                printf("Phone number already exists\n");
                continue;
            }

            break;
        }

        // Email
        while(1)
        {
            printf("Enter new email: ");
            scanf(" %[^\n]", tempEmail);

            if(validateEmail(tempEmail) == 0)
            {
                printf("Invalid email\n");
                continue;
            }

            int duplicate = 0;

            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(i == selected)
                {
                    continue;
                }

                if(strcmp(addressBook->contacts[i].email, tempEmail) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }

            if(duplicate == 1)
            {
                printf("Email already exists\n");
                continue;
            }

            break;
        }

        // Update all fields
        strcpy(addressBook->contacts[selected].name, tempName);
        strcpy(addressBook->contacts[selected].phone, tempPhone);
        strcpy(addressBook->contacts[selected].email, tempEmail);

        printf("Contact updated successfully\n");
        break;
    }


    case 5:
        // Exit without making any changes
        return;

    default:
        // Handle invalid edit choice
        printf("Enter valid choice\n");
        return;

    }
}

// To delete a contact from the address book
void deleteContact(AddressBook *addressBook)
{
    int choice;
    int i, j;
    int matchCount = 0;
    int matches[MAX_CONTACTS];
    int selected;
    char search[50];
    char temp[50];
    char confirm[10];

    // Check whether address book is empty
    if(addressBook->contactCount == 0)
    {
        printf("No contacts to delete\n");
        return;
    }

    // Display delete search options
    printf("\nDelete Contact\n");
    printf("1. Search by name\n");
    printf("2. Search by phone\n");
    printf("3. Search by email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Search for the contact based on the selected option
    switch(choice)
    {
        case 1:
            printf("Enter name: ");
            scanf(" %[^\n]", search);

            // Convert search name to lowercase
            for(i = 0; search[i] != '\0'; i++)
            {
                search[i] = tolower(search[i]);
            }

            // Find matching contacts by name
            for(i = 0; i < addressBook->contactCount; i++)
            {
                strcpy(temp, addressBook->contacts[i].name);

                // Convert stored name to lowercase
                for(j = 0; temp[j] != '\0'; j++)
                {
                    temp[j] = tolower(temp[j]);
                }

                // Store the index of matching contact
                if(strstr(temp, search) != NULL)
                {
                    matches[matchCount] = i;
                    matchCount++;
                }
            }
            break;

        case 2:
            printf("Enter phone: ");
            scanf(" %[^\n]", search);

            // Find matching contacts by phone
            for(i = 0; i < addressBook->contactCount; i++)
            {
                if(strstr(addressBook->contacts[i].phone, search) != NULL)
                {
                    matches[matchCount] = i;
                    matchCount++;
                }
            }
            break;

        case 3:
            printf("Enter email: ");
            scanf(" %[^\n]", search);

            // Convert search email to lowercase
            for(i = 0; search[i] != '\0'; i++)
            {
                search[i] = tolower(search[i]);
            }

            // Find matching contacts by email
            for(i = 0; i < addressBook->contactCount; i++)
            {
                strcpy(temp, addressBook->contacts[i].email);

                // Convert stored email to lowercase
                for(j = 0; temp[j] != '\0'; j++)
                {
                    temp[j] = tolower(temp[j]);
                }

                // Store the index of matching contact
                if(strstr(temp, search) != NULL)
                {
                    matches[matchCount] = i;
                    matchCount++;
                }
            }
            break;

        case 4:
            return;

        default:
            printf("Invalid choice\n");
            return;
    }

    // Check whether any contact was found
    if(matchCount == 0)
    {
        printf("No contacts found\n");
        return;
    }

    // Display matching contacts when multiple contacts are found
    if(matchCount > 1)
    {
        printf("\nMatching contacts:\n");

        for(i = 0; i < matchCount; i++)
        {
            selected = matches[i];

            printf("\n%d. %s\n", i + 1,addressBook->contacts[selected].name);

            printf("   Phone : %s\n",addressBook->contacts[selected].phone);

            printf("   Email : %s\n",addressBook->contacts[selected].email);
        }

        // Ask the user to select a contact
        printf("\nSelect contact to delete: ");
        scanf("%d", &selected);

        // Check whether the selected number is valid
        if(selected < 1 || selected > matchCount)
        {
            printf("Invalid selection\n");
            return;
        }

        // Get the actual contact index
        selected = matches[selected - 1];
    }
    else
    {
        // Select the contact when only one match is found
        selected = matches[0];
    }

    // Display the selected contact details
    printf("\nContact found:\n");
    printf("Name  : %s\n", addressBook->contacts[selected].name);
    printf("Phone : %s\n", addressBook->contacts[selected].phone);
    printf("Email : %s\n", addressBook->contacts[selected].email);

    // Ask for confirmation before deleting
    printf("\nDelete %s? (yes/no): ",addressBook->contacts[selected].name);
    scanf("%9s", confirm);

    // Delete the contact if user confirms
    if(strcmp(confirm, "yes") == 0 || strcmp(confirm, "YES") == 0)
    {
        // Shift remaining contacts one position to the left
        for(i = selected; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        // Decrease the contact count
        addressBook->contactCount--;

        printf("Contact deleted successfully\n");
    }
    else
    {
        // Cancel deletion if user does not confirm
        printf("Deletion cancelled\n");
    }
}