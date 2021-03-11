#pragma once
using namespace std;
enum state { empty, full, deleted };
template <class K, class T>
class item // helper class
{
public:
	T data;
	K key;
	state flag;
	item<K, T>() {}
	item<K, T>(K k, T d, state f) : data(d), key(k), flag(f) {}
};