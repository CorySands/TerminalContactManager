//============================================================================
// Name        : Contact.h
// Author      : Cory Sands
// Description : Declares all data members and methods for the Contact class
//============================================================================

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#ifndef CONTACT_H
#define CONTACT_H

class Contact {

private:

	// Data Members

	string id, firstName, lastName, email, phoneNumber, company, position,
			notes;

public:

	Contact(); // Constructor

	// Mutators
	void setID(string inID);
	void setFirstName(string inFirstName);
	void setLastName(string inLastName);
	void setEmail(string inEmail);
	void setPhoneNumber(string inPhoneNumber);
	void setCompany(string inCompany);
	void setPosition(string inPosition);
	void setNotes(string inNotes);

	// Accessors
	string getID();
	string getFirstName();
	string getLastName();
	string getEmail();
	string getPhoneNumber();
	string getCompany();
	string getPosition();
	string getNotes();

};

#endif
