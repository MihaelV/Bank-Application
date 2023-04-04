#include "afxdialogex.h"
#include "AddUserDlg.h"
#include "resource.h"

// AddUserDlg dialog

IMPLEMENT_DYNAMIC(AddUserDlg, CDialog)

AddUserDlg::AddUserDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(ID_ADD_USER_DLG, pParent)
	, Name(_T(""))
	, Surname(_T(""))
	, Age(_T(""))
	, Country(_T(""))
	, City(_T(""))
	, Street(_T(""))
	, HouseNumber(_T(""))
	, Job(_T(""))
	, PhoneNumber(_T(""))
	, HousePhoneNumber(_T(""))
	, Email(_T(""))
	, GenderMaleFemale(0)
	, DriverLicenceYesNo(1)
	, MarriedYesNo(1)
	, ChildrenYesNo(1)
	, HousePhoneNumberYesNo(1)
	, NumberOfChildren(_T(""))
{

}

AddUserDlg::~AddUserDlg()
{
}

void AddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, ID_AU_DLG_NAME, Name);
	DDV_MaxChars(pDX, Name, 15);
	DDX_Text(pDX, ID_AU_DLG_SURNAME, Surname);
	DDV_MaxChars(pDX, Surname, 15);
	DDX_Text(pDX, ID_AU_DLG_AGE, Age);
	DDV_MaxChars(pDX, Age, 3);
	DDX_Text(pDX, ID_AU_DLG_COUNTRY, Country);
	DDV_MaxChars(pDX, Country, 15);
	DDX_Text(pDX, ID_AU_DLG_CITY, City);
	DDV_MaxChars(pDX, City, 15);
	DDX_Text(pDX, ID_AU_DLG_STREET, Street);
	DDV_MaxChars(pDX, Street, 20);
	DDX_Text(pDX, ID_AU_DLG_HOUSE_NUMBER, HouseNumber);
	DDV_MaxChars(pDX, HouseNumber, 5);
	DDX_Text(pDX, ID_AU_DLG_JOB, Job);
	DDV_MaxChars(pDX, Job, 20);
	DDX_Text(pDX, ID_AU_DLG_PHONE_NUMBER, PhoneNumber);
	DDV_MaxChars(pDX, PhoneNumber, 15);
	DDX_Text(pDX, ID_AU_DLG_HOUSE_PHONE_NUMBER, HousePhoneNumber);
	DDV_MaxChars(pDX, HousePhoneNumber, 15);
	DDX_Text(pDX, ID_AU_DLG_EMAIL_ADDRESS, Email);
	DDV_MaxChars(pDX, Email, 40);
	DDX_Control(pDX, ID_AU_DLG_MALE, MaleControl);
	DDX_Radio(pDX, ID_AU_DLG_MALE, GenderMaleFemale);
	DDX_Radio(pDX, ID_AU_DLG_DRIVE_LICENCE_YES, DriverLicenceYesNo);
	DDX_Radio(pDX, ID_AU_DLG_MARRIED_YES, MarriedYesNo);
	DDX_Radio(pDX, ID_AU_DLG_CHILDREN_YES, ChildrenYesNo);
	DDX_Radio(pDX, ID_AU_DLG_HOUSE_PHONE_NUMBER_YES, HousePhoneNumberYesNo);
	DDX_Control(pDX, ID_AU_DLG_HOUSE_PHONE_NUMBER, HousePhoneNumberControl);
	DDX_Control(pDX, ID_AU_DLG_HOUSE_PHONE_NUMBER_NO, HousePhoneNumberControlNo);
	DDX_Control(pDX, ID_AU_DLG_HOUSE_PHONE_NUMBER_YES, HousePhoneNumberControlYes);
	DDX_Control(pDX, ID_AU_DLG_FEMALE, FemaleControl);
	DDX_Control(pDX, ID_AU_DLG_DRIVE_LICENCE_YES, DriverLicenceYesControl);
	DDX_Control(pDX, ID_AU_DLG_DRIVE_LICENCE_NO, DriverLicenceNoControl);
	DDX_Control(pDX, ID_AU_DLG_MARRIED_YES, MarriedYesControl);
	DDX_Control(pDX, ID_AU_DLG_MARRIED_NO, MarriedNoControl);
	DDX_Control(pDX, ID_AU_DLG_CHILDREN_YES, ChildrenYesControl);
	DDX_Control(pDX, ID_AU_DLG_CHILDREN_NO, ChildrenNoControl);
	DDX_Text(pDX, IDC_EDIT1, NumberOfChildren);
	DDV_MaxChars(pDX, NumberOfChildren, 2);
	DDX_Control(pDX, IDC_EDIT1, NumberOfChildrenControl);
	DDX_Control(pDX, ID_AU_DLG_DATE_OF_BIRTH, DateOfBirthControl);
	DDX_Control(pDX, ID_HOW_MANY_CHILDREN_TEXT, HowManyChildrenTextControl);
	DDX_Control(pDX, ID_AU_DLG_NAME, NameControler);
	DDX_Control(pDX, ID_AU_DLG_SURNAME, SurnameControl);
	DDX_Control(pDX, ID_AU_DLG_AGE, AgeControler);
	DDX_Control(pDX, ID_AU_DLG_COUNTRY, CountryControler);
	DDX_Control(pDX, ID_AU_DLG_CITY, CityControler);
	DDX_Control(pDX, ID_AU_DLG_STREET, StreetControler);
	DDX_Control(pDX, ID_AU_DLG_HOUSE_NUMBER, HouseNumberControler);
	DDX_Control(pDX, ID_AU_DLG_JOB, JobControler);
	DDX_Control(pDX, ID_AU_DLG_PHONE_NUMBER, PhoneNumberControler);
	DDX_Control(pDX, ID_AU_DLG_EMAIL_ADDRESS, EmailControler);
}


