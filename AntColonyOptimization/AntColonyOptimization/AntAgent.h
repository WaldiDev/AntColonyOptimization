#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
class TileMap;

struct DecisionEntry
{
	sf::Vector2i index;
	double coefficient;
};

class AntAgent
{
public:
	AntAgent(double alpha, double beta);
	~AntAgent();

	bool FindFeed(TileMap& map, sf::Vector2i start);
	void MarkPath(TileMap& newMap);

private:
	std::vector<sf::Vector2i> m_path;
	double m_alpha;
	double m_beta;
	
	sf::Vector2i MakeDecision(TileMap& map, sf::Vector2i position);
	std::vector<sf::Vector2i> GetUnvisited(TileMap& map, sf::Vector2i position);
		
};

