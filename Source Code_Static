#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<sql.h>
#include<sqltypes.h>
#include<sqlext.h>

using namespace std;

void main()
{
	SQLHANDLE henv;
	SQLHANDLE hconn;
	SQLHANDLE hstmt;

	//1. Allocating Environment Handle
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

	//2. Stating ODBC Version
	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

	//3. Allocating Connection Handle
	SQLAllocHandle(SQL_HANDLE_DBC, henv, &hconn);
	SQLCHAR* dsnName = (SQLCHAR*)"		";
	SQLCHAR* userid = (SQLCHAR*)"		";
	SQLCHAR* password = (SQLCHAR*)"		";

	//4. Opening DB Connection
	SQLConnect(hconn, dsnName, SQL_NTS, userid, SQL_NTS, password, SQL_NTS);

	//5. Allocating Statement Handle
	SQLAllocHandle(SQL_HANDLE_STMT, hconn, &hstmt);

	//6. Querying
	SQLCHAR* query = (SQLCHAR*)"select * from aircrafts;";
	SQLExecDirect(hstmt, query, SQL_NTS);

	//7.Fetch Data
	SQLFetch(hstmt);
	SQLLEN numRows;
	SQLRowCount(hstmt, &numRows);
	printf("%2d rows were fetched. \n", numRows);
	SQLSMALLINT numCols;
	SQLNumResultCols(hstmt, &numCols);
	printf("%2d columns were fetched. \n", numCols);
	cout << "\n";
	SQLSMALLINT ColNameLen, DataType, NumDecimalDigit, AllowsNullValues;
	SQLUINTEGER ColSize;
	SQLCHAR colname[256];
	for (int i = 1; i <= numCols; ++i) //Columns
	{
		SQLDescribeColA(hstmt, i, colname, 255, &ColNameLen, &DataType, &ColSize, &NumDecimalDigit, &AllowsNullValues);
		{
			printf("Column #%d: '%s' \n", i, colname);
		}
	}
	cout << "\n";
	{
		for (int i = 1; i == 1 || SQL_SUCCEEDED(SQLFetch(hstmt)); ++i) //Output Rows
		{
			char buffer[512];
			printf("%2d.", i);
			{								//Output Column Data
				SQLINTEGER Bytes;
				for (int j = 1; j <= numCols; ++j)
				{
					SQLGetData(hstmt, j, SQL_C_CHAR, buffer, 511, &Bytes);
					{
						if (j == 4)
						{
							printf("%30s", buffer);
						}
						else
							printf("%10s", buffer);
					}
				}
				cout << "\n"; //New row break
			}
		}
		cout << "\n";
	}

	//8. Termination
	if (!SQL_SUCCEEDED(SQLFetch(hstmt)))
	{
		printf("Last row fetched. Program terminated. ");
	}

	//9. Free Up Resources
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	SQLFreeHandle(SQL_HANDLE_DBC, hconn);
	SQLFreeHandle(SQL_HANDLE_ENV, hstmt);
}
