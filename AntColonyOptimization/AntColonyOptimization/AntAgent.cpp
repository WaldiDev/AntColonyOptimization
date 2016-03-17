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

std::vector<int> AntAgent::GetUnvisited(TileMap& map, sf::Vector2i startPos)
{
	std::vector<int> result;
	result.reserve(6);

	auto neighbours = map.GetNeighbour(startPos);

	return result;
}

