#include "FzgParken.h"
#include "Weg.h"
#include "MathTools.h"
#include "Losfahren.h"

extern double dGlobaleZeit;

FzgParken::FzgParken()
{
}

FzgParken::FzgParken(Weg* weg, double dStartZeit) : FzgVerhalten(weg), p_dStartZeit(dStartZeit)
{
}


FzgParken::~FzgParken()
{
}

double FzgParken::dBerechneFahrbareStrecke(Fahrzeug* fahrzeug, double zeit)
{
	if (dGlobaleZeit >= this->p_dStartZeit)
	{
		throw Losfahren(fahrzeug, this->p_pWeg);
	}
	return 0;
}