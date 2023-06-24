#include <afxwin.h>
#include "resource.h"
#include "AddUserDlg.h"
#include "LoanApplicationDlg.h"
#include "odbcinst.h"
#include "afxdb.h"

class MyFrameWnd : public CFrameWnd
{
public:
	MyFrameWnd() {

		CString WndClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW, AfxGetApp()->LoadStandardCursor(IDC_ARROW),
			(HBRUSH)::CreateSolidBrush(RGB(240, 248, 255)));
		

		Create(WndClass, L"Bank",WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZE, rectDefault,NULL, NULL);
	}
	DECLARE_MESSAGE_MAP()

	// FUNCTIONS
	void CreateElements();

	// DISPLAY SHOW FUNCTIONS
	void ChangeDisplayDraw(int ReceivedDisplay);
	void LogInPageDisplay();
	void MainPageDisplay();
	void UserDisplay();

	// DISPLAY CLEAR FUNCITONS
	void LogInPageDisplayClear();
	void MainPageDisplayClear();
	void UserDisplayClear();

	// AFX_MSG Functions

	// WINDOWS MESSAGES
	afx_msg int PreCreateWindow(CREATESTRUCT& cs);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	// BUTTONS FUNCTIONS
	afx_msg void OnLogInButtonClicked();
	afx_msg void OnLogOutButtonClicked();
	afx_msg void OnAddUserButtonClicked();
	afx_msg void OnSearchButtonClicked();
	afx_msg void OnLoanApplicationButtonClicked();
	afx_msg void OnUserButtonDeleteClicked();
	afx_msg void OnUserButtonExitClicked();
	afx_msg void OnUserButtonIncreaseMoneyClicked();
	afx_msg void OnUserButtonDecreaseMoneyClicked();

	// INPUT FUNCTIONS
	afx_msg void OnSearchInputChange();

private:
	CButton LoginButton, AddUserButton, SearchButton,FindUser,LogOutButton;
	CButton UserDeleteButton, UserExitButton, UserIncreaseMoneyButton, UserDecreaseMoneyButton;
	CEdit UserInputIncreaseMoney, UserInputDecreaseMoney;
	CEdit NameInput, SurnameInput, PasswordInput, SearchUserInput;
	AddUserDlg AddUserDlg;
	LoanApplicationDlg LoanApplicationDlg;
	CString LogInName, LogInSurname, LogInPassword, LogInNameDatabase, LogInSurnameDatabase, LogInPasswordDatabase;
	CString SearchInputNameSurname,UserName, UserSurname;
	CString UserNameDatabase, UserSurnameDatabase, UserAgeDatabase, UserGenderDatabase, UserCountryDatabase,
		UserCityDatabase, UserStreetDatabase, UserHouseNumberDatabase, UserDateOfBirthDatabase, UserJobDatabase,
		UserPhoneNumberDatabase, UserHasHousePhoneNumberDatabase, UserHousePhoneNumberDatabase, UserDriverLicenceDatabase,
		UserEmailAddressDatabase, UserMarriedDatabase, UserChildrenDatabase, UserNumberOfChildrenDatabase, UserAmountOfMoneyDatabase;
	CString UserDeleteMessageBoxText;
	CString UserAmountOfMoney;

	int Display = ID_DISPLAY_LOGIN;
	int PositionCounterOfUserslist = 0;

	bool isLoginTrue = false;
	bool isSpaceFind = false;
	bool isUserFind = false;

	// DATABASE
	CDatabase database;
	CString SqlString;
	CString	dbID, dbName, dbSurname;
	CString sDriver = L"Microsoft Access Driver (*.mdb, *.accdb)";
	CString sDsn;
	CString sFile = L"../Bank Application Database";
};

