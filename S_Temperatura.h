#ifndef SENSORE_TEMPERATURA_H
#define SENSORE_TEMPERATURA_H

#include "Sensore_Astratto.h"

class S_Temperatura: public Sensore_Astratto {
  private:
    Misura scala_Misura;
    double precisione;
    double livello_massimo; 
    double livello_minimo;
    static std::string MisurazioneToString(Misura tipoMisura);
  public:
    S_Temperatura(
        const unsigned int codice,
        const std::string nome,
        const std::string descrizione,
        const unsigned int  percorso_immagine,
        const double costo,
        const Energia impianto,
        const bool funzionante,
        const Misura scala_Misura,
        const double precisione,
        const double livello_massimo,
        const double livello_minimo
    );
    static const double Zero_Assoluto;
    static const double Range;

    const Misura& getScala_Misura() const ;
    S_Temperatura& setScala_Misura(const Misura scala_Misura);
    double getLivello_Massimo() const;
    S_Temperatura& setLivello_Massimo(const double livello);
    double getLivello_Minimo() const;
    S_Temperatura& setLivello_Minimo(const double livello);
    double getPrecisione() const;
    S_Temperatura& setPrecisione(const double precisione);
    bool superamento_livello_massimo(const double livello) const;
    bool superamento_livello_minimo(const double livello) const;
    virtual void modifica(const Sensore_Astratto& s) override;

    virtual void accept(IConstVisitor& visitor) const override ;
    virtual void accept(IVisitor& visitor)override ;
    
    S_Temperatura* clona() const  override ;

    virtual double getValore() override;
    virtual double getValoreParametri(double precedente,bool s) override;
    virtual double getValoreParametriTemp(double precedente);

    virtual std::string toString() const override;
};

#endif
