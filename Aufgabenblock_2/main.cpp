#include "Fahrzeug.h"
#include "Pkw.h"
#include "Fahrrad.h"
#include "MathTools.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "main.h"
#include "Weg.h"
#include "SimuClient.h"
#include "LazyListe.h"
#include <stdlib.h>

using  namespace std;

double dGlobaleZeit = 0.0;

void vTankeAlleFahrzeuge(vector<Fahrzeug*> &fahrzeuge)
{
	vector<Fahrzeug*>::iterator fahrzeugeIterator = fahrzeuge.begin();
	while (fahrzeugeIterator != fahrzeuge.end()) {
		(*fahrzeugeIterator)->dTanken();
		fahrzeugeIterator++;
	}
}

void vSchreibeHeaderFahrzeugAusgabeTabelle()
{
	cout << "\nID";

	cout.width(10);
	cout << "Name";

	cout.width(10);
	cout << ":";

	cout.width(10);
	cout << "MaxKmh";

	cout.width(10);
	cout << "Kmh";

	cout.width(20);
	cout << "GesamtStrecke";

	cout.width(20);
	cout << "Gesamtverbrauch";

	cout.width(20);
	cout << "Verbrauch/100Km";

	cout.width(10);
	cout << "Tank" << endl;

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void vAufgabe_2()
{
	/*
	Zeige das der Copy-Konstruktors funktionier
	Ich lasse ihn nur die konstanten Daten kopieren, da ein neues Auto immer bei z.B. 0km anfängt

	*/
	dGlobaleZeit = 1.0;
	Pkw* pPkw = new Pkw("PkwCopy", 10, 20, 5);
	pPkw->vAbfertigung();
	Pkw* pCopyPkw = new Pkw(*pPkw);
	cout << *pPkw << endl << *pCopyPkw << endl << endl;

	Fahrrad* pFahrrad= new Fahrrad("FahrradCopy", 30);
	pFahrrad->vAbfertigung();
	Fahrrad* pCopyFahrrad = new Fahrrad(*pFahrrad);
	cout << *pFahrrad << endl << *pCopyFahrrad << endl << endl;

	Pkw* pPkw2 = new Pkw("t",0,0);
	*pPkw2 = *pPkw;
	cout << *pPkw2 << endl << *pPkw << endl << endl;

	//Frage wie viele Pkw und Fahrräder erstellt werden sollen
	printf("Wie viele Pkw sollen erstellt werden?");
	int iAnzahlZuErzeugenderPkw = 0;
	scanf_s("%d", &iAnzahlZuErzeugenderPkw);

	printf("Wie viele Fahhräder sollen erstellt werden?");
	int iAnzahlZuErzeugenderFahrraeder = 0;
	scanf_s("%d", &iAnzahlZuErzeugenderFahrraeder);

	vector<Fahrzeug*> vFahrzeuge;

	for (int i = 1; i <= iAnzahlZuErzeugenderFahrraeder; i++)
	{
		Fahrrad* fahrrad = new Fahrrad("Fahrrad " + to_string(i), 20*i);
		vFahrzeuge.push_back(fahrrad);
	}
	for (int i = 1; i <= iAnzahlZuErzeugenderPkw; i++)
	{
		Pkw* pkw = new Pkw("Pwk " + to_string(i), 10 * i, 20, 5);
		vFahrzeuge.push_back(pkw);
	}

	//Lass die Autos fahren
	dGlobaleZeit = 0.0;
	double dZeitTakt = 1.0;
	while (dGlobaleZeit <= 10) {
		vSchreibeHeaderFahrzeugAusgabeTabelle();

		if (MathTools::nearly_equal(dGlobaleZeit, 3.0))
		{
			vTankeAlleFahrzeuge(vFahrzeuge);
		}

		vector<Fahrzeug*>::iterator fahrzeugeIterator = vFahrzeuge.begin();
		while (fahrzeugeIterator != vFahrzeuge.end()) {
			(*fahrzeugeIterator)->vAbfertigung();
			cout << *(*fahrzeugeIterator) << endl;
			fahrzeugeIterator++;
		}

		dGlobaleZeit += dZeitTakt;
	}
}

void vAufgabe_2_4()
{
	Weg* weg = new Weg("test", 20, Weg::Innerorts);

	Pkw* pPkw = new Pkw("BMW", 10, 20, 5);
	Pkw* pPkw2 = new Pkw("Audi", 10, 20, 5);
	Fahrrad* pFahrrad = new Fahrrad("BMX", 30);

	weg->vAnnehmen(pPkw);
	weg->vAnnehmen(pPkw2, 2);
	weg->vAnnehmen(pFahrrad);

	cout << *weg;

	vSchreibeHeaderFahrzeugAusgabeTabelle();
	cout << *pPkw << endl;
	cout << *pPkw2 << endl;
	cout << *pFahrrad << endl;

	dGlobaleZeit = 3.0;
	weg->vAbfertigung();
	weg->vAbfertigung();
	cout << *weg;
	
	vSchreibeHeaderFahrzeugAusgabeTabelle();
	cout << *pPkw << endl;
	cout << *pPkw2 << endl;
	cout << *pFahrrad << endl;
	cout << *weg;
}

void vAufgabe_2_4_amEndAngekommen()
{
	Weg* weg = new Weg("test", 20, Weg::Innerorts);

	Pkw* pPkw = new Pkw("BMW", 10, 20, 20);

	weg->vAnnehmen(pPkw);

	dGlobaleZeit = 1.0;
	weg->vAbfertigung();
	dGlobaleZeit = 2.0;
	weg->vAbfertigung();
	dGlobaleZeit = 3.0;
	weg->vAbfertigung();
}

void vAufgabe_2_4_Parken()
{
	Weg* weg = new Weg("test", 20, Weg::Innerorts);

	Pkw* pPkw = new Pkw("BMW", 100, 20, 20);

	weg->vAnnehmen(pPkw, 3);

	dGlobaleZeit = 1.0;
	weg->vAbfertigung();
	dGlobaleZeit = 2.0;
	weg->vAbfertigung();
	dGlobaleZeit = 3.0;
	weg->vAbfertigung();
}

void vAufgabe_2_5_2()
{
	Weg* weg = new Weg("test", 20, Weg::Innerorts);

	Pkw* pPkw = new Pkw("BMW", 100, 20, 20);
	Fahrrad* pFahrrad = new Fahrrad("BMX", 30);

	weg->vAnnehmen(pPkw, 3);
	weg->vAnnehmen(pFahrrad);

	dGlobaleZeit = 1.0;
	cout << "G: " << dGlobaleZeit << endl;
	vSchreibeHeaderFahrzeugAusgabeTabelle();
	cout << *pFahrrad << endl;
	cout << *pPkw << endl;
	weg->vAbfertigung();
	dGlobaleZeit = 2.0;
	cout << "G: " << dGlobaleZeit << endl;
	cout << *pFahrrad << endl;
	cout << *pPkw << endl;
	weg->vAbfertigung();
	dGlobaleZeit = 3.0;
	cout << "G: " << dGlobaleZeit << endl;
	cout << *pFahrrad << endl;
	cout << *pPkw << endl;
	weg->vAbfertigung();
}

void vAufgabe_2_6()
{
	Weg* pWegInnen = new Weg("innen", 500, Weg::Innerorts);
	Weg* pWegAutobahn = new Weg("aBahn", 500, Weg::Landstraße);

	Pkw* pPkwFahr = new Pkw("Auto_un", 100, 10, 200);
	Fahrrad* pFahrradPark = new Fahrrad("Velo_on", 50);
	Pkw* pPkwPark = new Pkw("Auto_deux", 100, 10, 200);
	Fahrrad* pFahrradFahr = new Fahrrad("Velo_deux", 50);

	pWegInnen->vAnnehmen(pFahrradPark);
	pWegInnen->vAnnehmen(pPkwFahr, 1.2);
	pWegAutobahn->vAnnehmen(pFahrradFahr, 1.4);
	pWegAutobahn->vAnnehmen(pPkwPark);

	bInitialisiereGrafik(800, 800);
	int koordinaten[] = { 700, 250, 100, 250 };
	bZeichneStrasse(pWegInnen->sGetName(), pWegAutobahn->sGetName(), 500, 2, koordinaten);


	dGlobaleZeit = 0.0;
	double dZeitTakt = 0.1;
	while (dGlobaleZeit <= 100) 
	{
		vSetzeZeit(dGlobaleZeit);
		vSleep(1);

		if (MathTools::nearly_equal(dGlobaleZeit, 30.0))
		{
			
		}
		
		pWegAutobahn->vAbfertigung();
		pWegInnen->vAbfertigung();

		dGlobaleZeit += dZeitTakt;
	}

}

void vAufgabe_2_6a()
{
	srand(time(NULL));

	LazyListe<int>* liste = new LazyListe<int>();

	for (int i = 0; i < 10; i++)
	{
		liste->push_back((int)(rand() % 11));
	}
	liste->vAktualisieren();

	LazyListe<int>::iterator point;
	for ( point = liste->begin(); point != liste->end(); point++)
	{
		cout << (*point) << " ";
	}
	cout << endl;

	for (point = liste->begin(); point != liste->end(); point++)
	{
		if (*point > 5)
		{
			liste->erase(point);
		}
	}

	for (point = liste->begin(); point != liste->end(); point++)
	{
		cout << (*point) << " ";
	}
	cout << endl;

	liste->vAktualisieren();
	for (point = liste->begin(); point != liste->end(); point++)
	{
		cout << (*point) << " ";
	}
	cout << endl;
}

int main()
{
	vAufgabe_2_6a();
	cin.get();
	return 0;
}