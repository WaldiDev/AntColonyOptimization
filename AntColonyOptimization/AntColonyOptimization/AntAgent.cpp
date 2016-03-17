#include "AntAgent.h"

#include "TileMap.h"
#include "RandomNumberGenerator.h"

AntAgent::AntAgent(double alpha, double beta)
	: m_alpha(alpha)
	, m_beta(beta)
{
}

AntAgent::~AntAgent()
{
}

void AntAgent::Go(TileMap& oldMap, TileMap& newMap, sf::Vector2i startPos)
{	
	m_path.clear();
	
	// Travesierungsphase
	m_path.push_back(startPos);
	while (true)
	{
		auto currentPos = m_path.at(m_path.size() - 1);
		auto nextPos = MakeDecision(oldMap, currentPos);
		if (nextPos != currentPos)
		{
			m_path.push_back(nextPos);
		}
		else
		{
			break;
		}		
	}

	// Makierungsphase
	auto length = m_path.size();
	auto manhatten = oldMap.Distance(m_path.at(0), m_path.at(length - 1));
	auto pheromone = manhatten / length;

	for (auto& tile : m_path)
	{
		newMap.AddPheromone(tile, pheromone);
	}
}

bool AntAgent::FindFeed(TileMap& map, sf::Vector2i start)
{
	m_path.push_back(start);
	auto currentTile = start;

	while (map.GetTileType(currentTile) != FEED)
	{
		auto newTile = MakeDecision(map, currentTile);
		if (newTile == currentTile)
		{
			return false;
		}

		m_path.push_back(newTile);
		currentTile = newTile;
	}

	return true;
}

void AntAgent::MarkPath(TileMap& newMap)
{
	auto pathLength = m_path.size();
	auto manhattanDistance = newMap.Distance(m_path.at(0), m_path.at(pathLength - 1));
	auto pheromone = manhattanDistance / static_cast<double>(pathLength);

	for (auto index : m_path)
	{
		newMap.AddPheromone(index, pheromone);
	}
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

	double neighbourSum = 0;
	std::vector<DecisionEntry> decisionTable;
	for (auto tile : nextTiles)
	{
		auto pheromone = map.GetPheromone(tile);
		auto heuristic = 1 / static_cast<double>(map.GetWeight(tile));
		auto result = pow(pheromone, m_alpha) * pow(heuristic, m_beta);

		DecisionEntry entry;
		entry.index = tile;
		entry.coefficient = result;

		neighbourSum += result;
		decisionTable.push_back(entry);
	}

	/*if (neighbourSum < m_Eps)
	{
		return position;
	}*/

	for (auto& decision : decisionTable)
	{
		decision.coefficient /= neighbourSum;
	}

	sort (decisionTable.begin(), decisionTable.end(), DecisionTableGetLower);
	
	auto random = RandomNumberGenerator::GetRandom();
	
	double sumCoefficient = 0;
	for (auto decision : decisionTable)
	{
		sumCoefficient += decision.coefficient;
		if (sumCoefficient > random)
		{
			return decision.index;
		}
	}

	return position;
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

bool AntAgent::DecisionTableGetLower(const DecisionEntry &e1, const DecisionEntry &e2)
{
	if (e1.coefficient < e2.coefficient)
	{
		return true;
	}		
	
	return false;
}
