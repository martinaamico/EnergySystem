#include "S_Umidita.h"
#include <random>
#include <stdexcept>


S_Umidita::S_Umidita(
        const unsigned int codice,
        const std::string nome,
        const std::string descrizione,
        const unsigned int  percorso_immagine,
        const double costo,
        const Energia impianto,
        const bool funzionante,
        const double livello_massimo, 
        const double livello_muffa
    )
        :Sensore_Astratto(codice,nome,descrizione,percorso_immagine,costo,impianto,
        funzionante),livello_massimo(livello_massimo), livello_muffa(livello_muffa)
{
}
    
double  S_Umidita::getLivello_Massimo() const{
        return livello_massimo;
}
S_Umidita& S_Umidita::setLivello_Massimo(const double livello){
    this->livello_massimo = livello;
    return *this;
}
double  S_Umidita::getLivello_Muffa() const{
    return livello_muffa;
}
S_Umidita& S_Umidita::setLivello_Muffa(const double livello){
    this->livello_muffa = livello;
    return *this;
}
bool  S_Umidita::superamento_livello_Muffa(const double livello) const{
     return livello>livello_muffa;
}
double S_Umidita::getValore(){
    if(getFunzionante()){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> distribuzione(0.0, livello_massimo);
        double valore =distribuzione(gen);
        if(superamento_livello_Muffa(valore)){
            setFunzionante(false);
        }
        else return valore;
    }
    return 0.0;
}


const unsigned int S_Umidita:: Range=5;

double S_Umidita::getValoreParametri(double precedente,bool asc){
    std::random_device rd;
    double valore;
    std::mt19937 gen(rd());
    
    if(asc){ 
        std::uniform_real_distribution<double> distribuzione(precedente,precedente+Range);
        valore =distribuzione(gen);
    }
    else {
        std::uniform_real_distribution<double> distribuzione(precedente,precedente-Range);
        valore =distribuzione(gen);
    }

    if (superamento_livello_Muffa(valore)) {
        setFunzionante(false);
    }
    else {
        return valore;
    }
    return 0.0;
}

std::string S_Umidita::toString() const{
    std::string result= Sensore_Astratto::toString()+ ";";
    result += "LivelloMassimo:" + std::to_string(livello_massimo)+ ";" ;
    result += "LivelloMuffa:" + std::to_string(livello_muffa);
    return result;
}

void S_Umidita::modifica(const Sensore_Astratto& s)  {
    const S_Umidita* sensore = dynamic_cast<const S_Umidita*>(&s);
    // Se i tipi sono diversi, allora lanciare un'eccezione
    if (!sensore)
        throw std::invalid_argument("Il sensore passato non è di tipo Umidità.");

    Sensore_Astratto::modifica(s);
    livello_massimo = sensore->getLivello_Massimo();
    livello_muffa = sensore->getLivello_Muffa();
}

S_Umidita* S_Umidita::clona() const {
    return new S_Umidita(*this);
}
void S_Umidita::accept(IConstVisitor& visitor) const {
    visitor.visit(*this);
}
void S_Umidita::accept(IVisitor& visitor) {
    visitor.visit(*this);
}
