#ifndef SENSOR_ABSTRACT_SENSOR_H
#define SENSOR_ABSTRACT_SENSOR_H

#include <string>
#include "utilities.h"
#include "sensore_i_const_visitor.h"
#include "sensore_i_visitor.h"

class Sensore_Astratto{
  friend std::ostream& operator<<(std::ostream& os, const Sensore_Astratto& sensore);
  private:
    const unsigned int codice;
    std::string nome;
    std::string descrizione;
    unsigned int percorso_immagine;
    const double costo;
    Energia impianto;
    bool funzionante;

    static std::string EnergiaToString(Energia tipoEnergia);

  protected: 
    Sensore_Astratto(
        const unsigned int codice,
        const std::string nome,
        const std::string descrizione,
        unsigned int  percorso_immagine,
        const double costo,
        const Energia impianto,
        const bool funzionante

        );
    
    public: 
    virtual ~Sensore_Astratto()= default;
    unsigned int getCodice() const;
    double getCosto() const;
    Energia getImpianto() const;
    Sensore_Astratto& setImpianto(const Energia e );
    const std::string& getNome() const;
    Sensore_Astratto& setNome(const std::string nome);
    std::string getDescrizione() const;
    Sensore_Astratto& setDescrizione(const std::string descrizione);
    unsigned int  getPercorso_Immagine() const;
    Sensore_Astratto& setPercorso_Immagine(unsigned int percorso_immagine);
    const bool& getFunzionante() const;
    Sensore_Astratto& setFunzionante(bool f);
    const std::string&  getDescrizionecon_()const;

    virtual Sensore_Astratto* clona() const = 0;
    virtual void accept(IConstVisitor& visitor) const = 0;
    virtual void accept(IVisitor& visitor) = 0;
    
    virtual void modifica(const Sensore_Astratto& s);

    virtual double getValore() =0;
    virtual double getValoreParametri(double precedente,bool s) =0;

    virtual std::string toString() const;
};

#endif
