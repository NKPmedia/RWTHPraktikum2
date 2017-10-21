#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"

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
	double iProzentVonMaxGesch = pow(1 - Fahrrad::iABZUGPRO20KM, iGefahrene20Km);

	double dAktuelleGeschwindigkeit = this->p_dMaxGeschwindigkeit * iProzentVonMaxGesch;

	if (dAktuelleGeschwindigkeit < Fahrrad::dMINGESCHWINDIGKEIT)
	{
		dAktuelleGeschwindigkeit = Fahrrad::dMINGESCHWINDIGKEIT;
	}

	Weg* weg = this->p_pVerhalten->pGetWeg();
	if (weg->dGetLimit() == -1)
	{
		return dAktuelleGeschwindigkeit;
	}
	if (weg->dGetLimit() < dAktuelleGeschwindigkeit)
	{
		return weg->dGetLimit();
	}

	return dAktuelleGeschwindigkeit;
}

void Fahrrad::vZeichnen(Weg * pWeg)
{
	bZeichneFahrrad(this->p_sName, pWeg->sGetName(), this->dGetRelPosition(), this->dGeschwindigkeit());
}
