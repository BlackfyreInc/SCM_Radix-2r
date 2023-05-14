CC = g++
CFLAGS = -Wall -c -std=c++11
LDFLAGS = -lstdc++
EXECUTABLE = scm.exe

# Define source and object file paths
SRC_DIR = src
OBJ_DIR = obj
BFloat_DIR = $(SRC_DIR)/BFloat
TESTS_DIR = $(SRC_DIR)/TESTS
SCM_DIR = $(SRC_DIR)/SCM

# List all source files
BFloat_SRCS = $(wildcard $(BFloat_DIR)/*.cpp)
TESTS_SRCS = $(wildcard $(TESTS_DIR)/*.cpp)
SCM_SRCS = $(wildcard $(SCM_DIR)/*.cpp)
MAIN_SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Define object file nasize_exp
BFloat_OBJS = $(patsubst $(BFloat_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(BFloat_SRCS))
TESTS_OBJS = $(patsubst $(TESTS_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TESTS_SRCS))
SCM_OBJS = $(patsubst $(SCM_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SCM_SRCS))
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))

# Default target
all: $(EXECUTABLE)

# Link object files into executable
$(EXECUTABLE): $(BFloat_OBJS) $(TESTS_OBJS) $(SCM_OBJS) $(MAIN_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# create OBJ_DIR if it is absent
$(shell mkdir -p $(OBJ_DIR))

# Compile BFloat source files
$(OBJ_DIR)/%.o: $(BFloat_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Compile TESTS source files
$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Compile SCM source files
$(OBJ_DIR)/%.o: $(SCM_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@
	
# Compile main source file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ_DIR)/* $(EXECUTABLE)
