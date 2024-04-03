#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QMenuBar>
#include <QLabel>
#include <QPushButton>

#include "energiabutton.h"

//#include "contenuto.h"
class Controller;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setController(Controller * c);
    ~MainWindow();

public slots:
    void switchWidget(Energia);
    void carica();
    void salva();

private:
    Controller* controller;

    void addButtons();
    QLabel* imageLabel;
    QVBoxLayout* sideMenuLayout;
    QLayout* screenLayout;

    QWidget* sideWidget;

};
#endif // MAINWINDOW_H
