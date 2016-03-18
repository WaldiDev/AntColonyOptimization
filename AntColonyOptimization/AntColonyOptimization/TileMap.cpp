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
			//auto leftQ = q - static_cast<int>(floor(r / 2.f));
			Tile tile(r, q - static_cast<int>(floor(r / 2.f)), q, terrain);
			row.push_back(tile);
		}

		m_grid.push_back(row);
	}
}


TileMap::~TileMap()
{
}

void TileMap::Render(sf::RenderWindow& window, bool grey)
{
	for (auto& tileRow : m_grid)
	{
		for (auto& tile : tileRow)
		{
			tile.Render(window, grey);
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

int TileMap::GetWeight(sf::Vector2i tile)
{
	return TileAt(tile).GetWeight();
}

int TileMap::Distance(sf::Vector2i start, sf::Vector2i dest) const
{
	 return (abs(start.x - dest.x) + abs(start.x + start.y - dest.x - dest.y) + abs(start.y - dest.y)) / 2;
}

double TileMap::GetPheromone(sf::Vector2i tile)
{
	return TileAt(tile).GetPheromone();
}

bool TileMap::GetNestPosition(sf::Vector2i& nestPos) const
{
	if (Exist(m_nest))
	{
		nestPos = m_nest;
		return true;
	}

	return false;
}

void TileMap::AddPheromone(sf::Vector2i tile, double pheromone)
{
	TileAt(tile).AddPheromone(pheromone);
}

TileType TileMap::GetTileType(sf::Vector2i tile)
{
	return TileAt(tile).GetType();
}

void TileMap::Evaporation(double rho)
{
	auto value = 1 - rho;
	for (auto& row : m_grid)
	{
		for (auto& tile : row)
		{
			tile.Evaporation(value);
		}
	}
}

void TileMap::SetColorMode(bool s)
{
	m_color = s;
}

Tile& TileMap::TileAt(int q, int r)
{
	auto col = q + static_cast<int>(floor(r / 2.f));
	return m_grid.at(r).at(col);
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

	if (index.x < -floorX || index.x >= m_ColCount - floorX)
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
		for (auto q = 0u; q < row.size(); ++q)
		{
			if (!row.at(q).ContainMousePos(mousePos))
			{
				continue;
			}

			index.y = r;
			index.x = q - static_cast<int>(floor(r / 2.f));
			return index;			
		}
	}
	
	return index;
}
