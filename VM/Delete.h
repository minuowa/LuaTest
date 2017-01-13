#pragma once

template<typename T1,typename T2>
void DeleteMap(map<T1, T2>& m)
{
	for (auto i = m.begin(); i != m.end(); ++i)
		delete i->second;
	m.clear();
}
