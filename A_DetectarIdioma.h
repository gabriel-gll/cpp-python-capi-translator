#ifndef A_DETECTAR_IDIOMA_H
#define A_DETECTAR_IDIOMA_H

#include "AcaoMenu.h"
#include <iostream>

class A_DetectarIdioma : public AcaoMenu {
public:
    void executar(string &texto,
                  string &idioma_destino,
                  vector<Registro> &historico,
                  PyObject *pDetect,
                  PyObject *pTranslate,
                  PyObject *pListar) override 
    {
        if (texto.empty()) {
                    cout << "⚠️ Nenhum texto inserido!\n";
                    return;
                }

                PyObject* args = PyTuple_Pack(
                    1, PyUnicode_FromString(texto.c_str())  //Essa função transforma uma string C++ em uma string Python (str)
                );                                          //e coloca esse objeto Python dentro de uma tupla python

                PyObject* result = PyObject_CallObject(pDetect, args);  //Chama a função Python armazenada em pDetect e recebe o retorno da função
                Py_DECREF(args);    // Libera a referência à tupla, permitindo que o Python limpe a memória

                if (!result) {
                    PyErr_Print();
                    cerr << "Erro ao chamar detect_language\n";
                    return;
                }

                const char* idioma = PyUnicode_AsUTF8(result);  //É convertido o retorno da função para const char* pois o retorno vem como PyObject* 
                if (!idioma) idioma = "(retorno inválido)";

                cout << "🗣️ Idioma detectado: " << idioma << "\n";
                Py_DECREF(result);  // Libera a referência ao objeto, permitindo que o Python limpe a memória
    }
};

#endif
