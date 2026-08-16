#ifndef ACAO_MENU_H
#define ACAO_MENU_H

#include <string>
#include <vector>
#include <Python.h>
#include "Registro.h"

using namespace std;

class AcaoMenu {
public:
    virtual void executar(string &texto,
                          string &idioma_destino,
                          vector<Registro> &historico,
                          PyObject *pDetect,
                          PyObject *pTranslate,
                          PyObject *pListar) = 0;

    virtual ~AcaoMenu() {}
};

#endif