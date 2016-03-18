#include "AntManager.h"
#include "AntAgent.h"
#include <thread>

AntManager::AntManager()
	: m_alpha(1.0)
	, m_beta(2.0)
	, m_evaporation(0.3)
	, m_antCount(1000u)
{
}

void AntManager::Run(TileMap currentMap, TileMap& newMap)
{
	sf::Vector2i nestPos;
	
	newMap.Evaporation(m_evaporation);
	
	if (!currentMap.GetNestPosition(nestPos))
	{
		return;
	}
		
	for (auto i = 0u; i < m_antCount; ++i)
	{
		AntAgent ant(m_alpha, m_beta);		
		if (ant.FindFeed(currentMap, nestPos))
		{
			ant.MarkPath(newMap);
		}
	}
}


void AntManager::SetAlphaValue(double alpha)
{
	m_alpha = alpha;
}

void AntManager::SetBetaValue(double beta)
{
	m_beta = beta;
}

void AntManager::SetEvaporation(double evaporation)
{
	m_evaporation = evaporation;
}

void AntManager::SetAntCount(unsigned int antCount)
{
	m_antCount = antCount;
}
