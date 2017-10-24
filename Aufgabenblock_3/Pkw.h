#pragma once
#include "Fahrzeug.h"

class Pkw :
	public Fahrzeug
{
public:
	Pkw();
	Pkw(const Pkw& pkw);
	Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch);
	Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankVolumen);
	~Pkw();

	const string type = "PKW";

	void virtual vAbfertigung();

	double dBerechneGesamtVerbrauch();
	double virtual dTanken(double dMenge = -1);
	void virtual vOstreamAusgabe(ostream& out);
	istream virtual & istreamEingabe(istream& in);
	Pkw& operator=(const Pkw& fahrzeugZuKopieren);
	void virtual vZeichnen(Weg* pWeg);

	bool virtual istFahrrend();

private:
	double p_dVerbrauch; // Liter pro 100km
	double p_dTankinhalt; // Liter
	double p_dTankvolumen; // Liter
	static double p_dDefaulTankVolumen; // Liter
	double p_dGesamtVerbrauch; //Liter
	bool p_bTankLeer;

	double dBerechneDefaultTankInhalt(double dTankVolumen);
	double virtual dBerechneVerbrauchAufTeilstrecke(double dTeilstrecke);
};

