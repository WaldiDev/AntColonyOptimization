#include "TileMap.h"


TileMap::TileMap()
{
	for (auto i = 0; i < 30; ++i)
	{
		for (auto y = 0; y < 50; ++y)
		{
			auto type = m_Map[i][y];			
			Tile tile(i, y, static_cast<TerrainType>(type));
			m_tiles.push_back(tile);
		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::Render(sf::RenderWindow& window)
{
	for (auto& m_tile : m_tiles)
	{
		m_tile.Render(window);
	}
}

void TileMap::MouseMovement(sf::Vector2f mousePos)
{
	if (m_active >= 0)
	{
		m_tiles.at(m_active).UnsetBorder();
	}

	auto index = FindMousePos(mousePos);
	if (index >= 0)
	{
		m_active = index;
		m_tiles.at(index).SetBorder();
		return;
	}

	m_active = -1;
}

void TileMap::MouseClick(sf::Vector2f mousePos)
{
	auto index = FindMousePos(mousePos);
	if (index >= 0)
	{
		auto& tile = m_tiles.at(index);

		if (m_nest < 0)
		{
			tile.SetType(NEST);
			m_nest = index;
		}
		else if (m_nest == index)
		{
			tile.SetType(NOTHING);
			m_nest = -1;
		}
		else if (tile.GetType() == FEED)
		{
			tile.SetType(NOTHING);
		}
		else
		{
			tile.SetType(FEED);
		}
	}
}

int TileMap::FindMousePos(sf::Vector2f mousePos)
{
	for (auto i = 0u; i < m_tiles.size(); ++i)
	{
		if (m_tiles.at(i).ContainMousePos(mousePos))
		{
			return i;
		}
	}

	return -1;
}
