#pragma once
#include "FzgVerhalten.h"
class FzgParken :
	public FzgVerhalten
{
public:
	FzgParken();
	FzgParken(Weg * weg, double sStartZeit);
	~FzgParken();

	double dBerechneFahrbareStrecke(Fahrzeug* fahrzeug, double zeit);
private:
	double p_dStartZeit;
};

