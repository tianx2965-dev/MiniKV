#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<sstream>
#include<fstream>
#include<ctime>

using namespace std;

struct Entry
{
	string _value;
	time_t _expireTime = 0;//过期时间
};

class MiniKV
{
public:
	//存数据/修改数据
	bool Set(const string& key, const string& value);

	//根据key查找value
	bool Get(const string& key, string& value) ;

	//删除key
	bool Del(const string& key);

	//判断key是否存在
	bool Exists(const string& key) const;

	//输出所有key
	void Keys() const;

	//持久化
	bool Save(const string& filename) const;
	bool Load(const string& filename);

	//给某个key设置一个过期时间
	bool Expire(const string& key, int seconds);


private:
	unordered_map<string, Entry> _data;
};