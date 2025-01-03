# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Ilib

# Directories
SRC_DIR = src
LIB_DIR = lib

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

# Target executable
TARGET = coffeeShop

# Default target
all: $(TARGET)

# Linking target
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Compilation target
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(LIB_DIR)/%.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	del /Q $(SRC_DIR)\*.o $(TARGET)
