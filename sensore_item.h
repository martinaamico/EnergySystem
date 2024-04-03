#ifndef SENSORE_ITEM_H
#define SENSORE_ITEM_H

#include <QListWidgetItem>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "Sensore_Astratto.h"
#include <QCheckBox>
#include "utilities.h"
class SensoreItem : public QWidget
{
    Q_OBJECT
public:
    SensoreItem(Sensore_Astratto *s , bool mostra_pulsanti=true,bool mostra_check= false);
    QString getCodice()const ;
    bool isChecked() const;
    QString getNome() const;

private:
    QIcon img;
    QString nome;
    QString codice;
    QPushButton* modifica;
    QPushButton * elimina;
    QFrame* background;
    QCheckBox* selezioneCheckBox;
public slots:
    void ModificaSensoreDialog();
    void eliminaSensore();

signals:
    void eliminaSensoreClicked(int codice);
    void modificaSensoreClicked(int codice);
};
#endif // SENSORE_ITEM_H
