#include "ContactList.h"
#include <fstream>


ContactList::ContactList(void)
{
}

vector<Contact*>* ContactList::getContacts() 
{
	return &contacts;
}

vector<Contact*>::iterator ContactList::posToIterator(int pos)
{
	vector<Contact*>::iterator i = contacts.begin();
	while(pos--) {
		i++;
	}
	return i;
}

void ContactList::addContact(Contact *newContact) 
{
	contacts.push_back(newContact);
}

void ContactList::clearAll() 
{
	contacts.clear();
}

void ContactList::removeContact(vector<Contact*>::iterator i)
{
	contacts.erase(i);
}

void ContactList::save(CString path) 
{
	static int nr = 0;
	static fstream f;

	if (!f.is_open()) {
		f.open(path, ios::out);
		nr = 0;
	}

	for (i=contacts.begin();i != contacts.end();++i) {
		f<< (*i)->getFirstName() << "|";
		f<< (*i)->getLastName() << "|";
		f<< (*i)->getAddress() << "|";
		f<< (*i)->getPhone();
		f<<endl;
		nr++;
	}
	f.close();
}

void ContactList::load(CString path) 
{
	static fstream f;
	static int nr = 0;
	char ln[256], *p, *tok, str[255];
	bool loadOk = true;
	Contact *cmpTmp;
	CString firstName, lastName, address, phone;

	if(!f.is_open()) {
		f.open(path, ios::in);
		f.seekg(0);
		nr = 0;
	}

	ContactList::clearAll();
	while (!f.eof()) {
		f.getline(ln,255);
		try {
			p = strtok_s(ln,"|",&tok);
			if(!p) {
				throw("Reading error: firstName");
			} else {
				firstName = CString(p);
			}

			p = strtok_s(NULL,"|",&tok);
			if(!p) {
				throw("Reading error: lastName");
			} else {
				lastName = CString(p);
			}

			p = strtok_s(NULL,"|",&tok);
			if(!p) {
				throw("Reading error: address");
			} else {
				address = CString(p);
			}

			p = strtok_s(NULL,"|",&tok);
			if(!p) {
				throw("Reading error: phone");
			} else {
				phone = CString(p);
			}	
		}
		catch (char *err) {
			loadOk = false;
			break;
		}

		if(loadOk) {
			nr++;
			addContact(new Contact(firstName, lastName, address, phone));
		}
	}

	f.close();
}

