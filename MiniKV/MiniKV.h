#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<sstream>
#include<fstream>

using namespace std;

class MiniKV
{
public:
	//存数据/修改数据
	bool Set(const string& key, const string& value);

	//根据key查找value
	bool Get(const string& key, string& value) const;

	//删除key
	bool Del(const string& key);

	//判断key是否存在
	bool Exists(const string& key) const;

	//输出所有key
	void Keys() const;

	//持久化
	bool Save(const string& filename) const;
	bool Load(const string& filename);

private:
	unordered_map<string, string> _data;

};