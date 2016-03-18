#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum TerrainType
{
	STREET = 1,
	GRASS = 2,
	HIGHGRASS = 3,
	SWAMPLAND = 4,
	WATER = 5,
	HILL = 6,
	MOUNTAIN = 7
};

enum TileType
{
	NOTHING = 1,
	FEED = 2,
	NEST = 3
};

class Tile
{
public:
	Tile(unsigned int row, unsigned int col, unsigned int pCol, TerrainType terrain);
	~Tile();

	bool ContainMousePos(sf::Vector2f mousePos) const;
	void Render(sf::RenderWindow& window, bool grey);

	void SetBorder();
	void UnsetBorder();
	TileType GetType() const;
	void SetType(TileType newType);

	double GetPheromone() const;
	int GetWeight() const;

	void AddPheromone(double pheromone);
	void SetPheromone(double pheromone);
	void Evaporation(double rho);

private:
	TerrainType m_terrain;
	TileType m_type;
	sf::CircleShape m_shape;
	sf::Vector2i m_position;
	const double m_ShapeRadius = 20.0f;
	double m_pheromone;
	int m_weight;
	static bool drawGrey;

	sf::Vector2f ComputePosition(unsigned int row, unsigned int col) const;
	static sf::Color ComputeColor(TerrainType type);
	static int ComputeWeight(TerrainType type);
	void RenderFeed(sf::RenderWindow& window);
	void RenderNest(sf::RenderWindow& window);
};

