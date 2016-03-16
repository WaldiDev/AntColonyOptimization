#include "Tile.h"

Tile::Tile(unsigned int row, unsigned int col, TileType type)
	: m_type(type)
{
	m_shape.setRadius(m_ShapeRadius);
	m_shape.setPointCount(6);
	m_shape.setPosition(ComputePosition(row, col));
	m_shape.setOrigin(m_ShapeRadius, m_ShapeRadius);
	m_shape.setFillColor(ComputeColor(type));
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
}

void Tile::SetBorder()
{
	m_shape.setOutlineThickness(2.0f);
}

void Tile::UnsetBorder()
{
	m_shape.setOutlineThickness(0.0f);
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

sf::Color Tile::ComputeColor(TileType type) const
{
	switch (type)
	{
	case STREET: 
		return sf::Color(192, 186, 153);
		break;
	case GRASS: 
		return sf::Color(166, 200, 64);
		break;
	case HIGHGRASS: 
		return sf::Color(64, 69, 25);
		break;
	case SWAMPLAND: 
		return sf::Color(78, 62, 21);
		break;
	case WATER: 
		return sf::Color(21, 104, 156);
		break;
	case HILL: 
		return sf::Color(161, 64, 5);
		break;
	case MOUNTAIN:
		return sf::Color(128, 128, 128);
		break;
	default: 
		break;
	}

	return sf::Color::White;
}
