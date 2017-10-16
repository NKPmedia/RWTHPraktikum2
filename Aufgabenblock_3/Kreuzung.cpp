#include "Kreuzung.h"
#include "Weg.h"
#include <list>
#include "Fahrzeug.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

Kreuzung::Kreuzung()
{
}


Kreuzung::~Kreuzung()
{
}

void Kreuzung::vVerbinde(string sNameHinweg, string sNameRueckweg, double dWeglaenge, Kreuzung * pZuVerbindendeKreuzung, Weg::GeschwindigkeitBegrenzung dLimit, bool bUeberholverbot)
{
	Weg* weg1 = new Weg(sNameHinweg, dWeglaenge, dLimit, bUeberholverbot);
	Weg* weg2 = new Weg(sNameRueckweg, dWeglaenge, dLimit, bUeberholverbot);
	weg1->vSetZugehoerigerWeg(weg2);
	weg2->vSetZugehoerigerWeg(weg1);
	//weg1->vSetZielKreuzung(pZuVerbindendeKreuzung);
	//weg2->vSetZielKreuzung(this);


	this->p_pWegfuehrendeStraﬂen.push_back(weg1);
	pZuVerbindendeKreuzung->vGetWegfuehrendeStraﬂen().push_back(weg2);
}

void Kreuzung::vTanken(Fahrzeug * pZuTankenesFahrzeug)
{
	if (this->p_dTankstelle <= 0)
	{
		return;
	}
	double dGetanktenVolumen = pZuTankenesFahrzeug->dTanken();
	this->p_dTankstelle -= dGetanktenVolumen;

}

void Kreuzung::vAnnehmen(Fahrzeug * fahrzeug, double zeit)
{
	this->vTanken(fahrzeug);
	Weg* weg = this->p_pWegfuehrendeStraﬂen.front();
	weg->vAnnehmen(fahrzeug, zeit);
}

void Kreuzung::vAbfertigen()
{
	list<Weg*>::iterator it;
	for (it = this->p_pWegfuehrendeStraﬂen.begin(); it != this->p_pWegfuehrendeStraﬂen.end(); it++)
	{
		(*it)->vAbfertigung();
	}
}

/*Weg * Kreuzung::pZufaelligerWeg(Weg * pHinWeg)
{
	srand(time(NULL));

	int iAnzahlWege = this->p_pWegfuehrendeStraﬂen.size();
	Weg* weg;
	
	if (iAnzahlWege == 1)
	{
		list<Weg*>::iterator it = this->p_pWegfuehrendeStraﬂen.begin();
		weg = (*it);
		return weg;
	}

	do
	{
		int iWegNummer = rand() % iAnzahlWege;
		list<Weg*>::iterator it = this->p_pWegfuehrendeStraﬂen.begin();
		advance(it, iWegNummer);
		weg = (*it);
	} 
	while (weg == pHinWeg || weg->pGetZugehoerigerWeg() == weg);

	return weg;
}*/

void Kreuzung::vSetTankstelle(double volumen)
{
	this->p_dTankstelle = volumen;
}

list<Weg*> Kreuzung::vGetWegfuehrendeStraﬂen()
{
	return this->p_pWegfuehrendeStraﬂen;
}
