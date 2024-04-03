#ifndef SENSORI_LISTA_WIDGET_H
#define SENSORI_LISTA_WIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include "sensore_item.h"
#include "Sensore_Astratto.h"

class SensorListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorListWidget(QWidget *parent=nullptr,bool bottoni=true, bool check=false);
    QList<SensoreItem*> getSensoriSelezionati() const;


public slots:
    void nuovo(Sensore_Astratto * s);
    void eliminaSensore(int codice);
    void clear();
signals:
    void eliminaSensoreClicked(int codice);
    void modificaSensoreClicked(int codice);
    void sensoreRimosso(int codice);

private:
    void clearLayout(QLayout *layout);
    QVBoxLayout* layout;
    QVector<SensoreItem*> sensori;
    bool mostra_pulsanti;
    bool check_box;
};
#endif // SENSORI_LISTA_WIDGET_H
