#include "trie.h"
bool Trie::search(string str)
{
	TrieNode* dummy;
	return search(str, dummy);
}

bool Trie::search(string str, TrieNode*& endNode)
{
	if (find(str, endNode) == str.length() && endNode->isEnd)
		return true;	//if entire string is found and the final node has end of word flag, word exists in trie
	return false;
}

int Trie::printAutoSuggestions(string str, TrieNode* node) 
{
	int count = 0;
	if (node == NULL)
		find(str, node);												//if node is NULL (by default), set node to end node of str
	if (node->isEnd)
	{
		++count;
		cout << str << endl;
	}
	for (int i = 0; i < 26; ++i) {
		if (node->children[i] != NULL)
			count += printAutoSuggestions(str + char(i + 97), node->children[i]);		//if child is NULL, continue on to next child
	}
	return count;
}

void Trie::insert(string str)
{
	TrieNode* node = NULL;
	int found = find(str, node);								//start = number of characters already in trie
	string::iterator it = str.begin() + found;					//start iterator at first character not in trie
	while (it != str.end())
	{									//iterate until end of string
		node->children[*it - 97] = new TrieNode(node);			//continuously add children until the end of string
		node = node->children[*it - 97];						//step into the new node
		++it;
	}
	node->isEnd = true;											//set end of word flag to true on final node
}

bool Trie::del(string str)
{
	TrieNode* end = NULL;
	if (search(str, end)) 
	{		//if string exists
		del(end);				//delete it's end node
		return true;
	}
	return false;
}

int Trie::find(string str, TrieNode*& end)
{
	TrieNode* node = root;							//initialize current node as root
	string::iterator it = str.begin();				//iterate through str
	while (it != str.end() && node->children[*it - 97] != NULL)
	{		//continue down trie until nullptr or iterator is complete
		node = node->children[*it - 97];			//set node as the child which represents the letter of iterator
		++it;
	}
	end = node;
	return it - str.begin();					//returns number of characters found from string
}

void Trie::del(TrieNode* node) 
{
	if (node == root)
		return;											//dont delete root
	if (node->isPrefix())
		node->isEnd = false;							//if node is prefix, set it's end flag to false
	else {
		TrieNode* parent = node->parent;								//keep track of node's parent
		int index = 0;
		while (index < 26 && node != parent->children[index])
			++index;	//increment i until the index of node
		delete parent->children[index];									//delete node
		parent->children[index] = NULL;									//set index of node as NULL
		if (!parent->isPrefix())
			del(parent);							//if parent is not a prefix (anymore), delete it
	}
}