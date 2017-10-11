#include "Fahrzeug.h"

#include <stdio.h>
#include <iostream>
#include <iomanip>

extern double dGlobaleZeit;
int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug()
{
	this->vInitialisierung();

	//printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

Fahrzeug::Fahrzeug(const Fahrzeug& fahrzeug)
{
	this->vInitialisierung();
	this->p_sName = fahrzeug.p_sName;
	this->p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;
}

Fahrzeug::Fahrzeug(string fahrzeugName)
{
	this->vInitialisierung();
	this->p_sName = fahrzeugName;

	//printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

Fahrzeug::Fahrzeug(string fahrzeugName, double maxGeschwindigkeit)
{
	this->vInitialisierung();
	this->p_sName = fahrzeugName;
	this->p_dMaxGeschwindigkeit = maxGeschwindigkeit;

	//printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}


Fahrzeug::~Fahrzeug()
{
	//printf("Lösche das Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

void Fahrzeug::vOstreamAusgabe(ostream &out)
{
	out.precision(2);
	out << fixed;

	out << this->p_iID;

	out.width(10);
	out << this->p_sName.c_str();

	out.width(10);
	out << ":";

	out.width(10);
	out << this->p_dMaxGeschwindigkeit;

	out.width(10);
	out << this->dGeschwindigkeit();

	out.width(20);
	out << this->p_dGesamtGefahreneStrecke;
}

void Fahrzeug::vAusgabeFahrzeugInfosInOneRow()
{
	cout.precision(2);
	cout << fixed;

	cout << this->p_iID;

	cout.width(10);
	cout << this->p_sName.c_str();

	cout.width(10);
	cout << ":";

	cout.width(10);
	cout << this->p_dMaxGeschwindigkeit;

	cout.width(10);
	cout << this->dGeschwindigkeit();

	cout.width(20);
	cout << this->p_dGesamtGefahreneStrecke << endl;
}

void Fahrzeug::vInitIDWithUniqueNumber()
{
	this->p_iID = Fahrzeug::p_iMaxID + 1;
	Fahrzeug::p_iMaxID = this->p_iID;
}

void Fahrzeug::vInitialisierung()
{
	this->vInitIDWithUniqueNumber();
	this->p_dZeitLetzterAbfertigung = 0;
	this->p_dGesamtGefahreneStrecke = 0;
	this->p_dGesamtGefahreneZeit = 0;
	this->p_dMaxGeschwindigkeit = 0;
	this->p_sName = "";
}

double Fahrzeug::dGeschwindigkeit()
{
	return this->p_dMaxGeschwindigkeit;
}

void Fahrzeug::vAbfertigung()
{
	if (!this->bWurdeSchonAbgefertigt())
	{
		double zeitDifferenz = this->dBerechneZeitSeitLetzterAbfertigung();
		this->p_dGesamtGefahreneStrecke += this->dBerechneGefahreneStreckeInZeit(zeitDifferenz);
		this->p_dZeitLetzterAbfertigung = dGlobaleZeit;
	}
}

double Fahrzeug::dGetGesamtGefahreneStrecke()
{
	return this->p_dGesamtGefahreneStrecke;
}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

double Fahrzeug::dBerechneZeitSeitLetzterAbfertigung()
{
	return dGlobaleZeit - this->p_dZeitLetzterAbfertigung;
}

bool Fahrzeug::bWurdeSchonAbgefertigt()
{
	if (this->p_dZeitLetzterAbfertigung == dGlobaleZeit) 
	{
		return true;
	}
	return false;
}

double Fahrzeug::dBerechneGefahreneStreckeInZeit(double zeit)
{
	return this->dGeschwindigkeit() * zeit;
}


ostream& operator <<(ostream& out, Fahrzeug& fahrzeug)
{
	fahrzeug.vOstreamAusgabe(out);
	return out;
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
	}
	return *this;
}