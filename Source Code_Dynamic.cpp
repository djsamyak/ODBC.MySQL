#include<iostream>
#include<windows.h>
#include<sql.h>
#include<sqlext.h>

using namespace std;

void main()
{
	//Creation of Handles
	SQLHANDLE henv;		//Environment Handle
	SQLHANDLE hconn;	//Connection Handle
	SQLHANDLE hstmt;	//Statement Handle

	//Allocation of Environment Handle
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);

	//Allocation of Enviroment Attributes
	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

	//Allocation of Connection Handle along with Credentials
	SQLAllocHandle(SQL_HANDLE_DBC, henv, &hconn);
	SQLCHAR* dsnName = (SQLCHAR*)"          ";
	SQLCHAR* userid = (SQLCHAR*)"          ";
	SQLCHAR* password = (SQLCHAR*)"          ";

	//Connection to DB
	SQLConnect(hconn, dsnName, SQL_NTS, userid, SQL_NTS, password, SQL_NTS);

	//Allocation of Statement Handle
	SQLAllocHandle(SQL_HANDLE_STMT, hconn, &hstmt);

	char ch;
	cout << "Select Statment Type. \nPress 'm' for Modification. \nPress 'v' Viewing Mode \n \n";
	cin >> ch;
	cout << "\n";
	
	//Dynamic Query Entry
	SQLCHAR * query;
	query = new SQLCHAR;
	char s[100];
	cin.ignore(100, '\n');
	cout << "Enter the query. \n";
	cin.getline(s, 100);
	cout << "\n";
	strcpy_s((char *)query, 100, s);
	SQLExecDirect(hstmt, query, SQL_NTS);		//Query Execution

	//Start fetching data from DB
	SQLFetch(hstmt);
	SQLLEN numRows;
	SQLRowCount(hstmt, &numRows);			//Get number of Rows
	if (ch == 'm')
	{
		printf("%2d rows were affected. \n", numRows);
		goto term;
	}
	else
	{
		printf("%2d rows were fetched. \n", numRows);
	}
	SQLSMALLINT numCols;
	SQLNumResultCols(hstmt, &numCols);		//Get number of Columns
	printf("%2d columns were fetched. \n", numCols);
	cout << "\n";
	SQLSMALLINT ColNameLen, DataType, NumDecimalDigit, AllowsNullValues;
	SQLUINTEGER ColSize;
	SQLCHAR colname[256];
	
	//Get and display column attributes
	for (int i = 1; i <= numCols; ++i) 						//Column Data
	{
		SQLDescribeColA(hstmt, i, colname, 255, &ColNameLen, &DataType, &ColSize, &NumDecimalDigit, &AllowsNullValues);
		{
			printf("Column #%d: '%s' \n", i, colname);
		}
	}
	cout << "\n";
	{
		for (int i = 1; i == 1 || SQL_SUCCEEDED(SQLFetch(hstmt)); ++i) 		//Output Rows
		{
			char buffer[512];
			printf("%2d.", i);
			{								//Output Column Data
				SQLINTEGER Bytes;
				for (int j = 1; j <= numCols; ++j)
				{
					SQLGetData(hstmt, j, SQL_C_CHAR, buffer, 511, &Bytes);
					{
						printf("%20s", buffer);
					}
				}
				cout << "\n";						 //New row break
			}
		}
		cout << "\n";
	}

	term:
	if (!SQL_SUCCEEDED(SQLFetch(hstmt)))
	{
		printf("Fetch terminated. ");
	}

	//Freeing up of handles
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	SQLFreeHandle(SQL_HANDLE_DBC, hconn);
	SQLFreeHandle(SQL_HANDLE_ENV, hstmt);

	//Disconnecting Handles
	SQLDisconnect(henv);
	SQLDisconnect(hconn);
	SQLDisconnect(hstmt);
}
