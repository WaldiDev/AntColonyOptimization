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
	std::vector<int> m_path;

	std::vector<int> GetUnvisited(TileMap& map, sf::Vector2i startPos);
};

