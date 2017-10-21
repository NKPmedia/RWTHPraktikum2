#include "Fahrzeug.h"
#include "Pkw.h"
#include "Fahrrad.h"
#include "MathTools.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "main.h"

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

void vAufgabe_3()
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

	Fahrrad* pFahrrad = new Fahrrad("FahrradCopy", 30);
	pFahrrad->vAbfertigung();
	Fahrrad* pCopyFahrrad = new Fahrrad(*pFahrrad);
	cout << *pFahrrad << endl << *pCopyFahrrad << endl << endl;

	Pkw* pPkw2 = new Pkw("t", 0, 0);
	*pPkw2 = *pPkw;
	cout << *pPkw2 << endl << *pPkw << endl << endl;

	cout << "sollte 0 sein, da copy noch nicht gefahren!" << endl;
	cout << (*pFahrrad < *pCopyFahrrad) << endl;
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
			(*fahrzeugeIterator)->vAusgabeFahrzeugInfosInOneRow();
			fahrzeugeIterator++;
		}

		dGlobaleZeit += dZeitTakt;
	}
}

void vAufgabe_1()
{
	Fahrzeug testCarstatic1;
	Fahrzeug testCarstatic2("testName1", 30);
	string name1;
	string name2;
	getline(std::cin, name1);
	getline(std::cin, name2);
	Fahrzeug* testCarDynamic1 = new Fahrzeug(name1);
	Fahrzeug* testCarDynamic2 = new Fahrzeug(name2, 20);

	vSchreibeHeaderFahrzeugAusgabeTabelle();
	testCarDynamic1->vAusgabeFahrzeugInfosInOneRow();
	testCarDynamic2->vAusgabeFahrzeugInfosInOneRow();
	testCarstatic1.vAusgabeFahrzeugInfosInOneRow();
	testCarstatic2.vAusgabeFahrzeugInfosInOneRow();

	double dZeitTakt = 1;
	while (dGlobaleZeit <= 10) {
		testCarDynamic1->vAbfertigung();
		testCarDynamic2->vAbfertigung();
		testCarstatic1.vAbfertigung();
		testCarstatic2.vAbfertigung();

		vSchreibeHeaderFahrzeugAusgabeTabelle();
		testCarDynamic1->vAusgabeFahrzeugInfosInOneRow();
		testCarDynamic2->vAusgabeFahrzeugInfosInOneRow();
		testCarstatic1.vAusgabeFahrzeugInfosInOneRow();
		testCarstatic2.vAusgabeFahrzeugInfosInOneRow();

		dGlobaleZeit += dZeitTakt;
	}

	delete testCarDynamic2;
	delete testCarDynamic1;
}

void vAufgabe_1_deb()
{
	Fahrzeug* testCar1 = new Fahrzeug("testName1", 10);
	Fahrzeug* testCar2 = new Fahrzeug("testName2", 20);
	Fahrzeug* testCar3 = new Fahrzeug("testName3", 30);
	Fahrzeug* testCar4 = new Fahrzeug("testName4", 40);

	vector<Fahrzeug*> fahrzeuge;
	fahrzeuge.push_back(testCar1);
	fahrzeuge.push_back(testCar2);
	fahrzeuge.push_back(testCar3);
	fahrzeuge.push_back(testCar4);

	fahrzeuge[2] = 0;

	double dZeitTakt = 1;
	while (dGlobaleZeit <= 10) {
		
		vector<Fahrzeug*>::iterator fahrzeugeIterator = fahrzeuge.begin();
		int i = 3; //Nur für die Aufgabe mit dem Debugger und em Haltepunkt bei i == 3
		while (fahrzeugeIterator != fahrzeuge.end()) {
			(*fahrzeugeIterator)->vAbfertigung();
			fahrzeugeIterator++;
			i++;
		}

		vSchreibeHeaderFahrzeugAusgabeTabelle();
		fahrzeugeIterator = fahrzeuge.begin();
		while (fahrzeugeIterator != fahrzeuge.end()) {
			(*fahrzeugeIterator)->vAusgabeFahrzeugInfosInOneRow();
			fahrzeugeIterator++;
		}

		dGlobaleZeit += dZeitTakt;
	}

	delete testCar2;
	delete testCar3;
	delete testCar4;
	delete testCar1;
}

int main()
{
	vAufgabe_2();
	cin.get();
	cin.get();
	return 0;
}