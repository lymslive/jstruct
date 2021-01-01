TARGET = tast.out
SRC_DIR = .
ALL_SRC = $(wildcard $(SRC_DIR:%=%/*.cpp)) # 自动获取所有 .c 源文件
ALL_OBJ = $(ALL_SRC:%.cpp=%.o) # 替换 .c 后缀为 .o 得到所有目标文件列表
ALL_DEP = $(ALL_SRC:%.cpp=%.d) # 得到一系列 .d 依赖文件列表

CXX = g++
CXXFLAGS += -Wall 

.PHONY: all clean run
all: $(TARGET)
run:
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(ALL_OBJ) $(ALL_DEP)

$(TARGET) : $(ALL_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(ALL_OBJ)

$(ALL_DEP): %.d : %.cpp # 用 cpp 处理每个 .c ，保存 .d 依赖文件
	cpp -MM $< > $@

$(ALL_OBJ): %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

ifeq ($(MAKECMDGOALS), all)
-include $(ALL_DEP) # 将所有 .d 文件包含进来，实现目标文件的依赖规则
endif
