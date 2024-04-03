#include "S_Temperatura.h"
#include <random>
#include <stdexcept>

S_Temperatura::S_Temperatura(
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
    )
        :Sensore_Astratto(codice,nome,descrizione,percorso_immagine,costo,impianto,funzionante),
        scala_Misura(scala_Misura),precisione(precisione),livello_massimo(livello_massimo),livello_minimo(livello_minimo)
    {
    }
std::string S_Temperatura::MisurazioneToString(Misura tipoMisura) {
        if(tipoMisura==0) return "Kelvin";
        else if(tipoMisura==1) return "Fahrenheit";
        else return "Celsius";
}
const Misura& S_Temperatura::getScala_Misura() const {
    return scala_Misura;
}
S_Temperatura& S_Temperatura::setScala_Misura(const Misura scala_Misura){
    this->scala_Misura=scala_Misura;
    return *this;
}
double S_Temperatura::getLivello_Massimo() const{
    return livello_massimo;
}
S_Temperatura& S_Temperatura::setLivello_Massimo(const double livello){
    this->livello_massimo = livello;
    return *this;
}
double S_Temperatura::getLivello_Minimo() const{
    return livello_minimo;
}
S_Temperatura& S_Temperatura::setLivello_Minimo(const double livello){
    this->livello_minimo = livello;
    return *this;
}
bool  S_Temperatura::superamento_livello_minimo(const double livello) const{
     return livello<livello_minimo;
}
double  S_Temperatura::getPrecisione() const{
    return precisione;
}
S_Temperatura& S_Temperatura::setPrecisione(const double precisione){
    this->precisione = precisione;
    return *this;
}

double S_Temperatura:: getValore(){
    double valore=Zero_Assoluto;
    if (scala_Misura == Misura::Fahrenheit) {
        valore = (Zero_Assoluto * 9.0 / 5.0) - 459.67;
    }
    if(getFunzionante()){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> distribuzione(livello_minimo, livello_massimo);

            valore= distribuzione(gen);
            valore = std::round(valore / precisione) * precisione;

            if (superamento_livello_massimo(valore)|| superamento_livello_minimo(valore)){
                setFunzionante(false);
            }
            return valore;
    }
    return valore;
}

const double S_Temperatura::Range=3.5;
//ogni ora si può alzare di 3.5 gradi

double S_Temperatura::getValoreParametri(double precedente,bool asc) {
    std::random_device rd;
    double valore=Zero_Assoluto;
    if (scala_Misura == Misura::Fahrenheit) {
        valore = (Zero_Assoluto * 9.0 / 5.0) - 459.67;
    }
    std::mt19937 gen(rd());
    if(getFunzionante()){
        std::uniform_real_distribution<double> distribuzione;
        if(asc){
            //DO
            distribuzione=std::uniform_real_distribution<double>(precedente, precedente + Range);
        }
        else {
            distribuzione = std::uniform_real_distribution<double>(precedente - Range, precedente);
        }
        valore = distribuzione(gen);

        if (superamento_livello_massimo(valore)|| superamento_livello_minimo(valore)){
            setFunzionante(false);
        }
    }
    return valore;
}
double S_Temperatura::getValoreParametriTemp(double precedente) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<double> distribuzione(precedente, precedente+10.0);
    double valore = distribuzione(gen);
    return valore;
}
bool S_Temperatura::superamento_livello_massimo(const double livello) const {
    return livello>livello_massimo;
}


std::string S_Temperatura::toString() const{
    std::string result= Sensore_Astratto::toString()+ ";";
    result += +"ScalaMisurazione:" + MisurazioneToString(scala_Misura)+";" ;
    result += "Precisione:" + std::to_string(precisione)+ ";" ;
    result += "LivelloMassimo:" + std::to_string(livello_massimo) + ";";
    result += "LivelloMinimo:" + std::to_string(livello_minimo) ;
    return result;
}

void S_Temperatura::modifica(const Sensore_Astratto& s) {
    const S_Temperatura* sensore = dynamic_cast<const S_Temperatura*>(&s);
    if (!sensore) {
    throw std::invalid_argument("Il sensore passato non è di tipo Temperatura.");
    }

    Sensore_Astratto::modifica(s);
    livello_massimo = sensore->getLivello_Massimo();
    scala_Misura =sensore->getScala_Misura();
    livello_minimo= sensore->getLivello_Minimo();
}
S_Temperatura* S_Temperatura::clona() const {
    return new S_Temperatura(*this);
}
void S_Temperatura::accept(IConstVisitor& visitor) const {
    visitor.visit(*this);
}
void S_Temperatura::accept(IVisitor& visitor) {
    visitor.visit(*this);
}
const double S_Temperatura::Zero_Assoluto = -273.15;
