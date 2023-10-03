#include "stdafx.h"
#include "constants.h"
#include "char.h"
#include "desc_client.h"
#include "unique_item.h"
#include "utils.h"
#include "log.h"
#include "login_security.h"
#include "db.h"

#include "../../common/service.h" //Or other file with defines (if is not already defined)

CLoginSecurity::CLoginSecurity()
{
}

bool CLoginSecurity::IsMatchIP(const char* pLogin, const char* pIP)
{	
	if(NULL == pLogin || NULL == pIP)
		return true;
	
	char szQuery[512];
	int rows;
	snprintf(szQuery, sizeof(szQuery), "SELECT ip FROM account.login_security WHERE login = '%s'", pLogin);
	SQLMsg *msg = DBManager::instance().DirectQuery(szQuery);
	MYSQL_RES *res = msg->Get()->pSQLResult;
	
	if (!res)
		return true;
	
	if ((rows = mysql_num_rows(res)) <= 0)
		return true;
	
	for (int i = 1; i <= rows; i++)
	{		
		int cur = 0;
		MYSQL_ROW row = mysql_fetch_row(res);
		const char* dbIP = row[cur++];
		cur++;
		
		if(strcmp(dbIP, pIP) == 0)
			return true;
		else if (cur  > rows)
			return false;
	} 
	return true;
}

