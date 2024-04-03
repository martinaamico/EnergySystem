#include "controller.h"
#include <QFileDialog>

Controller::Controller(QObject* parent)
		: QObject(parent) {}

Controller::~Controller() { }

void Controller::setModel(Modello* m) { model = m; }

void Controller::setView(MainWindow* v) { view = v; }

std::vector<Sensore_Astratto*> Controller::get_lista_sesnori(std::string s) const {
    Energia i;
    if (s == "solare") {i = Energia::solare; }
    else if (s == "eolico") { i = Energia::eolico; }
    else { i = Energia::solare; }

    try {
        return model->filtraSensori(s, i);
    } catch (std::invalid_argument e) {
        throw std::invalid_argument("Sensori non trovati");
    }

}
std::vector<Sensore_Astratto*> Controller::getSensoriTipo(Energia tipo) const {
    return model->getSensoriTipo(tipo);
}
void Controller::aggiungi(Sensore_Astratto* s) const{
    try {
        model->aggiungiSensore(*s);
    } catch (std::invalid_argument e) {
        throw e;
    }
}
void Controller::eliminaSensore(unsigned int codice) const {
    model->rimuoviSensore(codice);
}
void  Controller::modifica_sensore(const Sensore_Astratto& s)const{
        model->modificaSensore(s);
}
std::vector<Sensore_Astratto*> Controller::cercaSensori(const std::string& testoRicerca, const std::string& categoria)const {
    try {
        std::vector<Sensore_Astratto*> listaFiltrata = model->filtraSensori(testoRicerca, convertStoE(categoria));
        return listaFiltrata;
    }
    catch (std::invalid_argument e) {
        throw e;
    }


}
void Controller::carica_file(const QString& filePath) const {
    try{
        model->carica(filePath.toStdString());
    }
    catch (std::invalid_argument e) {
        throw e;
    }
}

void Controller::salva_file(const QString& filePath) const {
    model->salva(filePath.toStdString());
}
Sensore_Astratto& Controller::get_sensore(unsigned int codice)const{
    try {
        return model->get_Sensore(codice);
    }
    catch (std::invalid_argument e) {
        throw e;
    }
}

bool Controller::codiceEsiste(unsigned int codice) const {
    return model->sensoreEsiste(codice);
}


std::vector<Simulazione>  Controller::avviasimulazione( const std::vector<QString> & lista, unsigned int days)const{
    std::vector<Sensore_Astratto* > sensori;
   for(auto it=lista.begin();it!=lista.end();it++){
        sensori.push_back(&(model->get_Sensore(it->toUInt())));
    }

   return model->simulaGrafico(sensori,days);
}
