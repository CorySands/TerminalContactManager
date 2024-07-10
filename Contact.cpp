//============================================================================
// Name        : Contact.cpp
// Author      : Cory Sands
// Description : Defines all methods for the Contact class
//============================================================================

#include "Contact.h"

#include <string>

// Constructor
Contact::Contact() {
}
;

// Mutators
void Contact::setID(string inID) {
	id = inID;
}

void Contact::setFirstName(string inFirstName) {
	firstName = inFirstName;
}

void Contact::setLastName(string inLastName) {
	lastName = inLastName;
}

void Contact::setEmail(string inEmail) {
	email = inEmail;
}

void Contact::setPhoneNumber(string inPhoneNumber) {
	phoneNumber = inPhoneNumber;
}

void Contact::setCompany(string inCompany) {
	company = inCompany;
}

void Contact::setPosition(string inPosition) {
	position = inPosition;
}

void Contact::setNotes(string inNotes) {
	notes = inNotes;
}

// Accessors

string Contact::getID() {
	return id;
}

string Contact::getFirstName() {
	return firstName;
}

string Contact::getLastName() {
	return lastName;
}

string Contact::getEmail() {
	return email;
}

string Contact::getPhoneNumber() {
	return phoneNumber;
}

string Contact::getCompany() {
	return company;
}

string Contact::getPosition() {
	return position;
}

string Contact::getNotes() {
	return notes;
}
