CXX = g++
CXXFLAGS = -Wall -g -std=c++17
TEST_LIBS = -lgtest -lgtest_main -pthread

CORE_IMPL = BMP.cpp img_processor.cpp
CORE_OBJS = $(CORE_IMPL:.cpp=.o)

APP_SRC = main.cpp
APP_OBJ = main.o

TEST_IMPL = tests/Images.cpp tests/BMP.cpp tests/ImageProcessor.cpp
TEST_OBJS = $(TEST_IMPL:.cpp=.o)

APP_TARGET = bmpImageProcessor
TEST_TARGET = run_tests

.PHONY: all clean

all: $(APP_TARGET) $(TEST_TARGET)

$(APP_TARGET): $(CORE_OBJS) $(APP_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(CORE_OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o tests/*.o $(APP_TARGET) $(TEST_TARGET)
