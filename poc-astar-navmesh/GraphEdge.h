#pragma once

#include <iostream>

#include "common.h"

class GraphEdge
{
protected:
	// Index of the source and destination nodes
	int m_iSrc;
	int m_iDest;
	// Cost of the edge
	double m_dCost;

public:
	GraphEdge(int srcNode, int destNode, double cost) : m_iSrc(srcNode), m_iDest(destNode), m_dCost(cost) {};
	GraphEdge(int srcNode, int destNode) : m_iSrc(srcNode), m_iDest(destNode), m_dCost(1.0) {};
	GraphEdge() : m_iSrc(g_INVALID_NODE_INDEX), m_iDest(g_INVALID_NODE_INDEX), m_dCost(1.0) {};
	~GraphEdge() {};

	int getSrc() const
	{
		return m_iSrc;
	};

	int getDest() const
	{
		return m_iDest;
	};

	double getCost() const
	{
		return m_dCost;
	}

	void setSrc(int srcNode)
	{
		m_iSrc = srcNode;
	};

	void setDest(int destNode)
	{
		m_iDest = destNode;
	};

	void setCost(double cost)
	{
		m_dCost = cost;
	};

	bool isValid() const
	{
		return ((m_iSrc != g_INVALID_NODE_INDEX) || (m_iDest != g_INVALID_NODE_INDEX));
	};

	// For use in list
	bool operator==(const GraphEdge& rhs)
	{
		return rhs.m_iSrc == this->m_iSrc &&
			rhs.m_iDest == this->m_iDest   &&
			rhs.m_dCost == this->m_dCost;
	};

	bool operator!=(const GraphEdge& rhs)
	{
		return !(*this == rhs);
	};

	friend std::ostream& operator<<(std::ostream& os, const GraphEdge& e)
	{
		os << "source: " << e.m_iSrc << " destination: " << e.m_iDest
			<< " cost: " << e.m_dCost << std::endl;

		return os;
	}
};

