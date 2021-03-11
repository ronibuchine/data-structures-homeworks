#pragma once
#include "hashtable.h"
#include <list>
#include <string>
using namespace std;
class HSubject : public hashtable<string, list<string> >
{
public:
	HSubject() : hashtable() {}
	HSubject(int size) : hashtable(size) 
	{
		for (int i = 0; i < table.size(); i++)
			table[i].flag = (state)0;								// sets all flags to be empty
	}
	~HSubject() {}
// methods
	int virtual h1(string key); // returns place in the table
	int virtual h2(string key); // returns step size
	int virtual hash(string key, int step); // returns the position in the table of the given key and in the given step
	int virtual search(string key);
	void virtual insert(item<string, list<string> > entry);
	void virtual remove(string key);
	void virtual update(item<string, list<string> > entry);
	void virtual print();
	void printS(string key);
	void printN(string key, int n);
	void startNewTable();
	void addSubjectAndTitle(string key, string discussion);

};