BEGIN_MESSAGE_MAP(MyFrameWnd, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCLBUTTONDOWN()
	ON_EN_CHANGE(ID_SEARCH_USER_INPUT, OnSearchInputChange)
	ON_BN_CLICKED(ID_BUTTON_LOGIN, OnLogInButtonClicked)
	ON_BN_CLICKED(ID_BUTTON_LOGOUT, OnLogOutButtonClicked)
	ON_BN_CLICKED(ID_BUTTON_ADD_USER, OnAddUserButtonClicked)
	ON_BN_CLICKED(ID_BUTTON_SEARCH, OnSearchButtonClicked)
	ON_BN_CLICKED(ID_BUTTON_LOAN_APPLICATION, OnLoanApplicationButtonClicked)
	ON_BN_CLICKED(ID_BUTTON_USER_DELETE, OnUserButtonDeleteClicked)
	ON_BN_CLICKED(ID_BUTTON_USER_EXIT, OnUserButtonExitClicked)
	ON_BN_CLICKED(ID_BUTTON_USER_INCREASE_MONEY, OnUserButtonIncreaseMoneyClicked)
	ON_BN_CLICKED(ID_BUTTON_USER_DECREASE_MONEY, OnUserButtonDecreaseMoneyClicked)
	
END_MESSAGE_MAP()

class MyWinApp : public CWinApp {
public:
	int InitInstance() {
		MyFrameWnd* wndPtr = new MyFrameWnd();
		m_pMainWnd = wndPtr;
		wndPtr->ShowWindow(SW_SHOW);

		return 1;
	}
};

MyWinApp app;

int MyFrameWnd::PreCreateWindow(CREATESTRUCT& cs) {
	sDsn.Format(L"ODBC;DRIVER={%s};DBQ=%s;", sDriver, sFile);

	return CFrameWnd::PreCreateWindow(cs);
}

void MyFrameWnd::OnClose()
{
	if (AfxMessageBox(CString("Are you sure you want Exit"), MB_YESNO) == IDYES) {MyFrameWnd::DestroyWindow();}
}

void MyFrameWnd::OnDestroy()
{
	CFrameWnd::OnDestroy();

	TRY{
		database.Open(NULL,false,false, sDsn);

		SqlString.Format(L"UPDATE Employees SET LogIn='No' WHERE Name='%s' AND Surname='%s' AND Password='%s';",LogInName,LogInSurname,LogInPassword);
		database.ExecuteSQL(SqlString);

		database.Close();

	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
		database.Close();
	}
	END_CATCH;
}

void MyFrameWnd::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	switch (nHitTest) {

	case HTCAPTION:
		return;
		break;

	case HTBORDER:
		return;
		break;
	}
	
	CFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}

void MyFrameWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	switch (nHitTest) {
	case HTCAPTION:
		return;
		break;

	case HTBORDER:
		return;
		break;

	case HTCLOSE:
		OnClose();
		break;

	case HTMINBUTTON:
		this->ShowWindow(SW_MINIMIZE);
		break;
	}

	CFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void MyFrameWnd::OnPaint() {
	CPaintDC dc(this);

	switch (Display)
	{
	case ID_DISPLAY_LOGIN:
		dc.SetBkColor(RGB(240, 248, 255));
		dc.SetTextColor(RGB(218, 165, 32));
		dc.TextOutW(750, 270, CString("NAME"));
		dc.TextOutW(750, 370, CString("SURNAME"));
		dc.TextOutW(750, 470, CString("PASSWORD"));
		break;
	case ID_DISPLAY_LOGIN_WRONG:
		dc.SetBkColor(RGB(240, 248, 255));
		dc.SetTextColor(RGB(218, 165, 32));
		dc.TextOutW(750, 270, CString("NAME"));
		dc.TextOutW(750, 370, CString("SURNAME"));
		dc.TextOutW(750, 470, CString("PASSWORD"));
		dc.SetTextColor(RGB(255, 0, 0));
		dc.TextOutW(800, 210, CString("LOGIN IS NOT CORRECT!"));
		break;
	case ID_DISPLAY_MAIN:
		dc.SetBkColor(RGB(240, 248, 255));
		dc.SetTextColor(RGB(218, 165, 32));
		dc.TextOutW(840, 410, CString("SEARCH USER"));
		dc.TextOutW(150, 900, CString("Welcome"));
		dc.TextOutW(150, 930, LogInName + _T(" ") + LogInSurname);
		break;
	case ID_DISPLAY_USER:
		dc.SetBkColor(RGB(240, 248, 255));
		dc.SetTextColor(RGB(218, 165, 32));

		dc.TextOutW(100, 100, CString("NAME"));
		dc.MoveTo(70, 135);
		dc.LineTo(650, 135);
		dc.TextOutW(100, 150, CString("SURNAME"));
		dc.MoveTo(70, 185);
		dc.LineTo(650, 185);
		dc.TextOutW(100, 200, CString("AGE"));
		dc.MoveTo(70, 235);
		dc.LineTo(650, 235);
		dc.TextOutW(100, 250, CString("DATE OF BIRTH"));
		dc.MoveTo(70, 285);
		dc.LineTo(650, 285);
		dc.TextOutW(100, 300, CString("GENDER"));
		dc.MoveTo(70, 335);
		dc.LineTo(650, 335);

		dc.TextOutW(450, 100, UserNameDatabase);
		dc.TextOutW(450, 150, UserSurnameDatabase);
		dc.TextOutW(450, 200, UserAgeDatabase);
		dc.TextOutW(450, 250, UserDateOfBirthDatabase);
		dc.TextOutW(450, 300, UserGenderDatabase);

		dc.TextOutW(900, 100, CString("COUNTRY"));
		dc.MoveTo(850, 135);
		dc.LineTo(1500, 135);
		dc.TextOutW(900, 150, CString("CITY"));
		dc.MoveTo(850, 185);
		dc.LineTo(1500, 185);
		dc.TextOutW(900, 200, CString("STREET"));
		dc.MoveTo(850, 235);
		dc.LineTo(1500, 235);
		dc.TextOutW(900, 250, CString("HOUSE NUMBER"));
		dc.MoveTo(850, 285);
		dc.LineTo(1500, 285);
		dc.TextOutW(900, 300, CString("DRIVER LICENCE"));
		dc.MoveTo(850, 335);
		dc.LineTo(1500, 335);

		dc.TextOutW(1250, 100, UserCountryDatabase);
		dc.TextOutW(1250, 150, UserCityDatabase);
		dc.TextOutW(1250, 200, UserStreetDatabase);
		dc.TextOutW(1250, 250, UserHouseNumberDatabase);
		dc.TextOutW(1250, 300, UserDriverLicenceDatabase);
		
		dc.TextOutW(100, 500, CString("JOB"));
		dc.MoveTo(70, 540);
		dc.LineTo(700, 540);
		dc.TextOutW(100, 570, CString("PHONE NUMBER"));
		dc.MoveTo(70, 610);
		dc.LineTo(700, 610);
		dc.TextOutW(100, 640, CString("HOUSE PHONE NUMBER"));
		dc.MoveTo(70, 680);
		dc.LineTo(700, 680);
		dc.TextOutW(100, 710, CString("EMAIL ADDRESS"));
		dc.MoveTo(70, 750);
		dc.LineTo(700, 750);
		dc.TextOutW(100, 790, CString("MARRIED"));
		dc.MoveTo(70, 830);
		dc.LineTo(700, 830);
		dc.TextOutW(100, 860, CString("CHILDREN"));
		dc.MoveTo(70, 900);
		dc.LineTo(700, 900);

		dc.TextOutW(450, 500, UserJobDatabase);
		dc.TextOutW(450, 570, UserPhoneNumberDatabase);
		if (UserHasHousePhoneNumberDatabase == CString("Yes")) {dc.TextOutW(450, 640, UserHousePhoneNumberDatabase);}
		else {dc.TextOutW(450, 640, CString("No House Phone Number"));}
		if (UserEmailAddressDatabase == CString("")){dc.TextOutW(450, 710,CString("No Email Address"));}
		else {dc.TextOutW(450, 710, UserEmailAddressDatabase);}
		dc.TextOutW(450, 790, UserMarriedDatabase);
		if (UserChildrenDatabase == CString("Yes")){dc.TextOutW(450, 860, UserNumberOfChildrenDatabase);}
		else {dc.TextOutW(450, 860, CString("No Children"));}
		

		dc.TextOutW(950, 500, CString("AMOUNT OF MONEY"));
		dc.TextOutW(1200, 500, UserAmountOfMoneyDatabase + CString("   Euro"));
		dc.MoveTo(930, 530);
		dc.LineTo(1450, 530);

		dc.TextOutW(1000, 570, CString("INCREASE MONEY"));
		dc.TextOutW(1000, 670, CString("DECREASE MONEY"));

		break;
	case ID_DISPLAY_CLEAR:
		// ONLY CLEAR DISPLAY
		break;
	}
}

