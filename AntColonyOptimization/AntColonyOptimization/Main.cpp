#include <iostream>
#include "Graph.h"

int main()
{
	Graph<char> g;
	g.AddNode('A');
	g.AddNode('B');
	g.AddNode('C');
	g.AddNode('D');
	g.AddNode('E');
	g.AddNode('F');
	g.AddNode('G');

	g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(0, 3);
	g.AddEdge(0, 4);
	g.AddEdge(0, 5);
	g.AddEdge(0, 6);



	return 0;
}
