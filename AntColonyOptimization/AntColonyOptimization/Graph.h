#pragma once
#include "GraphNode.h"

template<typename T>
class Graph
{
public:
	size_t AddNode(const T& data);
	void AddEdge(unsigned int originIndex, unsigned int destinationIndex);

private:
	std::vector<GraphNode<T>> m_nodes;	
	
};

template <typename T>
size_t Graph<T>::AddNode(const T& data)
{
	GraphNode<T> node(data);	
	m_nodes.push_back(node);
	return m_nodes.size() - 1;
}

template <typename T>
void Graph<T>::AddEdge(unsigned originIndex, unsigned destinationIndex)
{
	if (m_nodes.size() < originIndex || m_nodes.size() < destinationIndex)
	{
		return;
	}

	GraphEdge edge(originIndex, destinationIndex);
	m_nodes.at(originIndex).AddEdge(edge);
}

