#include "Sensore_Astratto.h"

Sensore_Astratto::Sensore_Astratto(
    const unsigned int codice,
    const std::string nome,
    const std::string descrizione,
    const unsigned int percorso_immagine,
    const double costo,
    const Energia impianto,
    const bool funzionante
)
    :codice(codice),
    nome(nome),
    descrizione(descrizione),
    percorso_immagine(percorso_immagine),
    costo(costo),
    impianto(impianto),
    funzionante(funzionante)
{
}


unsigned int Sensore_Astratto::getCodice() const {
    return codice;
}
double Sensore_Astratto::getCosto() const{
    return costo;
}
Energia Sensore_Astratto::getImpianto() const{
    return impianto;
}
const std::string& Sensore_Astratto::getNome() const {
    return nome;
}
std::string Sensore_Astratto::getDescrizione() const {
    std::string desc= descrizione;
    desc.replace(descrizione.begin(),descrizione.end(),"_"," ");
    return desc;
}
unsigned int Sensore_Astratto::getPercorso_Immagine() const {
    return percorso_immagine;
}

const bool& Sensore_Astratto::getFunzionante() const {
    return funzionante;
}
Sensore_Astratto& Sensore_Astratto::setImpianto(const Energia e) {
    impianto = e;
    return *this;
}

Sensore_Astratto& Sensore_Astratto::setNome(const std::string nome) {
    this->nome = nome;
    return *this;
}
Sensore_Astratto& Sensore_Astratto::setDescrizione(const std::string descrizione) {
    this->descrizione = descrizione;
    return *this;
}
Sensore_Astratto& Sensore_Astratto::setPercorso_Immagine(unsigned int percorso_immagine) {
    this->percorso_immagine = percorso_immagine;
    return *this;
}

Sensore_Astratto& Sensore_Astratto::setFunzionante(const bool f) {
    this->funzionante = f;
    return *this;
}
const std::string& Sensore_Astratto::getDescrizionecon_()const{
    return descrizione;
}
void Sensore_Astratto::modifica(const Sensore_Astratto& s) {
    nome = s.getNome();
    descrizione = s.getDescrizionecon_();
    percorso_immagine = s.getPercorso_Immagine();
    funzionante = s.getFunzionante();
    impianto=s.getImpianto();
}


std::string Sensore_Astratto::toString() const {
        std::string result;

        result += "Codice:" + std::to_string(codice) + ";" ;
        result += "Nome:" + nome + ";";
        result += "Descrizione:" + descrizione + ";" ;
        result += "PercorsoImmagine:" + std::to_string(percorso_immagine) + ";";
        result += "Costo:" + std::to_string(costo)+ ";" ;
        result += "Impianto:" + convertEtoS(impianto)+ ";" ;
        result += "Funzionante:" + std::to_string(funzionante);

        return result;
}


std::ostream& operator<<(std::ostream& os, const Sensore_Astratto& sensore) {
    os << sensore.toString();
    return os;
}
