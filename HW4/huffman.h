#pragma once
#include <string>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class HuffmanNode
{
public:
	HuffmanNode(string str, int freq, HuffmanNode* left = NULL, HuffmanNode* right = NULL) : str(str), frequency(freq), left(left), right(right) {}
	~HuffmanNode() {
		delete left;
		delete right;
	}

	string structNode() {
		if (str != "") return "1";
		return "0" + left->structNode() + right->structNode();
	}

private:
	string str;
	int frequency;
	HuffmanNode* left;
	HuffmanNode* right;

	friend class compareNode;
	friend class HuffmanTree;
};
class compareNode {
public:
	bool operator()(HuffmanNode* const& n1, HuffmanNode* const& n2)
	{
		return n1->frequency > n2->frequency;
	}
};

class HuffmanTree {
public:
	HuffmanTree() {}
	~HuffmanTree() { delete root; }

	//buildTree for entered word
	void buildTree(string word);
	//buildTree for entered tree
	void buildTree(string characters, string structure);

	string encode(string word); 

	string decode(string encodedText);

private:
	int countChars(int* array); 
	//in order traversal starting from passed node. Also builds the encodingTable for use by encoder function
	string traverseNode(HuffmanNode* node, string code = "");
	void buildNode(HuffmanNode*& node, string& tS, string& tT);

	HuffmanNode* root = NULL;
	string encodingTable[94];
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, compareNode> pQueue;
};

