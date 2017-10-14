#pragma once
#include "FahrAusnahme.h"
#include "Fahrzeug.h"
#include"Weg.h"

class Losfahren :
	public FahrAusnahme
{
public:
	Losfahren();
	Losfahren(Fahrzeug* pFahrzeug, Weg* pWeg);
	~Losfahren();

	void virtual vBearbeiten();
};

