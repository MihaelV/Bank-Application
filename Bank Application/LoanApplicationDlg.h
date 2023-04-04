#pragma once
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"

// LoanApplicationDlg dialog

class LoanApplicationDlg : public CDialog
{
	DECLARE_DYNAMIC(LoanApplicationDlg)

public:
	LoanApplicationDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LoanApplicationDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_LOAN_APPLICATION_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	// FUNCTIONS
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedLaDlgSendRequestBtn();
	afx_msg void OnBnClickedLaDlgCancleBtn();
	afx_msg void OnBnClickedLaDlgResetBtn();
	afx_msg void ResetAllElements();
	afx_msg void OnBnClickedLaDlgRentHomeYes();
	afx_msg void OnBnClickedLaDlgRentHomeNo();

	// VALUES
	// VALUES
	CString DesiredLoanAmountInput;
	CString AnnualIncomeInput;
	CString LoanWillBeUsedFor;
	CString IsRentHome;
	CString MonthlyRentIncome;
	CString Name;
	CString Surname;
	CString UserNameDatabase, UserSurnameDatabase;


	bool isUserFound = false;
	int LoanWillBeUsed;
	int RentHomeYesNo;


	// CONTROLS
	CButton BusinessLaunchingControl;
	CButton HomeImprovementControl;
	CButton EducationControl;
	CButton HouseBuyingControl;
	CButton InvesmentControl;
	CButton OtherControl;
	CButton RentHomeYesControl;
	CButton RentHomeNoControl;

	CEdit DesiredLoanAmountInputControl;
	CEdit MonthlyRentInComeInputControl;
	CEdit AnnualIncomeInputControl;
	CEdit NameControl;
	CEdit SurnameControl;

	CStatic MonthlyRentIncomeTextControl;
	CStatic MonthlyRentIncomeEuroTextControl;

	// DATABASE
	CDatabase database;
	CString SqlString;
	CString	dbID, dbName, dbSurname;
	CString sDriver = L"Microsoft Access Driver (*.mdb, *.accdb)";
	CString sDsn;
	CString sFile = L"../Bank Application Database";
	
};
