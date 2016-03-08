#pragma once
#include <vector>
#include "GraphEdge.h"

template <typename T>
class GraphNode
{
public:
	explicit GraphNode(const T& data) : m_data(data) {}
	void AddEdge(const GraphEdge& edge) { m_edges.push_back(edge); }

private:
	T m_data;
	std::vector<GraphEdge> m_edges;
};