void MyFrameWnd::CreateElements(){
	// ********** LOGIN PAGE **********
	// INPUTS
	NameInput.Create(WS_CHILD | WS_BORDER | ES_CENTER | ES_UPPERCASE, CRect(750, 300, 1050, 320), this, ID_INPUT_NAME);
	NameInput.SetLimitText(20);
	SurnameInput.Create(WS_CHILD | WS_BORDER | ES_CENTER | ES_UPPERCASE, CRect(750, 400, 1050, 420), this, ID_INPUT_SURNAME);
	SurnameInput.SetLimitText(20);
	PasswordInput.Create(WS_CHILD | WS_BORDER | ES_CENTER | ES_PASSWORD, CRect(750, 500, 1050, 520), this, ID_INPUT_PASSWORD);
	PasswordInput.SetLimitText(20);
	// BUTTONS
	LoginButton.Create(CString("LOGIN"), WS_CHILD | BS_PUSHBUTTON, CRect(950, 580, 1150, 630), this, ID_BUTTON_LOGIN);

	// ********** MAIN PAGE ************
	//INPUTS
	SearchUserInput.Create(WS_CHILD | WS_BORDER | ES_CENTER | ES_UPPERCASE, CRect(700, 450, 1100, 470), this, ID_SEARCH_USER_INPUT);
	SearchUserInput.SetLimitText(30);
	//BUTTONS
	LogOutButton.Create(CString("LOGOUT"), WS_CHILD | BS_PUSHBUTTON, CRect(200, 100, 350, 150), this, ID_BUTTON_LOGOUT);
	FindUser.Create(CString("LOAN APPLICATION"), WS_CHILD | BS_PUSHBUTTON, CRect(800, 100, 1000, 170), this, ID_BUTTON_LOAN_APPLICATION);
	AddUserButton.Create(CString("ADD USER"), WS_CHILD | BS_PUSHBUTTON, CRect(1450, 100, 1600, 150), this, ID_BUTTON_ADD_USER);
	SearchButton.Create(CString("SEARCH"), WS_CHILD | BS_PUSHBUTTON, CRect(1130, 440, 1230, 480), this, ID_BUTTON_SEARCH);

	// ********** USER PAGE **********

	UserInputIncreaseMoney.Create(WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER, CRect(1000, 600, 1200, 620), this, ID_INPUT_USER_INCREASE_MONEY);
	UserInputIncreaseMoney.SetLimitText(10);
	UserInputDecreaseMoney.Create(WS_CHILD | WS_BORDER | ES_CENTER | ES_NUMBER, CRect(1000, 700, 1200, 720), this, ID_INPUT_USER_DECREASE_MONEY);
	UserInputDecreaseMoney.SetLimitText(10);

	UserDeleteButton.Create(CString("DELETE USER"), WS_CHILD | BS_PUSHBUTTON, CRect(1600, 850, 1800, 900), this, ID_BUTTON_USER_DELETE);
	UserExitButton.Create(CString("EXIT"), WS_CHILD | BS_PUSHBUTTON, CRect(1600, 70, 1800, 130), this, ID_BUTTON_USER_EXIT);
	UserIncreaseMoneyButton.Create(CString("INCREASE"), WS_CHILD | BS_PUSHBUTTON, CRect(1250, 590, 1350, 630), this, ID_BUTTON_USER_INCREASE_MONEY);
	UserDecreaseMoneyButton.Create(CString("DECREASE"), WS_CHILD | BS_PUSHBUTTON, CRect(1250, 690, 1350, 730), this, ID_BUTTON_USER_DECREASE_MONEY);
}

int MyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CreateElements();
	LogInPageDisplay();
	return 0;
}

// **************** DISPLAYS ****************

void MyFrameWnd::ChangeDisplayDraw(int ReceivedDisplay) {
	Display = ReceivedDisplay;
	Invalidate();
	UpdateWindow();
}

void MyFrameWnd::LogInPageDisplay() {
	NameInput.ShowWindow(SW_SHOW);
	SurnameInput.ShowWindow(SW_SHOW);
	PasswordInput.ShowWindow(SW_SHOW);
	LoginButton.ShowWindow(SW_SHOW);
	ChangeDisplayDraw(ID_DISPLAY_LOGIN);
}

