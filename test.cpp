#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "cJSON.h"
#include "JsonDocument.h"
#include "JsonObject.h"
#include "JsonArray.h"
#include "JsonValue.h"
using namespace std;

void test01()
{
	JsonDocument doc = JsonDocument::fromFile("./test.json");
	if (!doc.isObject())
	{
		cout << "document is not object" << endl;
	}

	JsonObject obj = doc.object();
	if (obj.isEmpty())
	{
		cout << "object is null" << endl;
	}
}

void test02()
{
	JsonObject obj;

	{
		JsonObject obj1;
		JsonValue vhost("smtp.163.com");
		JsonValue vport(25);
		JsonValue vemail("test@163.com");
		JsonValue vtitle("this is title");

		obj1.insert("host", vhost);
		obj1.insert("port", vport);
		obj1.insert("email", vemail);
		obj1.insert("title", vtitle);

		obj.insert("object1", obj1);
	}

	JsonObject obj2;

	{
		

		JsonValue v1("smtp.163.com");
		v1 = "999999999999999.com";
		JsonValue v2(25);
		v2 = 29;
		v2 = "29";
		JsonValue v3("test@163.com");
		v3 = string("com.163@test");
		JsonValue v4("this is title");

		obj2.insert("host", v1);
		obj2.insert("port", v2);
		obj2.insert("email", v3);
		obj2.insert("title", v4);

		obj.insert("object2", obj2);
	}


	cout << obj.toJson() << endl;

	obj["object1"].toObject()["host"] = "---------------------------";

	cout << "object1:::::" << obj["object1"].toJson() << endl;
}

void test03()
{
	JsonArray arr;

	JsonValue vhost("smtp.163.com");
	JsonValue vport(25);
	JsonValue vemail("test@163.com");
	JsonValue vtitle("this is title");

	arr.insert(0, vhost);
	arr.insert(0, vport);
	arr.insert(0, vemail);
	arr.insert(0, vtitle);

	cout << arr.toJson() << endl;
}

int main()
{
	test02();

	system("pause");
	return EXIT_SUCCESS;
}