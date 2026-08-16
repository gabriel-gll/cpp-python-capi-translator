#ifndef A_EXIBIR_HISTORICO_H
#define A_EXIBIR_HISTORICO_H

#include "AcaoMenu.h"
#include <iostream>

class A_ExibirHistorico : public AcaoMenu {
public:
    void executar(string &texto,
                  string &idioma_destino,
                  vector<Registro> &historico,
                  PyObject *pDetect,
                  PyObject *pTranslate,
                  PyObject *pListar) override 
    {
        if (historico.empty()) {
            cout << "Nenhum histórico disponível.\n";
            return;
        }

        cout << "\n======= HISTÓRICO DE TRADUÇÕES =======\n";
        for (size_t i = 0; i < historico.size(); ++i) {
            cout << "Tradução #" << (i+1) << ":\n";
            cout << "Original:  " << historico[i].original << "\n";
            cout << "Destino:   " << historico[i].destino << "\n";
            cout << "Traduzido: " << historico[i].traducao << "\n\n";
        }
    }
};

#endif
