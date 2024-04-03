#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm> // Per std::find_if
#include <cctype>    // Per std::tolower
#include <sstream>   // Per std::stringstream

#include "modello.h"
#include  "parser.cpp"
#include "simulatore.h"
#include <stdexcept>
#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include "smistatore.h"


void Modello::aggiungiSensore(const Sensore_Astratto& sensore) {
    for(auto it= sensori.begin();it!=sensori.end();it++){
        if(sensore.getCodice()==(*it)->getCodice()){
            throw std::invalid_argument("Impossibile inserire il nuovo sensore perchè il codice è già utilizzato da un altro sensore");
        }
    }
    Sensore_Astratto* newSensor = sensore.clona();
    this->sensori.push_back(newSensor);
}


void Modello::rimuoviSensore(unsigned int codice) {
    bool find=false;
    for (auto it = sensori.begin(); it != sensori.end() && find != true;) {
        if ((*it)->getCodice() == codice) {
            find = true;
            delete *it;
            it = sensori.erase(it);
        } else {
            ++it;
        }
    }
}


Sensore_Astratto& Modello::modificaSensore(const Sensore_Astratto &s) {
    bool find = false;

    auto it = sensori.begin();

    if (sensori.empty()) {
        throw std::invalid_argument("Il vettore di sensori è vuoto.");
    }

    for (; it != sensori.end() && !find; ++it) {

        if (s.getCodice() == (*it)->getCodice()) {
            try {
                (*it)->modifica(s);
                find = true;
            } catch (const std::invalid_argument& e) {
                throw e;
            }
        }
    }

    if (!find) {
        throw std::invalid_argument("Il sensore non è stato trovato.");
    }

    return **it;
}

