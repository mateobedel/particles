CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
BIN = bin/program

SRCS = $(wildcard $(SRC_DIR)/*.cxx)
OBJS = $(patsubst $(SRC_DIR)/%.cxx, $(OBJ_DIR)/%.o, $(SRCS))

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p bin

clean:
	rm -rf $(OBJ_DIR) $(BIN)

run: $(BIN)
	./$(BIN)

visu: $(BIN)
	./$(BIN) > p.data && python3 visu.py

.PHONY: clean