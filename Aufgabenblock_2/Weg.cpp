#include "Weg.h"
#include <list>
#include "Fahrzeug.h"
#include "FzgParken.h"
#include "FahrAusnahme.h"
#include "LazyListe.h"

using namespace std;

Weg::Weg()
{
}

Weg::Weg(string sName, double dLaenge, GeschwindigkeitBegrenzung eLimit) : AktivesVerkehrsobjekt(sName), p_dLaenge(dLaenge), p_eLimit(eLimit)
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
	list<Fahrzeug*>::iterator pFahrzeugIterator = this->p_pFahrzeugeAufWeg.begin();
	while (pFahrzeugIterator != this->p_pFahrzeugeAufWeg.end())
	{
		try 
		{
			(*pFahrzeugIterator)->vAbfertigung();
		}
		catch (FahrAusnahme& exception)
		{
			exception.vBearbeiten();
		}

		(*pFahrzeugIterator)->vZeichnen(this);
		pFahrzeugIterator++;
	}
	this->p_pFahrzeugeAufWeg.vAktualisieren();
}

double Weg::dGetLaenge()
{
	return this->p_dLaenge;
}

double Weg::dGetLimit()
{
	return this->p_eLimit;
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
}

void Weg::vAbgeben(Fahrzeug * fahrzeug)
{
	LazyListe<Fahrzeug*>::iterator it = find(p_pFahrzeugeAufWeg.begin(), p_pFahrzeugeAufWeg.end(), fahrzeug);
	this->p_pFahrzeugeAufWeg.erase(it);
}