Sensore_Astratto& Modello::get_Sensore(unsigned int codice) const {
    bool find=false;
    Sensore_Astratto* p=nullptr;
    for(auto it=sensori.begin();it!= sensori.end() &&find!=true;it++){
        if((*it)->getCodice()==codice){
            find=true;
            p=*it;
        }
    }
    if(find==false) throw std::invalid_argument("Cerchi un sensore non presente nel modello.");
    return *p;
}
std::vector<Sensore_Astratto*> Modello::getSensoriTipo(Energia tipo) const {
    std::vector<Sensore_Astratto*> result;
    for (Sensore_Astratto* sensore : sensori) {
        if (sensore->getImpianto() == tipo)
            result.push_back(sensore);
    }
    return result;
}
std::vector<Sensore_Astratto*> Modello::filtraSensori(const std::string& ricerca, Energia tipo) const {
    struct RisultatoRicerca {
        Sensore_Astratto* sensore;
        int punteggio;
    };
    std::vector<RisultatoRicerca> risultati;
    std::vector<Sensore_Astratto*> vettorericerca;

    auto stringaMinuscola = [](const std::string& s) {
        std::string risultato;
        for (std::string::size_type i = 0; i < s.length(); ++i) {
            risultato += std::tolower(s[i]);
        }
        return risultato;
    };

    std::string ricercaMinuscola = stringaMinuscola(ricerca);

    bool soloNumeri = true;
    for (std::string::size_type i = 0; i < ricercaMinuscola.length(); ++i) {
        if (!std::isdigit(ricercaMinuscola[i])) {
            soloNumeri = false;
            break;
        }
    }

    std::stringstream ss;
    int punteggio = 0;

    if (!soloNumeri) {
        for (auto it = sensori.begin(); it != sensori.end(); ++it) {
            punteggio = 0;
            std::string nomeMinuscolo = stringaMinuscola((*it)->getNome());
            std::string descrizioneMinuscola = stringaMinuscola(((*it)->getDescrizionecon_()));
            std::string impiantoMinuscolo = stringaMinuscola((*it)->getImpianto() == 0 ? "solare" : "eolico");
            ss << nomeMinuscolo << " " << descrizioneMinuscola << " " << impiantoMinuscolo;
            
            for (std::string::size_type j = 0; j < ricercaMinuscola.length(); ++j) {
                if (ss.str().find(ricercaMinuscola[j]) != std::string::npos) {
                    if ((*it)->getImpianto() == tipo) punteggio++;
                }
            }
            risultati.push_back({*it, punteggio});
        }
    } else {
        for (auto it = sensori.begin(); it != sensori.end(); ++it) {
            punteggio = 0;
            double costo = (*it)->getCosto();
            unsigned int codice = (*it)->getCodice();
            double precisione=0;
            double livello_massimo=0;
            double livello_minimo=0;
            const S_Temperatura* t = dynamic_cast<const S_Temperatura*>(*it);
            if(t){
                precisione=t->getPrecisione(),
                livello_massimo=t->getLivello_Massimo();
                livello_minimo=t->getLivello_Minimo();
            }
            int livello_muffa=0;
            const S_Umidita* u = dynamic_cast<const S_Umidita*>(*it);
            if(u){
                livello_massimo=u->getLivello_Massimo(),
                livello_muffa=u->getLivello_Muffa();

            }
            double angolo_radiazione=0;
            double livello_fusione=0;
            const S_Radiazione* r = dynamic_cast<const S_Radiazione*>(*it);
            if(r){
                livello_minimo=r->getLivello_Minimo();
                livello_fusione=r->getLivello_Fusione();
                angolo_radiazione=r->getAngolo_Radiazione();
            }
            
            for (std::string::size_type j = 0; j < ricercaMinuscola.length(); ++j) {
                if (std::to_string(costo).find(ricercaMinuscola[j]) != std::string::npos ||
                    std::to_string(codice).find(ricercaMinuscola[j]) != std::string::npos||
                    std::to_string(precisione).find(ricercaMinuscola[j])!=std::string::npos||
                    std::to_string(livello_minimo).find(ricercaMinuscola[j])!=std::string::npos||
                    std::to_string(livello_fusione).find(ricercaMinuscola[j])!=std::string::npos||
                    std::to_string(livello_muffa).find(ricercaMinuscola[j])!=std::string::npos||
                    std::to_string(livello_massimo).find(ricercaMinuscola[j])!=std::string::npos||
                    std::to_string(angolo_radiazione).find(ricercaMinuscola[j])!=std::string::npos) {
                    if ((*it)->getImpianto() == tipo) punteggio++;
                }
            }
            risultati.push_back({*it, punteggio});
        }
    }

    if(risultati.size()==0) throw std::invalid_argument("Nessun elemento corrisponde alla ricerca") ;

    std::sort(risultati.begin(), risultati.end(), [](const auto& a, const auto& b) {
        return a.punteggio > b.punteggio;
    });

    
    for (std::vector<RisultatoRicerca>::size_type i = 0; i < risultati.size() && risultati[i].punteggio != 0; ++i) {
        if(risultati[i].punteggio >= ricerca.size())
            vettorericerca.push_back(risultati[i].sensore);
    }

    return vettorericerca;
}


std::vector<Simulazione> Modello::simulaGrafico(std::vector<Sensore_Astratto*> sensori,unsigned int n) {
    std::vector<std::vector<Sensore_Astratto*>> lista ;

    Simulatore simulatore(sensori);

    std::vector<Simulazione> risultato = simulatore.simula(n);

    return risultato;
}


void Modello::salva(const std::string& path) const {
    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Errore nell'apertura del file: " <<path << std::endl;
        return;
    }

    for (std::vector<Sensore_Astratto*>::const_iterator it = sensori.begin(); it != sensori.end(); ++it) {
        file << **it << "\n";
    }

    file.close();
}

void Modello::elimina(){
    for (auto it =sensori.begin(); it < sensori.end(); it++){
        delete *it;
    }
    sensori.clear();
}

/**
 * @brief Modello::carica
 * @param path
 * @throws std::exception
 */

void Modello::carica(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Errore nell'apertura del file: " << path << std::endl;
            return;
        }
        this->elimina();
        std::string riga;
        Parser parser = Parser();

        while (std::getline(file, riga)) {
            try{
                Sensore_Astratto* sensore = parser.parseriga(riga);
                aggiungiSensore(*sensore);
            }
            catch (std::invalid_argument e){
                throw e;
            }
        }
        file.close();
}

bool Modello::sensoreEsiste(unsigned int codice) const {
    for (const auto& sensore : sensori) {
        if (sensore->getCodice() == codice) {
            return true;
        }
    }
    return false;
}
