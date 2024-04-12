# Compiler and linker settings
CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2
LDFLAGS = -lcurl -lssl -lcrypto

# Directories
INCLUDE_DIR = /usr/local/include/kyte
LIB_DIR = /usr/local/lib

# Executable name
EXEC = example_app

# Source files
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ -L$(LIB_DIR) -lkyte $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(EXEC)

.PHONY: all clean
