# Compilador
CXX = g++
CXXFLAGS = -I./src/include -Wall -std=c++17

# Diretórios
SRC_DIR = src
INCLUDE_DIR = src/include
OBJ_DIR = obj
BUILD_DIR = build

# Arquivos
SOURCES = $(filter-out $(SRC_DIR)/graph_gen.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Nome do executável
TARGET = $(BUILD_DIR)/hungarian

all: $(TARGET)

# Linka os objetos no executável
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compila arquivos .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria diretórios se não existirem
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all clean
