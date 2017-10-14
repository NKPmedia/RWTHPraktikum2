#include "AktivesVerkehrsobjekt.h"

extern double dGlobaleZeit;
int AktivesVerkehrsobjekt::p_iMaxID = 0;

AktivesVerkehrsobjekt::AktivesVerkehrsobjekt() : p_sName(""), lokaleZeit(0)
{
	this->vInitIDWithUniqueNumber();
}

AktivesVerkehrsobjekt::AktivesVerkehrsobjekt(string name) : p_sName(name), lokaleZeit(0)
{
	this->vInitIDWithUniqueNumber();
}


AktivesVerkehrsobjekt::~AktivesVerkehrsobjekt()
{
}

string AktivesVerkehrsobjekt::sGetName()
{
	return this->p_sName;
}

void AktivesVerkehrsobjekt::vOstreamAusgabe(ostream & out)
{
	out.precision(2);
	out << fixed;

	out << this->p_iID;

	out.width(10);
	out << this->p_sName.c_str();

	out.width(10);
	out << ":";
}

void AktivesVerkehrsobjekt::vAbfertigung()
{
}

void AktivesVerkehrsobjekt::vInitIDWithUniqueNumber()
{
	this->p_iID = AktivesVerkehrsobjekt::p_iMaxID + 1;
	AktivesVerkehrsobjekt::p_iMaxID = this->p_iID;
}


ostream& operator <<(ostream& out, AktivesVerkehrsobjekt& fahrzeug)
{
	fahrzeug.vOstreamAusgabe(out);
	return out;
}

bool AktivesVerkehrsobjekt::operator==(const AktivesVerkehrsobjekt& rhs) 
{
	return this->p_iID == rhs.p_iID;
}