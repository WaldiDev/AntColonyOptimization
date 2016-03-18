#pragma once
#include "TileMap.h"

class AntAgent;

class AntManager
{
public:
	explicit AntManager();
	
	void Run(TileMap currentMap, TileMap& newMap);

	void SetAlphaValue(double alpha);
	void SetBetaValue(double beta);
	void SetEvaporation(double evaporation);
	void SetAntCount(unsigned int antCount);
	
private:
	double m_alpha;
	double m_beta;
	double m_evaporation;

	unsigned int m_antCount;
};

