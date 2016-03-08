#pragma once
class GraphEdge
{
public:
	GraphEdge(const int origin, const int destination) : m_origin(origin), m_destination(destination) {}

private:
	const int m_origin;
	const int m_destination;
};

