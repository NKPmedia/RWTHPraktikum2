#include "Pkw.h"
#include <iostream>

using namespace std;

double Pkw::p_dDefaulTankVolumen = 55;
extern double dGlobaleZeit;

Pkw::Pkw(const Pkw & pkw)
	: Fahrzeug(pkw.p_sName, pkw.p_dMaxGeschwindigkeit),
	p_dVerbrauch(pkw.p_dVerbrauch),
	p_dTankinhalt(0),
	p_dGesamtVerbrauch(0),
	p_dTankvolumen(pkw.p_dTankvolumen)
{
	this->p_dTankinhalt = this->dBerechneDefaultTankInhalt(pkw.p_dTankvolumen);
}

Pkw::Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch)
	: Fahrzeug(sFahrzeugName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),
	p_dTankinhalt(0),
	p_dGesamtVerbrauch(0),
	p_dTankvolumen(Pkw::p_dDefaulTankVolumen)
{
	this->p_dTankinhalt = this->dBerechneDefaultTankInhalt(Pkw::p_dDefaulTankVolumen);
}

Pkw::Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankVolumen)
	: Fahrzeug(sFahrzeugName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),
	p_dTankinhalt(0),
	p_dGesamtVerbrauch(0),
	p_dTankvolumen(dTankVolumen)
{
	this->p_dTankinhalt = this->dBerechneDefaultTankInhalt(dTankVolumen);
}


Pkw::~Pkw()
{
}


double Pkw::dBerechneGesamtVerbrauch()
{
	double verbrauchProKm = this->p_dVerbrauch / 100;
	return verbrauchProKm * this->p_dGesamtGefahreneStrecke;
}

double Pkw::dBerechneDefaultTankInhalt(double dTankVolumen)
{
	return dTankVolumen / 2.0;
}

void Pkw::vAbfertigung()
{
	if (!this->bWurdeSchonAbgefertigt())
	{
		double zeitDifferenz = this->dBerechneZeitSeitLetzterAbfertigung();
		double dTeilstrecke = this->dBerechneGefahreneStreckeInZeit(zeitDifferenz);

		double dVerbrauchAufTeilStrecke = this->dBerechneVerbrauchAufTeilstrecke(dTeilstrecke);

		if (this->p_dTankinhalt >= dVerbrauchAufTeilStrecke)
		{
			this->p_dTankinhalt -= dVerbrauchAufTeilStrecke;
			this->p_dGesamtVerbrauch += dVerbrauchAufTeilStrecke;
			this->p_dGesamtGefahreneStrecke += dTeilstrecke;
		}
		this->p_dZeitLetzterAbfertigung = dGlobaleZeit;
	}

}

double Pkw::dBerechneVerbrauchAufTeilstrecke(double dTeilstrecke)
{
	double dVerbrauchProKm = this->p_dVerbrauch / 100;
	return dVerbrauchProKm * dTeilstrecke;
}

double Pkw::dTanken(double dMenge)
{
	if (dMenge == -1)
	{
		dMenge = this->p_dTankvolumen;
	}

	double dTankInhaltZuvor = this->p_dTankinhalt;
	double dTankInhaltDanach = dTankInhaltZuvor + dMenge;
	if (dTankInhaltDanach > this->p_dTankvolumen)
	{
		this->p_dTankinhalt = this->p_dTankvolumen;
	}
	return dTankInhaltDanach - dTankInhaltZuvor;
}

void Pkw::vAusgabeFahrzeugInfosInOneRow()
{
	cout << fixed;
	cout.precision(2);

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
	cout << this->p_dGesamtGefahreneStrecke;

	cout.width(20);
	cout << this->p_dGesamtVerbrauch;

	cout.width(20);
	cout << this->p_dVerbrauch;

	cout.width(10);
	cout << this->p_dTankinhalt << endl;
}

void Pkw::vOstreamAusgabe(ostream& out)
{
	out << fixed;
	out.precision(2);

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

	out.width(20);
	out << this->p_dGesamtVerbrauch;
	
	out.width(20);
	out << this->p_dVerbrauch;

	out.width(10);
	out << this->p_dTankinhalt;
}

Pkw& Pkw::operator=(const Pkw& fahrzeugZuKopieren)
{
	if (this != &fahrzeugZuKopieren) {
		this->p_dGesamtGefahreneZeit = fahrzeugZuKopieren.p_dGesamtGefahreneZeit;
		this->p_dGesamtGefahreneStrecke = fahrzeugZuKopieren.p_dGesamtGefahreneStrecke;
		this->p_dMaxGeschwindigkeit = fahrzeugZuKopieren.p_dMaxGeschwindigkeit;
		this->p_dZeitLetzterAbfertigung = fahrzeugZuKopieren.p_dZeitLetzterAbfertigung;
		this->p_sName = fahrzeugZuKopieren.p_sName;
		this->p_dTankinhalt = fahrzeugZuKopieren.p_dTankinhalt;
		this->p_dDefaulTankVolumen = fahrzeugZuKopieren.p_dDefaulTankVolumen;
		this->p_dGesamtVerbrauch = fahrzeugZuKopieren.p_dGesamtVerbrauch;
		this->p_dTankinhalt = fahrzeugZuKopieren.p_dTankinhalt;
		this->p_dTankvolumen = fahrzeugZuKopieren.p_dTankvolumen;
		this->p_dVerbrauch = fahrzeugZuKopieren.p_dVerbrauch;
	}
	return *this;
}