#pragma once
#ifndef _JSON_DOCUMENT_H_
#define _JSON_DOCUMENT_H_

#define _CRT_SECURE_NO_WARNINGS

#include <string>

#include "cJSON.h"
#include "JsonParseError.h"

using namespace std;

class JsonObject;
class JsonArray;

class JsonDocument
{
public:
	JsonDocument();
	JsonDocument(const JsonObject &obj);
	JsonDocument(const JsonArray &arr);
	JsonDocument(const JsonDocument &doc);
	~JsonDocument();

	JsonDocument& operator=(const JsonDocument &doc);

	bool isArray();
	bool isObject();
	bool isEmpty();
	bool isNull();

	string toJson() const;

	JsonObject object();
	JsonArray array();

	static JsonDocument fromFile(const string filename, JsonParseError *error = NULL);
	static JsonDocument fromJson(const string json);

private:
	cJSON * m_root;
};

#endif // !_JSON_DOCUMENT_H_
