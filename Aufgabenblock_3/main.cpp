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
#include "Kreuzung.h"
#include <fstream>
#include "Welt.h"

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

void vAufgabe_2_4_5()
{
	Weg* weg = new Weg("test", 20, Weg::Innerorts);
	Weg* weg2 = new Weg("aussen", 20, Weg::Autobahnbahn);

	Pkw* pPkw = new Pkw("BMW", 10, 20, 5);
	Pkw* pPkw2 = new Pkw("Audi", 10, 20, 5);
	Fahrrad* pFahrrad = new Fahrrad("BMX", 30);

	weg->vAnnehmen(pPkw);
	weg->vAnnehmen(pPkw2);
	weg->vAnnehmen(pFahrrad);

	cout << *weg;

	vSchreibeHeaderFahrzeugAusgabeTabelle();
	cout << *pPkw << endl;
	cout << *pPkw2 << endl;
	cout << *pFahrrad << endl;

	dGlobaleZeit = 1.0;
	weg->vAbfertigung();
	
	vSchreibeHeaderFahrzeugAusgabeTabelle();
	cout << *pPkw << endl;
	cout << *pPkw2 << endl;
	cout << *pFahrrad << endl;
}

void vAufgabe_2_4_9_amEndAngekommen()
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

void vAufgabe_2_4_9_Parken()
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
	cout << dGlobaleZeit << endl;
	weg->vAbfertigung();
	dGlobaleZeit = 2.0;
	cout << dGlobaleZeit << endl;
	weg->vAbfertigung();
	dGlobaleZeit = 3.0;
	cout << dGlobaleZeit << endl;
	weg->vAbfertigung();
}

void vAufgabe_2_5_4()
{
	Weg* pWegInnen = new Weg("innen", 500, Weg::Innerorts);
	Weg* pWegAutobahn = new Weg("aBahn", 500, Weg::Autobahnbahn);

	Pkw* pPkwFahr = new Pkw("BMW", 120, 5, 50);
	Fahrrad* pFahrradPark = new Fahrrad("BMX", 30);
	Pkw* pPkwPark = new Pkw("Audi", 130, 5, 100);
	Fahrrad* pFahrradFahr = new Fahrrad("Velo", 30);

	pWegInnen->vAnnehmen(pPkwFahr);
	pWegInnen->vAnnehmen(pFahrradPark, 2);
	pWegAutobahn->vAnnehmen(pPkwPark, 4);
	pWegAutobahn->vAnnehmen(pFahrradFahr);

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

void vAufgabe_3_7()
{
	Weg* pWegInnen = new Weg("innen", 500, Weg::Innerorts, true);
	Weg* pWegAutobahn = new Weg("aBahn", 500, Weg::Autobahnbahn, true);

	Pkw* pPkwFahr = new Pkw("BMW", 120, 5, 10);
	Fahrrad* pFahrradPark = new Fahrrad("BMX", 30);
	Pkw* pPkwPark = new Pkw("Audi", 130, 5, 100);

	pWegInnen->vAnnehmen(pPkwFahr, 4);
	pWegInnen->vAnnehmen(pFahrradPark, 2);
	
	bInitialisiereGrafik(800, 800);
	int koordinaten[] = { 700, 250, 100, 250 };
	bZeichneStrasse(pWegInnen->sGetName(), pWegAutobahn->sGetName(), 500, 2, koordinaten);


	dGlobaleZeit = 0.0;
	double dZeitTakt = 0.1;
	while (dGlobaleZeit <= 100)
	{
		vSetzeZeit(dGlobaleZeit);
		vSleep(1);

		if (MathTools::nearly_equal(dGlobaleZeit, 10.0))
		{
			pWegInnen->vAnnehmen(pPkwPark, 12);
		}

		pWegAutobahn->vAbfertigung();
		pWegInnen->vAbfertigung();

		cout << *pWegInnen << endl;

		dGlobaleZeit += dZeitTakt;
	}

}

void vAufgabe_3_8()
{
	bInitialisiereGrafik(1000, 1000);

	Kreuzung* kr1 = new Kreuzung();
	Kreuzung* kr2 = new Kreuzung();
	kr2->vSetTankstelle(1000);
	Kreuzung* kr3 = new Kreuzung();
	Kreuzung* kr4 = new Kreuzung();

	kr1->vVerbinde("W12", "W21", 40, kr2, Weg::Innerorts, true);
	kr2->vVerbinde("W23a", "W32a", 115, kr3, Weg::Autobahnbahn, false);
	kr2->vVerbinde("W23b", "W32b", 40, kr3, Weg::Innerorts, true);
	kr2->vVerbinde("W24", "W42", 55, kr4, Weg::Innerorts, true);
	kr3->vVerbinde("W34", "W43", 85, kr4, Weg::Autobahnbahn, false);
	kr4->vVerbinde("W44a", "W44b", 130, kr4, Weg::Landstraße, false);

	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	int koordinaten[] = { 680, 40, 680, 300 };
	bZeichneStrasse("W12", "W21", 40, 2, koordinaten);

	int koordinaten2[] = { 680, 300, 850, 300 ,970, 390, 970, 500, 850, 570, 680, 570};
	bZeichneStrasse("W23a", "W32a", 115, 6, koordinaten2);

	int koordinaten3[] = { 680, 300, 680, 570};
	bZeichneStrasse("W23b", "W32b", 40, 2, koordinaten3);

	int koordinaten4[] = { 680, 300, 320, 300 };
	bZeichneStrasse("W24", "W42", 55, 2, koordinaten4);

	int koordinaten5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	bZeichneStrasse("W34", "W43", 85, 5, koordinaten5);

	int koordinaten6[] = { 320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300 };
	bZeichneStrasse("W44a", "W44b", 130, 7, koordinaten6);

	Pkw* pPkwFahr = new Pkw("BMW", 120, 5, 10);
	Fahrrad* pFahrradPark = new Fahrrad("BMX", 30);
	Pkw* pPkwPark = new Pkw("Audi", 130, 5, 100);



	kr1->vAnnehmen(pPkwFahr, 2);
	kr1->vAnnehmen(pFahrradPark, 4);

	dGlobaleZeit = 0.0;
	double dZeitTakt = 0.1;
	while (dGlobaleZeit <= 100)
	{
		vSetzeZeit(dGlobaleZeit);
		vSleep(1);

		if (MathTools::nearly_equal(dGlobaleZeit, 10.0))
		{
			kr1->vAnnehmen(pPkwPark, 12);
		}

		kr1->vAbfertigung();
		kr2->vAbfertigung();
		kr3->vAbfertigung();
		kr4->vAbfertigung();

		dGlobaleZeit += dZeitTakt;
	}

}

void vAufgabe_3_9()
{
	bInitialisiereGrafik(1000, 1000);

	ifstream fin("SimuDisplay.dat");
	if (!fin.good())
	{
		cout << "ERROR mit Datei" << endl;
	}
		
	Welt* welt = new Welt();
	welt->vEinlesen(fin);

	dGlobaleZeit = 0.0;
	double dZeitTakt = 0.1;
	while (dGlobaleZeit <= 100)
	{
		vSetzeZeit(dGlobaleZeit);
		vSleep(1);

		welt->vSimulieren();

		dGlobaleZeit += dZeitTakt;
	}

}
int main()
{
	vAufgabe_3_9();
	cin.get();
	return 0;
}