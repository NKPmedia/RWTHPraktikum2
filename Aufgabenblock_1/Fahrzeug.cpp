#include "Fahrzeug.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>

extern double dGlobaleZeit;
int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug()
{
	this->vInitialisierung();

	printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

Fahrzeug::Fahrzeug(string fahrzeugName)
{
	this->vInitialisierung();
	this->p_sName = fahrzeugName;

	printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

Fahrzeug::Fahrzeug(string fahrzeugName, double maxGeschwindigkeit)
{
	this->vInitialisierung();
	this->p_sName = fahrzeugName;
	this->p_dMaxGeschwindigkeit = maxGeschwindigkeit;

	printf("Erstelle ein Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}


Fahrzeug::~Fahrzeug()
{
	printf("Lösche das Fahrzeug mit dem Namen %s und der ID %i\n", this->p_sName.c_str(), this->p_iID);
}

void Fahrzeug::vAusgabeFahrzeugInfosInOneRow()
{
	cout << this->p_iID;
	cout.width(10);
	cout << this->p_sName.c_str();
	cout.width(10);
	cout << ":";
	cout.width(10);
	cout.precision(2);
	cout << fixed;
	cout << this->p_dMaxGeschwindigkeit;
	cout.width(20);
	cout.precision(2);
	cout << fixed;
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

void Fahrzeug::vAbfertigung()
{
	if (!this->bWurdeSchonAbgefertigt())
	{
		double zeitDifferenz = this->dBerechneZeitSeitLetzterAbfertigung();
		this->p_dGesamtGefahreneStrecke += this->dBerechneGefahreneStreckeInZeit(zeitDifferenz);
		this->p_dZeitLetzterAbfertigung = dGlobaleZeit;
	}
	
}

double Fahrzeug::dBerechneZeitSeitLetzterAbfertigung()
{
	return dGlobaleZeit - this->p_dZeitLetzterAbfertigung;
}

bool Fahrzeug::bWurdeSchonAbgefertigt()
{
	if (this->p_dZeitLetzterAbfertigung == dGlobaleZeit) {
		return true;
	}
	return false;
}

double Fahrzeug::dBerechneGefahreneStreckeInZeit(double zeit)
{
	return this->p_dMaxGeschwindigkeit * zeit;
}
