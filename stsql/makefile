TARGET = tast.out
SRC_DIR = .
ALL_SRC = $(wildcard $(SRC_DIR:%=%/*.cpp)) # �Զ���ȡ���� .c Դ�ļ�
ALL_OBJ = $(ALL_SRC:%.cpp=%.o) # �滻 .c ��׺Ϊ .o �õ�����Ŀ���ļ��б�
ALL_DEP = $(ALL_SRC:%.cpp=%.d) # �õ�һϵ�� .d �����ļ��б�

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

$(ALL_DEP): %.d : %.cpp # �� cpp ����ÿ�� .c ������ .d �����ļ�
	cpp -MM $< > $@

$(ALL_OBJ): %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

ifeq ($(MAKECMDGOALS), all)
-include $(ALL_DEP) # ������ .d �ļ�����������ʵ��Ŀ���ļ�����������
endif