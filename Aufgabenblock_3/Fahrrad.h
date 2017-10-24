#pragma once
#include "Fahrzeug.h"

class Fahrrad :
	public Fahrzeug
{
public:
	static double const iABZUGPRO20KM;
	static double const dMINGESCHWINDIGKEIT;

	const string type = "Fahrrad";

	Fahrrad();
	Fahrrad(string carName);
	Fahrrad(string carName, double maxGeschwindigkeit);
	~Fahrrad();

	double virtual dGeschwindigkeit();
	void virtual vZeichnen(Weg* pWeg);
private:

protected:
};

