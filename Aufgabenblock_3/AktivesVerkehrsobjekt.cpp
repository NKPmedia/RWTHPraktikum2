#include "AktivesVerkehrsobjekt.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include "MapException.h"

using namespace std;

extern double dGlobaleZeit;
int AktivesVerkehrsobjekt::p_iMaxID = 0;
map <string, AktivesVerkehrsobjekt*> AktivesVerkehrsobjekt::mapAlleAVObjekte;


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

istream& AktivesVerkehrsobjekt::istreamEingabe(istream& in)
{
	if (this->p_sName != "")
	{
		throw "Error: man kann nur leere Objekte befuellen";
	}
	in >> this->p_sName;
	return in;
}

AktivesVerkehrsobjekt * AktivesVerkehrsobjekt::ptObjekt(string sName)
{
	if (AktivesVerkehrsobjekt::doesAVObjektNameExist(sName))
	{
		return AktivesVerkehrsobjekt::mapAlleAVObjekte[sName];
	}
	else
	{
		throw MapException("ERROR: "+sName+" exestiert nicht!");
	}
}

void AktivesVerkehrsobjekt::vAddPtObjekt(AktivesVerkehrsobjekt * pObjekt)
{
	if(AktivesVerkehrsobjekt::doesAVObjektNameExist(pObjekt->p_sName))
	{
		throw MapException("ERROR: Objekt "+pObjekt->p_sName+" existiert bereits");
	}
	else
	{
		AktivesVerkehrsobjekt::mapAlleAVObjekte[pObjekt->p_sName] = pObjekt;
		cout << pObjekt->p_sName << " wurde hinzugefuegt" << endl;
	}
}

void AktivesVerkehrsobjekt::vAddPtObjekte(list<AktivesVerkehrsobjekt*> listObjekte)
{
	list<AktivesVerkehrsobjekt*>::iterator it;
	for (it = listObjekte.begin(); it != listObjekte.end(); it++)
	{
		AktivesVerkehrsobjekt::vAddPtObjekt((*it));
	}
}

void AktivesVerkehrsobjekt::vInitIDWithUniqueNumber()
{
	this->p_iID = AktivesVerkehrsobjekt::p_iMaxID + 1;
	AktivesVerkehrsobjekt::p_iMaxID = this->p_iID;
}

bool AktivesVerkehrsobjekt::doesAVObjektNameExist(string name)
{
	if (AktivesVerkehrsobjekt::mapAlleAVObjekte.count(name) > 0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}


ostream& operator <<(ostream& out, AktivesVerkehrsobjekt& fahrzeug)
{
	fahrzeug.vOstreamAusgabe(out);
	return out;
}

istream & operator>>(istream & in, AktivesVerkehrsobjekt & x)
{
	x.istreamEingabe(in);
	return in;
}

bool AktivesVerkehrsobjekt::operator==(const AktivesVerkehrsobjekt& rhs) 
{
	return this->p_iID == rhs.p_iID;
}