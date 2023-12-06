# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -Wextra

# Source files
SRC := $(wildcard *.cpp)

# Object files
OBJ := $(SRC:.cpp=.o)

# Target executable
TARGET := tetris

# Default rule to build the target
all: $(TARGET)

# Rule to build the target from object files
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to generate object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the project
clean:
	rm -f $(OBJ) $(TARGET)
