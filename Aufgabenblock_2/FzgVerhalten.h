#pragma once

class Weg;
class Fahrzeug;

class FzgVerhalten
{
public:
	FzgVerhalten();
	FzgVerhalten(Weg* weg);
	~FzgVerhalten();

	Weg* pGetWeg();
	double virtual dBerechneFahrbareStrecke(Fahrzeug*, double zeit) = 0;
protected:
	Weg* p_pWeg;
};

