CXXFLAGS = -std=c++2a
OBJ = test_rec.o test_lex.o buffer.o lexical_analysis.o recursive_descent.o
OBJ_LEX = test_lex.o buffer.o lexical_analysis.o
OBJ_REC = test_rec.o buffer.o lexical_analysis.o recursive_descent.o
TARGET = test_lex test_rec

all: $(TARGET)

test_lex: $(OBJ_LEX)
	$(CXX) $(CXXFLAGS) -o $@ $^

test_rec: $(OBJ_REC)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean
clean:
	rm -rf $(OBJ) $(TARGET)
