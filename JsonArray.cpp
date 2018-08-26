#include "JsonArray.h"
#include "JsonValue.h"



JsonArray::JsonArray()
{
	m_root = cJSON_CreateArray();
}

JsonArray::JsonArray(const string & json)
{
	m_root = cJSON_Parse(json.c_str());
}

JsonArray::JsonArray(const JsonArray & arr)
{
	m_root = cJSON_Parse(arr.toJson().c_str());
}


JsonArray::~JsonArray()
{
	if (m_root != NULL)
	{
		cJSON_Delete(m_root);
		m_root = NULL;
	}
}

JsonArray & JsonArray::operator=(const JsonArray & arr)
{
	if (&arr == this)
	{
		return *this;
	}

	if (m_root != NULL)
	{
		cJSON_Delete(m_root);
		m_root = NULL;
	}

	m_root = cJSON_Parse(arr.toJson().c_str());

	return *this;
}

void JsonArray::insert(int i, const JsonValue & val)
{
	cJSON * v = cJSON_Parse(val.toJson().c_str());
	cJSON_InsertItemInArray(m_root, i, v);
}

bool JsonArray::isEmpty()
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

string JsonArray::toJson() const
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
