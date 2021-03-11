#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "item.h"
using namespace std;
template <class K, class T>
class hashtable
{
public:
	int prime(int n) // recieves a number n and returns the next largest number that is prime
	{
		while (true) //loop runs until a prime number is found
		{
			for (int i = 2; i < 10; i++)
			{
				if (n % i == 0)
					break;
				if (i == 9)
					return n;
			}
			n++;
		}
		throw "ERROR IN PRIME NUMBER FUNCTION";
	}
	// constructors and destructor
	hashtable()  { table.resize(0); }
	hashtable(int size) 
	{
		table.resize(prime(size));
	}
	virtual ~hashtable() {}

	// abstract methods
	int virtual h1(K key) = 0; // returns place in the table
	int virtual h2(K key) = 0; // returns step size
	int virtual hash(K key, int step) = 0;
	int virtual search(K key) = 0;
	void virtual insert(item<K, T> entry) = 0;
	void virtual remove(K key) = 0;
	void virtual update(item<K, T> entry) = 0;
	void virtual print() = 0;

protected:

	vector<item<K, T> > table;

};

