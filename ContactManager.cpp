//============================================================================
// Name        : ContactManager.h
// Author      : Cory Sands
// Description : Manages contacts in files
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Contact.h"
using namespace std;

string fileDirectory = "files/";
string currentFile;
vector<Contact> contacts;

// Gets contact data from file and stores each listing in the 'contacts' vector
void readFile() {
	contacts.clear(); // Removes all elements from contacts

	// Accesses data from file
	ifstream file;
	string line;
	file.open(currentFile);

	if (file.is_open()) {
		int currentLine = 0;

		// Checks each line of file
		while (getline(file, line)) {
			currentLine++;

			// If the current line contains "id" then creates contact in 'contacts' vector. Otherwise, if the line contains another field, the field data will be stored in the last created contact.
			if (line.find("id", 0) != string::npos) {
				contacts.push_back(Contact());
				contacts.back().setID(line.erase(0, 3));
			} else if (line.find("first_name", 0) != string::npos) {
				contacts.back().setFirstName(line.erase(0, 11));
			} else if (line.find("last_name", 0) != string::npos) {
				contacts.back().setLastName(line.erase(0, 10));
			} else if (line.find("email", 0) != string::npos) {
				contacts.back().setEmail(line.erase(0, 6));
			} else if (line.find("phone_number", 0) != string::npos) {
				contacts.back().setPhoneNumber(line.erase(0, 13));
			} else if (line.find("company", 0) != string::npos) {
				contacts.back().setCompany(line.erase(0, 8));
			} else if (line.find("position", 0) != string::npos) {
				contacts.back().setPosition(line.erase(0, 9));
			} else if (line.find("notes", 0) != string::npos) {
				contacts.back().setNotes(line.erase(0, 6));
			}

		}
	}

	file.close(); // Closes file
}

// Locates last contact id in file
int findLatestID() {

// Determine the last line with "id"
	ifstream file;
	string line;
	string latestLineWithID;
	string search = "id";
	file.open(currentFile);

	if (file.is_open()) {
		int currentLine = 0;
		while (getline(file, line)) {
			currentLine++;
			if (line.find(search, 0) != string::npos) {
				latestLineWithID = line;
			}
		}
	}
	file.close();

// Remove spaces from latestLineWithID
	latestLineWithID.erase(
			remove(latestLineWithID.begin(), latestLineWithID.end(), ' '),
			latestLineWithID.end());

// Get id value from line
	string id = latestLineWithID.erase(0, 3);

// Determine if id contains only digits
	bool allowConversion = true;
	for (char letter : id) {
		if (!isdigit(letter)) {
			cout << "\nError: ID is not in the correct format\n";
			allowConversion = false;
		}
	}

// If id contains only digits, then convert id to an integer and return it
	if (allowConversion && id.length() > 0) {
		return stoi(id);
	} else {
		return 0;
	}

}

// Displays all contacts in file
void displayContacts() {
	for (Contact contact : contacts) {
		cout << "\n\nContact " << contact.getID()
				<< "\n----------------------------\nFirst Name: "
				<< contact.getFirstName() << "\nLast Name: "
				<< contact.getLastName() << "\nEmail: " << contact.getEmail()
				<< "\nPhone Number: " << contact.getPhoneNumber()
				<< "\nCompany: " << contact.getCompany() << "\nPosition: "
				<< contact.getPosition() << "\nNotes: " << contact.getNotes();
	}

	cout << endl << endl;
}

