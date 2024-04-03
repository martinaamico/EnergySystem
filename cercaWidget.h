#ifndef CERCAWIDGET_H
#define CERCAWIDGET_H
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>

#include "sensori_lista_widget.h"

class Controller;

class cercaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit cercaWidget(QString title, Controller* c, QWidget *parent = nullptr);


private:
    QVBoxLayout * layout;
    QHBoxLayout* barra ;
    Controller* controller;
    QString title;
    QHBoxLayout* layout_lista;
    SensorListWidget *lista;
    QPushButton * aggiungi;
    QPushButton * trova_risultati;
    QPushButton * simula;
    QScrollArea *scrollArea;
public slots:
signals:
};


#endif // CERCAWIDGET_H
