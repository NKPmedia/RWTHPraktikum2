#include "Streckenende.h"
#include <iostream>

using namespace std;


Streckenende::Streckenende()
{
}

Streckenende::Streckenende(Fahrzeug * pFahrzeug, Weg * pWeg) : FahrAusnahme(pFahrzeug, pWeg)
{
}


Streckenende::~Streckenende()
{
}

void Streckenende::vBearbeiten()
{
	cout << "Streckenende ++++++++++++++++++++++++++++++++++++++" << endl;
	cout << *this->p_pFahrzeug << endl;
	cout << *this->p_pWeg << endl;

	this->p_pWeg->vAbgeben(this->p_pFahrzeug);
	this->p_pWeg->pGetZielKreuzung()->vTanken(this->p_pFahrzeug);
	//Weg* pNeuerWeg = this->p_pWeg->pGetZielKreuzung()->pZufaelligerWeg(this->p_pWeg);
	//pNeuerWeg->vAnnehmen(this->p_pFahrzeug);
}
