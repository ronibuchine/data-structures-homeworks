#include "treelist.h"
void treeList::addNewTree(string cont) 
{
	Tree* t = new Tree(cont); //creates empty tree
	discussions.push_back(*t); //and pushes it to the list of discussions
}

void treeList::deleteTree(Tree* victim)
{
	discussions.remove(*victim);
}

bool treeList::modifyTree(string root, string target, string son, bool add)
{
	list<Tree>::iterator it = discussions.begin();
	while (it != discussions.end()) 
	{
		if (it->getRootContent() == root)
		{
			try {
				if (add) 
					it->addNode(target, son);
				else if (it->getRootContent() == target)
					deleteTree(&(*it));
				else 
					it->deleteSubtree(target);
				return true;
			}
			catch (...) { return false; }
		}
		++it;
	}
	return false;
}

void treeList::printAllTrees() //prints all trees
{ 
	list<Tree>::reverse_iterator it = discussions.rbegin();
	for (int i = 1; it != discussions.rend(); ++it, ++i) 
	{
		cout << "Tree #" << i << endl;
		it->printTree();
		cout << endl;
	}
}

void treeList::Print(string root, string cont, bool allTrees, bool path, bool subtree) 
{	//a template for a variety of print statements
	list<Tree>::reverse_iterator it = discussions.rbegin();
	bool exists = false;
	while (it != discussions.rend()) 
	{
		if (allTrees || it->getRootContent() == root)  //check if root matches
		{ 
			Tree::Node* n = it->find(cont);
			if (n != NULL) 
				exists = true;
			if (subtree) 
				it->printTree(n);
			if (path && it->getRootContent() != cont)
				it->printPath(cont); //prints path from root to node
			cout << endl;
		}
		++it;
	}
	if (allTrees && !exists) 
		cout << "ERROR" << endl;
}