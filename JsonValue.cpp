#include "JsonValue.h"
#include "JsonArray.h"
#include "JsonObject.h"


JsonValue::JsonValue()
{
	m_root = cJSON_CreateNull();
}

JsonValue::JsonValue(bool b)
{
	if (b)
	{
		m_root = cJSON_CreateTrue();
	}
	else
	{
		m_root = cJSON_CreateFalse();
	}
}

JsonValue::JsonValue(double d)
{
	m_root = cJSON_CreateNumber(d);
}

JsonValue::JsonValue(int i)
{
	m_root = cJSON_CreateNumber(i);
}

JsonValue::JsonValue(const string & str)
{
	m_root = cJSON_CreateString(str.c_str());
}

JsonValue::JsonValue(const char * ch)
{
	m_root = cJSON_CreateString(ch);
}

JsonValue::JsonValue(cJSON * json)
{
	m_root = json;
	m_isFree = false;
}

JsonValue::JsonValue(const JsonObject & obj)
{
	m_root = cJSON_Parse(obj.toJson().c_str());
}

JsonValue::JsonValue(const JsonArray & arr)
{
	m_root = cJSON_Parse(arr.toJson().c_str());
}

JsonValue::JsonValue(const JsonValue & val)
{
	m_root = cJSON_Parse(val.toJson().c_str());
}


JsonValue::~JsonValue()
{
	if (m_isFree && m_root != NULL)
	{
		cJSON_Delete(m_root);
		m_root = NULL;
	}
}

#define cJSON_False 0
#define cJSON_True 1
#define cJSON_NULL 2
#define cJSON_Number 3
#define cJSON_String 4
#define cJSON_Array 5
#define cJSON_Object 6

JsonValue & JsonValue::operator=(bool b)
{
	if (b)
	{
		m_root->type = cJSON_True;
	}
	else
	{
		m_root->type = cJSON_False;
	}
	
	
	return *this;
}

JsonValue & JsonValue::operator=(double d)
{
	m_root->valueint = (int)d;
	m_root->valuedouble = d;
	return *this;
}

JsonValue & JsonValue::operator=(int i)
{
	m_root->valueint = i;
	m_root->valuedouble = i;

	return *this;
}

JsonValue & JsonValue::operator=(const string & str)
{
	free(m_root->valuestring);
	m_root->valuestring = (char*)malloc(str.size() + 1);
	strcpy(m_root->valuestring, str.c_str());

	return *this;
}

JsonValue & JsonValue::operator=(const char * ch)
{
	free(m_root->valuestring);
	m_root->valuestring = (char*)malloc(strlen(ch) + 1);
	strcpy(m_root->valuestring, ch);

	return *this;
}

JsonValue & JsonValue::operator=(const JsonValue & val)
{
	if (&val == this)
	{
		return *this;
	}

	cJSON * json = cJSON_Parse(val.toJson().c_str());

	json->prev = m_root->prev;
	json->next = m_root->next;

	if (m_root->child != NULL)
	{
		cJSON_Delete(m_root->child);
		m_root->child = NULL;
	}

	if (m_root->valuestring != NULL)
	{
		free(m_root->valuestring);
		m_root->valuestring = NULL;
	}

	*m_root = *json;

	return *this;
}

bool JsonValue::isObject()
{
	if (m_root != NULL && m_root->type == cJSON_Object)
	{
		return true;
	}
	return false;
}

bool JsonValue::isArray()
{
	if (m_root != NULL && m_root->type == cJSON_Array)
	{
		return true;
	}
	return false;
}

bool JsonValue::isNumber()
{
	if (m_root != NULL && m_root->type == cJSON_Number)
	{
		return true;
	}
	return false;
}

bool JsonValue::isBool()
{
	if (m_root != NULL && (m_root->type == cJSON_True || m_root->type == cJSON_False))
	{
		return true;
	}
	return false;
}

bool JsonValue::isString()
{
	if (m_root != NULL && m_root->type == cJSON_String)
	{
		return true;
	}
	return false;
}

bool JsonValue::isNull()
{
	if (m_root != NULL && m_root->type == cJSON_NULL)
	{
		return true;
	}
	return false;
}



JsonObject JsonValue::toObject()
{
	char *ch = cJSON_Print(m_root);
	JsonObject obj(ch);
	free(ch);
	
	return obj;
}

JsonArray JsonValue::toArray()
{
	char *ch = cJSON_Print(m_root);
	JsonArray arr(ch);
	free(ch);

	return arr;
}

double JsonValue::toDouble()
{
	return m_root->valuedouble;
}

int JsonValue::toInt()
{
	return m_root->valueint;
}

bool JsonValue::toBool()
{
	if (m_root->type == cJSON_True)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string JsonValue::toString()
{
	return m_root->valuestring;
}


string JsonValue::toJson() const
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
