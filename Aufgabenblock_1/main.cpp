#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>
#include <vector>

using  namespace std;

double dGlobaleZeit = 0.0;

void vSchreibeHeaderFahrzeugAusgabeTabelle()
{
	cout << "\nID";
	cout.width(10);
	cout << "Name";
	cout.width(10);
	cout << ":";
	cout.width(10);
	cout << "MaxKmh";
	cout.width(20);
	cout << "GesamtStrecke" << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void vAufgabe_1()
{
	Fahrzeug testCarstatic1;
	Fahrzeug testCarstatic2("testName1",30);
	Fahrzeug* testCarDynamic1 = new Fahrzeug();
	Fahrzeug* testCarDynamic2 = new Fahrzeug("testName2",20);

	vSchreibeHeaderFahrzeugAusgabeTabelle();
	testCarDynamic1->vAusgabeFahrzeugInfosInOneRow();
	testCarDynamic2->vAusgabeFahrzeugInfosInOneRow();
	testCarstatic1.vAusgabeFahrzeugInfosInOneRow();
	testCarstatic2.vAusgabeFahrzeugInfosInOneRow();

	double dZeitTakt = 500.0;
	while (dGlobaleZeit <= 10000) {
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

	double dZeitTakt = 500.0;
	while (dGlobaleZeit <= 10000) {
		
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
	vAufgabe_1_deb();
	cin.get();
	return 0;
}