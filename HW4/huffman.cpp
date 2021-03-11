#include "huffman.h"
void HuffmanTree::buildTree(string word) 
{
	delete root;										//deallocate old tree

	//create list of character frequencies
	int charCount[94]{ 0 };
	for (string::iterator i = word.begin(); i != word.end(); ++i) {
		++charCount[*i - '!'];
	}

	//add all characters with non-0 frequencies, as HuffmanNodes, into priority queue
	for (size_t i = 0; i < 94; ++i) {
		if (charCount[i] > 0) pQueue.push(new HuffmanNode(string(1, i + '!'), charCount[i]));
	}

	//pull out 2 least frequent characters and create parent node
	while (pQueue.size() > 1) {
		HuffmanNode* left = pQueue.top();
		pQueue.pop();
		HuffmanNode* right = pQueue.top();
		pQueue.pop();
		pQueue.push(new HuffmanNode("", left->frequency + right->frequency, left, right)); //place fresh parent node back into queue
	}
	root = pQueue.top();							//set final remaining (parent) node as root
	pQueue.pop();									//remove last element from queue in case another tree is built

	cout << countChars(charCount) << endl;
	cout << traverseNode(root) << endl;
	cout << root->structNode() << endl;
}
void HuffmanTree::buildTree(string characters, string structure)
{
	delete root;															//deallocate old tree
	buildNode(root, structure, characters);
}
string HuffmanTree::encode(string word) 
{
	string encoded;
	for (string::iterator it = word.begin(); it != word.end(); ++it) {
		encoded += encodingTable[*it - '!'];
	}
	return encoded;
}
string HuffmanTree::decode(string encodedText)
{
	string word;
	for (string::iterator it = encodedText.begin(); it != encodedText.end();) {		//for every bit in code
		HuffmanNode* node = root;											//starting from root
		while (node->str == "") {											//step down tree until leaf
			(*it == '0') ? node = node->left : node = node->right;
			++it;
		}
		word += node->str;													//append leaf's character to word
	}
	return word;
}

int HuffmanTree::countChars(int* array) 
{
	int count = 0;
	for (size_t i = 0; i < 94; ++i) {
		if (array[i] > 0) ++count;
	}
	return count;
}

string HuffmanTree::traverseNode(HuffmanNode* node, string code)
{
	if (node->left == NULL) {
		encodingTable[node->str[0] - '!'] = code;
		return node->str;
	}
	return traverseNode(node->left, code + '0') + node->str + traverseNode(node->right, code + '1');
}

void HuffmanTree::buildNode(HuffmanNode*& node, string& tS, string& tT)
{
	node = new HuffmanNode("", 0);								//create parent node
	if (tS[0] == '1') {										//if node is leaf...
		node->str = tT[0];										//set node's character
		tT.erase(tT.begin());
		tS.erase(tS.begin());
	}
	else {														//else (node is internal)...
		tS.erase(tS.begin());
		buildNode(node->left, tS, tT);								//build left node
		buildNode(node->right, tS, tT);								//build right node
	}
}
