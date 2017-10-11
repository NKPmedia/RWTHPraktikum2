#pragma once
#include <string>

using namespace std;

class Fahrzeug
{
public:
	Fahrzeug();
	Fahrzeug(const Fahrzeug &fahrzeug);
	Fahrzeug(string carName);
	Fahrzeug(string carName, double maxGeschwindigkeit);
	~Fahrzeug();

	void virtual vOstreamAusgabe(ostream& out);
	void virtual vAusgabeFahrzeugInfosInOneRow();
	void virtual vAbfertigung();

	double dGetGesamtGefahreneStrecke();
	double virtual dTanken(double dMenge = -1);

	bool operator<(const Fahrzeug& vergleich);
	Fahrzeug& operator=(const Fahrzeug& fahrzeugZuKopieren);
private:
	static int p_iMaxID;

	void vInitIDWithUniqueNumber();
	void vInitialisierung();

protected:
	double p_dGesamtGefahreneStrecke;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtGefahreneZeit;
	double p_dZeitLetzterAbfertigung;
	string p_sName;
	int p_iID;

	bool bWurdeSchonAbgefertigt();

	double dBerechneZeitSeitLetzterAbfertigung();
	double dBerechneGefahreneStreckeInZeit(double zeit);
	double virtual dGeschwindigkeit();
};

ostream& operator <<(ostream& out, Fahrzeug&x);