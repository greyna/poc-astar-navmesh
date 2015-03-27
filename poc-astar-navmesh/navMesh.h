#pragma once

#include "common.h"
#include "Graph.h"

// Clears the graph then add the nodes and edges accordingly to the navmesh
void navMeshToGraph(const std::vector<Triangle>& navMesh, Graph<Vec2f>& graph,
	Vec2f root, Vec2f target, int& rootNodeIndex, int& targetNodeIndex)
{
	graph.clear();
	for (auto t : navMesh)
	{
		GraphNode<Vec2f> n1, n2, n3;
		n1.setInfo(new Vec2f(t.p1));
		n2.setInfo(new Vec2f(t.p2));
		n3.setInfo(new Vec2f(t.p3));

		graph.addNode(n1);
		graph.addNode(n2);
		graph.addNode(n3);

		GraphEdge e12(n1.getIndex(), n2.getIndex(), dist(t.p1, t.p2));
		GraphEdge e13(n1.getIndex(), n3.getIndex(), dist(t.p1, t.p3));
		GraphEdge e23(n2.getIndex(), n3.getIndex(), dist(t.p2, t.p3));

		graph.addEdge(e12);
		graph.addEdge(e13);
		graph.addEdge(e23);

		if (t.contains(root))
		{
			GraphNode<Vec2f> n0;
			n0.setInfo(new Vec2f(root));
			graph.addNode(n0);
			rootNodeIndex = n0.getIndex();

			GraphEdge e01(n0.getIndex(), n1.getIndex(), dist(root, t.p1));
			GraphEdge e02(n0.getIndex(), n2.getIndex(), dist(root, t.p2));
			GraphEdge e03(n0.getIndex(), n3.getIndex(), dist(root, t.p3));

			graph.addEdge(e01);
			graph.addEdge(e02);
			graph.addEdge(e03);
		}

		if (t.contains(target))
		{
			GraphNode<Vec2f> n0;
			n0.setInfo(new Vec2f(target));
			graph.addNode(n0);
			targetNodeIndex = n0.getIndex();

			GraphEdge e01(n0.getIndex(), n1.getIndex(), dist(target, t.p1));
			GraphEdge e02(n0.getIndex(), n2.getIndex(), dist(target, t.p2));
			GraphEdge e03(n0.getIndex(), n3.getIndex(), dist(target, t.p3));

			graph.addEdge(e01);
			graph.addEdge(e02);
			graph.addEdge(e03);
		}
	}
};