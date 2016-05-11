//-----------------------------------------------------------------------------------------
#include <afxwin.h>      //MFC core and standard components
#include <afxcmn.h>
#include "resource.h"    //main symbols
#include "ContactList.h"
//-----------------------------------------------------------------------------------------
//Globals
CEdit *txtFirstName;
CEdit *txtLastName;
CEdit *txtAddress;
CEdit *txtPhone;
CButton *btnSave;
CButton *btnDelete;
CButton *btnInsert;
CListCtrl *lstContacts;

ContactList *contactList;



class PhoneBookForm : public CDialog
{
    public:
    PhoneBookForm(CWnd* pParent = NULL): CDialog(PhoneBookForm::IDD, pParent)
    {    }
    // Dialog Data, name of dialog form
    enum{IDD = IDD_DIALOG1};
    protected:
    virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); }
    //Called right after constructor. Initialize things here.
    virtual BOOL OnInitDialog() 
    { 
            CDialog::OnInitDialog();
				
				//model manip
				contactList = new ContactList;
				contactList->load("data.txt");

			   //link controls
				txtFirstName = (CEdit*) GetDlgItem(IDC_FIRSTNAME);
				txtLastName = (CEdit*) GetDlgItem(IDC_LASTNAME);
				txtAddress = (CEdit*) GetDlgItem(IDC_ADDRESS);
				txtPhone = (CEdit*) GetDlgItem(IDC_PHONE);
				lstContacts = (CListCtrl*) GetDlgItem(IDC_LIST1);
				btnSave = (CButton*) GetDlgItem(IDC_SAVE);
				btnDelete = (CButton*) GetDlgItem(IDC_DELETE);
				btnInsert = (CButton*) GetDlgItem(IDC_INSERT);

				//list setup
				CRect rect;
				lstContacts->GetClientRect(&rect);
				int width = rect.Width();
				lstContacts->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
				lstContacts->InsertColumn(0,_T("Nume"),LVCFMT_LEFT,width,-1);
				reloadList();
				

            return true; 
    }

	void PhoneBookForm::reloadList() 
{
	vector<Contact*> *contacts = contactList->getContacts();
	int i;
	lstContacts->DeleteAllItems();
	for(i=(*contacts).size()-1;i>=0;i--) {
		CString fullName = (*contacts)[i]->getFirstName() + " " + (*contacts)[i]->getLastName();
		lstContacts->InsertItem(0,fullName);
	}
}

	void PhoneBookForm::newContact()
	{
	CString firstName, lastName, address, phone;
	Contact *tempContact = new Contact;

	txtFirstName->GetWindowText(firstName);
	txtLastName->GetWindowText(lastName);
	txtAddress->GetWindowText(address);
	txtPhone->GetWindowText(phone);

	tempContact->setFirstName(firstName);
	tempContact->setLastName(lastName);
	tempContact->setAddress(address);
	tempContact->setPhone(phone);
	contactList->addContact(tempContact);

	txtFirstName->SetWindowText("");
	txtLastName->SetWindowText("");
	txtAddress->SetWindowText("");
	txtPhone->SetWindowText("");
	}

	void PhoneBookForm::deleteContact() 
	{
		POSITION p = lstContacts->GetFirstSelectedItemPosition();
		int i = lstContacts->GetNextSelectedItem(p);

		contactList->removeContact(contactList->posToIterator(i));
	}
public:
DECLARE_MESSAGE_MAP()

afx_msg void OnBnClickedInsert();
afx_msg void OnLbnSelchangeList1();
afx_msg void OnBnClickedDelete();
afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
afx_msg void OnBnClickedSave();
};




//-----------------------------------------------------------------------------------------
class ContactsApp : public CWinApp
{
public:
ContactsApp() {  }
public:
virtual BOOL InitInstance()
    {
   CWinApp::InitInstance();
   SetRegistryKey(_T("PhoneBookApp"));

   //create form
   PhoneBookForm dlg;
   m_pMainWnd = &dlg;
   INT_PTR nResponse = dlg.DoModal();

   return FALSE;
} //close function
};
//-----------------------------------------------------------------------------------------
//Need a Message Map Macro for both CDialog and CWinApp
BEGIN_MESSAGE_MAP(PhoneBookForm, CDialog)
	
	ON_BN_CLICKED(IDC_INSERT, &PhoneBookForm::OnBnClickedInsert)
	ON_LBN_SELCHANGE(IDC_LIST1, &PhoneBookForm::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_DELETE, &PhoneBookForm::OnBnClickedDelete)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &PhoneBookForm::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_SAVE, &PhoneBookForm::OnBnClickedSave)
END_MESSAGE_MAP()
//-----------------------------------------------------------------------------------------
ContactsApp theApp;  //Starts the Application

void PhoneBookForm::OnBnClickedInsert()
{
	// TODO: Add your control notification handler code here
	newContact();
	contactList->save("data.txt");
	reloadList();

}




void PhoneBookForm::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void PhoneBookForm::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	deleteContact();
	txtFirstName->SetWindowText("");
	txtLastName->SetWindowText("");
	txtAddress->SetWindowText("");
	txtPhone->SetWindowText("");
	reloadList();
	contactList->save("data.txt");
}


void PhoneBookForm::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	BOOL selectedNow = pNMLV->uNewState & LVIS_SELECTED;
	BOOL selectedBefore = pNMLV->uOldState & LVIS_SELECTED;
	if (selectedNow && !selectedBefore) {
		int i = pNMLV->iItem;
		vector<Contact *> *contacts = contactList->getContacts();
		Contact *tempContact = (Contact *)(*contacts)[i];

		txtFirstName->SetWindowText(tempContact->getFirstName());
		txtLastName->SetWindowText(tempContact->getLastName());
		txtAddress->SetWindowText(tempContact->getAddress());
		txtPhone->SetWindowText(tempContact->getPhone());
	}
	*pResult = 0;
}


void PhoneBookForm::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here
	deleteContact();
	newContact();
	reloadList();
	contactList->save("data.txt");
}
