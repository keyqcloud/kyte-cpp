# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -Iinclude -std=c++11 -O2
LDFLAGS = -lcurl -lssl -lcrypto

# Build directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
LIB_DIR = lib

# Library target
LIB_TARGET = $(LIB_DIR)/libkyte.a

# Source files for the library
LIB_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default target
all: build $(LIB_TARGET)

build:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR)  # Ensure the object and library directories exist

$(LIB_TARGET): $(LIB_OBJECTS)
	@echo "Building library..."
	@echo "LIB_TARGET = $(LIB_TARGET)"
	@echo "LIB_OBJECTS = $(LIB_OBJECTS)"
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $(LIB_OBJECTS)

# Generic rule for compiling C++ files to objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ_DIR)/*.o $(LIB_TARGET)
	@echo "Cleanup complete."

.PHONY: all clean build
