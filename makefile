CXXFLAGS = -std=c++2a
OBJ = test.o buffer.o lexical_analysis.o
TARGET = test

all: test

test: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

*.o: *.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean
clean:
	rm -rf $(OBJ) $(TARGET)
