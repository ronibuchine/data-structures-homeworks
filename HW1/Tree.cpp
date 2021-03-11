#include "Tree.h"

string Tree::getRootContent()
{ //getter function for finding correct tree in treeList
	if (root == NULL) 
		throw "ERROR: Tree is Empty";
	return root->content;
}

Tree::Node* Tree::find(Node* start, string cont, bool parent ) {								
	if (parent == 0 && start->content == cont)
		return start;	//if the root is the target, return it
	list<Node>::iterator it = start->responses.begin();
	for (; it != start->responses.end(); ++it) //iterate through response list, looking for target node
	{									
		if (it->content == cont)
		{
			return parent ? start : &(*it);
		}
		Node* node = find(&(*it), cont, parent);									
		if (node != NULL)
			return node;											
	}
	return NULL;	//if target node isn't found beneath start node, return NULL
}

void Tree::addNode(string father, string son)
{
	Node* parent = find(father);													
	if (parent == NULL)
		throw "ERROR: Node not found.";
	Node child;	        															
	child.content = son;
	parent->responses.push_back(child);												
}

void Tree::deleteSubtree(string cont) 
{
	Node* parent = find(root, cont, 1);												
	if (parent == NULL)
		throw "ERROR: Node not found.";
	list<Node>::iterator it = parent->responses.begin();
	while (it->content != cont)
		++it;
	parent->responses.erase(it);                                          		
}

void Tree::printTree(Node* start, int indent)
{
	if (start == NULL) return;
	for (int i = indent; i > 0; --i)
		cout << ' ';
	cout << start->content << endl;			//first prints content of starting node itself  recursively print all nodes in responses list
	list<Node>::iterator it = start->responses.begin();
	while (it != start->responses.end()) 
	{											
		printTree(&(*it), indent + 3);
		++it;
	}
}

void Tree::printPath(Node* start, string cont) 
{											
	if (find(start, cont) == NULL)
		return;		//stop recursion if content node is not in tree
	if (start->content == cont) 
		cout << start->content << "=>";						
	else {
		list<Node>::iterator it = start->responses.begin();							
		for (; find(&(*it), cont) == NULL; ++it);								
		printPath(&(*it), cont);													
		cout << start->content;
		if (root != start) 
			cout << "=>";
		else 
			cout << endl;
	}
}

bool Tree::operator==(const Tree& t) const 
{ 
	return root == t.root;
}



