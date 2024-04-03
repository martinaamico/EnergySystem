#include "sensori_lista_widget.h"
#include <QDialog>

SensorListWidget::SensorListWidget(QWidget *parent,bool bottoni, bool check)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    sensori = QVector<SensoreItem*>();
    mostra_pulsanti= bottoni;
    check_box= check;
}

void SensorListWidget::nuovo(Sensore_Astratto * s)
{
    QFrame* frame = new QFrame(this);
    SensoreItem* sensoreItem = new SensoreItem(s,mostra_pulsanti,check_box);

    QVBoxLayout* frameLayout = new QVBoxLayout;
    frameLayout->addWidget(sensoreItem);

    frame->setLayout(frameLayout);

    if (sensori.size() % 2 == 0) {
        frame->setStyleSheet("QWidget { background-color: #E6E6E6; }");
    } else {
        frame->setStyleSheet("QWidget { background-color: #FFFFFF; }");
    }

    layout->addWidget(frame);
    sensori.push_back(sensoreItem);

    connect(sensoreItem, SIGNAL(eliminaSensoreClicked(int)), this, SIGNAL(eliminaSensoreClicked(int)));
    connect(sensoreItem, SIGNAL(modificaSensoreClicked(int)), this, SIGNAL(modificaSensoreClicked(int)));
}



void SensorListWidget::eliminaSensore(int codice)
{

    for (int i = 0; i < sensori.size(); ++i) {
        if (sensori[i]->getCodice() == QString::number(codice)) {
            sensori.removeAt(i);
            break;
        }
    }
}

QList<SensoreItem*> SensorListWidget::getSensoriSelezionati() const {
    QList<SensoreItem*> sensoriSelezionati;
    for (SensoreItem* sensoreItem : sensori) {
        if (sensoreItem->isChecked()) {
            sensoriSelezionati.push_back(sensoreItem);
        }
    }
    return sensoriSelezionati;
}


void SensorListWidget::clear() {
    clearLayout(layout);
    sensori.clear();
}

void SensorListWidget::clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

