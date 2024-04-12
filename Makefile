# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -Iinclude -std=c++11 -O2
LDFLAGS = -lcurl -lssl -lcrypto

# Build directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Find all CPP files in SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Replace .cpp from SOURCES with .o and prepend OBJ_DIR
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Target executable
TARGET = $(BIN_DIR)/kyte_client

all: build $(TARGET)

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

# Link the target with all objects files
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile each source file to an object
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all build clean
