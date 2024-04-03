#include <string>
#include <vector>
#include <map>
#include<sstream>
#include "utilities.h"

#include  "parser.h"
#include "S_Umidita.h"
#include "S_Temperatura.h"
#include "S_Radiazione.h"


std::string Parser::ValoreCampo(const std::string strInput, const std::string& campo) const {
    for (size_t i = 0; i < strInput.length(); ++i) {
        size_t pos = strInput.find(campo, i);
        if (pos != std::string::npos) {
            return strInput.substr(pos + campo.length() + 2);
        }
    }


    return "";
}

std::vector<std::string> Parser::split(const std::string& s, char delimiter) const {
    std::string mutableString = s; // Crea una copia modificabile di s oppure const cast?

    for (unsigned int i = 0; i < mutableString.size(); ++i) {
        if(mutableString[i] == ' ') mutableString[i] = '_';
        if (mutableString[i] == delimiter) mutableString[i] = ' ';
    }

    std::stringstream ss(mutableString);
    std::string word;
    std::vector<std::string> fields;

    while (ss >> word) {
        fields.push_back(word);
    }

    return fields;
}



Sensore_Astratto* Parser:: parseriga(const std::string& riga) const {
    if (riga.empty()) {
        throw std::invalid_argument("La riga è vuota.");

    }

    std::vector<std::string> fieldsAndValues = split(riga,';');

    std::map<std::string, std::string> fieldsValuesMap;

    for (const auto& s : fieldsAndValues) {
        auto fieldValue = split(s, ':');
        if (fieldValue.size() == 2) {
            std::string value = fieldValue[1];
            for(auto it=value.begin();it!=value.end();it++){
                if(*it == '_') *it=' ';
            }
            fieldsValuesMap[fieldValue[0]] = value;
        } else {
            //fare con .empty
           throw std::invalid_argument("Il campo " +fieldValue[0]+ " deve avere un valore");
        }
    }

    try {
        unsigned int codice = std::stoi(fieldsValuesMap.at("Codice"));
        std::string nome = fieldsValuesMap.at("Nome");
        std::string descrizione = fieldsValuesMap.at("Descrizione");
        unsigned int  percorso_immagine = std::stoi(fieldsValuesMap.at("PercorsoImmagine"));
        double costo = std::stod(fieldsValuesMap.at("Costo"));
        Energia impianto = convertStoE(fieldsValuesMap.at("Impianto"));
        bool funzionante = (fieldsValuesMap.at("Funzionante") == "1");

        if (riga.find("ScalaMisurazione") != std::string::npos) {
            Misura scala_Misura = convertStoM(fieldsValuesMap.at("ScalaMisurazione"));
            double precisione = std::stod(fieldsValuesMap.at("Precisione"));
            double livello_massimo = std::stod(fieldsValuesMap.at("LivelloMassimo"));
            double livello_minimo = std::stod(fieldsValuesMap.at("LivelloMinimo"));
            return new S_Temperatura(codice, nome, descrizione, percorso_immagine, costo, impianto, funzionante, scala_Misura, precisione, livello_massimo, livello_minimo);
        } else if (riga.find("AngoloRadiazione") != std::string::npos) {
            double angolo_radiazione = std::stod(fieldsValuesMap.at("AngoloRadiazione"));
            double livello_fusione = std::stod(fieldsValuesMap.at("LivelloFusione"));
            double livello_minimo = std::stod(fieldsValuesMap.at("LivelloMinimo"));
            return new S_Radiazione(codice, nome, descrizione, percorso_immagine, costo, impianto,funzionante, angolo_radiazione, livello_fusione, livello_minimo);
        } else {
            double livello_massimo = std::stod(fieldsValuesMap.at("LivelloMassimo"));
            double livello_muffa = std::stod(fieldsValuesMap.at("LivelloMuffa"));
            return new S_Umidita(codice, nome, descrizione, percorso_immagine, costo, impianto, funzionante, livello_massimo, livello_muffa);
        }
    } catch (const std::out_of_range& e) {
        throw std::invalid_argument("La riga non e' del formato corretto.");
    }
}

