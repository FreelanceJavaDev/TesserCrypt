CC = g++
CORE_OBJS = ./core/tesseract.o ./core/rotate.o

FLAGS = -std=c++17
TEST_OBJS = ./tests/tesseract_unit_tests.o ./tests/rotate_unit_tests.o ./tests/core_tests.o 

all: core

$(CORE_OBJS): %.o : %.cpp
	$(CC) -std=c++17 -c $< -o $@

$(TEST_OBJS): %.o : %.cpp
	$(CC) -std=c++17 -c $< -o $@

core: $(CORE_OBJS)


test_core: $(TEST_OBJS) $(CORE_OBJS)
	$(CC) $(FLAGS) $(TEST_OBJS) $(CORE_OBJS) -o test_core -lboost_unit_test_framework

clean:
	rm -f $(CORE_OBJS) $(TEST_OBJS) test_core