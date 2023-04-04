#include "afxdialogex.h"
#include "LoanApplicationDlg.h"
#include "resource.h"
#include "odbcinst.h"
#include "afxdb.h"


// LoanApplicationDlg dialog

IMPLEMENT_DYNAMIC(LoanApplicationDlg, CDialog)

LoanApplicationDlg::LoanApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(ID_LOAN_APPLICATION_DLG, pParent)
	, LoanWillBeUsed(0)
	, RentHomeYesNo(1)
	, DesiredLoanAmountInput(_T(""))
	, AnnualIncomeInput(_T(""))
	, MonthlyRentIncome(_T(""))
	, Name(_T(""))
	, Surname(_T(""))
{

}

LoanApplicationDlg::~LoanApplicationDlg()
{
}

void LoanApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_LA_DLG_BUSINESS_LAUNCHING, BusinessLaunchingControl);
	DDX_Control(pDX, ID_LA_DLG_HOME_IMPROVEMENT, HomeImprovementControl);
	DDX_Control(pDX, ID_LA_DLG_EDUCATION, EducationControl);
	DDX_Control(pDX, ID_LA_DLG_HOUSE_BUYING, HouseBuyingControl);
	DDX_Control(pDX, ID_LA_DLG_INVESTMENT, InvesmentControl);
	DDX_Control(pDX, OTHER, OtherControl);
	DDX_Control(pDX, ID_LA_DLG_RENT_HOME_YES, RentHomeYesControl);
	DDX_Control(pDX, ID_LA_DLG_RENT_HOME_NO, RentHomeNoControl);
	DDX_Control(pDX, ID_LA_DLG_MONTHLY_RENT_INCOME_TEXT, MonthlyRentIncomeTextControl);
	DDX_Control(pDX, ID_LA_DLG_MONTHLY_RENT_INCOME_VALUE, MonthlyRentInComeInputControl);
	DDX_Control(pDX, ID_LA_DLG_MONTHLY_RENT_INCOME_EURO_TEXT, MonthlyRentIncomeEuroTextControl);
	DDX_Control(pDX, ID_LA_DLG_ANNUAL_INCOME, AnnualIncomeInputControl);
	DDX_Control(pDX, ID_LA_DLG_DESIRED_LOAN_AMOUNT_INPUT, DesiredLoanAmountInputControl);
	DDX_Radio(pDX, ID_LA_DLG_BUSINESS_LAUNCHING, LoanWillBeUsed);
	DDX_Radio(pDX, ID_LA_DLG_RENT_HOME_YES, RentHomeYesNo);
	DDX_Text(pDX, ID_LA_DLG_DESIRED_LOAN_AMOUNT_INPUT, DesiredLoanAmountInput);
	DDV_MaxChars(pDX, DesiredLoanAmountInput, 10);
	DDX_Text(pDX, ID_LA_DLG_ANNUAL_INCOME, AnnualIncomeInput);
	DDV_MaxChars(pDX, AnnualIncomeInput, 10);
	DDX_Text(pDX, ID_LA_DLG_MONTHLY_RENT_INCOME_VALUE, MonthlyRentIncome);
	DDV_MaxChars(pDX, MonthlyRentIncome, 10);
	DDX_Control(pDX, ID_LA_DLG_NAME_INPUT, NameControl);
	DDX_Control(pDX, ID_LA_DLG_SURNAME_INPUT, SurnameControl);
	DDX_Text(pDX, ID_LA_DLG_NAME_INPUT, Name);
	DDV_MaxChars(pDX, Name, 30);
	DDX_Text(pDX, ID_LA_DLG_SURNAME_INPUT, Surname);
	DDV_MaxChars(pDX, Surname, 30);
}


BEGIN_MESSAGE_MAP(LoanApplicationDlg, CDialog)
	ON_WM_ACTIVATE()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_BN_CLICKED(ID_LA_DLG_SEND_REQUEST_BTN, &LoanApplicationDlg::OnBnClickedLaDlgSendRequestBtn)
	ON_BN_CLICKED(ID_LA_DLG_CANCLE_BTN, &LoanApplicationDlg::OnBnClickedLaDlgCancleBtn)
	ON_BN_CLICKED(ID_LA_DLG_RESET_BTN, &LoanApplicationDlg::OnBnClickedLaDlgResetBtn)
	ON_BN_CLICKED(ID_LA_DLG_RENT_HOME_YES, &LoanApplicationDlg::OnBnClickedLaDlgRentHomeYes)
	ON_BN_CLICKED(ID_LA_DLG_RENT_HOME_NO, &LoanApplicationDlg::OnBnClickedLaDlgRentHomeNo)
END_MESSAGE_MAP()



void LoanApplicationDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

}


void LoanApplicationDlg::OnClose()
{
	if (AfxMessageBox(CString("Are you sure you want Exit"), MB_YESNO) == IDYES) {
		ResetAllElements();
		CDialog::OnClose();
	}
	
}


int LoanApplicationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	sDsn.Format(L"ODBC;DRIVER={%s};DBQ=%s;", sDriver, sFile);

	return 0;
}

//   ************** BUTTONS **************

void LoanApplicationDlg::OnBnClickedLaDlgSendRequestBtn()
{
	if (AfxMessageBox(CString("Send Request"), MB_YESNO) == IDYES) { 
		UpdateData(TRUE);

		// IF USER EXIT IN DATABASE SET isUserFound = true
		TRY{

		database.Open(NULL,false,false, sDsn);

		CRecordset recset(&database);
	
		SqlString.Format(L"SELECT * FROM Users");
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) {
			recset.GetFieldValue(CString("Name"), UserNameDatabase);
			recset.GetFieldValue(CString("Surname"), UserSurnameDatabase);

			if (UserNameDatabase == Name && UserSurnameDatabase == Surname)
			{
				isUserFound = true;
				break;
			}
			else { recset.MoveNext(); }
		}
		database.Close();

		}CATCH(CDBException, e) {
			AfxMessageBox(L"Database error: " + e->m_strError);
			isUserFound = false;
			database.Close();
		}
		END_CATCH;



		if (isUserFound)
		{

			switch (LoanWillBeUsed)
			{
			case 0:
				LoanWillBeUsedFor = "Business Launching";
				break;
			case 1:
				LoanWillBeUsedFor = "Home Improvement";
				break;
			case 2:
				LoanWillBeUsedFor = "Education";
				break;
			case 3:
				LoanWillBeUsedFor = "House Buying";
				break;
			case 4:
				LoanWillBeUsedFor = "Invesment";
				break;
			case 5:
				LoanWillBeUsedFor = "Other";
				break;
			}

			if (RentHomeYesNo) { IsRentHome = "No"; }
			else { IsRentHome = "Yes"; }

			TRY{
				database.Open(NULL,false,false, sDsn);

				SqlString.Format(L"INSERT INTO LoanApplication (DesiredLoanAmount,AnnualIncome,LoanWillBeUseFor,RentHome,MonthlyRentIncome,Name,Surname) VALUES ('%s','%s','%s','%s','%s','%s','%s')", DesiredLoanAmountInput, AnnualIncomeInput, LoanWillBeUsedFor, IsRentHome, MonthlyRentIncome, Name, Surname);
				database.ExecuteSQL(SqlString);

				database.Close();

			}CATCH(CDBException, e) {
				AfxMessageBox(L"Database error: " + e->m_strError);
				database.Close();
			}
			END_CATCH;

			isUserFound = 0;
			ResetAllElements();
			OnCancel();

		}
		else {AfxMessageBox(CString("User has not Found"));}

	}
}

void LoanApplicationDlg::OnBnClickedLaDlgCancleBtn()
{
	if (AfxMessageBox(CString("Are you sure you want Exit"), MB_YESNO) == IDYES) {
		ResetAllElements();
		OnCancel();
	}
	
}

void LoanApplicationDlg::OnBnClickedLaDlgResetBtn()
{
	ResetAllElements();
}

void LoanApplicationDlg::ResetAllElements() {
	BusinessLaunchingControl.SetCheck(1);
	HomeImprovementControl.SetCheck(0);
	EducationControl.SetCheck(0);
	HouseBuyingControl.SetCheck(0);
	InvesmentControl.SetCheck(0);
	OtherControl.SetCheck(0);

	RentHomeYesControl.SetCheck(0);
	RentHomeNoControl.SetCheck(1);
	
	DesiredLoanAmountInputControl.SetWindowTextW(CString(""));
	MonthlyRentInComeInputControl.SetWindowTextW(CString(""));
	MonthlyRentInComeInputControl.EnableWindow(0);
	AnnualIncomeInputControl.SetWindowTextW(CString(""));
	NameControl.SetWindowText(_T(""));
	SurnameControl.SetWindowText(_T(""));

	MonthlyRentIncomeTextControl.EnableWindow(0);
	MonthlyRentIncomeEuroTextControl.EnableWindow(0);
	UpdateData(1);
}

void LoanApplicationDlg::OnBnClickedLaDlgRentHomeYes()
{
	MonthlyRentIncomeTextControl.EnableWindow(1);
	MonthlyRentInComeInputControl.EnableWindow(1);
	MonthlyRentIncomeEuroTextControl.EnableWindow(1);
}


void LoanApplicationDlg::OnBnClickedLaDlgRentHomeNo()
{
	MonthlyRentIncomeTextControl.EnableWindow(0);
	MonthlyRentInComeInputControl.EnableWindow(0);
	MonthlyRentInComeInputControl.SetWindowTextW(CString(""));
	MonthlyRentIncomeEuroTextControl.EnableWindow(0);
}