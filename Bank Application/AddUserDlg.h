#include "afxdialogex.h"
#include "afxdtctl.h"
#include "odbcinst.h"
#include "afxdb.h"

// AddUserDlg dialog

class AddUserDlg : public CDialog
{
	DECLARE_DYNAMIC(AddUserDlg)

public:
	AddUserDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddUserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_ADD_USER_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// FUNCTIONS
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnBnClickedAuDlgAddBtn();
	afx_msg void OnBnClickedAuDlgCancle();
	afx_msg void OnBnClickedAuDlgResetBtn();
	afx_msg void OnBnClickedAuDlgHousePhoneNumberYes();
	afx_msg void OnBnClickedAuDlgHousePhoneNumberNo();
	afx_msg void OnBnClickedAuDlgChildrenYes();
	afx_msg void OnBnClickedAuDlgChildrenNo();
	afx_msg void ResetAllElements();

	// VALUES
	CString Name;
	CString Surname;
	CString Age;
	CString Gender;
	CString Country;
	CString City;
	CString Street;
	CString HouseNumber;
	CString DateOfBirth;
	CString Job;
	CString PhoneNumber;
	CString HasHousePhoneNumber;
	CString HousePhoneNumber;
	CString HasDriverLicence;
	CString Email;
	CString IsMarried;
	CString HasChildren;
	CString NumberOfChildren;

	int GenderMaleFemale;
	int DriverLicenceYesNo;
	int MarriedYesNo;
	int ChildrenYesNo;
	int HousePhoneNumberYesNo;

	// CONTROLERS
	CEdit NameControler;
	CEdit SurnameControl;
	CEdit AgeControler;
	CEdit CountryControler;
	CEdit CityControler;
	CEdit StreetControler;
	CEdit HouseNumberControler;
	CEdit JobControler;
	CEdit PhoneNumberControler;
	CEdit HousePhoneNumberControl;
	CEdit EmailControler;
	CEdit NumberOfChildrenControl;

	CButton MaleControl;
	CButton FemaleControl;
	CButton HousePhoneNumberControlNo;
	CButton HousePhoneNumberControlYes;
	CButton DriverLicenceYesControl;
	CButton DriverLicenceNoControl;
	CButton MarriedYesControl;
	CButton MarriedNoControl;
	CButton ChildrenYesControl;
	CButton ChildrenNoControl;
	
	CStatic HowManyChildrenTextControl;

	CDateTimeCtrl DateOfBirthControl;
	CTime DateOfBirthCTime;

	// DATABASE
	CDatabase database;
	CString SqlString;
	CString	dbID, dbName, dbSurname;
	CString sDriver = L"Microsoft Access Driver (*.mdb, *.accdb)";
	CString sDsn;
	CString sFile = L"../Bank Application Database";
};