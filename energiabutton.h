#ifndef ENERGIABUTTON_H
#define ENERGIABUTTON_H

#include <QPushButton>
#include "utilities.h"


class EnergiaButton : public QPushButton
{
    Q_OBJECT
public:
    EnergiaButton(const Energia &kind, QWidget* parent = nullptr);

private:
    Energia kind;

signals:
    void change(Energia);

private slots:
    void resignal();
};

#endif // ENERGIABUTTON_H
