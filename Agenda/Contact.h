#include<afx.h>
#include <atlstr.h>

class Contact
{
	CString firstName;
	CString lastName;
	CString address;
	CString phone;


public:
	Contact::Contact(CString newFirstName = CString(""), CString newLastName = CString(""), CString newAddress = CString(""), CString newPhone = CString(""));
	
	CString Contact::getFirstName();
	CString Contact::getLastName();
	CString Contact::getAddress();
	CString Contact::getPhone();

	void Contact::setFirstName(CString newFirstName);
	void Contact::setLastName(CString newLastName);
	void Contact::setAddress(CString newAddress);
	void Contact::setPhone(CString newPhone);

};

