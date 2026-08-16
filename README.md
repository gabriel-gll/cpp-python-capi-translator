📝 Tradutor Multilíngue em C++ com Integração Python
Projeto Final — Linguagem de Programação Eletrônica — UFRJ

Aluno: Gabriel Lopes Lima

Este projeto implementa um tradutor multilíngue em C++, utilizando polimorfismo para estruturar as ações do menu, além de integrar funções Python através da API C/Python.

O Python é responsável por:

Detectar o idioma de um texto (via langdetect)

Traduzir textos usando a API MyMemory

Listar idiomas suportados

O C++ é responsável pelo aplicativo principal, organização do fluxo, histórico e interação com o usuário.

📁 Estrutura do Projeto
projeto_final/
├── main.cpp
├── Registro.h
├── AcaoMenu.h
├── A_InserirTexto.h
├── A_DetectarIdioma.h
├── A_EscolherDestino.h
├── A_Traduzir.h
├── A_ExibirHistorico.h
├── A_ListarIdiomas.h
├── tradutor.py
├── Makefile
├── venv/  (criado pelo usuário)
└── README.md

🚀 Como Compilar e Executar
1️⃣ Criar e ativar o ambiente virtual Python

Se ainda não existir:

python3 -m venv venv


Ativar:

source venv/bin/activate


⚠️ IMPORTANTE:
O venv deve estar ativo ao compilar e ao executar o programa, pois o Python embutido no C++ utiliza as bibliotecas do ambiente virtual.

2️⃣ Instalar as dependências Python
pip install requests langdetect

3️⃣ Compilar o projeto
make


Isso gera o executável:

./tradutor

4️⃣ Executar o programa

Ainda com o venv ativo:

./tradutor

📋 Funcionamento do Programa

Ao rodar, será exibido o menu:

======= MENU TRADUTOR =======
0. Sair
1. Inserir texto
2. Detectar idioma
3. Escolher idioma de destino
4. Traduzir texto
5. Exibir histórico
6. Exibir idiomas disponíveis
Escolha:

🧩 Explicação das Opções (via Polimorfismo)

Cada opção do menu é implementada como uma classe derivada de AcaoMenu, seguindo o padrão:

class A_InserirTexto : public AcaoMenu {
    void executar(...) override;
};


O main mantém um vetor de ponteiros base:

vector<AcaoMenu*> acoes(7);
acoes[1] = new A_InserirTexto();
acoes[2] = new A_DetectarIdioma();
...


Assim, basta chamar:

acoes[opcao]->executar(...);


Ou seja, cada ação é um objeto polimórfico independente, deixando o menu organizado e modular.

🔍 Descrição das Funcionalidades
1 — Inserir texto

O usuário insere o texto que será usado para detecção e tradução.

2 — Detectar idioma

Utiliza a função Python:

detect_language(texto)

Que:

Usa langdetect para identificar idioma

Retorna código ISO e confiança

3 — Escolher idioma de destino

O usuário informa o código ISO (en, pt, es, etc.)
C++ apenas registra a escolha.

4 — Traduzir texto

Chama a função Python translate_text(origem, destino, texto):

Detecta idioma automaticamente

Cria e envia requisição à API MyMemory

Retorna apenas translatedText

O resultado é salvo no histórico como objeto Registro.

5 — Exibir histórico

Mostra:

Texto original

Idioma de destino

Tradução realizada

6 — Exibir idiomas disponíveis

Lista idiomas contidos no dicionário do tradutor.py.

🧠 Integração C++ ↔ Python (API C/Python)

O fluxo da integração é:

Inicializar o interpretador:

Py_Initialize();


Importar o módulo Python:

pModule = PyImport_Import(PyUnicode_FromString("tradutor"));


Obter funções:

pDetect = PyObject_GetAttrString(pModule, "detect_language");
pTranslate = PyObject_GetAttrString(pModule, "translate_text");
pListar = PyObject_GetAttrString(pModule, "listar_idiomas");


Criar tuplas Python com argumentos (PyTuple_New, PyTuple_SetItem)

Chamar as funções Python:

PyObject* resultado = PyObject_CallObject(funcao, args);


Converter retorno Python → C++ (PyUnicode_AsUTF8)

Liberar objetos Python com Py_DECREF.

A principal complexidade está na integração entre C++ e Python, especialmente no:

Gerenciamento de tuplas de argumentos Python

Tratamento correto de objetos PyObject

Conversão segura entre tipos Python ↔ C++

🔧 Dependências
Tecnologia	Uso
C++	Aplicativo principal, menu polimórfico
Python 3.10+	Lógica de detecção e tradução
requests	Acessar API MyMemory
langdetect	Identificação automática do idioma
API C/Python	Comunicação entre C++ e Python
venv	Isolamento do ambiente Python
🎓 Objetivo Acadêmico

Este projeto demonstra:

✔ Integração completa C++ ↔ Python via API C
✔ Estruturação de software orientada a objetos
✔ Uso de polimorfismo para modularizar o menu
✔ Manipulação de APIs web
✔ Organização de código em múltiplas classes
✔ Uso de venv e linking com Python no C++