// Registro.h
#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

class Registro {    //classe para registrar traduções
public:
    std::string original;
    std::string destino;
    std::string traducao;

    Registro(const std::string& orig, const std::string& dest, const std::string& trad)
        : original(orig), destino(dest), traducao(trad) {}
};

#endif