void MyFrameWnd::LogInPageDisplayClear() {
	NameInput.ShowWindow(SW_HIDE);
	SurnameInput.ShowWindow(SW_HIDE);
	PasswordInput.ShowWindow(SW_HIDE);
	LoginButton.ShowWindow(SW_HIDE);
	ChangeDisplayDraw(ID_DISPLAY_CLEAR);
}

void MyFrameWnd::MainPageDisplay() {
	SearchUserInput.ShowWindow(SW_SHOW);
	LogOutButton.ShowWindow(SW_SHOW);
	FindUser.ShowWindow(SW_SHOW);
	AddUserButton.ShowWindow(SW_SHOW);
	SearchButton.ShowWindow(SW_SHOW);
	ChangeDisplayDraw(ID_DISPLAY_MAIN);
}

void MyFrameWnd::MainPageDisplayClear() {
	SearchUserInput.ShowWindow(SW_HIDE);
	LogOutButton.ShowWindow(SW_HIDE);
	FindUser.ShowWindow(SW_HIDE);
	AddUserButton.ShowWindow(SW_HIDE);
	SearchButton.ShowWindow(SW_HIDE);
	ChangeDisplayDraw(ID_DISPLAY_CLEAR);
}


void MyFrameWnd::UserDisplay() {
	// INPUTS
	UserInputIncreaseMoney.ShowWindow(SW_SHOW);
	UserInputDecreaseMoney.ShowWindow(SW_SHOW);
	
	// BUTTONS
	UserDeleteButton.ShowWindow(SW_SHOW);
	UserExitButton.ShowWindow(SW_SHOW);
	UserIncreaseMoneyButton.ShowWindow(SW_SHOW);
	UserDecreaseMoneyButton.ShowWindow(SW_SHOW);

	ChangeDisplayDraw(ID_DISPLAY_USER);

}

void MyFrameWnd::UserDisplayClear() {

	UserNameDatabase = "";
	UserSurnameDatabase = "";
	UserAgeDatabase = "";
	UserGenderDatabase = "";
	UserCountryDatabase = "";
	UserCityDatabase = "";
	UserStreetDatabase = "";
	UserHouseNumberDatabase = "";
	UserDateOfBirthDatabase = "";
	UserJobDatabase = "";
	UserPhoneNumberDatabase = "";
	UserHasHousePhoneNumberDatabase = "";
	UserHousePhoneNumberDatabase = "";
	UserDriverLicenceDatabase = "";
	UserEmailAddressDatabase = "";
	UserMarriedDatabase = "";
	UserChildrenDatabase = "";
	UserNumberOfChildrenDatabase = "";
	UserAmountOfMoneyDatabase = "";

	UserInputDecreaseMoney.SetWindowTextW(CString(""));
	UserInputIncreaseMoney.SetWindowTextW(CString(""));

	// INPUTS
	UserInputIncreaseMoney.ShowWindow(SW_HIDE);
	UserInputDecreaseMoney.ShowWindow(SW_HIDE);

	// BUTTONS
	UserDeleteButton.ShowWindow(SW_HIDE);
	UserExitButton.ShowWindow(SW_HIDE);
	UserIncreaseMoneyButton.ShowWindow(SW_HIDE);
	UserDecreaseMoneyButton.ShowWindow(SW_HIDE);

	ChangeDisplayDraw(ID_DISPLAY_CLEAR);
}


// **************** BUTTON EVENTS ****************

