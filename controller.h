#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "mainwindow.h"
#include "modello.h"


class Controller : public QObject
{
	Q_OBJECT
private:
	MainWindow* view;
    Modello* model;


public:
	explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void setModel(Modello *m);
    void setView(MainWindow * w);

    std::vector<Sensore_Astratto*> get_lista_sesnori(std::string s) const;
    void aggiungi(Sensore_Astratto* s) const;
    void eliminaSensore(unsigned int codice) const;
    void modifica_sensore(const Sensore_Astratto& s)const;
    void carica_file(const QString& filePath) const;
    void salva_file(const QString& filePath) const;
    Sensore_Astratto&  get_sensore(unsigned int codice)const;
    bool codiceEsiste(unsigned int codice) const;
    std::vector<Sensore_Astratto*> cercaSensori(const std::string& testoRicerca, const std::string& categoria) const;
    std::vector<Simulazione>  avviasimulazione(const std::vector<QString> & lista, unsigned int days)const ;
    std::vector<Sensore_Astratto*> getSensoriTipo(Energia tipo) const;

public slots:



};
#endif
