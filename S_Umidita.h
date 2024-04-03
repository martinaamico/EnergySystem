#ifndef SENSORE_UMIDITA_H
#define SENSORE_UMIDITA_H

#include "Sensore_Astratto.h"

class S_Umidita: public Sensore_Astratto {
  private:
  double livello_massimo;
  int livello_muffa;
  public:
    S_Umidita(
        const unsigned int codice,
        const std::string nome,
        const std::string descrizione,
        const unsigned int  percorso_immagine,
        const double costo,
        const Energia impianto,
        const bool funzionante,
        const double livello_massimo, 
        const double livello_muffa
    );
    double getLivello_Massimo() const;
    S_Umidita& setLivello_Massimo(const double livello);
    double getLivello_Muffa() const;
    S_Umidita& setLivello_Muffa(const double livello);
    bool superamento_livello_Muffa(const double livello) const;
    virtual void modifica(const Sensore_Astratto& s) override;
    static const unsigned int Range;

    virtual void accept(IConstVisitor& visitor) const override;
    virtual void accept(IVisitor& visitor) override;

    S_Umidita* clona() const  override ;


    virtual double getValore() override;
    virtual double getValoreParametri(double precedente,bool s) override;

    virtual std::string toString() const override;
};

#endif
