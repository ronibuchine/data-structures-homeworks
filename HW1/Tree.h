#pragma once
#include <list>
#include <iostream>
#include <string>
using namespace std;
class Tree
{
public:
	// custom Node Object
	struct Node
	{
		string content;
		list<Node> responses;
	};
	// class constructors/destructor
	Tree() : root(NULL) {} //creates new tree with no root
	Tree(string cont)
	{
		if (root != NULL) delete root;
		root = new Node; //sets root to new Node
		root->content = cont; //sets content of root Node to given string
	}
	~Tree() { 	delete root;}
	// class methods
	string getRootContent(); //getter function for finding correct tree in treeList
	Node* find(string cont) { return find(root, cont); }	
	Node* find(Node* start, string cont, bool parent = 0); 
	void addNode(string father, string son);
	void deleteSubtree(string cont);
	void printTree() { printTree(root, 0); }
	void printTree(Node* start, int indent = 0);
	void printPath(string cont) { return printPath(root, cont); }						
	void printPath(Node* start, string cont);
	// operators
	bool operator==(const Tree& t) const;
private:
	Node* root;
};


