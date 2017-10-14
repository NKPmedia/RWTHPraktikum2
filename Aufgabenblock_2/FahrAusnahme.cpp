#include "FahrAusnahme.h"
#include <iostream>

using namespace std;

FahrAusnahme::FahrAusnahme()
{
}

FahrAusnahme::FahrAusnahme(Fahrzeug * pFahrzeug, Weg * pWeg) : p_pFahrzeug(pFahrzeug), p_pWeg(pWeg)
{
}


FahrAusnahme::~FahrAusnahme()
{
}

void FahrAusnahme::vBearbeiten()
{
	cout << "FahrAusnahme ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << *this->p_pFahrzeug << endl;
	cout << *this->p_pWeg << endl;
}
