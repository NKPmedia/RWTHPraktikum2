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
#include "SimuClient.h"
#include <vector>

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
		(*it)->vAbfertigung();
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
			int x;
			int y;

			ifstreamKonfig >> x;
			ifstreamKonfig >> y;
			AktivesVerkehrsobjekt::vAddPtObjekt(pNeueKreuzung);
			this->listKreuzungen.push_back(pNeueKreuzung);

			bZeichneKreuzung(x, y);
		}
		else if (sObjektType == Welt::STRASSENTAG)
		{
			string sNameQ;
			string sNameZ;
			string sNameW1;
			string sNameW2;
			double dLaenge;
			double dGeschw;
			int iUeberholverbot;
			bool bUeberholverbot;
			int iAnzahlPunkte;
			ifstreamKonfig >> sNameQ;
			ifstreamKonfig >> sNameZ;
			ifstreamKonfig >> sNameW1;
			ifstreamKonfig >> sNameW2;
			ifstreamKonfig >> dLaenge;
			ifstreamKonfig >> dGeschw;
			ifstreamKonfig >> iUeberholverbot;
			if (iUeberholverbot != 0 && iUeberholverbot != 1)
			{
				throw ParseException("ERROR: " + to_string(iUeberholverbot) + " ist keine bool Wert");
			}
			bUeberholverbot = (bool)iUeberholverbot;
			ifstreamKonfig >> iAnzahlPunkte;

			vector<int> pKoordinaten;
			for (int i = 0; i < iAnzahlPunkte; i++)
			{
				int x;
				int y;
				ifstreamKonfig >> x;
				ifstreamKonfig >> y;
				pKoordinaten.push_back(x);
				pKoordinaten.push_back(y);
			}

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

			bZeichneStrasse(sNameW1, sNameW2, dLaenge, iAnzahlPunkte, &pKoordinaten[0]);
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