// Deletes selected contact
void deleteContact() {

	// If there are zero contacts, the function will end
	if (contacts.size() == 0) {
		cout << "\n\nThe current files has 0 contacts\n\n";
		return;
	}

	// Prompts user to select contact
	cout << "\n\nPlease select a contact";

	// Lists each contact with name and id
	int x = 1;
	for (Contact contact : contacts) {

		cout << "\n(" << x << ") " << contact.getFirstName() << " "
				<< contact.getLastName() << " [id: " << contact.getID() << "]";

		x++;
	}
	cout << "\n\n(1-" << contacts.size() << "): ";

	// Ensures user enters a valid value
	string contactSelection;
	do {
		cin >> contactSelection;

		if (!isdigit(contactSelection[0]) || contactSelection.length() != 1) {
			continue;
		}
	} while (stoi(contactSelection) < 1
			|| stoi(contactSelection) > contacts.size());

	// converts user input to vector index
	int contactIndex = stoi(contactSelection) - 1;

	cout
			<< "\n\nAre you sure you want to delete this contact (y = yes / n = no): ";

	// Ensures user enters valid value
	string selection;
	do {
		cin >> selection;
	} while (selection != "y" && selection != "n");

	if (selection == "n") {
		return;
	}

	// Creates a vector containing file contents
	ifstream fileRead;
	string line;
	fileRead.open(currentFile);

	vector<string> fileContent;
	while (getline(fileRead, line)) {
		fileContent.push_back(line);
	}

	fileRead.close(); // Closes file

	// Removes specified contact from vector
	for (int x = 0; x < fileContent.size(); x++) {

		// Checks if the current line contains the correct contact id. If it does, then deletes the next 9 lines
		if (fileContent[x].find("id:" + contacts[contactIndex].getID())
				!= string::npos) {

			// Erases lines pertaining to selected contact
			fileContent.erase(fileContent.begin() + x,
					fileContent.begin() + x + 9);

			// Overwrites file with altered vector
			ofstream fileWrite;
			fileWrite.open(currentFile);

			for (const std::string &line : fileContent) {
				fileWrite << line << '\n';
			}

			fileWrite.close(); // Closes file
			cout << "\n\n\n";

			return; // Exits function
		}
	}

}

// Changes contact field based on user input and stores result in file
void editContact() {

// If there are zero contacts, the function will end
	if (contacts.size() == 0) {
		cout << "\n\nThe current files has 0 contacts\n\n";
		return;
	}

// Prompts user to select contact
	cout << "\n\nPlease select a contact";

// Lists each contact with name and id
	int x = 1;
	for (Contact contact : contacts) {

		cout << "\n(" << x << ") " << contact.getFirstName() << " "
				<< contact.getLastName() << " [id: " << contact.getID() << "]";

		x++;
	}
	cout << "\n\n(1-" << contacts.size() << "): ";

// Ensures user enters a valid value
	string contactSelection;
	do {
		cin >> contactSelection;

		if (!isdigit(contactSelection[0]) || contactSelection.length() != 1) {
			continue;
		}
	} while (stoi(contactSelection) < 1
			|| stoi(contactSelection) > contacts.size());

// converts user input to vector index
	int contactIndex = stoi(contactSelection) - 1;

// Displays list of fields
	cout << "\n\nContact " << contacts[contactIndex].getID()

	<< "\n----------------------------\n(1) First Name: "
			<< contacts[contactIndex].getFirstName() << "\n(2) Last Name: "
			<< contacts[contactIndex].getLastName() << "\n(3) Email: "
			<< contacts[contactIndex].getEmail() << "\n(4) Phone Number: "
			<< contacts[contactIndex].getPhoneNumber() << "\n(5) Company: "
			<< contacts[contactIndex].getCompany() << "\n(6) Position: "
			<< contacts[contactIndex].getPosition() << "\n(7) Notes: "
			<< contacts[contactIndex].getNotes()
			<< "\n\nPlease select a value to edit (1-7): ";

// Ensures user enters a valid value
	string fieldSelection;
	do {
		cin >> fieldSelection;

		if (!isdigit(fieldSelection[0]) || fieldSelection.length() != 1) {
			continue;
		}
	} while (stoi(fieldSelection) < 1 || stoi(fieldSelection) > 7);

// List of field names. This is used when entering in a value to the file.
	string fieldNames[7] = { "first_name", "last_name", "email", "phone_number",
			"company", "position", "notes" };

// Prompts user to enter value for selected field
	cout << "\n\nPlease enter a value for "
			<< fieldNames[stoi(fieldSelection) - 1] << ": ";
	string newValue;

// Receives user input
	cin >> newValue;

// Creates a vector containing file contents
	ifstream fileRead;
	string line;
	fileRead.open(currentFile);

	vector<string> fileContent;
	while (getline(fileRead, line)) {
		fileContent.push_back(line);
	}

	fileRead.close(); // Closes file

// Replaces line with user value
	bool foundCorrectID = false;
	for (int x = 0; x < fileContent.size(); x++) {

		// Checks if the current line contains the correct contact id. If it does, then changes foundCorrectID to true.
		if (fileContent[x].find("id:" + contacts[contactIndex].getID())
				!= string::npos) {
			foundCorrectID = true;
		}

		// Checks if the current line contains the specified field and if the correct id has been found.
		else if (fileContent[x].find(fieldNames[stoi(fieldSelection) - 1] + ":")
				!= string::npos && foundCorrectID) {

			// Replaces value in line
			fileContent[x] = fieldNames[stoi(fieldSelection) - 1] + ":"
					+ newValue;
			break;
		}
	}

// Overwrites file with altered vector
	ofstream fileWrite;
	fileWrite.open(currentFile);

	for (const std::string &line : fileContent) {
		fileWrite << line << '\n';
	}

	fileWrite.close(); // Closes file

	cout << "\n\n\n";

}

