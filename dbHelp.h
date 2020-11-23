#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<stdlib.h>
#include "Student.h"
class DBHelper
{
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1024
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

public:
	void init();
	void Insert();
	void Select(Student*&);
	void Update();
	void Delete();
	void close();

};

