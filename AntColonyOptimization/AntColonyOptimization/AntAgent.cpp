#include "AntAgent.h"

#include "TileMap.h"

AntAgent::AntAgent()
{
}


AntAgent::~AntAgent()
{
}

void AntAgent::Go(TileMap& map, sf::Vector2i startPos)
{
	
}

sf::Vector2i AntAgent::MakeDecision(TileMap& map, sf::Vector2i position)
{
	auto nextTiles = GetUnvisited(map, position);
	if (nextTiles.size() == 0)
	{
		return position;
	}
	if (nextTiles.size() == 1)
	{
		return nextTiles.at(0);
	}

	for (auto tile : nextTiles)
	{
		auto pheromone = map.GetPheromone(tile);
		auto heuristic = 1 / map.Distance(position, tile);
		auto result = pow(pheromone, m_alpha) * pow(heuristic, m_beta);
	}
//https://github.com/bolek117/Ant-Colony/blob/master/main.cpp

}

std::vector<sf::Vector2i> AntAgent::GetUnvisited(TileMap& map, sf::Vector2i position)
{
	std::vector<sf::Vector2i> result;
	result.reserve(6);

	auto neighbours = map.GetNeighbour(position);
	auto found = false;
	for (auto neighbour : neighbours)
	{
		for (auto path : m_path)
		{
			found = false;
			if (neighbour == path)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			result.push_back(neighbour);
		}
	}

	return result;
}

