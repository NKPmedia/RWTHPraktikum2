#include <string>

using namespace std;

class Fahrzeug
{
public:
	Fahrzeug();
	Fahrzeug(string carName);
	Fahrzeug(string carName, double maxGeschwindigkeit);
	~Fahrzeug();

	void vAusgabeFahrzeugInfosInOneRow();
	void vAbfertigung();
private:
	static int p_iMaxID;
	string p_sName;
	int p_iID;
	double p_dMaxGeschwindigkeit;
	double p_dGesamtGefahreneStrecke;
	double p_dGesamtGefahreneZeit;
	double p_dZeitLetzterAbfertigung;

	void vInitIDWithUniqueNumber();
	void vInitialisierung();
	double dBerechneZeitSeitLetzterAbfertigung();
	bool bWurdeSchonAbgefertigt();
	double dBerechneGefahreneStreckeInZeit(double zeit);

};

