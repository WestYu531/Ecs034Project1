CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude -I/opt/homebrew/Cellar/googletest/1.15.2/include
GTEST_LIBS = -L/opt/homebrew/Cellar/googletest/1.15.2/lib -lgtest -lgtest_main -pthread

SRC_DIR = src
TEST_DIR = testsrc
OBJ_DIR = obj

OBJECTS = $(OBJ_DIR)/StringUtils.o
TEST_OBJECTS = $(OBJ_DIR)/StringUtilsTest.o

TARGET = stringutils_test

all: $(TARGET)

$(OBJ_DIR)/StringUtils.o: $(SRC_DIR)/StringUtils.cpp include/StringUtils.h
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/StringUtils.cpp -o $@

$(OBJ_DIR)/StringUtilsTest.o: $(TEST_DIR)/StringUtilsTest.cpp include/StringUtils.h
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/StringUtilsTest.cpp -o $@

$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LIBS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)