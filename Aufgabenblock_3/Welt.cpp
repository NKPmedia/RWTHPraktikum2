#include "Welt.h"
#include "Kreuzung.h"
#include "Weg.h"
#include "Pkw.h"
#include "Fahrrad.h"
#include <iostream> 
#include <fstream> 
#include <strstream> 
#include <list>
#include "ParseException.h"

const string Welt::KREUZUNGSTAG = "KREUZUNG";
const string Welt::STRASSENTAG = "STRASSE";
const string Welt::PKWTAG = "PKW";
const string Welt::FAHRRADTAG = "FAHRRAD";

Welt::Welt()
{
}


Welt::~Welt()
{
}

void Welt::vSimulieren()
{
	list<Kreuzung*>::iterator it;
	for (it = this->listKreuzungen.begin(); it != this->listKreuzungen.end(); it++)
	{

	}
}

void Welt::vEinlesen(ifstream & in)
{
	try
	{
		this->vParseIfstream(in);
	}
	catch (const char* s) 
	{
		cout << s;
	}
	catch (const ExceptionString s)
	{
		cout << s.what();
	}
}

void Welt::vParseIfstream(ifstream & ifstreamKonfig)
{
	list<AktivesVerkehrsobjekt*> listObjekte;

	string sObjektType;
	ifstreamKonfig >> sObjektType;
	while (!ifstreamKonfig.eof())
	{
		if (sObjektType == Welt::KREUZUNGSTAG)
		{
			Kreuzung* pNeueKreuzung = new Kreuzung();
			ifstreamKonfig >> *pNeueKreuzung;
			AktivesVerkehrsobjekt::vAddPtObjekt(pNeueKreuzung);
			this->listKreuzungen.push_back(pNeueKreuzung);
		}
		else if (sObjektType == Welt::STRASSENTAG)
		{
			string sNameQ;
			string sNameZ;
			string sNameW1;
			string sNameW2;
			double dLaenge;
			double dGeschw;
			bool bUeberholverbot;
			ifstreamKonfig >> sNameQ;
			ifstreamKonfig >> sNameZ;
			ifstreamKonfig >> sNameW1;
			ifstreamKonfig >> sNameW2;
			ifstreamKonfig >> dLaenge;
			ifstreamKonfig >> dGeschw;
			ifstreamKonfig >> bUeberholverbot;

			Kreuzung* kr1 = (Kreuzung*)AktivesVerkehrsobjekt::ptObjekt(sNameQ);
			Kreuzung* kr2 = (Kreuzung*)AktivesVerkehrsobjekt::ptObjekt(sNameZ);
			if (kr2->type == "Kreuzung" && kr1->type == "Kreuzung") {
				kr1->vVerbinde(sNameW1, sNameW2, dLaenge, kr2, Weg::zuGeschwindigkeitBegrenzung(dGeschw), bUeberholverbot);
				cout << "Strasse " << sNameQ << endl;
			}
			else
			{
				throw ParseException("ERROR: " + sNameZ + " oder "+sNameQ+" ist keine Kreuzung");
			}
		}
		else if (sObjektType == Welt::PKWTAG)
		{
			Pkw* pNeuePkw = new Pkw();
			ifstreamKonfig >> *pNeuePkw;
			string sName;
			double dLosFahren;
			ifstreamKonfig >> sName;
			ifstreamKonfig >> dLosFahren;
			AktivesVerkehrsobjekt::vAddPtObjekt(pNeuePkw);
			Kreuzung* kr = (Kreuzung*)AktivesVerkehrsobjekt::ptObjekt(sName);
			kr->vAnnehmen(pNeuePkw, dLosFahren);
		}
		else if (sObjektType == Welt::FAHRRADTAG)
		{
			Fahrrad* pNeueFahrrad = new Fahrrad();
			ifstreamKonfig >> *pNeueFahrrad;
			string sName;
			double dLosFahren;
			ifstreamKonfig >> sName;
			ifstreamKonfig >> dLosFahren;
			AktivesVerkehrsobjekt::vAddPtObjekt(pNeueFahrrad);
			Kreuzung* kr = (Kreuzung*)AktivesVerkehrsobjekt::ptObjekt(sName);
			kr->vAnnehmen(pNeueFahrrad, dLosFahren);
		}
		else
		{
			throw ParseException("ERROR: TAG " + sObjektType);
		}
		ifstreamKonfig >> sObjektType;
	}
}
