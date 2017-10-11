#include "Fahrrad.h"

const double Fahrrad::iABZUGPRO20KM = 0.1;
const double Fahrrad::dMINGESCHWINDIGKEIT = 12.5;

Fahrrad::Fahrrad() : Fahrzeug()
{
}

Fahrrad::Fahrrad(string fahrzeugName) : Fahrzeug(fahrzeugName)
{
}

Fahrrad::Fahrrad(string fahrzeugName, double maxGeschwindigkeit) : Fahrzeug(fahrzeugName, maxGeschwindigkeit)
{
}

Fahrrad::~Fahrrad()
{
}

double Fahrrad::dGeschwindigkeit()
{
	int iGefahrene20Km = this->dGetGesamtGefahreneStrecke() / 20.0;
	double iProzentVonMaxGesch = 1 - (iGefahrene20Km * Fahrrad::iABZUGPRO20KM);

	double dAktuelleGeschwindigkeit = this->p_dMaxGeschwindigkeit * iProzentVonMaxGesch;

	if (dAktuelleGeschwindigkeit < Fahrrad::dMINGESCHWINDIGKEIT)
	{
		return Fahrrad::dMINGESCHWINDIGKEIT;
	}
	return dAktuelleGeschwindigkeit;
}
