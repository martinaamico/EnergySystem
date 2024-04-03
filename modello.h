#ifndef MODELLO_H
#define MODELLO_H

#include <vector>

#include "Sensore_Astratto.h"


class Modello {
  private:
    std::vector<Sensore_Astratto*> sensori;
    void elimina();

  public:
    void aggiungiSensore(const Sensore_Astratto &sensore);
    void rimuoviSensore(unsigned int codice);
    Sensore_Astratto& modificaSensore(const Sensore_Astratto& sensore);
    std::vector<Sensore_Astratto*>  filtraSensori(const std::string& ricerca,Energia tipo) const;
    Sensore_Astratto& get_Sensore(unsigned int codice) const ;
    //non const per chiamata a setFunzionante()
    std::vector<Simulazione>  simulaGrafico( std::vector<Sensore_Astratto*> sensori,unsigned int n);
    void salva(const std::string& path)const;
    void carica(const std::string& path) ;
    bool sensoreEsiste(unsigned int codice) const;
    std::vector<Sensore_Astratto*> getSensoriTipo(Energia tipo) const;
};
#endif
