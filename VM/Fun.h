#pragma once

template<typename T1,typename T2>
void dDeleteMap(map<T1, T2>& m)
{
	for (auto i = m.begin(); i != m.end(); ++i)
		delete i->second;
	m.clear();
}

template<typename T1, typename T2>
bool dTryGetValue(map<T1, T2>& m, T1 key, T2& ret)
{
	auto i = m.find(key);
	if ( i!= m.end())
	{
		ret = i->second;
		return true;
	}
	return false;
}

template< typename T2>
bool dTryGetValue(map<string, T2>& m, string key, T2& ret)
{
	auto i = m.find(key);
	if (i != m.end())
	{
		ret = i->second;
		return true;
	}
	return false;
}
