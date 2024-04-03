#ifndef AGGIUNGI_SENSORE_H
#define AGGIUNGI_SENSORE_H
//è la versione giusta
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include "S_Temperatura.h"
#include "S_Radiazione.h"
#include "S_Umidita.h"
#include "utilities.h"
#include <string>
#include "controller.h"

class AggiungiSensore : public QDialog {
    Q_OBJECT
private:
    QLabel *title;
    QVBoxLayout* layoutcomune;
    QVBoxLayout* layoutspecifico;
    QVBoxLayout* mainlayout;

    QLineEdit* costo;
    QLineEdit* nome;
    QLineEdit* codice;
    QTextEdit* descrizione;
    QComboBox* img;
    QLineEdit* precisione;
    QLineEdit* livello_massimo;
    QLineEdit* livello_minimo;
    QLineEdit* livello_muffa;
    QLineEdit* angolo_radiazione;
    QLineEdit* livello_fusione;

    QComboBox* scalaBox;
    QComboBox* tipoBox;
    QLineEdit* impianto;

    QHBoxLayout* angoloLayout;
    QHBoxLayout* fusioneLayout;
    QHBoxLayout* minimoLayout;
    QHBoxLayout* scalaLayout;
    QHBoxLayout* precisioneLayout;
    QHBoxLayout* massimoLayout;
    QHBoxLayout* muffaLayout;
    Controller* controller;

    void pulisciLayoutSpecifichi(QLayout* layout);

public:
    AggiungiSensore(QString t,Controller *c,QWidget *parent = nullptr);

public slots:
    void cambiaWidget(int index);
    void aggiungi();

signals:
    void sensoreAggiunto(Sensore_Astratto* s);
};

#endif // AGGIUNGI_SENSORE_H

