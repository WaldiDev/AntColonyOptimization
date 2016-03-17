#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
class TileMap;

class AntAgent
{
public:
	AntAgent();
	~AntAgent();

	void Go(TileMap& map, sf::Vector2i startPos);

private:
	std::vector<sf::Vector2i> m_path;
	float m_alpha = 0.0f;
	float m_beta = 0.0f;

	sf::Vector2i MakeDecision(TileMap& map, sf::Vector2i position);
	std::vector<sf::Vector2i> GetUnvisited(TileMap& map, sf::Vector2i position);
	
};

