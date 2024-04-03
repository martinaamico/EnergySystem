#ifndef PARSER_H
#define PARSER_H

#include "Sensore_Astratto.h"
#include<vector>



class Parser {
    private:
        std::vector<std::string> split(const std::string& s, char delimiter) const;
        std::string ValoreCampo(const std::string str, const std::string& campo) const;
        Misura stringToMisura(const std::string& str) const;
        Energia stringToEnergia(const std::string& str) const ;
    public:
        Sensore_Astratto* parseriga(const std::string& riga) const;
    
};
#endif
