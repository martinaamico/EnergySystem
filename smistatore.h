#ifndef SMISTATORE_H
#define SMISTATORE_H
#include "sensore_i_visitor.h"

#include <vector>

class smistatore : public IVisitor
{
private:
    std::vector<std::vector<Sensore_Astratto*>> liste;

public:
    smistatore();
    std::vector<std::vector<Sensore_Astratto*>> getListe() const;

    virtual void visit(S_Temperatura& s_temperatura) override;
    virtual void visit(S_Radiazione& s_radiazione) override;
    virtual void visit(S_Umidita& s_umidita) override;
};

#endif // SMISTATORE_H
