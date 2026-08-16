// A_ListarIdiomas.h
#ifndef A_LISTAR_IDIOMAS_H
#define A_LISTAR_IDIOMAS_H

#include "AcaoMenu.h"
#include <iostream>

class A_ListarIdiomas : public AcaoMenu {
public:
    void executar(string &texto,
                  string &idioma_destino,
                  vector<Registro> &historico,
                  PyObject *pDetect,
                  PyObject *pTranslate,
                  PyObject *pListar) override 
    {
        cout << "\n======= IDIOMAS DISPONÍVEIS =======\n";

                // Chama listar_idiomas() no Python — sem argumentos
                PyObject* result = PyObject_CallObject(pListar, NULL);

                if (!result) {
                    PyErr_Print();
                    cerr << "Erro ao chamar listar_idiomas\n";
                    return;
                }

                const char* lista = PyUnicode_AsUTF8(result);   //converte retorno Python → char*
                cout << lista << "\n";

                Py_DECREF(result);  //libera o objeto retornado
    }
};

#endif
