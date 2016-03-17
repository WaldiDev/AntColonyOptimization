#include "AntManager.h"
#include "AntAgent.h"

AntManager::AntManager(TileMap& tileMap)
	: m_alpha(1.0)
	, m_beta(5.0)
	, m_antCount(1000u)
{
}

bool AntManager::Run(TileMap currentMap, TileMap& newMap)
{
	sf::Vector2i nestPos;
	if (!currentMap.GetNestPosition(nestPos))
	{
		return false;
	}

	for (auto i = 0u; i < m_antCount; ++i)
	{
		AntAgent ant(m_alpha, m_beta);
		if (ant.FindFeed(currentMap, nestPos))
		{
			ant.MarkPath(newMap);
		}
	}

	return true;
}


void AntManager::SetAlphaValue(double alpha)
{
	m_alpha = alpha;
}

void AntManager::SetBetaValue(double beta)
{
	m_beta = beta;
}

void AntManager::SetAntCount(unsigned int antCount)
{
	m_antCount = antCount;
}
