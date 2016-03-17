#pragma once
#include "TileMap.h"

class AntAgent;

class AntManager
{
public:
	explicit AntManager(TileMap& tileMap);
	
	bool Run(TileMap currentMap, TileMap& newMap);

	void SetAlphaValue(double alpha);
	void SetBetaValue(double beta);
	void SetAntCount(unsigned int antCount);
	
private:
	double m_alpha;
	double m_beta;

	unsigned int m_antCount;
};

