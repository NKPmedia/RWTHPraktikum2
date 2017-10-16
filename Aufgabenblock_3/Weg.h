#pragma once
#include "AktivesVerkehrsobjekt.h"
#include <list>
#include <string>
#include "LazyListe.h"
#include "Kreuzung.h"
#include "Weg.h"
#include "Fahrzeug.h"

using namespace std;

class Fahrzeug;

class Weg : public AktivesVerkehrsobjekt
{
public:
	enum GeschwindigkeitBegrenzung { Innerorts = 50, Landstraﬂe = 100, Autobahnbahn = -1 }; //In km/h

	Weg();
	Weg(string sName, double dLaenge, GeschwindigkeitBegrenzung eLimit, bool bUeberholverbot = true);
	~Weg();

	void virtual vOstreamAusgabe(ostream& out);
	void virtual vAbfertigung();
	double dGetLaenge();
	double dGetLimit();
	Weg* pGetZugehoerigerWeg();
	Kreuzung* pGetZielKreuzung();
	void vSetZugehoerigerWeg(Weg* weg);
	void vSetZielKreuzung(Kreuzung* kreu);
	
	bool bIstUeberholverbot();
	int iParkendeFahrzeuge;
	Fahrzeug* pZuLetztAbgefertigtesFahrzeug;

	void vAnnehmen(Fahrzeug* fahrzeug);
	void vAnnehmen(Fahrzeug * fahrzeug, double dStartZeit);
	void vAbgeben(Fahrzeug* fahrzeug);
private:
	double p_dLaenge;
	LazyListe<Fahrzeug*> p_pFahrzeugeAufWeg;
	double  p_eLimit;
	bool p_bUeberholverbot = true;
	Weg* p_pZugehoerigerWeg;
	Kreuzung* p_pZielKreuzung;
};
