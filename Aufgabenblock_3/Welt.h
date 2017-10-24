#pragma once
#include <iostream>
#include "AktivesVerkehrsobjekt.h"
#include <list>
#include <map>
#include "Kreuzung.h"

class Welt
{
public:
	static const string KREUZUNGSTAG;
	static const string STRASSENTAG;
	static const string PKWTAG;
	static const string FAHRRADTAG;

	Welt();
	~Welt();

	void vSimulieren();
	void vEinlesen(ifstream& in);
private:
	list<Kreuzung*> listKreuzungen;

	void vParseIfstream(ifstream& ifstreamKonfig);
};

