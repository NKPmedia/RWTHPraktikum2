#pragma once
#include "FahrAusnahme.h"
class Streckenende :
	public FahrAusnahme
{
public:
	Streckenende();
	Streckenende(Fahrzeug* pFahrzeug, Weg* pWeg);
	~Streckenende();

	void virtual vBearbeiten();
};

