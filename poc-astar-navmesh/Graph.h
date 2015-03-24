#pragma once

#include <vector>
#include <list>

#include "GraphNode.h"
#include "GraphEdge.h"

template <class extra>
class Graph
{
protected:
	// Vector of all nodes whose index should comply with their vector index
	// Elements can be invalid (their index equals g_INVALID_NODE_INDEX)
	std::vector<GraphNode<extra>> nodes;

	// Vector of adjacency edge lists. Each node has its list of outgoing edges in the vector, using its index.
	std::vector<std::list<GraphEdge>> edges;

	// Next free index for a node in the vector nodes
	// (the first invalid node in the vector, or if no invalid node exists the number of elements in the vector)
	int m_iNextNodeIndex;

	void computeNextFreeNodeIndex()
	{
		unsigned int i = 0;
		for (; i < nodes.size(); i++)
		{
			// If we find an invalid node, we keep its index value into i thanks to the break
			if (!nodes[i].isValid()) break;
			// If not, the value of i should be of the first empty space of the vector
		}
		m_iNextNodeIndex = i;
	};
public:
	Graph() : m_iNextNodeIndex(0) {};
	~Graph() {};

	int getNextFreeNodeIndex() const
	{
		return m_iNextNodeIndex;
	};

	// Adds a node to the graph and returns its index
	int addNode(GraphNode<extra> & node)
	{
		int index = m_iNextNodeIndex;
		node.setIndex(index);
		try
		{
			nodes.at(index) = node;
		}
		catch (...)
		{
			nodes.push_back(node);
			edges.push_back(std::list<GraphEdge>());
		}
		computeNextFreeNodeIndex();
		return index;
	};

	GraphNode<extra>& getNode(int index)
	{
		return nodes.at(index);
	};

	void removeNode(int node)
	{
		nodes[node].setIndex(g_INVALID_NODE_INDEX);
		computeNextFreeNodeIndex();
	};

	void addEdge(GraphEdge edge)
	{
		edges[edge.getSrc()].push_back(edge);
		GraphEdge bidirectionalEdge(edge.getDest(), edge.getSrc(), edge.getCost());
		edges[edge.getDest()].push_back(bidirectionalEdge);
	};

	GraphEdge getEdge(int src, int dest)
	{
		for (auto edge : edges[src])
		{
			if (edge.getDest() == dest) return edge;
		}

		throw;
	};

	void removeEdge(int src, int dest)
	{
		for (auto edge : edges[src])
		{
			if (edge.getDest() == dest)
			{
				edges[src].remove(edge);
				break; // break is mandatory here because we modify the list inside a loop through it
			}
		}

		// remove bidirectionnal edge
		for (auto edge : edges[dest])
		{
			if (edge.getSrc() == src)
			{
				edges[dest].remove(edge);
				break; // break is mandatory here because we modify the list inside a loop through it
			}
		}
	};
};

