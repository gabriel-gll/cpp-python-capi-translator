// A_EscolherDestino.h
#ifndef A_ESCOLHER_DESTINO_H
#define A_ESCOLHER_DESTINO_H

#include "AcaoMenu.h"
#include <iostream>

class A_EscolherDestino : public AcaoMenu {
public:
    void executar(string &texto,
                  string &idioma_destino,
                  vector<Registro> &historico,
                  PyObject *pDetect,
                  PyObject *pTranslate,
                  PyObject *pListar) override 
    {
        cout << "Digite o idioma destino (ex: en, es, fr): ";
        cin >> idioma_destino;
    }
};

#endif
