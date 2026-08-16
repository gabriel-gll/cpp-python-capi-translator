// A_Traduzir.h
#ifndef A_TRADUZIR_H
#define A_TRADUZIR_H

#include "AcaoMenu.h"
#include <iostream>

class A_Traduzir : public AcaoMenu {
public:
    void executar(string &texto,
                  string &idioma_destino,
                  vector<Registro> &historico,
                  PyObject *pDetect,
                  PyObject *pTranslate,
                  PyObject *pListar) override 
    {
        if (texto.empty()) {
                    cout << "⚠️ Primeiro insira um texto!\n";
                    return;
                }
                if (idioma_destino.empty()) {
                    cout << "⚠️ Escolha o idioma de destino!\n";
                    return;
                }
                
                // Criação da tupla com dois argumentos:
                // 1) texto original convertido para string Python
                // 2) idioma destino convertido para string Python
                PyObject* args = PyTuple_Pack(
                    2,
                    PyUnicode_FromString(texto.c_str()),    //string C++ → str Python
                    PyUnicode_FromString(idioma_destino.c_str())    //string C++ → str Python
                );

                // Chama translate_text(texto, idioma_destino) no Python
                PyObject* result = PyObject_CallObject(pTranslate, args);
                Py_DECREF(args);    //libera a tupla de argumentos

                if (!result) {
                    PyErr_Print();
                    cerr << "Erro ao chamar translate_text\n";
                    return;
                }

                const char* traducao_c = PyUnicode_AsUTF8(result);  // Converte o retorno Python para string C++
                string traducao = traducao_c ? traducao_c : "(retorno inválido)";   //se traducao_c for null, retorno invalido
                Py_DECREF(result);  //libera o objeto retornado

                historico.push_back({texto, idioma_destino, traducao}); //adiciona no historico a traducao

                cout << "\n🟩 Tradução: " << traducao << "\n";
    }
};

#endif
