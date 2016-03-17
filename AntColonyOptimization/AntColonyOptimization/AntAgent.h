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

	void Go(TileMap& oldMap, TileMap& newMap, sf::Vector2i startPos);
	bool FindFeed(TileMap& map, sf::Vector2i start);
	void MarkPath(TileMap& newMap);

private:
	std::vector<sf::Vector2i> m_path;
	double m_alpha;
	double m_beta;
	//const double m_Eps = 1e-250;

	sf::Vector2i MakeDecision(TileMap& map, sf::Vector2i position);
	std::vector<sf::Vector2i> GetUnvisited(TileMap& map, sf::Vector2i position);
	static bool DecisionTableGetLower(const DecisionEntry &e1, const DecisionEntry &e2);
	
};

