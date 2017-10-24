#pragma once
#include <string>
#include <map>
#include <list>

using namespace std;

class AktivesVerkehrsobjekt
{
public:
	AktivesVerkehrsobjekt();
	AktivesVerkehrsobjekt(string name);
	~AktivesVerkehrsobjekt();

	const string type = "AVO";

	string sGetName();

	void virtual vOstreamAusgabe(ostream& out);
	istream virtual & istreamEingabe(istream& in);
	bool operator==(const AktivesVerkehrsobjekt& rhs);
	void virtual vAbfertigung() = 0;
	static AktivesVerkehrsobjekt* ptObjekt(string sName);
	static void vAddPtObjekt(AktivesVerkehrsobjekt* pObjekt);
	static void vAddPtObjekte(list<AktivesVerkehrsobjekt*> listObjekte);
	static bool doesAVObjektNameExist(string);
private:
	static int p_iMaxID;
	static map <string, AktivesVerkehrsobjekt*> mapAlleAVObjekte;

	void vInitIDWithUniqueNumber();
protected:
	string p_sName;
	int p_iID;

	double lokaleZeit;
};

ostream& operator <<(ostream& out, AktivesVerkehrsobjekt& x);
istream& operator >>(istream& in, AktivesVerkehrsobjekt& x);