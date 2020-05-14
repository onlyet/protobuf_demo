#include <string>
#include <exception>

using std::string;
using std::exception;

// “Ï≥£¥¶¿Ì
class ConnException : public exception
{
public:
	int m_nExc;
	string m_sMsg;
	DWORD m_dErr;

public:
	ConnException(int e,const string str,DWORD er)
	{
		m_nExc = e;
		m_sMsg = str;
		m_dErr = er;
	}

	~ConnException()
	{

	}
};