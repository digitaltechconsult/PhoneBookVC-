using namespace std;

#include "Contact.h"
#include<cstring>
#include<vector>


class ContactList
{

protected:
	vector<Contact*> contacts;
	vector<Contact*>::iterator i;

public:
	ContactList(void);
	vector<Contact*>* getContacts();
	vector<Contact*>::iterator posToIterator(int);
	void load(CString);
	void save(CString);

	void addContact(Contact *);
	void clearAll();
	void removeContact(vector<Contact*>::iterator);
};

