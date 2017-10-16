#include "Losfahren.h"
#include <iostream>

using namespace std;


Losfahren::Losfahren()
{
}

Losfahren::Losfahren(Fahrzeug * pFahrzeug, Weg * pWeg) : FahrAusnahme(pFahrzeug, pWeg)
{
}


Losfahren::~Losfahren()
{
}

void Losfahren::vBearbeiten()
{
	cout << "Losfahren ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << *this->p_pFahrzeug << endl;
	cout << *this->p_pWeg << endl;

	this->p_pWeg->vAbgeben(this->p_pFahrzeug);
	this->p_pWeg->vAnnehmen(this->p_pFahrzeug);
	this->p_pWeg->iParkendeFahrzeuge--;
}