void createContact() {

	string id, firstName, lastName, email, phoneNumber, company, position,
			notes; // Initialize contact field variables

	id = to_string(findLatestID() + 1);

	cout << endl << endl << endl;

// Prompt user for field input
	cout << "Enter Contact Information (id: " << id
			<< ")\n----------------------------\nFirst Name: ";
	cin >> firstName;
	cout << "\nLast Name: ";
	cin >> lastName;
	cout << "\nEmail: ";
	cin >> email;
	cout << "\nPhone Number: ";
	cin >> phoneNumber;
	cout << "\nCompany: ";
	cin >> company;
	cout << "\nPosition: ";
	cin >> position;
	cout << "\nNotes: ";
	cin >> notes;

	fstream file(currentFile,
			std::fstream::in | std::fstream::out | std::fstream::app);
	if (file.is_open()) {
		file << "\nid:" << id << "\nfirst_name:" << firstName << "\nlast_name:"
				<< lastName << "\nemail:" << email << "\nphone_number:"
				<< phoneNumber << "\ncompany:" << company << "\nposition:"
				<< position << "\nnotes:" << notes << "\n";
	}
	file.close(); // Closes file
}

// Either selects file or creates file based on user input
void selectFile() {

	// Prompts user to decide whether to select or create file
	cout
			<< "\nPlease select a file or create a new file\n(1 = select file / 2 = create file): ";
	string selection;

	// Ensures input is valid
	do {
		cin >> selection;
	} while (selection != "1" && selection != "2");

	bool fileFound = false;

	// Repeats prompts until either a file is selected or created successfully
	do {

		// Prompts user to create file
		if (selection == "2") {

			// Prompts user to enter file name
			cout
					<< "\nPlease enter a new file name\nfile name (do not include .contact): ";

			// Gets user input
			cin >> selection;

			// Creates file
			ofstream file(fileDirectory + selection + ".contact");
			currentFile = fileDirectory + selection + ".contact";
			fileFound = true;
		}

		// Prompts user to select file
		else {

			// Prompts user to enter file name
			cout
					<< "\nPlease enter the name of an existing file\nfile name (do not include .contact): ";

			// Gets user input
			cin >> selection;

			// Ensures file exists
			ifstream file;
			file.open(fileDirectory + selection + ".contact");
			if (file) {
				file.close(); // Closes file
				currentFile = fileDirectory + selection + ".contact";
				fileFound = true;
			} else {
				cout << "\n\nError: file does not exist\n\n";
			}
		}

	} while (fileFound == false);
}

int main() {

	// Creates the 'files' directory if it does not already exist
	system("if not exist \"files\" mkdir files");

	// Prompts user to select or create file
	selectFile();

	// Loops main menu
	while (true) {

		// Gets data from file
		readFile();

		// Determines if 'contact' should be plural or not
		string contactPlurality =
				(contacts.size() == 1) ? " contact)" : " contacts)";

		// Displays main menu
		cout << "\n\n     Contact Manager    (" << contacts.size()
				<< contactPlurality;
		cout
				<< "\n-------------------------\n(1) Display contacts\n(2) Edit contact\n(3) Create contact\n(4) Delete contact\n(5) Select or Create a file\n(6) Exit\nPlease select an option (1-6): ";

		// Gets user input
		string selection;

		// Ensures input is valid
		do {
			cin >> selection;
			if (selection.length() != 1 || !isdigit(selection[0])) {
				continue;
			}
		} while (stoi(selection) > 6 || stoi(selection) < 1);

		// Determines what function to call based on user input
		switch (selection[0]) {
		case '1':
			displayContacts();
			break;
		case '2':
			editContact();
			break;
		case '3':
			createContact();
			break;
		case '4':
			deleteContact();
			break;
		case '5':
			selectFile();
			break;
		case '6':
			exit(0);
			break;
		}

	}
	return 0;
}
