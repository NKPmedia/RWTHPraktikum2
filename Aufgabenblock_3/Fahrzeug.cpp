#include "Fahrzeug.h"
#include "FzgVerhalten.h"
#include "FzgFahren.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "Weg.h"

extern double dGlobaleZeit;

Fahrzeug::Fahrzeug() : AktivesVerkehrsobjekt()
{
	this->vInitialisierung();

	//printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

Fahrzeug::Fahrzeug(const Fahrzeug& fahrzeug) : AktivesVerkehrsobjekt (fahrzeug.p_sName)
{
	this->vInitialisierung();
	this->p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
}

Fahrzeug::Fahrzeug(string fahrzeugName) : AktivesVerkehrsobjekt(fahrzeugName)
{
	this->vInitialisierung();

	//printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

Fahrzeug::Fahrzeug(string fahrzeugName, double maxGeschwindigkeit) : AktivesVerkehrsobjekt(fahrzeugName)
{
	this->vInitialisierung();
	this->p_dMaxGeschwindigkeit = maxGeschwindigkeit;

	//printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}


Fahrzeug::~Fahrzeug()
{
	//printf("Lösche das Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

void Fahrzeug::vOstreamAusgabe(ostream &out)
{
	AktivesVerkehrsobjekt::vOstreamAusgabe(out);

	out.precision(2);
	out << fixed;

	out.width(10);
	out << this->p_dMaxGeschwindigkeit;

	out.width(10);
	out << this->dGeschwindigkeit();

	out.width(20);
	out << this->p_dGesamtGefahreneStrecke;
}

istream & Fahrzeug::istreamEingabe(istream & in)
{
	AktivesVerkehrsobjekt::istreamEingabe(in);
	in >> this->p_dMaxGeschwindigkeit;
	
	return in;
}

void Fahrzeug::vInitialisierung()
{
	this->p_dZeitLetzterAbfertigung = 0;
	this->p_dGesamtGefahreneStrecke = 0;
	this->p_dGesamtGefahreneZeit = 0;
	this->p_dMaxGeschwindigkeit = 0;
	this->p_dAbschnittGefahreneStrecke = 0;
	this->p_pVerhalten = NULL;
	this->p_pAktuelleStrecke = NULL;

}

double Fahrzeug::dGeschwindigkeit()
{
	Weg* weg = this->p_pVerhalten->pGetWeg();
	if (weg->dGetLimit() == -1)
	{
		return this->p_dMaxGeschwindigkeit;
	}
	if (weg->dGetLimit() < this->p_dMaxGeschwindigkeit)
	{
		return weg->dGetLimit();
	}
	return this->p_dMaxGeschwindigkeit;
}

void Fahrzeug::vAbfertigung()
{
	if (!this->bWurdeSchonAbgefertigt())
	{
		double zeitDifferenz = this->dBerechneZeitSeitLetzterAbfertigung();
		this->p_dZeitLetzterAbfertigung = dGlobaleZeit;
		double dFahrbareStrecke = this->p_pVerhalten->dBerechneFahrbareStrecke(this, zeitDifferenz);
		this->p_dGesamtGefahreneStrecke += dFahrbareStrecke;
		this->p_dAbschnittGefahreneStrecke += dFahrbareStrecke;
	}
}

bool Fahrzeug::istFahrrend()
{
	if (this->p_pVerhalten->iType == FzgVerhalten::Fahren)
	{
		return true;
	}
	return false;
}

double Fahrzeug::dGetGesamtGefahreneStrecke()
{
	return this->p_dGesamtGefahreneStrecke;
}

double Fahrzeug::dGetAbschnittGefahreneStrecke()
{
	return this->p_dAbschnittGefahreneStrecke;
}

void Fahrzeug::vSetVerhalten(FzgVerhalten * pVerhalten)
{
	this->p_pVerhalten = pVerhalten;
}

void Fahrzeug::vSetAbschnittGefahreneStrecke(double strecke)
{
	this->p_dAbschnittGefahreneStrecke = strecke;
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

void Fahrzeug::vZeichnen(Weg * pWeg)
{
}

double Fahrzeug::dBerechneZeitSeitLetzterAbfertigung()
{
	return dGlobaleZeit - this->p_dZeitLetzterAbfertigung;
}

double Fahrzeug::dGetRelPosition()
{
	double dWegLaenge = this->p_pAktuelleStrecke->dGetLaenge();
	return this->p_dAbschnittGefahreneStrecke / dWegLaenge;
}

bool Fahrzeug::bWurdeSchonAbgefertigt()
{
	if (this->p_dZeitLetzterAbfertigung == dGlobaleZeit) 
	{
		return true;
	}
	return false;
}

bool Fahrzeug::operator<(const Fahrzeug & vergleich)
{
	if (this->p_dGesamtGefahreneStrecke < vergleich.p_dGesamtGefahreneStrecke)
	{
		return true;
	}
	return false;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& fahrzeugZuKopieren)
{
	if (this != &fahrzeugZuKopieren) {
		this->p_dGesamtGefahreneZeit = fahrzeugZuKopieren.p_dGesamtGefahreneZeit;
		this->p_dGesamtGefahreneStrecke = fahrzeugZuKopieren.p_dGesamtGefahreneStrecke;
		this->p_dMaxGeschwindigkeit = fahrzeugZuKopieren.p_dMaxGeschwindigkeit;
		this->p_dZeitLetzterAbfertigung = fahrzeugZuKopieren.p_dZeitLetzterAbfertigung;
		this->p_sName = fahrzeugZuKopieren.p_sName;
		this->p_dAbschnittGefahreneStrecke = fahrzeugZuKopieren.p_dAbschnittGefahreneStrecke;
		//TODO Vielleicht sollte man hier eine neue Instanze erstellen!?
		this->p_pVerhalten = fahrzeugZuKopieren.p_pVerhalten;
		this->p_pAktuelleStrecke = fahrzeugZuKopieren.p_pAktuelleStrecke;
	}
	return *this;
}

void Fahrzeug::vNeueStrecke(Weg * weg)
{
	this->p_pAktuelleStrecke = weg;
	delete this->p_pVerhalten;
	this->p_pVerhalten = new FzgFahren(weg);

	this->p_dAbschnittGefahreneStrecke = 0;
}