BEGIN_MESSAGE_MAP(AddUserDlg, CDialog)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(ID_AU_DLG_ADD_BTN, &AddUserDlg::OnBnClickedAuDlgAddBtn)
	ON_BN_CLICKED(ID_AU_DLG_CANCLE, &AddUserDlg::OnBnClickedAuDlgCancle)
	ON_BN_CLICKED(ID_AU_DLG_HOUSE_PHONE_NUMBER_YES, &AddUserDlg::OnBnClickedAuDlgHousePhoneNumberYes)
	ON_BN_CLICKED(ID_AU_DLG_HOUSE_PHONE_NUMBER_NO, &AddUserDlg::OnBnClickedAuDlgHousePhoneNumberNo)
	ON_BN_CLICKED(ID_AU_DLG_CHILDREN_YES, &AddUserDlg::OnBnClickedAuDlgChildrenYes)
	ON_BN_CLICKED(ID_AU_DLG_CHILDREN_NO, &AddUserDlg::OnBnClickedAuDlgChildrenNo)
	ON_BN_CLICKED(ID_AU_DLG_RESET_BTN, &AddUserDlg::OnBnClickedAuDlgResetBtn)
END_MESSAGE_MAP()


// AddUserDlg message handlers

int AddUserDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	sDsn.Format(L"ODBC;DRIVER={%s};DBQ=%s;", sDriver, sFile);

	return 0;
}

void AddUserDlg::OnClose()
{
	if (AfxMessageBox(CString("Are you sure you want Exit"), MB_YESNO) == IDYES) { ResetAllElements(); CDialog::OnClose(); };
	
}

void AddUserDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
}

