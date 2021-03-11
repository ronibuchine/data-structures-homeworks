#pragma once
#include <iostream>
#include <string>
using namespace std;
class Trie
{
protected:
	class TrieNode {
	public:
		TrieNode() : parent(NULL) {}
		TrieNode(TrieNode* parent) : parent(parent) {}

		bool isPrefix() {
			bool prefix = false; //assume node isn't prefix
			for (int i = 0; prefix == false && i < 26; ++i) {
				if (children[i] != NULL) prefix = true; //if child is found, prefix = true
			}
			return prefix;
		}

		TrieNode* parent;
		bool isEnd = false;
		TrieNode* children[26] = { 0 };
	};

	TrieNode* root = new TrieNode;

public:
	Trie() {}		//default constructor
	bool search(string str);	
	bool search(string str, TrieNode*& endNode);
	int printAutoSuggestions(string str, TrieNode* node = NULL); 
	void insert(string str);
	bool del(string str);

private:
	int find(string str, TrieNode*& end);
	void del(TrieNode* node); 
};

