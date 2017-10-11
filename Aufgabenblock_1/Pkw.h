#pragma once
#include "Fahrzeug.h"

class Pkw :
	public Fahrzeug
{
public:
	Pkw(const Pkw& pkw);
	Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch);
	Pkw(string sFahrzeugName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankVolumen);
	~Pkw();

	void virtual vAbfertigung();

	double dBerechneGesamtVerbrauch();
	double virtual dTanken(double dMenge = -1);
	void vAusgabeFahrzeugInfosInOneRow();
	void virtual vOstreamAusgabe(ostream& out);
	Pkw& operator=(const Pkw& fahrzeugZuKopieren);

private:
	double p_dVerbrauch; // Liter pro 100km
	double p_dTankinhalt; // Liter
	double p_dTankvolumen; // Liter
	static double p_dDefaulTankVolumen; // Liter
	double p_dGesamtVerbrauch; //Liter

	double dBerechneDefaultTankInhalt(double dTankVolumen);
	double virtual dBerechneVerbrauchAufTeilstrecke(double dTeilstrecke);
};

