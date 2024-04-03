#ifndef SENSORE_RADIAZIONE_H
#define SENSORE_RADIAZIONE_H

#include "Sensore_Astratto.h"

class S_Radiazione: public Sensore_Astratto{
  private:
    double angolo_radiazione;
    double livello_fusione;
    double livello_minimo;

  public:
    S_Radiazione(
        const unsigned int codice,
        const std::string nome,
        const std::string descrizione,
        const unsigned int percorso_immagine,
        const double costo,
        const Energia impianto,
        const bool funzionante,
        double angolo_radiazione,
        double livello_fusione,
        const double livello_minimo
    );
    static const double Range;
    double getAngolo_Radiazione() const;
    S_Radiazione& setAngolo_Radiazione(const double angolo_radiazione);
    double getLivello_Fusione() const;
    S_Radiazione& setLivello_Fusione(double livello_fusione);
    double getLivello_Minimo() const;
    S_Radiazione& setLivello_Minimo(const double livello);
    virtual void modifica(const Sensore_Astratto& s) override;

    virtual void accept(IConstVisitor& visitor) const override;
    virtual void accept(IVisitor& visitor) override;

    S_Radiazione* clona() const  override ;

    virtual double getValore() override;
    virtual double getValoreParametri(double precedente,bool s) override;

    virtual std::string toString() const override;
};

#endif
