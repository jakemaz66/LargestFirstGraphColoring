// Largest First Graph Coloring.cpp : Defines the entry point for the console application.
//
//************************************************************
// Jacob Mazurkiewicz
//   Program #7
//  due 4/4/2023
//   This program contains an implementation of the graph
//   data structure and an implementation of the largest
//   first graph-coloring algorithm
//************************************************************

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include<string>
#include<deque>
#include <stack>
#include <algorithm>
#include <functional>
using namespace std;

class Edge {
public:
	int DestId;

	Edge() {

	}

	Edge(int dest) {
		DestId = dest;
	}

	//Setters
	void setEdges(int dest) {
		DestId = dest;
	}

	//Getters
	int returnID() {
		return DestId;
	}


};

//Vertex class that holds an ID of the vertex, the current Distance variable for algorithm processing, a name, and a list of the vertex's edges
class Vertex {
public:
	int vertexId;
	int color;
	string name;
	int numConnections = 0;

	//Creating a list containing all edges
	list<Edge> edges;

	Vertex() {
		vertexId = 0;
		name = "";
	}

	Vertex(int vId, string vName) {
		vertexId = vId;
		name = vName;
	}

	//Getters
	int returnId() {
		return vertexId;
	}

	string returnName() {
		return name;
	}

	int returnColor() {
		return color;
	}

	int returnConnection() {
		return numConnections;
	}

	list<Edge> returnEdges() {
		return edges;
	}

	//Setters
	void setId(int vId) {
		vertexId = vId;
	}

	void setName(string vName) {
		name = vName;
	}

	void setColor(int vertexColor) {
		color = vertexColor;
	}

	//Function to print the edges of a vertex
	void printEdgeList() {
		cout << "[";
		for (auto it = edges.begin(); it != edges.end(); it++) {
			cout << it->returnID() << "("  << ") --> ";
		}
		cout << "]";
		cout << endl;
	}

	//Function to return number of edges of vertex
	void updateConnections() {
		numConnections++;
	}


};


//Graph class which assembles the verticies and contains functions for assembling graph; also holds a vector of all verticies
class Graph {
public:
	//Storing all Verticies
	vector<Vertex*> verticies;

	//Check if vertex exists function
	bool vertexCheck(int vId) {
		bool exists = false;

		for (int i = 0; i < verticies.size(); i++) {
			if (verticies.at(i)->returnId() == vId)
				exists = true;
		}
		return exists;
	}

	//Adding a vertex to graph
	void addVertex(Vertex* vert) {
		//Check if vertex already exists
		bool exists = vertexCheck(vert->returnId());

		if (exists == true)
			return;
		else {
			verticies.push_back(vert);
		}
	}

	//Returns a vertex when given an ID
	Vertex getVertex(int vId) {
		Vertex* temp;
		for (int i = 0; i < verticies.size(); i++) {
			temp = verticies.at(i);
			if (temp->returnId() == vId) {
				return *temp;
			}
		}
		return *temp;
	}

	//Function to check if edge already exists
	bool edgeCheck(int sourceVertex, int destVertex) {
		Vertex v = getVertex(sourceVertex);

		list<Edge> edges;
		edges = v.returnEdges();

		bool exists = false;

		for (auto it = edges.begin(); it != edges.end(); it++)

			if (it->returnID() == destVertex) {
				exists = true;
				return exists;
				break;
			}

		return exists;
	}

	//Add edges from verticies, source and dest Vertex are ID's, weight is weight of edge
	void addEdge(int sourceVertex, int destVertex) {
		
		//Updating Connections
		for (int i = 0; i < verticies.size(); i++) {
			if (verticies.at(i)->returnId() == sourceVertex)
				verticies.at(i)->updateConnections();
			else if (verticies.at(i)->returnId() == destVertex)
				verticies.at(i)->updateConnections();
		}

		bool exists1 = vertexCheck(sourceVertex);
		bool exists2 = vertexCheck(destVertex);

		//If both verticies passed through are valid
		if (exists1 && exists2 == true) {

			//Checks if edge already exists
			bool edgeExists = edgeCheck(sourceVertex, destVertex);

			//If the enetred edge already exists
			if (edgeExists == true)
				return;
			

			//Adding the edge after checks
			for (int i = 0; i < verticies.size(); i++) {

			
				//If the iterated vertex matches the source vertex
				if (verticies.at(i)->returnId() == sourceVertex) {


					//Create new edge object with a destination of 'destVertex' and a weight of 'weight'
					Edge edge(destVertex);

					//Add the edge to the list of edges 'edges'
					verticies.at(i)->edges.push_back(edge);
					//verticies.at(i)->edges.sort();
					
				}
				else if (verticies.at(i)->returnId() == destVertex) {
					Edge edge(sourceVertex);

					verticies.at(i)->edges.push_back(edge);
					//verticies.at(i)->edges.sort();
				}

			}
		}
		else
			//If any of the verticies passed through are invalid
			return;
	}

	//Function to print the graph - prints the verticies and correpsonding edges
	void printGraph() {
		for (int i = 0; i < verticies.size(); i++) {
			Vertex* temp;
			temp = verticies.at(i);
			cout << temp->returnName() << " (" << temp->returnId() << ") --> ";
			temp->printEdgeList();
		}
	}

	//Function to return the neighbors (Adjacent) verticies as a vector object (passed as an ID)
	vector<int> getAdjacentVerticies(int vId) {

		vector<int> adjacentVerticies;

		for (int i = 0; i < verticies.size(); i++) {
			if (verticies.at(i)->returnId() == vId) {
				for (auto it = verticies.at(i)->edges.begin(); it != verticies.at(i)->edges.end(); it++) {
					adjacentVerticies.push_back(it->returnID());
				}
			}
		}

		return adjacentVerticies;
	}

