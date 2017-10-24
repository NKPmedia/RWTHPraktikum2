#pragma once
#include "AktivesVerkehrsobjekt.h"
#include <list>
#include <iostream>
#include <string>

class KonfigDateiLader
{
public:
	KonfigDateiLader();
	~KonfigDateiLader();

	static const string KREUZUNGSTAG;
	static const string STRASSENTAG;
	static const string PKWTAG;
	static const string FAHRRADTAG;

	list<AktivesVerkehrsobjekt*>& listGetAVObjekteVonKonfig(string sPfad);

};

