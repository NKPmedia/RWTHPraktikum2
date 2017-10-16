#pragma once
#include "Fahrzeug.h"
#include"Weg.h"

class FahrAusnahme
{
public:
	FahrAusnahme();
	FahrAusnahme(Fahrzeug* pFahrzeug, Weg* pWeg);
	~FahrAusnahme();

	void virtual vBearbeiten();
protected:
	Fahrzeug* p_pFahrzeug;
	Weg* p_pWeg;
};

