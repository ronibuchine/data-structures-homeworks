#pragma once
#include <map>
#include <list>
#include <string>
using namespace std;

class Edge;
class Vertex {			//writer
public:
	Vertex() {}
	Vertex(string key) : key(key) {}

	bool operator==(const Vertex& v) const { return key == v.key; }

	string key;			//writer's name
	bool reached = false;
	list<Edge> edgeList;
};

class Edge {			//Follow
public:
	Edge(Vertex* source, Vertex* target) : source(source), target(target) {}
	Vertex* source;		//follower
	Vertex* target;		//being followed

	bool operator==(const Edge& e) const {
		if (source == e.source && target == e.target) return true;
		return false;
	}
};

/***
class Graph
{
public:
	Graph() {}							//default constructor
	~Graph() { graph.clear(); }		//destructor

	void addv(string key) {
		vertices.push_back(Vertex(key));
		graph[vertices.back()];
	}

	bool delv(string key) {
		while (!graph[key].empty()) {			//iterate through all edge's on vertex
			Edge edge = graph[key].front();
			graph[edge.source].remove(edge);			//remove edge from follower's list
			graph[edge.target].remove(edge);			//remove edge from followee's list
		}
		vertices.remove(Vertex(key));
		graph.erase(key);						//remove v from map
		return true;
	}

	bool adde(string v1, string v2) {
		//check that both writer's exist in graph and aren't the same writer
		if (!graph.count(v1)) return false;
		if (!graph.count(v2)) return false;
		if (v1 == v2) return false;

		Edge edge = Edge(Vertex(v1), Vertex(v2));

		//looks through vertex with less followers and looks for existing edge
		list<Edge> edgeList = graph[(graph[v1].size() < graph[v2].size()) ? v1 : v2];
		bool exists = false;
		for (list<Edge>::iterator it = edgeList.begin(); it != edgeList.end(); ++it) {
			if (*it == edge) return false;
		}

		//if edge doesn't already exist
		//edges.push_back(edge);				//add to graph's list of edges
		graph[v1].push_back(edge);		//add to source's list of edges
		graph[v2].push_back(edge);		//add to target's list of edges
		return true;
	}

	bool dele(string v1, string v2) {
		//verify that vertices exist
		if (!graph.count(v1)) return false;
		if (!graph.count(v2)) return false;

		graph[v1].remove(Edge(Vertex(v1), Vertex(v2)));
		graph[v2].remove(Edge(Vertex(v1), Vertex(v2)));
		return true;
	}

	void printNeighbors(string key) {
		for (list<Edge>::iterator it = graph[key].begin(); it != graph[key].end(); ++it) {
			if (it->source.key == key) cout << it->target.key << ' ';
		}
	}

	void printFollowers(string key) {
		if (!graph.count(key)) { cout << "ERROR"; return; }
		for (list<Edge>::iterator it = graph[key].begin(); it != graph[key].end(); ++it) {
			if (it->target.key == key) cout << it->source.key << ' ';
		}
	}

	void printAllReached(string key, list<string>* keys = nullptr) {
		if (!graph.count(key)) { cout << "ERROR"; return; }
		for (list<Edge>::iterator i = graph[key].begin(); i != graph[key].end(); ++i) {
			if (i->source.key == key) {
				keys->push_back(i->target.key);
				cout << i->source.key << ' ';
				printAllReached(i->source.key, keys);
			}
		}
		//keys.sort();
		//keys->unique();
		//for (list<string>::iterator it = keys->begin(); it != keys->end(); ++it) cout << *it << ' ';
	}

	void printAll() {
		for (map<Vertex, list<Edge>>::iterator it = graph.begin(); it != graph.end(); ++it) {
			cout << it->first.key << ": ";
			printNeighbors(it->first.key);
			cout << endl;
		}
	}

private:

	list<Vertex> vertices;
	map<Vertex, list<Edge>> graph;
};
***/
class Graph
{
public:
	Graph() {}							//default constructor
	~Graph() { graph.clear(); }		//destructor

	void addv(string key) {
		graph[key] = Vertex(key);
	}

	bool delv(string key) {
		while (!graph[key].edgeList.empty()) {			//iterate through all edge's on vertex
			Edge edge = graph[key].edgeList.front();
			edge.source->edgeList.remove(edge);			//remove edge from follower's list
			edge.target->edgeList.remove(edge);			//remove edge from followee's list
		}
		graph.erase(key);						//remove key from map
		return true;
	}

	bool adde(string v1, string v2) {
		//check that both writer's exist in graph and aren't the same writer
		if (!graph.count(v1)) return false;
		if (!graph.count(v2)) return false;
		if (v1 == v2) return false;

		Edge edge(&graph[v1], &graph[v2]);

		//looks through vertex with less followers and looks for existing edge
		list<Edge> edgeList = graph[(graph[v1].edgeList.size() < graph[v2].edgeList.size()) ? v1 : v2].edgeList;
		bool exists = false;
		for (list<Edge>::iterator it = edgeList.begin(); it != edgeList.end(); ++it) {
			if (*it == edge) return false;
		}

		//if edge doesn't already exist...
		graph[v1].edgeList.push_back(edge);		//add to source's list of edges
		graph[v2].edgeList.push_back(edge);		//add to target's list of edges
		return true;
	}

	bool dele(string v1, string v2) {
		//verify that vertices exist
		if (!graph.count(v1)) return false;
		if (!graph.count(v2)) return false;

		Edge edge(&graph[v1], &graph[v2]);
		graph[v1].edgeList.remove(edge);
		graph[v2].edgeList.remove(edge);
		return true;
	}

	void printNeighbors(string key) {
		if (!graph.count(key)) { return; }
		for (list<Edge>::iterator it = graph[key].edgeList.begin(); it != graph[key].edgeList.end(); ++it) {
			if (it->source->key == key) cout << it->target->key << ' ';
		}
	}

	void printFollowers(string key) {
		if (!graph.count(key)) { cout << "ERROR"; return; }
		for (list<Edge>::iterator it = graph[key].edgeList.begin(); it != graph[key].edgeList.end(); ++it) {
			if (it->target->key == key) cout << it->source->key << ' ';
		}
	}

	list<string> printAllReached(string key, bool recursive = false) {
		list<string> keys;
		if (recursive == false) {		//on first run, check that key exists and set all vertices' reached flags to false
			if (!graph.count(key)) {
				cout << "ERROR";
				return list<string>();
			}
			for (map<string, Vertex>::iterator it = graph.begin(); it != graph.end(); ++it) it->second.reached = false;
			graph[key].reached = true;
		}
		keys.push_back(key);
		for (list<Edge>::iterator it = graph[key].edgeList.begin(); it != graph[key].edgeList.end(); ++it) {
			if (it->source->key == key && !it->target->reached) {
				it->target->reached = true;
				list<string> newKeys = printAllReached(it->target->key, true);
				keys.merge(newKeys);
			}
		}
		if (recursive == false) {
			for (list<string>::iterator it = keys.begin(); it != keys.end(); ++it) cout << *it << ' ';
		}
		return keys;
	}

	void printAll() {
		for (map<string, Vertex>::iterator it = graph.begin(); it != graph.end(); ++it) {
			cout << it->first << ": ";
			printNeighbors(it->first);
			cout << endl;
		}
	}

private:

	map<string, Vertex> graph;
};
