#pragma once
#include "AktivesVerkehrsobjekt.h"
#include <list>
#include <string>
#include"LazyListe.h"

using namespace std;

class Fahrzeug;

class Weg : public AktivesVerkehrsobjekt
{
public:
	enum GeschwindigkeitBegrenzung { Innerorts = 50, Landstraﬂe = 100, Autobahnbahn = -1 }; //In km/h

	Weg();
	Weg(string sName, double dLaenge, GeschwindigkeitBegrenzung eLimit);
	~Weg();

	void virtual vOstreamAusgabe(ostream& out);
	void virtual vAbfertigung();
	double dGetLaenge();
	double dGetLimit();

	void vAnnehmen(Fahrzeug* fahrzeug);
	void vAnnehmen(Fahrzeug * fahrzeug, double dStartZeit);
	void vAbgeben(Fahrzeug* fahrzeug);
private:
	double p_dLaenge;
	LazyListe<Fahrzeug*> p_pFahrzeugeAufWeg;
	double  p_eLimit;
};