void MyFrameWnd::OnLogInButtonClicked() {

	NameInput.GetWindowTextW(LogInName);
	SurnameInput.GetWindowTextW(LogInSurname);
	PasswordInput.GetWindowTextW(LogInPassword);

	TRY{

	database.Open(NULL,false,false, sDsn);

	CRecordset recset(&database);

	SqlString.Format(L"SELECT Name,Surname,Password FROM Employees");
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
	while (!recset.IsEOF()) {
		recset.GetFieldValue(CString("Name"), LogInNameDatabase);
		recset.GetFieldValue(CString("Surname"), LogInSurnameDatabase);
		recset.GetFieldValue(CString("Password"), LogInPasswordDatabase);

		if (LogInNameDatabase == LogInName && LogInSurnameDatabase == LogInSurname && LogInPasswordDatabase == LogInPassword)
		{
			SqlString.Format(L"UPDATE Employees SET LogIn='Yes' WHERE Name='%s' AND Surname='%s' AND Password='%s';",LogInName,LogInSurname,LogInPassword);
			database.ExecuteSQL(SqlString);
			isLoginTrue = true;
			LogInNameDatabase = "";
			LogInSurnameDatabase = "";
			LogInPasswordDatabase = "";
			break;
		}
		else {recset.MoveNext();}
		
	}
	database.Close();

	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
		isLoginTrue = false;
		database.Close();
	}
	END_CATCH;

	if (isLoginTrue == true) {
		NameInput.SetWindowTextW(CString(""));
		SurnameInput.SetWindowTextW(CString(""));
		PasswordInput.SetWindowTextW(CString(""));
		LogInPageDisplayClear();
		MainPageDisplay();
	}
	else {
		PasswordInput.SetWindowTextW(CString(""));
		ChangeDisplayDraw(ID_DISPLAY_LOGIN_WRONG);
	}
}

void MyFrameWnd::OnLogOutButtonClicked() {

	TRY{
		database.Open(NULL,false,false, sDsn);

		SqlString.Format(L"UPDATE Employees SET LogIn='No' WHERE Name='%s' AND Surname='%s' AND Password='%s';",LogInName,LogInSurname,LogInPassword);
		database.ExecuteSQL(SqlString);
		isLoginTrue = false;
		LogInName = "";
		LogInSurname = "";
		LogInPassword = "";

		database.Close();

	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
		database.Close();
	}
	END_CATCH;

	MainPageDisplayClear();
	LogInPageDisplay();
};


void MyFrameWnd::OnAddUserButtonClicked() {
	AddUserDlg.DoModal();
};


void MyFrameWnd::OnSearchButtonClicked() {
	SearchUserInput.GetWindowTextW(SearchInputNameSurname);

	// SPLIT SearchInputNameSurname to UserName and UserSurname
	for (int i = 0; i < SearchInputNameSurname.GetLength(); i++)
	{
		if (!isSpaceFind) { if (SearchInputNameSurname.GetAt(i) == CString(" ")) { isSpaceFind = true; continue; } }

		if (isSpaceFind){UserSurname.AppendChar(SearchInputNameSurname.GetAt(i));}
		else {UserName.AppendChar(SearchInputNameSurname.GetAt(i));}
	}
	isSpaceFind = false;

	TRY{

	database.Open(NULL,false,false, sDsn);

	CRecordset recset(&database);

	SqlString.Format(L"SELECT * FROM Users");
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

	while (!recset.IsEOF()) {
		recset.GetFieldValue(CString("Name"), UserNameDatabase);
		recset.GetFieldValue(CString("Surname"), UserSurnameDatabase);
		
		if (UserNameDatabase == UserName && UserSurnameDatabase == UserSurname)
		{
			recset.GetFieldValue(CString("Age"), UserAgeDatabase);
			recset.GetFieldValue(CString("Gender"), UserGenderDatabase);
			recset.GetFieldValue(CString("Country"), UserCountryDatabase);
			recset.GetFieldValue(CString("City"), UserCityDatabase);
			recset.GetFieldValue(CString("Street"), UserStreetDatabase);
			recset.GetFieldValue(CString("HouseNumber"), UserHouseNumberDatabase);
			recset.GetFieldValue(CString("DateOfBirth"), UserDateOfBirthDatabase);
			recset.GetFieldValue(CString("Job"), UserJobDatabase);
			recset.GetFieldValue(CString("PhoneNumber"), UserPhoneNumberDatabase);
			recset.GetFieldValue(CString("HasHousePhoneNumber"), UserHasHousePhoneNumberDatabase);
			recset.GetFieldValue(CString("HousePhoneNumber"), UserHousePhoneNumberDatabase);
			recset.GetFieldValue(CString("DriverLicence"), UserDriverLicenceDatabase);
			recset.GetFieldValue(CString("EmailAddress"), UserEmailAddressDatabase);
			recset.GetFieldValue(CString("Married"), UserMarriedDatabase);
			recset.GetFieldValue(CString("Children"), UserChildrenDatabase);
			recset.GetFieldValue(CString("NumberOfChildren"), UserNumberOfChildrenDatabase);
			recset.GetFieldValue(CString("AmountOfMoney"), UserAmountOfMoneyDatabase);
			SearchUserInput.SetWindowTextW(CString(""));
			isUserFind = true;
			break;
		}
		else { recset.MoveNext(); }
	}
	database.Close();

	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
		isUserFind = false;
		database.Close();
	}
	END_CATCH;

	UserName = "";
	UserSurname = "";

	if (isUserFind)
	{
		isUserFind = false;
		MainPageDisplayClear();
		UserDisplay();
	}
	else{AfxMessageBox(CString("User Has Not Found"));}
	
};

