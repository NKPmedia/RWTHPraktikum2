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
	weg1->vSetZielKreuzung(pZuVerbindendeKreuzung);
	weg2->vSetZielKreuzung(this);


	this->p_pWegfuehrendeStra�en.push_back(weg1);
	pZuVerbindendeKreuzung->vAddWegFuehrendeSta�e(weg2);
}

istream & Kreuzung::istreamEingabe(istream & in)
{
	AktivesVerkehrsobjekt::istreamEingabe(in);

	in >> this->p_dTankstelle;

	return in;
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
	Weg* weg = this->p_pWegfuehrendeStra�en.front();
	weg->vAnnehmen(fahrzeug, zeit);
}

void Kreuzung::vAbfertigung()
{
	list<Weg*>::iterator it;
	for (it = this->p_pWegfuehrendeStra�en.begin(); it != this->p_pWegfuehrendeStra�en.end(); it++)
	{
		(*it)->vAbfertigung();
	}
}

Weg * Kreuzung::pZufaelligerWeg(Weg * pHinWeg)
{
	srand(time(NULL));

	int iAnzahlWege = this->p_pWegfuehrendeStra�en.size();
	Weg* weg;
	
	if (iAnzahlWege == 1)
	{
		list<Weg*>::iterator it = this->p_pWegfuehrendeStra�en.begin();
		weg = (*it);
		return weg;
	}

	do
	{
		int iWegNummer = rand() % iAnzahlWege;
		list<Weg*>::iterator it = this->p_pWegfuehrendeStra�en.begin();
		advance(it, iWegNummer);
		weg = (*it);
	} 
	while (weg == pHinWeg || pHinWeg->pGetZugehoerigerWeg() == weg);

	return weg;
}

void Kreuzung::vSetTankstelle(double volumen)
{
	this->p_dTankstelle = volumen;
}

void Kreuzung::vAddWegFuehrendeSta�e(Weg * weg)
{
	this->p_pWegfuehrendeStra�en.push_back(weg);
}
