#include"MiniKV.h"

bool MiniKV::Set(const string& key, const string& value)
{
	_data[key] = value;

	return true;
}

bool MiniKV::Get(const string& key, string& value) const
{
	auto it = _data.find(key);

	if (it == _data.end())
	{
		return false;
	}

	value = it->second;

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
		ofs << it->first << " " << it->second << endl;
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
	string value;

	while (ifs >> key >> value)
	{
		_data[key] = value;
	}

	ifs.close();

	return true;
}