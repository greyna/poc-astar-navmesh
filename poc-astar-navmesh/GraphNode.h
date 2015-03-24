#pragma once

#include "common.h"
#include <memory>

template <class extra>
class GraphNode
{
protected:
	// The index of the node, always >=0 if valid
	int m_iIndex;
	// A pointer to extra information for this node
	std::shared_ptr<extra> info;

public:
	GraphNode() : m_iIndex(g_INVALID_NODE_INDEX) {};
	GraphNode(int index) : m_iIndex(index) {};
	~GraphNode() {};

	int getIndex() const
	{
		return m_iIndex;
	};

	void setIndex(int newIndex)
	{
		m_iIndex = newIndex;
	};

	extra& getInfo() const
	{
		return *info;
	};

	// When using this setter, the node gets ownership of the memory in the extra
	void setInfo(extra* newInfo)
	{
		info = std::move(std::shared_ptr<extra>(newInfo));
	};

	bool isValid() const
	{
		return (m_iIndex > g_INVALID_NODE_INDEX);
	};
};

