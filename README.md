# Address Book

A menu-driven **Address Book application developed in C** for managing contact information. The project demonstrates the use of structures, functions, arrays, strings, file handling, and input validation.

## Features

* Add new contacts
* Search contacts by name, phone number, or email
* Edit existing contacts
* Delete contacts
* Display all contacts
* Save contacts to a file
* Load contacts from a file
* Input validation for name, phone number, and email
* Prevent duplicate names, phone numbers, and email addresses
* Case-insensitive name and email search

## Technologies & Concepts Used

* **Language:** C
* Structures
* Functions
* Arrays
* Strings
* Pointers
* File handling
* String manipulation
* Input validation
* Modular programming
* Header files ('.h') and source files ('.c')

## Project Structure


Address-Book/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── populate.h
├── .gitignore
└── README.md


## How to Compile

Open a terminal inside the project folder and compile the source files using GCC:


gcc "main.c" contact.c file.c populate.c -o addressbook


## How to Run

./addressbook

The application provides a menu through which contacts can be created, searched, edited, deleted, and displayed.

## File Handling

The project uses file handling to store and retrieve contact information, allowing contacts to be preserved between program executions.

## Learning Outcome

Through this project, I gained practical experience in developing a modular C application and applying concepts such as structures, functions, pointers, strings, file handling, and validation in a real-world style project.

## Author

Shreya D N

B.E. Electronics and Communication Engineering
