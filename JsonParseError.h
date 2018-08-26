#pragma once
#ifndef _JSON_PARSE_ERROR_H_
#define _JSON_PARSE_ERROR_H_

#include <iostream>
#include <string>

using namespace std;

class JsonParseError
{
public:
	JsonParseError();
	~JsonParseError();

	void setJsonParseError(bool error, const string &errinfo);

	bool isError();

	void printError();

private:
	bool m_error;
	string m_errinfo;
};

#endif // !_JSON_PARSE_ERROR_H_
