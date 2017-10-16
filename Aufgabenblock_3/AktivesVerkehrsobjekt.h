#pragma once
#include <string>

using namespace std;

class AktivesVerkehrsobjekt
{
public:
	AktivesVerkehrsobjekt();
	AktivesVerkehrsobjekt(string name);
	~AktivesVerkehrsobjekt();

	string sGetName();

	void virtual vOstreamAusgabe(ostream& out);
	bool operator==(const AktivesVerkehrsobjekt& rhs);
	void virtual vAbfertigung();
private:
	static int p_iMaxID;

	void vInitIDWithUniqueNumber();
protected:
	string p_sName;
	int p_iID;

	double lokaleZeit;
};

ostream& operator <<(ostream& out, AktivesVerkehrsobjekt&x);