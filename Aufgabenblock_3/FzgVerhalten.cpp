#include "FzgVerhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

FzgVerhalten::FzgVerhalten()
{
}

FzgVerhalten::FzgVerhalten(Weg* weg, int iType) : p_pWeg(weg), iType(iType)
{
}


FzgVerhalten::~FzgVerhalten()
{
}

Weg * FzgVerhalten::pGetWeg()
{
	return this->p_pWeg;
}
