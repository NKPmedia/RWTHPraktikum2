#pragma once
#include "Weg.h"
#include <list>
#include <string>

using namespace std;

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
	//Weg* pZufaelligerWeg(Weg*);

	void vSetTankstelle(double volumen);
	list<Weg*> vGetWegfuehrendeStraﬂen();

private:
	list<Weg*> p_pWegfuehrendeStraﬂen;
	double p_dTankstelle;
};

