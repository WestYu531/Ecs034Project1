# 指定编译器
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

# GoogleTest 相关路径 (如果你已经安装了 GoogleTest)
GTEST_DIR = /usr/local/lib  # 根据你的安装路径调整
GTEST_LIBS = -lgtest -lgtest_main -pthread

# 目录
SRC_DIR = src
TEST_DIR = testsrc
OBJ_DIR = obj

# 目标文件
OBJECTS = $(OBJ_DIR)/StringUtils.o
TEST_OBJECTS = $(OBJ_DIR)/StringUtilsTest.o

TARGET = stringutils_test

# 规则
all: $(TARGET)

# 编译 StringUtils.cpp
$(OBJ_DIR)/StringUtils.o: $(SRC_DIR)/StringUtils.cpp include/StringUtils.h
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/StringUtils.cpp -o $@

# 编译 TStringUtilsTest.cpp
$(OBJ_DIR)/TestStringUtils.o: $(TEST_DIR)/StringUtilsTest.cpp include/StringUtils.h
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/StringUtilsTest.cpp -o $@

# 生成可执行文件
$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LIBS)

# 运行 GoogleTest
test: $(TARGET)
	./$(TARGET)

# 清理编译文件
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
