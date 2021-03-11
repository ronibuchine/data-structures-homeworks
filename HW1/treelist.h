#pragma once
#include "Tree.h"
#include <iostream>
#include <list>
#include <string>
using namespace std;
class treeList {
public:
	// constructors/destructor
	treeList() {}
	~treeList() { discussions.clear(); }
	void addNewTree(string cont);
	void deleteTree(Tree* victim);
	bool addResponse(string root, string father, string son) { return modifyTree(root, father, son, 1); }	
	bool delResponse(string root, string victim) { return modifyTree(root, victim); }						
	bool modifyTree(string root, string target, string son = "", bool add = 0);
	void printAllTrees();
	void printTree(string root) { Print(root, root, 0, 0, 1); }		//finds specific tree and prints it
	void printSubTree(string root, string cont) { Print(root, cont, 0, 1, 1); }		//finds specific tree and prints the path and subtree of node
	void printPath(string root, string cont) { Print(root, cont, 0, 1, 0); }	//finds specific tree and prints path from root to node
	void printStringPath(string cont) { Print("", cont, 1, 1, 0); }		//prints path of given string within each tree
	void searchAndPrint(string cont) { Print("", cont, 1, 1, 1); }		//prints path and subtree of given string within each tree 
	void Print(string root, string cont, bool allTrees = 0, bool path = 0, bool subtree = 0);

private:
	list<Tree> discussions;
};
