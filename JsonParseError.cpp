#include "JsonParseError.h"



JsonParseError::JsonParseError()
{
	m_error = false;
}


JsonParseError::~JsonParseError()
{
}

void JsonParseError::setJsonParseError(bool error, const string & errinfo)
{
	m_error = error;
	m_errinfo = errinfo;
}

bool JsonParseError::isError()
{
	return m_error;
}

void JsonParseError::printError()
{
	if (m_error)
	{
		cout << "JsonParseError: " << m_errinfo << endl;
	}
	else
	{
		cout << "JsonParseError: " << "not error!" << endl;
	}
}
