#ifndef SIMULATORE_H
#define SIMULATORE_H

#include "Sensore_Astratto.h"
#include <vector>
#include "utilities.h"
#include "smistatore.h"


class Simulatore {
    private : 
        std::vector<Sensore_Astratto*> sensori; 

        static bool isMorning(int i);

        Simulazione extracted(const std::vector<Sensore_Astratto*>& s, unsigned int n) const;
    public:
        Simulatore(std::vector<Sensore_Astratto*>);
        std::vector<Simulazione>  simula(unsigned int n) const;
};

#endif
