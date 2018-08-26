#pragma once
#ifndef _JSON_OBJECT_H_
#define _JSON_OBJECT_H_

#include <string>

using namespace std;

#include "cJSON.h"

class JsonArray;
class JsonValue;

class JsonObject
{
public:
	JsonObject();
	JsonObject(const string &json);
	JsonObject(const JsonObject &obj);
	~JsonObject();

	JsonObject& operator=(const JsonObject &obj);

	JsonValue operator[](const string &key);

	void insert(const string &key, const JsonValue &val);

	bool isEmpty();

	string toJson() const;

private:
	cJSON * m_root;
};


#endif // !_JSON_OBJECT_H_