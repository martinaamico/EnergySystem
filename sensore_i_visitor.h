#ifndef SENSORE_I_VISITOR_H
#define SENSORE_I_VISITOR_H

class S_Temperatura;
class S_Radiazione;
class S_Umidita;

class Sensore_Astratto;

class IVisitor {
public:
    virtual ~IVisitor() {};
    virtual void visit( S_Temperatura& s_temperatura) = 0;
    virtual void visit( S_Radiazione& s_radiazione) = 0;
    virtual void visit( S_Umidita& s_umidita) = 0;
};



#endif
