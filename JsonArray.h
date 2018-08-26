#pragma once
#ifndef _JSON_ARRAY_H_
#define _JSON_ARRAY_H_

#include <string>

#include "cJSON.h"

using namespace std;

class JsonValue;

class JsonArray
{
public:
	JsonArray();
	JsonArray(const string &json);
	JsonArray(const JsonArray &arr);
	~JsonArray();

	JsonArray& operator=(const JsonArray &arr);

	void insert(int i, const JsonValue &val);

	bool isEmpty();

	string toJson() const;

private:
	cJSON * m_root;
};


#endif // !_JSON_ARRAY_H_

