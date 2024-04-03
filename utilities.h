#ifndef UTILITIES_H
#define UTILITIES_H

#include<vector>
#include <string>

enum Misura {Kelvin, Fahrenheit, Celsius};
enum Energia {eolico,solare};
Energia convertItoE(int i);
Energia convertStoE(std::string s);
Misura convertItoM(int i);

std::string misura2text(Misura implant);
std::string convertEtoS(Energia e);
const std::string icons_names[9] = {
    "radiazione1","radiazione2","radiazione3",
    "temperatura1","temperatura2","temperatura3",
    "umidita1","umidita2","umidita3"
};
Misura convertStoM(std::string str);

typedef std::vector<std::vector<double>> Simulazione;


#endif // UTILITIES_H
