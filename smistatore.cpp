#include "smistatore.h"

#include "S_Temperatura.h"
#include "S_Radiazione.h"
#include "S_Umidita.h"

smistatore::smistatore() : liste(std::vector<std::vector<Sensore_Astratto*>>(3,std::vector<Sensore_Astratto*>())) {}

std::vector<std::vector<Sensore_Astratto*>> smistatore::getListe() const {
    return liste;
}

void smistatore::visit(S_Temperatura& s_temperatura){
    liste[0].push_back(&s_temperatura);

}

void smistatore::visit(S_Radiazione& s_radiazione) {
    liste[1].push_back(&s_radiazione);
}

void smistatore::visit(S_Umidita& s_umidita) {
    liste[2].push_back(&s_umidita);
}
