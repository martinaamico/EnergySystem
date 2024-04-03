#ifndef SENSORE_I_VISITOR_H
#define SENSORE_I_VISITOR_H

#include "S_Temperatura.h"
#include "S_Radiazione.h"
#include "S_Umidita.h"

namespace Sensore{

class IVisitor {
  public:
    virtual ~IVisitor() {};


    virtual void visit( S_Temperatura& s_temperatura) = 0;
    virtual void visit( S_Radiazione& s_radiazione) = 0;
    virtual void visit( S_Umidita& s_umidita) = 0;
};

}

#endif
