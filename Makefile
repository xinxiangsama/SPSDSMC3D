# 编译器
# CXX = mpicxx
CXX = g++

# 编译选项
CXXFLAGS = 	-std=c++17 -Wall \
		 	-I./src \
		 	-I/usr/local/include\
			-I/usr/local/include/vtk-9.4\

# 链接选项
LDFLAGS = -L/usr/local/lib\
          -lvtkCommonCore-9.4 \
          -lvtkCommonDataModel-9.4 \
          -lvtkIOXML-9.4 \
		  -lvtkIOParallelXML-9.4 \
          -lvtkRenderingOpenGL2-9.4 \
          -lvtkRenderingCore-9.4 \
          -lvtksys-9.4 \


# 根目录
SRC_DIR := src
BUILD_DIR := build
TARGET := SPSDSMC3D

# 查找所有cpp文件
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')

# 将src/xxx.cpp映射成build/xxx.o
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# 默认目标
all: $(TARGET)

# 链接可执行文件
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 编译每个cpp到build目录下的o文件
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理目标
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	rm -f *.vtu

.PHONY: all clean
