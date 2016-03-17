#include "Tile.h"

#include <SFML/Graphics/RectangleShape.hpp>

Tile::Tile(unsigned int row, unsigned int col, TerrainType terrain)
	: m_terrain(terrain)
	, m_type(NOTHING)
	, m_position(col, row)
	, m_pheromone(0.0f)
{
	m_shape.setRadius(m_ShapeRadius);
	m_shape.setPointCount(6);
	m_shape.setPosition(ComputePosition(row, col));
	m_shape.setOrigin(m_ShapeRadius, m_ShapeRadius);
	m_shape.setFillColor(ComputeColor(terrain));
	m_shape.setOutlineColor(sf::Color::Blue);
}

Tile::~Tile()
{
}

bool Tile::ContainMousePos(sf::Vector2f mousePos) const
{
	return m_shape.getGlobalBounds().contains(mousePos);
}

void Tile::Render(sf::RenderWindow& window)
{
	window.draw(m_shape);

	if (m_type == FEED)
	{
		RenderFeed(window);
	}
	else if (m_type == NEST)
	{
		RenderNest(window);
	}
}

void Tile::SetBorder()
{
	m_shape.setOutlineThickness(2.0f);
}

void Tile::UnsetBorder()
{
	m_shape.setOutlineThickness(0.0f);
}

TileType Tile::GetType() const
{
	return m_type;
}

void Tile::SetType(TileType newType)
{
	m_type = newType;
}

float Tile::GetPheromone() const
{
	return m_pheromone;
}

sf::Vector2f Tile::ComputePosition(unsigned int row, unsigned int col) const
{
	sf::Vector2f position;
		
	auto offset = m_ShapeRadius;

	position.x = m_ShapeRadius * 2 * col + offset;
	if ((row % 2) != 0)
		position.x += m_ShapeRadius;

	position.y = m_ShapeRadius * 2 * row + offset;

	return position;
}

sf::Color Tile::ComputeColor(TerrainType type)
{
	switch (type)
	{
	case STREET: 
		return sf::Color(192, 186, 153);
	case GRASS: 
		return sf::Color(166, 200, 64);
	case HIGHGRASS: 
		return sf::Color(64, 69, 25);
	case SWAMPLAND: 
		return sf::Color(78, 62, 21);
	case WATER: 
		return sf::Color(21, 104, 156);
	case HILL: 
		return sf::Color(161, 64, 5);
	case MOUNTAIN:
		return sf::Color(128, 128, 128);
	default: 
		return sf::Color::White;
	}

	
}

int Tile::ComputeWeight(TerrainType type)
{
	switch (type)
	{
	case STREET:
		return 2;
	case GRASS:
		return 4;
	case HIGHGRASS:
		return 5;
	case SWAMPLAND:
		return 7;
	case WATER:
		return 9;
	case HILL:
		return 10;
	case MOUNTAIN:
		return 9999;
	default:
		return -1;
	}
}

void Tile::RenderFeed(sf::RenderWindow& window)
{
	sf::RectangleShape box(sf::Vector2f(10.0f, 10.0f));
	box.setPosition(m_shape.getPosition());
	box.setOrigin(5.0f, 5.0f);
	box.setFillColor(sf::Color::Blue);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.0f);

	window.draw(box);
}

void Tile::RenderNest(sf::RenderWindow& window)
{
	sf::CircleShape circle(10.0f);
	circle.setPosition(m_shape.getPosition());
	circle.setOrigin(10.0f, 10.0f);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineColor(sf::Color::Black);
	circle.setOutlineThickness(2.0f);

	window.draw(circle);
}
