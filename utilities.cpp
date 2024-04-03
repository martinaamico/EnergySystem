#include "utilities.h"

Energia convertItoE(int i){
    if(i==0) return Energia::eolico;
    if(i==1) return Energia::solare;
    return Energia::solare;
}


Energia convertStoE(std::string s){
    if(s == "eolico") return Energia::eolico;
    if(s == "solare") return Energia::solare;
    return Energia::solare;
}


std::string convertEtoS(Energia e){
    if(e == Energia::eolico) return "eolico";
    if(e == Energia::solare) return "solare";
    return "solare";
}

Misura convertItoM(int i){
    if(i==0) return Misura::Kelvin;
    if(i==1) return Misura::Fahrenheit;
    return Misura::Celsius;
}


Misura convertStoM(std::string str){
    if (str == "Celsius") {
        return Celsius;
    }
    if (str == "Fahrenheit") {
        return Fahrenheit;
    }
    if (str == "Kelvin") {
        return Kelvin;
    }
    return Misura::Celsius;
}

