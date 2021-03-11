//#pragma once
//#include "hashtable.h"
//
//using namespace std;
//class hashint : public hashtable<int, int>
//{
//public:
//	hashint() : hashtable() {}
//	hashint(int size) : hashtable(size)
//	{
//		for (int i = 0; i < table.size(); i++)
//			table[i].data = table[i].key = table[i].flag = (state)0; // initializes all table values to be empty items
//	}
//	~hashint() {}
//
//	//  methods
//	int virtual h1(int key) // returns place in the table
//	{
//		return key % table.size(); 
//	}
//
//	int virtual h2(int key) // returns step size
//	{
//		return (key * prime(key)) % table.size();
//	}
//
//	int virtual hash(int key, int step)
//	{
//		return h1(key) + step;
//	}
//
//	int virtual search(int key)
//	{
//		for (int i = 0; i < table.size(); i++)
//		{
//			int index = hash(h1(key), (i * h2(key))) % table.size();
//			if (table[index].key == key && table[index].flag == full)
//				return index;
//		}
//		return -1;
//	}
//
//	void virtual insert(item<int, int> item)
//	{
//		for (int i = 0; i < table.size(); i++)
//		{
//			int index = hash(h1(item.key), (i * h2(item.key))) % table.size();
//			if (table[index].flag == (state)0 || table[index].flag == deleted)
//			{
//				item.flag = full;
//				table[index] = item;
//				return;
//			}
//		}
//		throw "table full";
//	}
//
//	void virtual remove(int key)
//	{
//		for (int i = 0; i < table.size(); i++)
//		{
//			int index = hash(h1(key), (i * h2(key))) % table.size();
//			if (table[index].key == key && table[index].flag == full)
//			{
//				table[index].flag = deleted;
//				return;
//			}
//		}
//		throw "item not in table";
//	}
//
//	void virtual update(item<int, int> item)
//	{
//		cout << "unimplemented";
//	}
//
//	void virtual print()
//	{
//		for (item<int, int> i : table)
//		{
//			if (i.flag == full)
//			{
//				cout << i.key << ':' << i.data << endl;
//			}
//		}
//	}
//};
