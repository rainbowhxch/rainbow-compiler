CXXFLAGS = -std=c++2a -g
TEST_DIR = test/
SRC_DIR = src/
OBJ = $(TEST_DIR)test_rec.o $(TEST_DIR)test_lex.o $(TEST_DIR)/test_ope.o $(SRC_DIR)buffer.o $(SRC_DIR)lexical_analysis.o $(SRC_DIR)recursive_descent.o $(SRC_DIR)operator_first.o
OBJ_LEX = $(TEST_DIR)test_lex.o $(SRC_DIR)buffer.o $(SRC_DIR)lexical_analysis.o
OBJ_REC = $(TEST_DIR)test_rec.o $(SRC_DIR)buffer.o $(SRC_DIR)lexical_analysis.o $(SRC_DIR)recursive_descent.o
OBJ_OPE = $(TEST_DIR)test_ope.o $(SRC_DIR)buffer.o $(SRC_DIR)lexical_analysis.o $(SRC_DIR)operator_first.o
TARGET = $(TEST_DIR)test_lex $(TEST_DIR)test_rec $(TEST_DIR)test_ope

all: $(TARGET)

$(TEST_DIR)test_lex: $(OBJ_LEX)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_DIR)test_rec: $(OBJ_REC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_DIR)test_ope: $(OBJ_OPE)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: all clean
clean:
	rm -rf $(OBJ) $(TARGET)
