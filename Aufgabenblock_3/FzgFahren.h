#pragma once
#include "FzgVerhalten.h"

class Weg;
class Fahrzeug;

class FzgFahren :
	public FzgVerhalten
{
public:
	FzgFahren();
	FzgFahren(Weg* weg);
	~FzgFahren();

private:
	double virtual dBerechneFahrbareStrecke(Fahrzeug*, double zeit);
};

