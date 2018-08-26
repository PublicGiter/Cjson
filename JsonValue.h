#pragma once
#ifndef _JSON_VALUE_H_
#define _JSON_VALUE_H_
#define _CRT_SECURE_NO_WARNINGS

#include <string>

using namespace std;

#include "cJSON.h"

class JsonObject;
class JsonArray;

class JsonValue
{
	friend class JsonArray;
	friend class JsonObject;
public:
	JsonValue();
	JsonValue(bool b);
	JsonValue(double d);
	JsonValue(int i);
	JsonValue(const string &str);
	JsonValue(const char *ch);
	JsonValue(cJSON *json);
	JsonValue(const JsonObject &obj);
	JsonValue(const JsonArray &arr);
	JsonValue(const JsonValue &val);
	~JsonValue();

	JsonValue& operator=(bool b);
	JsonValue& operator=(double d);
	JsonValue& operator=(int i);
	JsonValue& operator=(const string &str);
	JsonValue& operator=(const char *ch);
	JsonValue& operator=(const JsonValue &val);

	bool isObject();
	bool isArray();
	bool isNumber();
	bool isBool();
	bool isString();
	bool isNull();


	JsonObject toObject();
	JsonArray toArray();
	double toDouble();
	int toInt();
	bool toBool();
	string toString();

	string toJson() const;


private:
	cJSON * m_root;
	bool m_isFree = true;
};

#endif // !_JSON_VALUE_H_
