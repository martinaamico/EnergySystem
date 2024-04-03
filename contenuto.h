#ifndef CONTENUTO_H
#define CONTENUTO_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QStackedWidget>
#include <QLineEdit>
#include <QDateEdit>

#include "sensori_lista_widget.h"

class Controller;

class Contenuto : public QWidget
{
    Q_OBJECT
public:
    explicit Contenuto(QString title, Controller* c, QWidget *parent = nullptr);

    void load_simulazione();
    void load_lista();
    void addCercaPage();
    void addSimulazionePage(QWidget *parent, QWidget *scrollAreaPage);

private:
    QVBoxLayout * layout;
    QHBoxLayout* barra;
    Controller* controller;
    QString title;
    SensorListWidget *risultatiListWidget;
    SensorListWidget *listaSimulazione;
    SensorListWidget *lista;
    QPushButton * aggiungi;
    QPushButton * cerca;
    QPushButton * simula;
    QScrollArea *scrollArea;
    bool cercaButtonClicked;
    QLineEdit *searchLineEdit;
    QStackedWidget *stackedWidget;
    QDateEdit *dateFromEdit;
    QDateEdit *dateToEdit;
    QLabel* noResultsLabel;

    void addButtons();

    void addHomePage();

    void addSimulazionePage();

public slots:
    void SimulaClicked();
    void onCercaButtonClicked();
    void trovaRisultatiClicked();
    void AggiungiSensoreDialog();
    void sensoreAggiunto(Sensore_Astratto* s);
    void eliminaSensore(int codice);
    void apriModificaSensoreDialog(int codice);
    void avviaSimulazione();
    void sensoreModificato();
signals:
    void sensoreRimosso(int codice);


};

#endif // CONTENUTO_H
