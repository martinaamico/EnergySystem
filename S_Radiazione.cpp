#include "S_Radiazione.h"
#include <random>
#include <stdexcept>


S_Radiazione::S_Radiazione (
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
    )
        :Sensore_Astratto(codice,nome,descrizione,percorso_immagine,costo,impianto,funzionante),
        angolo_radiazione(angolo_radiazione),
        livello_fusione(livello_fusione),livello_minimo(livello_minimo)
    {
    }
double S_Radiazione::getAngolo_Radiazione() const{
    return angolo_radiazione;
}
S_Radiazione& S_Radiazione:: setAngolo_Radiazione(const double angolo_radiazione){
    this->angolo_radiazione=angolo_radiazione;
    return *this;
}
double S_Radiazione::getLivello_Fusione() const{
    return livello_fusione;
}
S_Radiazione& S_Radiazione::setLivello_Fusione(double livello_fusione){
    this->livello_fusione=livello_fusione;
    return *this;
}
double S_Radiazione::getLivello_Minimo() const{
    return livello_minimo;
}
S_Radiazione& S_Radiazione::setLivello_Minimo(const double livello){
    this->livello_minimo = livello;
    return *this;
}

double S_Radiazione:: getValore(){
if(getFunzionante()){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> distribuzione(livello_minimo,std::numeric_limits<double>::max());
        double valore =distribuzione(gen);
        if(valore>livello_fusione){
            setFunzionante(false);
        }
        else return valore;
    }
    return -1;
}

const double S_Radiazione::Range=0.01;


double S_Radiazione::getValoreParametri(double precedente,bool s) {
    std::random_device rd;
    double valore=-1;
    std::mt19937 gen(rd());
    if(s){
        //definire range
        std::uniform_real_distribution<double> distribuzione(precedente,precedente+Range);
        valore = distribuzione(gen);
    }
    else{
        std::uniform_real_distribution<double> distribuzione(precedente,precedente-Range);
        valore = distribuzione(gen);
    }

    if (valore > livello_fusione) {
        setFunzionante(false);
    }
    return valore;
}

std::string S_Radiazione::toString() const{
    std::string result= Sensore_Astratto::toString()+ ";";
    result += "AngoloRadiazione:"  + std::to_string(angolo_radiazione)+ ";";
    result += "LivelloFusione:" + std::to_string(livello_fusione)+ ";" ;
    result += "LivelloMinimo:" + std::to_string(livello_minimo);
    return result;
}

void S_Radiazione::modifica(const Sensore_Astratto& s) {
    const S_Radiazione* sensore = dynamic_cast<const S_Radiazione*>(&s);
    if (!sensore) 
    throw std::invalid_argument("Il sensore passato non è di tipo Radiazione.");

    Sensore_Astratto::modifica(s);
    livello_minimo = sensore->getLivello_Minimo();
    angolo_radiazione= sensore->getAngolo_Radiazione();
    livello_fusione=sensore->getLivello_Fusione();
}

S_Radiazione* S_Radiazione::clona() const {
    return new S_Radiazione(*this);
}
void S_Radiazione::accept(IConstVisitor& visitor) const {
    visitor.visit(*this);
}
void S_Radiazione::accept(IVisitor& visitor) {
    visitor.visit(*this);
}
