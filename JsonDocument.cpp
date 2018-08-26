#include "JsonDocument.h"
#include "JsonObject.h"
#include "JsonArray.h"

JsonDocument::JsonDocument()
{
	m_root = NULL;
}

JsonDocument::JsonDocument(const JsonObject & obj)
{
	m_root = cJSON_Parse(obj.toJson().c_str());
}

JsonDocument::JsonDocument(const JsonArray & arr)
{
	m_root = cJSON_Parse(arr.toJson().c_str());
}

JsonDocument::JsonDocument(const JsonDocument & doc)
{
	m_root = cJSON_Parse(doc.toJson().c_str());
}

JsonDocument::~JsonDocument()
{
	if (m_root != NULL)
	{
		cJSON_Delete(m_root);
		m_root = NULL;
	}
}

JsonDocument & JsonDocument::operator=(const JsonDocument & doc)
{
	if (&doc == this)
	{
		return *this;
	}

	if (m_root != NULL)
	{
		cJSON_Delete(m_root);
		m_root = NULL;
	}

	m_root = cJSON_Parse(doc.toJson().c_str());

	return *this;
}


bool JsonDocument::isArray()
{
	if (m_root == NULL)
	{
		return false;
	}
	if (m_root->type == cJSON_Array)
	{
		return true;
	}

	return false;
}

bool JsonDocument::isObject()
{
	if (m_root == NULL)
	{
		return false;
	}

	if (m_root->type == cJSON_Object)
	{
		return true;
	}

	return false;
}

bool JsonDocument::isEmpty()
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

bool JsonDocument::isNull()
{
	if (m_root == NULL)
	{
		return true;
	}
	return false;
}

string JsonDocument::toJson() const
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

JsonObject JsonDocument::object()
{
	JsonObject obj(toJson());

	return obj;
}

JsonArray JsonDocument::array()
{
	JsonArray arr(toJson());

	return arr;
}

JsonDocument JsonDocument::fromFile(const string filename, JsonParseError * error)
{
	JsonDocument doc;
	FILE * file = fopen(filename.c_str(), "r");
	if (file == NULL)
	{
		error->setJsonParseError(true, "file open error");
		return doc;
	}

	char buf[4096] = { 0 };
	if (fread(buf, 1, sizeof(buf), file) == sizeof(buf))
	{
		error->setJsonParseError(true, "The file is too large to open");
		fclose(file);
		return doc;
	}

	doc.m_root = cJSON_Parse(buf);

	fclose(file);

	return doc;
}

JsonDocument JsonDocument::fromJson(const string json)
{
	JsonDocument doc;

	doc.m_root = cJSON_Parse(json.c_str());

	return doc;
}
