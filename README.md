# Duyen52
Làm đồ án QLKTX connect thử nghiệm
#include <iostream >
#include <Windows.h>
#include <sqlext.h>
#include <sql.h>
#include <string>

class Khoa
{
public : 
	void KetNoi();
	void HuyKetNoi();
	void XuatThongTin();
	void ThemDuLieu();
	void XoaDuLieu();
	void MaKhoa();
	
};

--------------------
file Khoa.cpp
#include "Khoa.h"
#include <iostream>
#include <iomanip>
using namespace std;
SQLHANDLE SQLEnvHandle = NULL; //xu ly su kien 
SQLHANDLE SQLConnectionHandle = NULL;//dong hoac mo ket noi 
SQLHANDLE SQLStatementHandle = NULL;//
SQLRETURN retCode = 0; //
void showSQLError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLState[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handleType, handle, 1, SQLState, NULL, message, 1024, NULL))
		// Returns the current values of multiple fields of a diagnostic record that contains error, warning, and status information
		cout << "SQL driver message: " << message << "\nSQL state: " << SQLState << "." << endl;
}
void Khoa::KetNoi() {
	do {
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &SQLEnvHandle))
			// Allocates the environment
			break;

		if (SQL_SUCCESS != SQLSetEnvAttr(SQLEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			// Sets attributes that govern aspects of environments
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, SQLEnvHandle, &SQLConnectionHandle))
			// Allocates the connection
			break;

		if (SQL_SUCCESS != SQLSetConnectAttr(SQLConnectionHandle, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0))
			// Sets attributes that govern aspects of connections
			break;

		SQLCHAR retConString[1024]; // Conection string
		switch (SQLDriverConnect(SQLConnectionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=DESKTOP-D9VU28Q\\SQLEXPRESS; DATABASE=QLKTX_Test2;Trusted_Connection=True;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
			// Establishes connections to a driver and a data source
		case SQL_SUCCESS:
			break;
		case SQL_SUCCESS_WITH_INFO:
			break;
		case SQL_NO_DATA_FOUND:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSQLError(SQL_HANDLE_DBC, SQLConnectionHandle);
			retCode = -1;
			break;
		default:
			break;
		}

		if (retCode == -1)
			break;

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConnectionHandle, &SQLStatementHandle))
			// Allocates the statement
			break;
	} while (FALSE);

}
void Khoa::HuyKetNoi() {
	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);//xu li su kien
	SQLDisconnect(SQLConnectionHandle);//dong ket noi
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConnectionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);
}
void Khoa::XuatThongTin() {
	KetNoi();
	char SQLQuery[] = "SELECT * FROM Khoa";
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS)) {
		// Executes a preparable statement
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
	}
	else {
		char makhoa[30], tenkhoa[70], sdt[14], tentruongkhoa[50];


		while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
			// Fetches the next rowset of data from the result
			SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &makhoa, sizeof(makhoa), NULL);
			SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &tenkhoa, sizeof(tenkhoa), NULL);
			SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &sdt, sizeof(sdt), NULL);
			SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &tentruongkhoa, sizeof(tentruongkhoa), NULL);
			// Retrieves data for a single column in the result set
			cout <<setw(7)<<left<< makhoa << setw(25) << tenkhoa << setw(20) << sdt <<setw(30) << tentruongkhoa << endl;
		}
	}
	HuyKetNoi();
}
void Khoa::ThemDuLieu() {
	KetNoi();
	string querry = "insert into KHOA values ('";
	string makhoa, tenkhoa, sdt, tenadmin;
	string beforeend = "','";
	string end = "')";
	cout << "Nhap du lieu cua khoa : " << endl;
	cout << "Nhap ma khoa : ";
	getline(cin, makhoa);
	cout << "Nhap ten khoa : ";
	
	getline(cin, tenkhoa);
	cout << "Nhap sdt : ";

	getline(cin, sdt);
	cout << "Nhap ten truong khoa :";
	getline(cin, tenadmin);

	querry.append(makhoa);
	querry.append(beforeend);
	querry.append(tenkhoa);
	querry.append(beforeend);
	querry.append(sdt);
	querry.append(beforeend);
	querry.append(tenadmin);
	querry.append(end);
	const char* SQLQuery = querry.c_str();
	if (SQL_SUCCESS == SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS)) {
		cout << "Da them du lieu vao!" << endl;
	}
	else {

		cout << "Du lieu khong them thanh cong !" << endl;
	}
	HuyKetNoi();
}
void Khoa::XoaDuLieu() {
	KetNoi();
	cout << "Dang thuc hien ham xoa!" << endl;
	string querry = "delete from KHOA where MaKhoa= '";
	string makhoa;
	string end = "'";
	cout << "XOA DU LIEU : " << endl;
	cout << "Nhap ma khoa can xoa : ";
	getline(cin, makhoa);
	querry.append(makhoa);
	querry.append(end);
	const char* SQLQuery = querry.c_str();
	cout << SQLQuery;
	if (SQL_SUCCESS == SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS)) {
		cout << "Da xoa du lieu vao!" << endl;
	}
	else {

		cout << "Du lieu xoa khong thanh cong !" << endl;
	}
	HuyKetNoi();


}

void Khoa::MaKhoa() {
	KetNoi();
	char SQLQuery[] = "select MaKhoa from KHOA";
	if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)SQLQuery, SQL_NTS)) {
		// Executes a preparable statement
		showSQLError(SQL_HANDLE_STMT, SQLStatementHandle);
	}
	else {
		char makhoa[30];

		while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS) {
			// Fetches the next rowset of data from the result
			SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &makhoa, sizeof(makhoa), NULL);
			
			// Retrieves data for a single column in the result set
			cout << setw(7) << left << makhoa  << endl;
		}
	}
	HuyKetNoi();

}
----
connectKhoa 
#include "Khoa.h"
#include <iostream>
using namespace std;
int main() {
	Khoa s1;
	s1.XuatThongTin();
	s1.ThemDuLieu();
	s1.ThemDuLieu();
	s1.ThemDuLieu();
	
	//s1.XoaDuLieu();
	s1.XuatThongTin();
	return 0;
}
