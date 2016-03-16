#include "TileMap.h"



TileMap::TileMap()
{
	for (auto i = 0; i < 30; ++i)
	{
		for (auto y = 0; y < 50; ++y)
		{
			auto c = m_map[i][y];
			auto type = static_cast<TileType>(c - '0');
			auto tile = new Tile(i, y, static_cast<TileType>(c));
			m_tiles.push_back(tile);
		}
	}
}


TileMap::~TileMap()
{
}
