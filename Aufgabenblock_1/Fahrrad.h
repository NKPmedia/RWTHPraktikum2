#pragma once
#include "Fahrzeug.h"

class Fahrrad :
	public Fahrzeug
{
public:
	static double const iABZUGPRO20KM;
	static double const dMINGESCHWINDIGKEIT;

	Fahrrad();
	Fahrrad(string carName);
	Fahrrad(string carName, double maxGeschwindigkeit);
	~Fahrrad();
private:

protected:
	double virtual dGeschwindigkeit();
};

