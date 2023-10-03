#include "../../common/service.h" //Or other file with defines (if is not already defined)
#ifdef ENABLE_LOGIN_SECURITY
class CLoginSecurity : public singleton<CLoginSecurity>
{
	public :
		CLoginSecurity();
		
		bool	IsMatchIP(const char* pLogin, const char* pIP);
};

#endif