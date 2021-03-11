#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <cmath>
#include "huffman.h"

using namespace std;
int main()

{
	int choice;
	string word;
	HuffmanTree* t = new HuffmanTree();
	cout << "enter 1 to encode a text\n";
	cout << "enter 2 to decode a text\n";
	cout << "enter 3 to exit\n";

	do
	{
		cin >> choice;
		switch (choice)
		{
		case 1:

			cout << "enter the original text" << endl;
			cin >> word;
			cout << "the encoded string is:" << endl;
			t->buildTree(word);
			cout << t->encode(word) << endl;

			//Build Huffman tree given the data inside "word".
			//Then find the code of each letter.
			//Then print the output - number of leaves, order of letters, tree structure and the encoded text - according to the explanation in the exercise.

			break;
		case 2:
			int n;
			string letters;
			string structure;
			string text;
			cout << "enter n ";
			cin >> n;
			cout << "enter the letters ";
			cin >> letters;
			cout << "enter the encoded structure ";
			cin >> structure;
			cout << "enter the encoded text ";
			cin >> text;
			t->buildTree(letters, structure);
			cout << "the decoded string is: " << t->decode(text) << endl;
			//input the number of leaves, the  order of letters, tree structure and the encoded text.
			//build the Huffman Tree according to the tree strcture. put the letters in the leaves according to the given order. 
			//Given the Huffman Tree and the encoded text, find the original text, and print it. 
			break;
		}

	} while (choice != 3);
	return 0;
}