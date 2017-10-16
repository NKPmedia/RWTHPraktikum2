#include "Pkw.h"
#include <iostream>
#include "FzgVerhalten.h"
#include "Weg.h"
#include "SimuClient.h"
#include "MathTools.h"

using namespace std;

double Pkw::p_dDefaulTankVolumen = 55;
extern double dGlobaleZeit;

Pkw::Pkw(const Pkw & pkw)
	: Fahrzeug(pkw.p_sName, pkw.p_dMaxGeschwindigkeit),
	p_dVerbrauch(pkw.p_dVerbrauch),
	p_dTankinhalt(0),
	p_dGesamtVerbrauch(0),
	p_dTankvolumen(pkw.p_dTankvolumen),
	p_bTankLeer(false)
{
	this->p_dTankinhalt = this->dBerechneDefaultTankInhalt(pkw.p_dTankvolumen);
}

Pkw::Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch)
	: Fahrzeug(sFahrzeugName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),
	p_dTankinhalt(0),
	p_dGesamtVerbrauch(0),
	p_dTankvolumen(Pkw::p_dDefaulTankVolumen),
	p_bTankLeer(false)
{
	this->p_dTankinhalt = this->dBerechneDefaultTankInhalt(Pkw::p_dDefaulTankVolumen);
}

Pkw::Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankVolumen)
	: Fahrzeug(sFahrzeugName, dMaxGeschwindigkeit),
	p_dVerbrauch(dVerbrauch),
	p_dTankinhalt(0),
	p_dGesamtVerbrauch(0),
	p_dTankvolumen(dTankVolumen),
	p_bTankLeer(false)
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
		double dTeilstrecke = this->p_pVerhalten->dBerechneFahrbareStrecke(this, zeitDifferenz);

		double dVerbrauchAufTeilStrecke = this->dBerechneVerbrauchAufTeilstrecke(dTeilstrecke);

		if (this->p_dTankinhalt >= dVerbrauchAufTeilStrecke)
		{
			this->p_dTankinhalt -= dVerbrauchAufTeilStrecke;
			this->p_dGesamtVerbrauch += dVerbrauchAufTeilStrecke;
			this->p_dGesamtGefahreneStrecke += dTeilstrecke;
			this->p_dAbschnittGefahreneStrecke += dTeilstrecke;
		}
		else
		{
			this->p_bTankLeer = true;
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
	this->p_bTankLeer = false;
	return dTankInhaltDanach - dTankInhaltZuvor;
}

void Pkw::vOstreamAusgabe(ostream& out)
{
	Fahrzeug::vOstreamAusgabe(out);

	out << fixed;
	out.precision(2);

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
		this->p_dAbschnittGefahreneStrecke = fahrzeugZuKopieren.p_dAbschnittGefahreneStrecke;
		//TODO Vielleicht sollte man hier eine neue Instanze erstellen!?
		this->p_pVerhalten = fahrzeugZuKopieren.p_pVerhalten;
		this->p_pAktuelleStrecke = fahrzeugZuKopieren.p_pAktuelleStrecke;
		this->p_bTankLeer = fahrzeugZuKopieren.p_bTankLeer;
	}
	return *this;
}

void Pkw::vZeichnen(Weg * pWeg)
{
	bZeichnePKW(this->p_sName, pWeg->sGetName(), this->dGetRelPosition(), this->dGeschwindigkeit(), this->p_dTankinhalt);
}

bool Pkw::istFahrrend()
{
	if (this->p_pVerhalten->iType == FzgVerhalten::Fahren
		&& !this->p_bTankLeer)
	{
		return true;
	}
	return false;
}