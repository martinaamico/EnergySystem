#ifndef MODIFICA_SENSORE_H
#define MODIFICA_SENSORE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QTextEdit>
#include "controller.h"
#include "Sensore_Astratto.h"
#include <QCheckBox>

class ModificaSensore : public QDialog {
    Q_OBJECT
private:
    QLabel *title;
    QVBoxLayout* mainlayout;
    QVBoxLayout* layoutcomune;
    QVBoxLayout* layoutspecifico;

    QLineEdit* costo;
    QLineEdit* nome;
    QLineEdit* codice;
    QTextEdit* descrizione;
    unsigned int img;
    QLineEdit* precisione;
    QLineEdit* livello_massimo;
    QLineEdit* livello_minimo;
    QLineEdit* livello_muffa;
    QLineEdit* angolo_radiazione;
    QLineEdit* livello_fusione;

    QComboBox* scalaBox;
    std::string tipo;
    QComboBox* impiantoBox;

    QHBoxLayout* angoloLayout;
    QHBoxLayout* fusioneLayout;
    QHBoxLayout* minimoLayout;
    QHBoxLayout* scalaLayout;
    QHBoxLayout* precisioneLayout;
    QHBoxLayout* massimoLayout;
    QHBoxLayout* muffaLayout;
    QCheckBox* funzionanteCheckBox;
    Controller* controller;
    int cod;

public:
   ModificaSensore(Sensore_Astratto &s,Controller *c,QWidget *parent = nullptr);

public slots:
    void modificaSensore();
signals:

};
#endif // MODIFICA_SENSORE_H
