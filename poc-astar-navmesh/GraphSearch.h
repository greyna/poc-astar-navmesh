#pragma once

#include <vector>
#include <queue>
#include <iostream>

#include "common.h"
#include "Graph.h"


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
	// Contains the edge on the search frontier that have the least cost leading to their destination yet
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

	static double euclidianHeuristic(extra pos1, extra pos2)
	{
		return dist(pos1, pos2);
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

			// Move the edge leading to it from the frontier to the SPT
			m_ShortestPathTree[nextClosestNode] = m_SearchFrontier[nextClosestNode];

			// If the target has been found exit
			if (nextClosestNode == m_iTarget) return;

			for (auto edge : m_graph.getEdges(nextClosestNode)) // For all edges from this node
			{
				// Heuristic cost
				double HCost = euclidianHeuristic(m_graph.getNode(edge.getDest()).getInfo(), m_graph.getNode(m_iTarget).getInfo());

				// Real cost
				double GCost = m_GCosts[nextClosestNode] + edge.getCost();

				// If the node has not been added to the frontier, add it and update the G and F costs
				if (!m_SearchFrontier[edge.getDest()].isValid())
				{
					m_FCosts[edge.getDest()] = GCost + HCost;
					m_GCosts[edge.getDest()] = GCost;

					pq.push(nodeAndCost(edge.getDest(), GCost + HCost));

					m_SearchFrontier[edge.getDest()] = edge;
				}
				// Edge relaxation: If this node is already on the frontier but the cost to get here
				// is cheaper than has been found previously, update the node cost and frontier.
				else if ((GCost < m_GCosts[edge.getDest()]) && (!m_ShortestPathTree[edge.getDest()].isValid()))
				{
					m_FCosts[edge.getDest()] = GCost + HCost;
					m_GCosts[edge.getDest()] = GCost;

					pq.push(nodeAndCost(edge.getDest(), GCost + HCost));

					m_SearchFrontier[edge.getDest()] = edge;
				}
			}
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
		std::list<int> path;

		int nextNode = m_iTarget;
		path.push_front(nextNode);

		while ((nextNode != m_iRoot) && (m_ShortestPathTree[nextNode].isValid()))
		{
			nextNode = m_ShortestPathTree[nextNode].getSrc();
			path.push_front(nextNode);
		}

		return path;
	};

	// Returns the total cost to the target
	double getCostToTarget() const 
	{
		return m_GCosts[m_iTarget];
	};
};
