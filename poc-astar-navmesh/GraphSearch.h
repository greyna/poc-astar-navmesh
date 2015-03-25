#pragma once

#include <vector>
#include <queue>

#include "common.h"
#include "Graph.h"


// TODO take heuristic as a function pointer
template<class extra>
class GraphSearch
{
protected:
	int m_iRoot;
	int m_iTarget;
	const Graph<extra>& m_graph;
	std::vector<double> m_GCosts;
	std::vector<double> m_FCosts;
	std::vector<GraphEdge> m_ShortestPathTree;
	std::vector<GraphEdge> m_SearchFrontier;

	struct nodeAndCost
	{
		int node;
		double cost;

		nodeAndCost(int _node, double _cost) : node(_node), cost(_cost) {};

		// Needed for the priority_queue to sort elements
		bool operator<(const nodeAndCost other) const
		{
			// Inverse comparison to have least cost on the top of the priority_queue
			return (cost > other.cost);
		};
	};
public:
	GraphSearch(Graph<extra> &graph, int root, int target):
		m_graph(graph), m_iRoot(root), m_iTarget(target),
		m_ShortestPathTree(graph.numNodes()), m_SearchFrontier(graph.numNodes()),
		m_GCosts(graph.numNodes(), 0.0), m_FCosts(graph.numNodes(), 0.0)
		{
			search();
		};
	~GraphSearch() {};
	void search()
	{
		// Priority queue of nodes and cost, lowest cost node is at the top
		// Contains nodes on the search frontier (not yet added to the SPT, not yet examined)
		std::priority_queue<nodeAndCost> pq;
		pq.push(nodeAndCost(m_iRoot, 0.0));

		while (!pq.empty())
		{
			int nextClosestNode = pq.top().node;
			pq.pop();
		}
	};

	// Returns the vector of edges that the algorithm has examined
	std::vector<GraphEdge> getSPT() const
	{
		return m_ShortestPathTree;
	};

	// Returns a vector of node indexes that comprise the shortest path from the root to the target node
	std::list<int> getPathToTarget() const
	{
		return std::list<int>();
	};

	// Returns the total cost to the target
	double getCostToTarget() const 
	{
		return m_GCosts[m_iTarget];
	};
};
