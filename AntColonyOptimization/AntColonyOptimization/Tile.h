#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum TileType
{
	STREET = 1,
	GRASS = 2,
	HIGHGRASS = 3,
	SWAMPLAND = 4,
	WATER = 5,
	HILL = 6,
	MOUNTAIN = 7
};

class Tile
{
public:
	Tile(unsigned int row, unsigned int col, TileType type);
	~Tile();

	void Render(sf::RenderWindow& window);
private:
	TileType m_type;
	sf::CircleShape m_shape;

	const float m_ShapeRadius = 20.0f;

	sf::Vector2f ComputePosition(unsigned int row, unsigned int col) const;
	sf::Color ComputeColor(TileType type) const;
};

