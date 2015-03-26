#include <iostream>

#include "common.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "Graph.h"
#include "GraphSearch.h"


void testGraph();
void testComplexGraph();

int main()
{
	std::cout << "\n=== A* and NavMesh POC for the Ubisoft Graduate Program 2015 at Annecy ===\n" << std::endl;

	testGraph();
	testComplexGraph();

	std::cout << "\n\n=== Correctly finished ===\n" << std::endl;

	char stop;
	std::cin >> stop;
	return 0;
}

void testGraph()
{
	GraphNode<Vec2f> n;
	n.setInfo(new Vec2f(3.0f, 4.0f));

	GraphNode<Vec2f> n2;
	n2.setInfo(new Vec2f(4.0f, 4.0f));

	GraphEdge e(0, 1, 2.2f);

	Graph<Vec2f> g;

	g.addNode(n);
	g.addNode(n2);
	g.addEdge(e);

	g.getNode(0);
	g.getNode(1);
	g.getEdge(0, 1);
	g.removeNode(0);
	g.removeNode(1);
	g.removeEdge(0, 1);
	g.addNode(n2);
	g.addNode(n);
	g.addEdge(e);
}


void testComplexGraph()
{
	Graph<Vec2f> graph;

	GraphNode<Vec2f> a; // index 0
	a.setInfo(new Vec2f(0.0f, 0.0f));
	GraphNode<Vec2f> b; // index 1
	b.setInfo(new Vec2f(0.0f, 1.0f));
	GraphNode<Vec2f> x; // index 2
	x.setInfo(new Vec2f(1.0f, 1.0f));
	GraphNode<Vec2f> f; // index 3
	f.setInfo(new Vec2f(2.0f, 1.0f));
	GraphNode<Vec2f> g; // index 4
	g.setInfo(new Vec2f(2.0f, 0.0f));
	GraphNode<Vec2f> d1; // Root node index 5
	d1.setInfo(new Vec2f(0.2f, 0.4f));
	GraphNode<Vec2f> a1; // Target node index 6
	a1.setInfo(new Vec2f(1.8f, 0.4f));

	GraphEdge ab(0, 1);
	GraphEdge ax(0, 2);
	GraphEdge bx(1, 2);
	GraphEdge xf(2, 3);
	GraphEdge xg(2, 4);
	GraphEdge fg(3, 4);

	GraphEdge d1x(5, 2, 0.8);
	GraphEdge d1b(5, 1, 0.2);
	GraphEdge d1a(5, 0, 0.1);
	GraphEdge a1x(6, 2, 0.8);
	GraphEdge a1f(6, 3, 0.5);
	GraphEdge a1g(6, 4, 0.1);

	graph.addNode(a);
	graph.addNode(b);
	graph.addNode(x);
	graph.addNode(f);
	graph.addNode(g);
	graph.addNode(d1);
	graph.addNode(a1);

	graph.addEdge(ab);
	graph.addEdge(ax);
	graph.addEdge(bx);
	graph.addEdge(xf);
	graph.addEdge(xg);
	graph.addEdge(fg);

	graph.addEdge(d1x);
	graph.addEdge(d1b);
	graph.addEdge(d1a);
	graph.addEdge(a1x);
	graph.addEdge(a1f);
	graph.addEdge(a1g);

	GraphSearch<Vec2f> astar(graph, d1.getIndex(), a1.getIndex());
	astar.getCostToTarget();
	astar.getSPT();

	std::cout << "Path to target: ";
	for (auto node : astar.getPathToTarget())
	{
		if (node!=6) std::cout << node << " -> ";
		else std::cout << node << std::endl; // target
	}
}