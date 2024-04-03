#include "energiabutton.h"

EnergiaButton::EnergiaButton(const Energia &k, QWidget *parent)
    : QPushButton(QString::fromStdString(convertEtoS(k)), parent), kind(k) {

    connect(this, SIGNAL(clicked()), this, SLOT(resignal()));
}


void EnergiaButton::resignal() {
    emit change(kind);
}