	//Function to print the adjacent verticies
	void printAdjacentVerticies(int vId) {
		cout << getVertex(vId).returnName() << " (" << getVertex(vId).returnId() << ") --> ";
		for (int i = 0; i < verticies.size(); i++) {
			if (verticies.at(i)->returnId() == vId) {
				cout << "[";
				for (auto it = verticies.at(i)->edges.begin(); it != verticies.at(i)->edges.end(); it++) {
					cout << it->returnID() << "(" << ") --> ";
				}
				cout << "]";
			}
		}
	}

};

void largestFirstColoringAlgorithm(Graph graph) {
	//Getting the verticies in order, with the one with most connections going first
	//Making stack to hold order of verticies
	stack<Vertex*> VertStack;

	//Making a vector of possible colors for the verticies
	list<int> colors;
	
	//Printing out the Verticies and their connections
	for (int i = 0; i < graph.verticies.size(); i++) {
		colors.push_back(i);

		cout << "Vertex: " << graph.verticies.at(i)->returnName() << " Connections: " << graph.verticies.at(i)->returnConnection() << " ";
	}

	//Adding onto the stack in largest first order
	int count = 0;
	while (VertStack.size() != graph.verticies.size()) {
		for (int i = graph.verticies.size() - 1; i >= 0; i--) {
			if (graph.verticies.at(i)->returnConnection() == count) {
				VertStack.push(graph.verticies.at(i));
			}
		}
		count++;
	}

	//Making vector and bool to remove duplicate processing
	vector<int> processed;
	bool proc;

	//Going through vertex stack
	while (VertStack.size() != 0) {
		int pos = 0;
		Vertex* v = VertStack.top();
		v->setColor(0);

		cout << endl << "Current Vertex Processing: " << v->returnName() << " ";

		processed.clear();

		//v->edges.sort();
		//Iterating through adjacent verticies of v
		for (list<Edge>::iterator i = v->edges.begin(); i != v->edges.end(); i++) {
			
			
			proc = false;

			Vertex* u = graph.verticies.at(i->DestId);

			for (int i = 0; i < processed.size(); i++) {
				if (u->returnColor() == processed.at(i))
					proc = true;
			}

			//If vertex of same color has already been processed
			if (proc == true)
				continue;

			processed.push_back(u->returnColor());

			//Advance position in color list
			for (int i = 0; i < colors.size(); i++) {

				if (u->returnColor() == colors.front() + i && v->returnColor() >= colors.front() + i) {
					pos++;
					v->color = colors.front() + pos;
					
				}

				cout << endl << "Processing adjacent vertex of " << v->returnName() << ": " << u->returnName() << " ";

			}
		}

		//Assign color to v, then pop off stack
		VertStack.pop();

	}


	//printing out the colors
	cout << endl << "These are the colors of the verticies: " << endl;
	for (int i = 0; i < graph.verticies.size(); i++) {
		cout << graph.verticies.at(i)->returnName() << " color: " << graph.verticies.at(i)->returnColor() << endl;

	}
	
}


int main()
{
	//Graph graph1;
	Graph graph2;

	
	Vertex v1;
	v1.setId(0);
	v1.setName("a");

	Vertex v2;
	v2.setId(1);
	v2.setName("b");

	Vertex v3;
	v3.setId(2);
	v3.setName("c");


	//Adding verticies to graph object
	//graph1.addVertex(v1P);
	//graph1.addVertex(v2P);
	//graph1.addVertex(v3P);

	//Adding Edges
	//graph1.addEdge(v1P->returnId(), v3P->returnId());
	
	//largestFirstColoringAlgorithm(graph1);

	Vertex v4;
	v4.setId(3);
	v4.setName("d");

	Vertex v5;
	v5.setId(4);
	v5.setName("e");

	Vertex v6;
	v6.setId(5);
	v6.setName("f");

	Vertex v7;
	v7.setId(6);
	v7.setName("g");

	Vertex v8;
	v8.setId(7);
	v8.setName("h");

	Vertex* v1P = &v1;
	Vertex* v2P = &v2;
	Vertex* v3P = &v3;
	Vertex* v4P = &v4;
	Vertex* v5P = &v5;
	Vertex* v6P = &v6;
	Vertex* v7P = &v7;
	Vertex* v8P = &v8;

	//Adding verticies to graph 2
	graph2.addVertex(v1P);
	graph2.addVertex(v2P);
	graph2.addVertex(v3P);
	graph2.addVertex(v4P);
	graph2.addVertex(v5P);
	graph2.addVertex(v6P);
	graph2.addVertex(v7P);
	graph2.addVertex(v8P);

	graph2.addEdge(v1P->returnId(), v5P->returnId());
	graph2.addEdge(v1P->returnId(), v7P->returnId());
	graph2.addEdge(v1P->returnId(), v6P->returnId());
	graph2.addEdge(v2P->returnId(), v5P->returnId());
	graph2.addEdge(v2P->returnId(), v8P->returnId());
	graph2.addEdge(v3P->returnId(), v7P->returnId());
	graph2.addEdge(v4P->returnId(), v6P->returnId());
	graph2.addEdge(v4P->returnId(), v7P->returnId());
	graph2.addEdge(v6P->returnId(), v7P->returnId());
	graph2.addEdge(v6P->returnId(), v8P->returnId());
	graph2.addEdge(v7P->returnId(), v8P->returnId());
	graph2.addEdge(v2P->returnId(), v3P->returnId());


	graph2.printGraph();

	largestFirstColoringAlgorithm(graph2);

    return 0;
}

