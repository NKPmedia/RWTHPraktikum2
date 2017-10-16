#pragma once

class Weg;
class Fahrzeug;

class FzgVerhalten
{
public:
	enum Typen { Fahren = 1, Parken = 2};

	FzgVerhalten();
	FzgVerhalten(Weg* weg, int iType);
	~FzgVerhalten();

	int iType;

	Weg* pGetWeg();
	double virtual dBerechneFahrbareStrecke(Fahrzeug*, double zeit) = 0;
protected:
	Weg* p_pWeg;
};

