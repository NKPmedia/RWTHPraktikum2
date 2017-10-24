#include "KonfigDateiLader.h"
#include <iostream> 
#include <fstream> 
#include <strstream> 
#include <list>
#include "Kreuzung.h"
#include "Weg.h"
#include "Pkw.h"
#include "Fahrrad.h"

using namespace std;



KonfigDateiLader::KonfigDateiLader()
{
}


KonfigDateiLader::~KonfigDateiLader()
{
}

list<AktivesVerkehrsobjekt*>& KonfigDateiLader::listGetAVObjekteVonKonfig(string sPfad)
{

	ifstream fin("efef");
	list<AktivesVerkehrsobjekt*>& listObjekte = this->listParseIfstream(fin);

	return listObjekte;
}

list<AktivesVerkehrsobjekt*>& KonfigDateiLader::listParseIfstream(ifstream& ifstreamKonfig)
{
	
}
