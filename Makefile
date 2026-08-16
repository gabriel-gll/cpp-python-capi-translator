# Compilador
CXX = g++

# Detecta as flags do Python 3 padrão instalado no sistema do usuário
PY_INC  := $(shell python3-config --includes)
PY_LIBS := $(shell python3-config --ldflags --embed)

# Arquivos do projeto
TARGET = tradutor
SRC = main.cpp

# Regra padrão
all: $(TARGET)

# Como compilar o binário final
$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(PY_INC) $(PY_LIBS)

# Limpeza dos arquivos compilados
clean:
	rm -f $(TARGET)

# Facilita recompilar só dando "make rebuild"
rebuild: clean all