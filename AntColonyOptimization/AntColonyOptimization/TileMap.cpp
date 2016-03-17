#include "TileMap.h"


TileMap::TileMap()
	: m_nest(0, -1)
	, m_active(0, -1)
{
	m_grid.reserve(m_RowCount);
	
	for (auto r = 0; r < m_RowCount; ++r)
	{
		std::vector<Tile> row;
		row.reserve(m_ColCount);

		for (auto q = 0; q < m_ColCount; ++q)
		{
			auto terrain = static_cast<TerrainType>(m_Map.at(r).at(q));
			Tile tile(r, q, terrain);
			row.push_back(tile);
		}

		m_grid.push_back(row);
	}
}


TileMap::~TileMap()
{
}

void TileMap::Render(sf::RenderWindow& window)
{
	for (auto& tileRow : m_grid)
	{
		for (auto& tile : tileRow)
		{
			tile.Render(window);
		}
	}
}

void TileMap::MouseMovement(sf::Vector2f mousePos)
{
	if (m_active.y >= 0)
	{
		TileAt(m_active).UnsetBorder();		
	}

	auto index = FindMousePos(mousePos);
	
	if (!Exist(index))
	{
		m_active.y = -1;
		return;
	}
		
	m_active = index;
	TileAt(m_active).SetBorder();	
}

void TileMap::MouseClick(sf::Vector2f mousePos)
{
	auto index = FindMousePos(mousePos);

	if (!Exist(index))
	{
		return;
	}
	
	auto& tile = TileAt(index);

	if (!Exist(m_nest))
	{
		tile.SetType(NEST);
		m_nest = index;
	}
	else if (m_nest == index)
	{
		tile.SetType(NOTHING);
		m_nest.y = -1;
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

std::vector<sf::Vector2i> TileMap::GetNeighbour(sf::Vector2i tile) const
{
	std::vector<sf::Vector2i> directions{ sf::Vector2i(1, 0), sf::Vector2i(1, -1), sf::Vector2i(0, -1), sf::Vector2i(-1, 0), sf::Vector2i(-1, 1), sf::Vector2i(0, 1) };

	std::vector<sf::Vector2i> neighbours;
	neighbours.reserve(6);

	for (auto dir : directions)
	{
		auto neighbour = tile + dir;
		if (Exist(neighbour))
		{
			neighbours.push_back(neighbour);
		}
	}

	return neighbours;
}

int TileMap::Distance(sf::Vector2i start, sf::Vector2i dest) const
{
	 return (abs(start.x - dest.x) + abs(start.x + start.y - dest.x - dest.y) + abs(start.y - dest.y)) / 2;
}

float TileMap::GetPheromone(sf::Vector2i tile)
{
	return TileAt(tile).GetPheromone();
}

Tile& TileMap::TileAt(int q, int r)
{
	return m_grid.at(r).at(q + r / 2 - static_cast<int>(floor(r / 2.f)));
}

Tile& TileMap::TileAt(sf::Vector2i index)
{
	return TileAt(index.x, index.y);
}

bool TileMap::Exist(sf::Vector2i index) const
{
	if (index.y < 0 || index.y >= m_RowCount)
	{
		return false;
	}

	auto floorX = static_cast<int>(floor(index.y / 2.f));

	if (index.x < -floorX || index.x >= m_ColCount)
	{
		return false;
	}

	return true;
}

sf::Vector2i TileMap::FindMousePos(sf::Vector2f mousePos)
{
	sf::Vector2i index(0, -1);

	for (auto r = 0; r < m_RowCount; ++r)
	{
		auto row = m_grid.at(r);
		for (auto q = 0; q < row.size(); ++q)
		{
			if (!row.at(q).ContainMousePos(mousePos))
			{
				continue;
			}

			index.y = r;
			index.x = q;
			return index;			
		}
	}
	
	return index;
}
