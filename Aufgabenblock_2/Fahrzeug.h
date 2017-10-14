#pragma once
#include <string>
#include "AktivesVerkehrsobjekt.h"
#include "FzgVerhalten.h"
#include "FzgFahren.h"

using namespace std;

class Fahrzeug : public AktivesVerkehrsobjekt
{
public:
	Fahrzeug();
	Fahrzeug(const Fahrzeug &fahrzeug);
	Fahrzeug(string carName);
	Fahrzeug(string carName, double maxGeschwindigkeit);
	~Fahrzeug();

	void virtual vOstreamAusgabe(ostream& out);

	double dGetGesamtGefahreneStrecke();
	double dGetAbschnittGefahreneStrecke();
	void vSetVerhalten(FzgVerhalten* pVerhalten);

	bool operator<(const Fahrzeug& vergleich);
	Fahrzeug& operator=(const Fahrzeug& fahrzeugZuKopieren);

	void vNeueStrecke(Weg * weg);
	double virtual dGeschwindigkeit();
	double virtual dTanken(double dMenge = -1);
	void virtual vZeichnen(Weg* pWeg);
	void virtual vAbfertigung();
private:
	void vInitialisierung();

protected:
	double p_dGesamtGefahreneStrecke;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtGefahreneZeit;
	double p_dZeitLetzterAbfertigung;
	double p_dAbschnittGefahreneStrecke;
	FzgVerhalten *p_pVerhalten;
	Weg *p_pAktuelleStrecke;

	bool bWurdeSchonAbgefertigt();

	double dBerechneZeitSeitLetzterAbfertigung();
	double dGetRelPosition();
};