void MyFrameWnd::OnLoanApplicationButtonClicked() {
	LoanApplicationDlg.DoModal();
}


void MyFrameWnd::OnUserButtonDeleteClicked() {
	UserDeleteMessageBoxText.Format(L"Do you really want remove '%s %s' from bank",UserNameDatabase,UserSurnameDatabase);
	if (AfxMessageBox(UserDeleteMessageBoxText,MB_YESNO) == IDYES)
	{
		TRY{
			database.Open(NULL,false,false, sDsn);

			SqlString.Format(L"DELETE FROM Users WHERE Name='%s' AND Surname='%s';",UserNameDatabase,UserSurnameDatabase);
			database.ExecuteSQL(SqlString);

			database.Close();

			UserDisplayClear();
			MainPageDisplay();

		}CATCH(CDBException, e) {
			AfxMessageBox(L"Database error: " + e->m_strError);
			database.Close();
		}
		END_CATCH;
	}
}


void MyFrameWnd::OnUserButtonExitClicked() {
	UserDisplayClear();
	MainPageDisplay();
}


void MyFrameWnd::OnUserButtonIncreaseMoneyClicked() {
	UserInputIncreaseMoney.GetWindowTextW(UserAmountOfMoney);
	UserInputIncreaseMoney.SetWindowTextW(CString(""));

	// ADD MONEY FROM DATA AND MONEY FROM INPUT
	UserAmountOfMoney.Format(L"%i",_wtoi(UserAmountOfMoneyDatabase) + _wtoi(UserAmountOfMoney));

	TRY{
			database.Open(NULL,false,false, sDsn);

			SqlString.Format(L"UPDATE Users SET AmountOfMoney='%s' WHERE Name='%s' AND Surname='%s';", UserAmountOfMoney,UserNameDatabase,UserSurnameDatabase);
			database.ExecuteSQL(SqlString);

			UserAmountOfMoneyDatabase = UserAmountOfMoney;
			database.Close();

			ChangeDisplayDraw(ID_DISPLAY_USER);

	}CATCH(CDBException, e) {
		AfxMessageBox(L"Database error: " + e->m_strError);
		database.Close();
	}
	END_CATCH;
	
}

void MyFrameWnd::OnUserButtonDecreaseMoneyClicked() {
	UserInputDecreaseMoney.GetWindowTextW(UserAmountOfMoney);
	UserInputDecreaseMoney.SetWindowTextW(CString(""));

	
	// SUBTRACT MONEY FROM DATA WITH MONEY FROM INPUT IF MONEY FROM DATA IS GRATHER THEN MONEY FROM INPUT
	if (_wtoi(UserAmountOfMoneyDatabase) >= _wtoi(UserAmountOfMoney))
	{
		UserAmountOfMoney.Format(L"%i", _wtoi(UserAmountOfMoneyDatabase) - _wtoi(UserAmountOfMoney));

		TRY{
			database.Open(NULL,false,false, sDsn);

			SqlString.Format(L"UPDATE Users SET AmountOfMoney='%s' WHERE Name='%s' AND Surname='%s';", UserAmountOfMoney,UserNameDatabase,UserSurnameDatabase);
			database.ExecuteSQL(SqlString);

			UserAmountOfMoneyDatabase = UserAmountOfMoney;
			database.Close();

			ChangeDisplayDraw(ID_DISPLAY_USER);

		}CATCH(CDBException, e) {
			AfxMessageBox(L"Database error: " + e->m_strError);
			database.Close();
		}
		END_CATCH;

	}
	else {AfxMessageBox(CString("User has not so much money on account"));}
	
}

// **************** EDIT EVENTS ****************

void MyFrameWnd::OnSearchInputChange() {

}
