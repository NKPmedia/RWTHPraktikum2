#include "FzgFahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "MathTools.h"
#include "Streckenende.h"

FzgFahren::FzgFahren()
{
}

FzgFahren::FzgFahren(Weg* weg) : FzgVerhalten(weg)
{
}

FzgFahren::~FzgFahren()
{
}

double FzgFahren::dBerechneFahrbareStrecke(Fahrzeug* fahrzeug, double zeit)
{
	double dMoeglicheStrecke = fahrzeug->dGeschwindigkeit() * zeit;
	double dPlatzAufWeg = this->p_pWeg->dGetLaenge() - fahrzeug->dGetAbschnittGefahreneStrecke();

	if (MathTools::nearly_equal(dPlatzAufWeg, 0))
	{
		throw Streckenende(fahrzeug, this->p_pWeg);
	}

	if (dPlatzAufWeg < dMoeglicheStrecke)
	{
		return dPlatzAufWeg;
	}
	return dMoeglicheStrecke;
}