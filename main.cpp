#include <iostream>
#include <Python.h> //permite usar Python dentro de C++
#include <vector>   //armazenam traduções e textos
#include <string>   //armazenam traduções e textos
#include <limits>   //usado para limpar buffer de entrada

#include"Registro.h"
#include"AcaoMenu.h"

#include "A_InserirTexto.h"
#include "A_DetectarIdioma.h"
#include "A_EscolherDestino.h"
#include "A_Traduzir.h"
#include "A_ExibirHistorico.h"
#include "A_ListarIdiomas.h"

using namespace std;


int main() {
    // 🟦 Inicializar Python
    Py_Initialize();

    // Garantir que o diretório atual está no sys.path
    //sys.path é uma lista de diretórios onde o Python procura módulos
    PyRun_SimpleString("import sys, os");
    PyRun_SimpleString("sys.path.append(os.getcwd())");

    // 🟦 Importar tradutor.py
    PyObject *pName = PyUnicode_FromString("tradutor");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (!pModule) {
        PyErr_Print();
        cerr << "Erro: Não foi possível carregar tradutor.py\n";
        Py_Finalize();
        return 1;
    }

    // Buscar funções
    //ponteiros para as funções do Python
    PyObject *pDetect = PyObject_GetAttrString(pModule, "detect_language");
    PyObject *pTranslate = PyObject_GetAttrString(pModule, "translate_text");
    PyObject *pListar = PyObject_GetAttrString(pModule, "listar_idiomas");

    //verifica se as funções existem
    if (!pDetect || !PyCallable_Check(pDetect) ||
        !pTranslate || !PyCallable_Check(pTranslate) ||
        !pListar || !PyCallable_Check(pListar)) {

        cerr << "Erro: Funções necessárias não encontradas.\n";
        Py_Finalize();
        return 1;
    }

    // ------------------------------
    // Variáveis principais
    // ------------------------------
    vector<Registro> historico;
    string texto = "";
    string idioma_destino = "";

    // Criar vetor de ações
    vector<AcaoMenu*> acoes(7);
    acoes[1] = new A_InserirTexto();
    acoes[2] = new A_DetectarIdioma();
    acoes[3] = new A_EscolherDestino();
    acoes[4] = new A_Traduzir();
    acoes[5] = new A_ExibirHistorico();
    acoes[6] = new A_ListarIdiomas();

    int opcao;

    do {
        cout << "\n======= MENU TRADUTOR =======\n";
        cout << "0. Sair\n";
        cout << "1. Inserir texto\n";
        cout << "2. Detectar idioma\n";
        cout << "3. Escolher idioma de destino\n";
        cout << "4. Traduzir texto\n";
        cout << "5. Exibir histórico\n";
        cout << "6. Exibir idiomas disponíveis\n";
        cout << "Escolha: ";
        cin >> opcao;

        if (opcao == 0) break;
        if (opcao < 1 || opcao > 6) {
            cout << "Opção inválida!\n";
            continue;
        }

        acoes[opcao]->executar(texto, idioma_destino, historico,
                               pDetect, pTranslate, pListar);

    } while (opcao != 0);

    for (auto a : acoes) delete a;

    Py_Finalize();
    return 0;
}