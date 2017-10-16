#include "FzgFahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "MathTools.h"
#include "Streckenende.h"

FzgFahren::FzgFahren()
{
}

FzgFahren::FzgFahren(Weg* weg) : FzgVerhalten(weg, FzgVerhalten::Fahren)
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
		dMoeglicheStrecke = dPlatzAufWeg;
	}

	if (this->p_pWeg->bIstUeberholverbot()) 
	{
		double dPunktNaechtesFahrendesFahrzeug = this->p_pWeg->pZuLetztAbgefertigtesFahrzeug->dGetAbschnittGefahreneStrecke();
		if (fahrzeug->dGetAbschnittGefahreneStrecke() + dMoeglicheStrecke > dPunktNaechtesFahrendesFahrzeug)
		{
			double dAbstand = dPunktNaechtesFahrendesFahrzeug - fahrzeug->dGetAbschnittGefahreneStrecke();
			//Begründung für -1
			//Damit sie nicht genau auf der selben Position sind und sich dadurch überholen
			//Dadurch wird auch die Liste in einer sortierten Reinfolge gehalten!
			dMoeglicheStrecke = dAbstand - 1;
		}
	}

	return dMoeglicheStrecke;
}
