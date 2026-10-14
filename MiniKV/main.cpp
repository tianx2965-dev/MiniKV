#define _CRT_SECURE_NO_WARNINGS 1
#include"MiniKV.h"

//验证增删改查
void test1()
{
	MiniKV db;

	db.Set("name", "suntianxiang");
	db.Set("age", "20");
	db.Set("sex", "man");
	db.Set("numbers", "2510250644");

	string value;

	if (db.Get("age", value))
	{
		cout << value << endl;
	}

	db.Set("age", "19");

	if (db.Get("age", value))
	{
		cout << value << endl;
	}

	auto ret = db.Exists("name");
	cout << ret << endl;

	ret = db.Exists("weight");
	cout << ret << endl;

	db.Keys();
}

void System_Start(MiniKV& db)
{
	while (true)
	{
		cout << "MiniKV> ";

		string line;
		//从标准输入读取用户输入的整行内容（包含空格），并存入 line 中，直到用户按下回车键
		getline(cin, line);

		stringstream ss(line);
		string cmd;
		ss >> cmd;//流中读取第一个以空格分隔的单词

		if (cmd == "SET")
		{
			string key;
			string value;

			ss >> key >> value;

			db.Set(key, value);

			cout << "OK" << endl;
		}
		else if (cmd == "GET")
		{
			string key;
			ss >> key;
			string value;
			if (db.Get(key, value))
			{
				cout << value << endl;
			}
			else
			{
				cout << "Key not found" << endl;
			}
		}
		else if (cmd == "DEL")
		{
			string key;
			ss >> key;

			if (db.Del(key)) cout << "OK" << endl;
			else cout << "Key not found" << endl;
		}
		else if (cmd == "EXISTS")
		{
			string key;
			ss >> key;

			cout << db.Exists(key) << endl;
		}
		else if (cmd == "KEYS")
		{
			db.Keys();
		}
		else if (cmd == "SAVE")
		{
			if (db.Save("minikv.db"))
				cout << "OK" << endl;
			else
				cout << "SAVE failed" << endl;
		}
		else if (cmd == "EXIT")
		{
			break;
		}
	}
}
int main()
{
	MiniKV db;
	
	db.Load("minikv.db");

	System_Start(db);

	return 0;
}