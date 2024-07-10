# TerminalContactManager
A contact manager written in C++ that runs in a terminal or command-line environment.

## Overview
Terminal Contact Manager is a contact manager that is run in a terminal. The program was written in entirely C++ and uses file management to store data.

## File Management
When the program is started, the user will be prompted to choose a file or create a new file. This accomodates the use of backing up or moving save files as necessary. Each file will require a unique name to be processed.

## Contact Management
After a file is selected, the program will enter the main menu where the user can choose to edit their data. From this menu the user can:
1. Display their contacts.
2. Edit a contact.
3. Create a new contact.
4. Delete an existing contact.
5. Select another file.
6. Create a new file.

## Stored Data
When creating or editing a contact, the user will be prompted to enter fields regarding the contact. These fields are comprised of the contact's:

* First Name
* Last Name
* Email
* Phone Number
* Company
* Position

Additionally, the manager will accept a Notes field that does not expect any specific data. This field is used to allow the user to enter any additional notes regarding the contact that they may find useful.
