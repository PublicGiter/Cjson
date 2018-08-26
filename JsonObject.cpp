#include "JsonObject.h"
#include "JsonValue.h"



JsonObject::JsonObject()
{
	m_root = cJSON_CreateObject();
}

JsonObject::JsonObject(const string & json)
{
	m_root = cJSON_Parse(json.c_str());
}

JsonObject::JsonObject(const JsonObject & obj)
{
	m_root = cJSON_Parse(obj.toJson().c_str());
}

JsonObject::~JsonObject()
{
	if (m_root != NULL)
	{
		cJSON_Delete(m_root);
		m_root = NULL;
	}
}

JsonObject & JsonObject::operator=(const JsonObject & obj)
{
	if (&obj == this)
	{
		return *this;
	}

	if (m_root != NULL)
	{
		cJSON_Delete(m_root);
		m_root = NULL;
	}
	m_root = cJSON_Parse(obj.toJson().c_str());

	return *this;
}

JsonValue JsonObject::operator[](const string & key)
{
	cJSON *json = cJSON_GetObjectItem(m_root, key.c_str());

	return json;
}

void JsonObject::insert(const string & key, const JsonValue & val)
{
	cJSON * v = cJSON_Parse(val.toJson().c_str());
	cJSON_AddItemToObject(m_root, key.c_str(), v);
}


bool JsonObject::isEmpty()
{
	if (m_root == NULL)
	{
		return false;
	}

	if (m_root->type == cJSON_NULL)
	{
		return true;
	}

	return false;
}

string JsonObject::toJson() const
{
	if (m_root == NULL)
	{
		return "";
	}
	char *ch = cJSON_Print(m_root);
	string json = ch;
	free(ch);
	return json;
}
