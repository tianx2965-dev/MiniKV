#include"MiniKV.h"

bool MiniKV::Set(const string& key, const string& value)
{
	_data[key]._value = value;

	return true;
}

bool MiniKV::Get(const string& key, string& value)
{
	auto it = _data.find(key);

	if (it == _data.end())
	{
		return false;
	}

	if (it->second._expireTime != 0
		&& time(nullptr) >= it->second._expireTime)
	{
		_data.erase(it);
		return false;

	}
	value = it->second._value;

	return true;
}

bool MiniKV::Del(const string& key)
{
	auto it = _data.find(key);
	if ( it == _data.end())
	{
		return false;
	}
	_data.erase(it);

	return true;
}

bool MiniKV::Exists(const string& key) const
{
	return _data.find(key) != _data.end();
}

void MiniKV::Keys() const
{
	for (auto it = _data.begin(); it != _data.end(); ++it)
	{
		cout << it->first << endl;
	}
}

bool MiniKV::Save(const string& filename) const
{
	ofstream ofs(filename);

	if (!ofs.is_open())
	{
		return false;
	}
	for (auto it = _data.begin(); it != _data.end(); ++it)
	{
		ofs << it->first << " "
			<< it->second._value <<" "
			<< it->second._expireTime<< endl;
	}

	ofs.close();

	return true;
}

bool MiniKV::Load(const string& filename)
{
	ifstream ifs(filename);

	if (!ifs.is_open())
	{
		return false;
	}

	string key;
	Entry entry;

	while (ifs >> key >> entry._value >> entry._expireTime)
	{
		if (entry._expireTime != 0
			&& time(nullptr) >= entry._expireTime)
		{
			continue;
		}
		_data[key]= entry;
	}

	ifs.close();

	return true;
}

bool MiniKV::Expire(const string& key, int seconds)
{
	auto it = _data.find(key);

	if (it == _data.end())
	{
		return false;
	}

	it->second._expireTime = time(nullptr) + seconds;

	return true;
}