#pragma once

template <class extra>
class GraphNode
{
protected:
	int m_iIndex;
	extra* info;

public:
	static const int INVALID_INDEX = -1;
	GraphNode() : m_iIndex(INVALID_INDEX) {};
	GraphNode(int index) : m_iIndex(index) {};
	~GraphNode() {};

	// return the index of the node
	int getIndex() const {
		return m_iIndex;
	};
	// sets a new index for the node
	void setIndex(int newIndex) {
		m_iIndex = newIndex;
	};
	// return the info associated with this node
	extra* getInfo() const {
		return info;
	}
	// sets the info associated with this node
	void setInfo(extra* newInfo) {
		info = newInfo;
	}
};

