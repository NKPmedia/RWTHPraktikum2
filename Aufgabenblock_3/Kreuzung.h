#pragma once
#include <list>
#include <string>
#include "Weg.h"
#include "AktivesVerkehrsobjekt.h"

using namespace std;

class Fahrzeug;

class Kreuzung : public AktivesVerkehrsobjekt
{
public:
	Kreuzung();
	~Kreuzung();

	const string type = "Kreuzung";

	void vVerbinde(string sNameHinweg,
		string sNameRueckweg,
		double dWeglaenge,
		Kreuzung* pZuVerbindendeKreuzung,
		Weg::GeschwindigkeitBegrenzung dLimit,
		bool bUeberholverbot);

	istream virtual & istreamEingabe(istream& in);

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

