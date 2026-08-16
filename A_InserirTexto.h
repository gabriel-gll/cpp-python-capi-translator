#ifndef A_INSERIR_TEXTO_H
#define A_INSERIR_TEXTO_H

#include "AcaoMenu.h"
#include <iostream>
#include <limits>

class A_InserirTexto : public AcaoMenu {
public:
    void executar(string &texto,
                  string &idioma_destino,
                  vector<Registro> &historico,
                  PyObject *pDetect,
                  PyObject *pTranslate,
                  PyObject *pListar) override 
    {
        cout << "Digite o texto: "; //armazena o texto que será usado nas outras opções
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, texto);
    }
};

#endif