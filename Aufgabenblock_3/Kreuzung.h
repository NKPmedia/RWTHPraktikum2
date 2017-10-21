#pragma once
#include <list>
#include <string>
#include "Weg.h"

using namespace std;

class Fahrzeug;

class Kreuzung
{
public:
	Kreuzung();
	~Kreuzung();

	void vVerbinde(string sNameHinweg,
		string sNameRueckweg,
		double dWeglaenge,
		Kreuzung* pZuVerbindendeKreuzung,
		Weg::GeschwindigkeitBegrenzung dLimit,
		bool bUeberholverbot);
	void vTanken(Fahrzeug* pZuTankenesFahrzeug);
	void vAnnehmen(Fahrzeug* fahrzeug, double);
	void vAbfertigen();
	Weg* pZufaelligerWeg(Weg*);

	void vSetTankstelle(double volumen);
	void vAddWegFuehrendeStaﬂe(Weg* weg);

private:
	list<Weg*> p_pWegfuehrendeStraﬂen;
	double p_dTankstelle;
};

