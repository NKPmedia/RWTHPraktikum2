#include "Weg.h"
#include <list>
#include "Fahrzeug.h"
#include "FzgParken.h"
#include "FahrAusnahme.h"
#include "LazyListe.h"
#include "DataHalterFahrzeug.h"
#include "MathTools.h"

using namespace std;

Weg::Weg()
{
}

Weg::Weg(string sName, double dLaenge, GeschwindigkeitBegrenzung eLimit, bool bUeberholverbot) 
	: AktivesVerkehrsobjekt(sName),
	p_dLaenge(dLaenge),
	p_eLimit(eLimit),
	p_bUeberholverbot(bUeberholverbot),
	iParkendeFahrzeuge(0)
{
}


Weg::~Weg()
{
}

void Weg::vOstreamAusgabe(ostream & out)
{
	AktivesVerkehrsobjekt::vOstreamAusgabe(out);
	out.precision(2);
	out << fixed;

	out << this->p_dLaenge;

	out << " ( ";
	list<Fahrzeug*>::iterator pFahrzeugIterator = this->p_pFahrzeugeAufWeg.begin();
	while (pFahrzeugIterator != this->p_pFahrzeugeAufWeg.end())
	{
		out << (*pFahrzeugIterator)->sGetName() << " ";
		pFahrzeugIterator++;
	}
	out << ")";
}

void Weg::vAbfertigung()
{
	this->p_pFahrzeugeAufWeg.vAktualisieren();
	this->p_pFahrzeugeAufWeg.vSortiereNurFahrendeFahrzeuge(this->iParkendeFahrzeuge);

	Fahrzeug* datenHalter = new DataHalterFahrzeug();
	datenHalter->vSetAbschnittGefahreneStrecke(this->p_dLaenge);
	this->pZuLetztAbgefertigtesFahrzeug = datenHalter;

	list<Fahrzeug*>::iterator pFahrzeugIterator = this->p_pFahrzeugeAufWeg.begin();
	while (pFahrzeugIterator != this->p_pFahrzeugeAufWeg.end())
	{
		try 
		{
			(*pFahrzeugIterator)->vAbfertigung();
			if ((*pFahrzeugIterator)->istFahrrend())
			{
				this->pZuLetztAbgefertigtesFahrzeug = (*pFahrzeugIterator);
			}
		}
		catch (FahrAusnahme& exception)
		{
			exception.vBearbeiten();
		}

		(*pFahrzeugIterator)->vZeichnen(this);
		pFahrzeugIterator++;
	}
	this->p_pFahrzeugeAufWeg.vAktualisieren();

	delete datenHalter;
}

double Weg::dGetLaenge()
{
	return this->p_dLaenge;
}

double Weg::dGetLimit()
{
	return this->p_eLimit;
}

Weg * Weg::pGetZugehoerigerWeg()
{
	return this->p_pZugehoerigerWeg;
}

Kreuzung * Weg::pGetZielKreuzung()
{
	return this->p_pZielKreuzung;
}

void Weg::vSetZugehoerigerWeg(Weg * weg)
{
	this->p_pZugehoerigerWeg = weg;
}

void Weg::vSetZielKreuzung(Kreuzung * kreu)
{
	this->p_pZielKreuzung = kreu;
}

bool Weg::bIstUeberholverbot()
{
	return this->p_bUeberholverbot;
}

Weg::GeschwindigkeitBegrenzung Weg::zuGeschwindigkeitBegrenzung(double gesch)
{
	if (gesch == 1) {
		return Weg::Innerorts;
	}
	else if (gesch == 2)
	{
		return Weg::Landstraße;
	}
	else if (gesch == 3)
	{
		return Weg::Autobahnbahn;
	}
	else 
	{
		throw "ERROR: Falsche Gesch";
	}
}

void Weg::vAnnehmen(Fahrzeug * fahrzeug)
{
	this->p_pFahrzeugeAufWeg.push_back(fahrzeug);
	fahrzeug->vNeueStrecke(this);
	fahrzeug->vSetVerhalten(new FzgFahren(this));
}

void Weg::vAnnehmen(Fahrzeug * fahrzeug, double dStartZeit)
{
	this->p_pFahrzeugeAufWeg.push_front(fahrzeug);
	fahrzeug->vNeueStrecke(this);
	fahrzeug->vSetVerhalten(new FzgParken(this, dStartZeit));
	this->iParkendeFahrzeuge++;
}

void Weg::vAbgeben(Fahrzeug * fahrzeug)
{
	LazyListe<Fahrzeug*>::iterator it = find(p_pFahrzeugeAufWeg.begin(), p_pFahrzeugeAufWeg.end(), fahrzeug);
	this->p_pFahrzeugeAufWeg.erase(it);
}
