#include "TileMap.h"



TileMap::TileMap()
{
	for (auto i = 0; i < 30; ++i)
	{
		for (auto y = 0; y < 50; ++y)
		{
			auto type = m_map[i][y];			
			Tile tile(i, y, static_cast<TileType>(type));
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

void TileMap::SetActiveTile(sf::Vector2f mousePos)
{
	if (m_active >= 0)
	{
		m_tiles.at(m_active).UnsetBorder();
	}

	for (auto i = 0u; i < m_tiles.size(); ++i)
	{
		if (m_tiles.at(i).ContainMousePos(mousePos))
		{			
			m_active = i;
			m_tiles.at(i).SetBorder();
			return;
		}
	}

	m_active = -1;
}