// ************ BUTTONS ************
void AddUserDlg::OnBnClickedAuDlgAddBtn()
{
	if (AfxMessageBox(CString("Add User"), MB_YESNO) == IDYES) {
		UpdateData(TRUE);

		// DATE OF BIRTH
		DateOfBirthControl.GetTime(DateOfBirthCTime);
		DateOfBirth.Format(L"%d/%d/%d", DateOfBirthCTime.GetMonth(), DateOfBirthCTime.GetDay(), DateOfBirthCTime.GetYear());

		if (GenderMaleFemale){Gender = "Female";}
		else {Gender = "Male";}
		if (DriverLicenceYesNo){ HasDriverLicence = "No";}
		else { HasDriverLicence = "Yes";}
		if (MarriedYesNo) { IsMarried = "No"; }
		else { IsMarried = "Yes"; }
		if (ChildrenYesNo) { HasChildren = "No"; }
		else { HasChildren = "Yes"; }
		if (HousePhoneNumberYesNo) { HasHousePhoneNumber = "No"; }
		else { HasHousePhoneNumber = "Yes"; }
		
		TRY{
			database.Open(NULL,false,false, sDsn);
			
			SqlString.Format(L"INSERT INTO Users (Name,Surname,Age,Gender,Country,City,Street,HouseNumber,DateOfBirth,Job,PhoneNumber,HasHousePhoneNumber,HousePhoneNumber,DriverLicence,EmailAddress,Married,Children,NumberOfChildren) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",Name,Surname,Age,Gender,Country,City,Street,HouseNumber,DateOfBirth,Job,PhoneNumber, HasHousePhoneNumber,HousePhoneNumber, HasDriverLicence,Email, IsMarried, HasChildren, NumberOfChildren);
			database.ExecuteSQL(SqlString);

			database.Close();

		}CATCH(CDBException, e) {
			AfxMessageBox(L"Database error: " + e->m_strError);
			database.Close();
		}
		END_CATCH;
		
		
		ResetAllElements();
		OnCancel();
	};
}

void AddUserDlg::OnBnClickedAuDlgCancle()
{
	if (AfxMessageBox(CString("Are you sure you want Exit"), MB_YESNO) == IDYES) { ResetAllElements();OnCancel();};
}

void AddUserDlg::OnBnClickedAuDlgResetBtn()
{
	ResetAllElements();
}

void AddUserDlg::OnBnClickedAuDlgHousePhoneNumberYes()
{
	HousePhoneNumberControl.EnableWindow(1);
}

void AddUserDlg::OnBnClickedAuDlgHousePhoneNumberNo()
{
	HousePhoneNumberControl.SetWindowTextW(CString(""));
	HousePhoneNumberControl.EnableWindow(0);
}


void AddUserDlg::OnBnClickedAuDlgChildrenYes()
{
	HowManyChildrenTextControl.EnableWindow(1);
	NumberOfChildrenControl.EnableWindow(1);
}


void AddUserDlg::OnBnClickedAuDlgChildrenNo()
{
	HowManyChildrenTextControl.EnableWindow(0);
	NumberOfChildrenControl.SetWindowTextW(CString(""));
	NumberOfChildrenControl.EnableWindow(0);
}


void AddUserDlg::ResetAllElements() {
	NameControler.SetWindowTextW(CString(""));
	SurnameControl.SetWindowTextW(CString(""));
	AgeControler.SetWindowTextW(CString(""));
	CountryControler.SetWindowTextW(CString(""));
	CityControler.SetWindowTextW(CString(""));
	StreetControler.SetWindowTextW(CString(""));
	HouseNumberControler.SetWindowTextW(CString(""));
	JobControler.SetWindowTextW(CString(""));
	PhoneNumberControler.SetWindowTextW(CString(""));
	HousePhoneNumberControl.SetWindowTextW(CString(""));
	EmailControler.SetWindowTextW(CString(""));
	NumberOfChildrenControl.SetWindowTextW(CString(""));

	HousePhoneNumberControl.EnableWindow(0);
	HowManyChildrenTextControl.EnableWindow(0);
	NumberOfChildrenControl.EnableWindow(0);
	
	MaleControl.SetCheck(1);
	FemaleControl.SetCheck(0);
	HousePhoneNumberControlNo.SetCheck(1);
	HousePhoneNumberControlYes.SetCheck(0);
	DriverLicenceYesControl.SetCheck(0);
	DriverLicenceNoControl.SetCheck(1);
	MarriedYesControl.SetCheck(0);
	MarriedNoControl.SetCheck(1);
	ChildrenYesControl.SetCheck(0);
	ChildrenNoControl.SetCheck(1);
	UpdateData(1);
}