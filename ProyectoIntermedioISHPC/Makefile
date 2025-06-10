CXX = g++
CXXFLAGS = -fsanitize=address,undefined,leak -fprofile-arcs -ftest-coverage
DEBUGFLAGS = -g -ggdb -O0 
VALGRINDFLAGS = -g -O1
COVERAGEFLAGS = -g -coverage -fprofile-arcs -ftest-coverage
FLAME = $(HOME)/Downloads/FlameGraph

L_valores = 32 64 128 256 512
p_valores = 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.56 0.57 0.58 0.59 0.6 0.61 0.62 0.63 0.64 0.65 0.7 0.73 0.76 0.79 0.82 0.85 0.88 0.91 0.94 0.97
semillas = $(shell seq 1 50)
OPTIMIZERS = O0 O1 O2 O3 Ofast 

BIN_DIR = bin
OPT_DIR = $(BIN_DIR)/opt
SRC     = main.cpp functions.cpp
OBJS    = $(SRC:%.cpp=$(BIN_DIR)/%.o)

all: $(BIN_DIR)/percolacion.x

$(BIN_DIR):
	@mkdir -p $@

$(OPT_DIR):
	@mkdir -p $@

$(BIN_DIR)/%.o: %.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR)/percolacion.x: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

percolacion_%.x : main.cpp functions.cpp | $(OPT_DIR)
	$(CXX) -$* $(CXXFLAGS) $^ -o $(OPT_DIR)/percolacion_$*.x

$(BIN_DIR)/test_functions.o : test_functions.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

resultados:
	mkdir -p resultados

ejecutar_%: percolacion_%.x resultados
	/usr/bin/time parallel "$(OPT_DIR)/percolacion_$*.x {1} {2} {3} 0 >> resultados/datos_{1}_{2}_$*.txt" ::: $(L_valores) ::: $(p_valores) ::: $(semillas)

ejecutar: $(foreach opt,$(OPTIMIZERS),ejecutar_$(opt))

analisis: ejecutar
	python3 probperc.py "$(L_valores)" "$(p_valores)" "$(OPTIMIZERS)"

simul : $(BIN_DIR)/percolacion.x
	./$< 512 0.7 10 1

test_functions.x: $(BIN_DIR)/test_functions.o $(BIN_DIR)/functions.o #spack load catch2
	$(CXX) $^ -o $@  -l Catch2Main -l Catch2

test: test_functions.x
	./$<

coverage: test_functions.x #firefox coverage.html
	./test_functions.x
	gcov -o $(BIN_DIR) functions.cpp test_functions.cpp
	gcovr --html-details coverage.html
	@echo "Open coverage/index.html en el navegador"

debug: 
	g++ $(DEBUGFLAGS) main.cpp functions.cpp -o percolacion_debug.x
	gdb ./percolacion_debug.x

valgrind:
	g++ $(VALGRINDFLAGS) main.cpp functions.cpp -o percolacion_val.x
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes ./percolacion_val.x 512 0.7 10

percolacion_pg.x: main.cpp functions_dfsviejo.cpp
	$(CXX) $(CXXFLAGS) -O0 -pg -g -fno-inline $^ -o $@ 


#flat-profile crítico -> profiling-report.txt (L=128, pc \approx 0.59271)
profiling-report.txt: percolacion_pg.x
	@mkdir -p profiling
	# graba un perfil estadístico en UNA pasada
	perf record -g --output=profiling/perf.data \
	            ./percolacion_pg.x 128 0.59271 10
	# vuelca un flat profile en texto
	perf report --stdio --input=profiling/perf.data > profiling-report.txt

profile: percolacion_pg.x #revisar si puede poner solo las funciones de interés
	@mkdir -p profiling
	./percolacion_pg.x 1000 0.5 10 
	gprof percolacion_pg.x gmon.out | grep -v 'std::\|__gnu_cxx\|operator\|std::chrono\|std::__' > profiling/analysis.txt

	perf record --call-graph dwarf -F99 -g -- ./percolacion_pg.x 1000 0.5 10
	perf script | $(FLAME)/stackcollapse-perf.pl > profiling/out.folded
	$(FLAME)/flamegraph.pl profiling/out.folded > profiling/flamegraph.svg

	@echo "Wrote flat profile and flamegraph to profiling/analysis.txt and profiling/flamegraph.svg"

clean:
	rm -f *.x *.gcda *.gcno *.txt *.pdf gmon.out perf.data* *.svg *.gcov *.html *.css
	rm -rf resultados profiling
	rm -rf $(BIN_DIR)