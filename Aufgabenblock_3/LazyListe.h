/*** LAZYLISTE.H ***/

//#ifndef __LazyListe_h
//#define __LazyListe_h

#pragma once
#include <list>
#include "LazyAktion.h"
#include <iterator>

using namespace std;

template <class T>
class LazyListe
{
   public:
      // typedef fuer iterator
      typedef typename list<T>::iterator iterator;
      typedef typename list<T>::const_iterator const_iterator;

      // Konstruktor / Destruktor
      LazyListe() { bChanged = false; }
      virtual ~LazyListe()
      {
         if (bChanged)
         {
            // ggf. noch anstehende Aktionen löschen
            do
            {
               delete *(p_ListeAktionen.begin());
               p_ListeAktionen.pop_front();
            }
            while (p_ListeAktionen.size() > 0);
         }
      }

      // Lesefunktionen
      const_iterator begin() const {return p_ListeObjekte.begin();}
	  const_iterator end() const { p_ListeObjekte.end(); }
      iterator begin() {return p_ListeObjekte.begin();}
	  iterator end() { return p_ListeObjekte.end(); }
      bool empty() const { p_ListeObjekte.empty()}

      // Schreibfunktionen
	  void push_back( const T einObjekt )
      {
		p_ListeAktionen.push_back(new LazyPushBack<T>(einObjekt, &this->p_ListeObjekte));
		bChanged = true;
		return;
      }

      void push_front( const T einObjekt )
      {
		  p_ListeAktionen.push_back(new LazyPushFront<T>(einObjekt, &this->p_ListeObjekte));

		bChanged = true;
		return;
      }

      void erase( iterator itObjekt )
      {
		  p_ListeAktionen.push_back(new LazyErase<T>(itObjekt, &this->p_ListeObjekte));

      bChanged = true;
      return;
      }

      // Änderungen auf Objektliste übertragen
      void vAktualisieren()
      {
         list <LazyAktion<T>*>::const_iterator itL;

         if ( bChanged )
         {
	         // ausstehende Aktionen durchfuehren
	         for (itL = p_ListeAktionen.begin(); itL != p_ListeAktionen.end(); itL++)
	         {
	         // Aktion ausführen
				 (*itL)->vAusfuehren();
             // Action-Element löschen
				 delete *itL;
	         }
	         // Liste der Aktionen leeren
             p_ListeAktionen.clear();

	         bChanged = false;
         }
      }

	  void vSortiereNurFahrendeFahrzeuge(int iParkendeFahrzeuge)
	  {
		  list<Fahrzeug*> parkendeFahrzeuge;
		  list<Fahrzeug*>::iterator pParkendeStart = this->p_ListeObjekte.begin();
		  list<Fahrzeug*>::iterator pParkendeEnde = this->p_ListeObjekte.begin();
		  pParkendeEnde = next(pParkendeEnde, iParkendeFahrzeuge);
		  parkendeFahrzeuge.splice(parkendeFahrzeuge.begin(), this->p_ListeObjekte, pParkendeStart, pParkendeEnde);
		  this->p_ListeObjekte.sort([]( Fahrzeug * a, Fahrzeug * b) { return a->dGetAbschnittGefahreneStrecke() < b->dGetAbschnittGefahreneStrecke(); });
		  this->p_ListeObjekte.reverse();
		  this->p_ListeObjekte.splice(this->p_ListeObjekte.begin(), parkendeFahrzeuge);
	  }

   private:
      list<T>				p_ListeObjekte;
      list<LazyAktion<T>*>	p_ListeAktionen;
      bool					bChanged;
};

//#endif