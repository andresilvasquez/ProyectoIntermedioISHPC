CXX = g++
CXXFLAGS = -fsanitize=address,undefined,leak -fprofile-arcs -ftest-coverage

BIN_DIR = bin
SRC = main.cpp functions.cpp
OBJS = $(SRC:%.cpp=$(BIN_DIR)/%.o)
TARGET = $(BIN_DIR)/percolacion.x

all: $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compilar .cpp a bin/*.o
$(BIN_DIR)/%.o: %.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Enlazar objetos a bin/percolacion.x
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TARGET)
	@if [ -z "$(L)" ] || [ -z "$(P)" ]; then \
		echo "Usage: make run L=10 P=0.6"; exit 1; \
	fi; \
	./$(TARGET) $(L) $(P)

coverage: $(TARGET)
	@if [ -z "$(L)" ] || [ -z "$(P)" ]; then \
		echo "Usage: make coverage L=10 P=0.6"; exit 1; \
	fi; \
	./$(TARGET) $(L) $(P); \
	gcov main.cpp functions.cpp; \
	lcov --capture --directory . --output-file coverage.info; \
	genhtml coverage.info --output-directory coverage

clean:
	rm -rf $(BIN_DIR) *.gcov *.gcno *.gcda *.info *~ a.out coverage

