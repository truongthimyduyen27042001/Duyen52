#include "DBHelper.h"
#include"Student.h"
#include <iostream>
#include<iomanip>
#include<conio.h>
#include<string.h>
using namespace std;
void DBHelper::init()
{
	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;
	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		close();

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		close();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		close();

	//output
	cout << "Attempting connection to SQL Server...";
	cout << "\n";
	switch (SQLDriverConnect(sqlConnHandle, NULL,(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=DESKTOP-VPF0AQ3;DATABASE=SQLDBUI;trusted = true;UID=sa;PWD=123456",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {

	case SQL_SUCCESS:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;

	case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;

	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		close();
		break;

	case SQL_ERROR:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		close();
		break;

	default:
		break;
	}
	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		close();
}




void DBHelper::Select(Student*& students) 
{
	
	//output
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Student", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		char id[10];
		char name[50];
		float result;
		int i = 0;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, id,  SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, name, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_C_FLOAT, &result, 1, &ptrSqlVersion);
			//display query result
			cout << "\nquery result: " << id << " " << name << " ";
			cout << setprecision(2) << fixed << result << endl;
			Student *St = new Student(id, name, result);
			*(students + i) = *St;
			i++;
		}	
	}
	SQLCancel(sqlStmtHandle);
}

void DBHelper::Insert()
{
	
	/*string s = "INSERT INTO Student VALUES('102180111',";
	string s1 = "'Quan',";
	string s2 = "'6')";

	s = s + s1 + s2;*/
	//int M = 50;

	/*char m[50];
	for (int i = 0; i < 50; i++)
	{
		m[i] = s[i];
		cout << m[i];
	}*/
	//cout << m;
	char m[] = "INSERT INTO Student VALUES('102180116','Quan','9')";

	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle,(SQLCHAR*)m , SQL_NTS)) {

		cout << "\n";
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {

		cout << "\nINSERT SUCCESS";
		return;
	}
}


void DBHelper::Update()
{
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"UPDATE Student SET Id = '102180100' where Id = '102180137'", SQL_NTS)) {
		cout << "\n";
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {

		cout << "\nUPDATE SUCCESS";
		return;
	}
}
void DBHelper::Delete()
{
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"DELETE from Student where Id = '102180138'", SQL_NTS)) {
		cout << "\n";
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {

		cout << "\nDELETE SUCCESS";
		return;
	}
}
void DBHelper::close()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}

//SQLCHAR							SalesPerson[11];
//SQLINTEGER				SalesPersonLenOrInd, CustIDInd;
//SQLUINTEGER			CustID;
////	Bind	SalesPerson	to	the	parameter	for	the	SalesPerson	column	and
////	CustID	to	the	parameter	for	the	CustID	column.
//SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 10, 0, SalesPerson, sizeof(SalesPerson), &SalesPersonLenOrInd);
//SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0, 	&CustID, 0, &CustIDInd);
////	Set	values	of	salesperson	and	customer	ID	and	length/indicators.
//strcpy_s((char*)SalesPerson, _countof(SalesPerson), "Garcia");
//SalesPersonLenOrInd = SQL_NTS;
//CustID = 1331;
//CustIDInd = 0;
////	Execute	a	statement	to	get	data	for	all	orders	made	to	the	specified
////	customer	by	the	specified	salesperson.
//SQLExecDirect(hstmt1, "SELECT	*	FROM	Orders	WHERE	SalesPerson=?	AND	CustID=?", SQL_NTS);
////	Prepare	the	procedure	invocation	statement.
//SQLPrepare(hstmt, "{call	test(?)}", SQL_NTS);
////	Populate	record	1	of	ipd.
//SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
//	30, 0, szQuote, 0, &cbValue);
////	Get	ipd	handle	and	set	the	SQL_DESC_NAMED	and	SQL_DESC_UNNAMED	fields
////	for	record	#1.
//SQLGetStmtAttr(hstmt, SQL_ATTR_IMP_PARAM_DESC, &hIpd, 0, 0);
//SQLSetDescField(hIpd, 1, SQL_DESC_NAME, "@quote", SQL_NTS);
////	Assuming	that	szQuote	has	been	appropriately	initialized,
////	execute.
//SQLExecute(hstmt);
