
#include "Contact.h"

Contact::Contact(CString newFirstName, CString newLastName, CString newAddress, CString newPhone)
{
	firstName = CString(newFirstName);
	lastName = CString(newLastName);
	address = CString(newAddress);
	phone = CString(newPhone);
}

CString Contact::getFirstName() 
{
	return firstName;
}

CString Contact::getLastName()
{
	return lastName;
}

CString Contact::getAddress()
{
	return address;
}

CString Contact::getPhone()
{
	return phone;
}

void Contact::setFirstName(CString newFirstName) 
{
	firstName = newFirstName;
}

void Contact::setLastName(CString newLastName)
{
	lastName = newLastName;
}

void Contact::setAddress(CString newAddress)
{
	address = newAddress;
}

void Contact::setPhone(CString newPhone)
{
	phone = newPhone;
}


