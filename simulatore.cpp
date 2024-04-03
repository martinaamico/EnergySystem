#include "simulatore.h"


Simulatore::Simulatore(std::vector<Sensore_Astratto*> s) : sensori(s) {
}

Simulazione Simulatore::extracted(const std::vector<Sensore_Astratto*>& s, unsigned int n) const {
    int Misurazioni = n * 24;
    Simulazione risultato =
        Simulazione(Misurazioni, std::vector<double>(s.size(), 0.0));

    for (unsigned int j = 0; j < s.size(); ++j) {
        risultato[0][j] = s[j]->getValore();
    }

    for (int i = 1; i < Misurazioni; i++) {
        for (unsigned int j = 0; j < s.size(); ++j) {
            risultato[i][j] =
                s[j]->getValoreParametri(risultato[i - 1][j], isMorning(i));
        }
    }

    return risultato;
}

std::vector<Simulazione> Simulatore::simula(unsigned int n) const {
    smistatore sm;
    for (Sensore_Astratto *s : sensori) {
        s->accept(sm);
    }

    std::vector<Simulazione> result;

    for (std::vector<Sensore_Astratto*> s : sm.getListe()) {
        result.push_back(extracted(s,n));
    }

    return result;
}

bool Simulatore::isMorning(int i) {
    return i % 24 < 12;
}
