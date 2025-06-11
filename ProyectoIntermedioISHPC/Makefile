CXX = g++
CXXFLAGS = -std=c++17 -fsanitize=address,undefined,leak 
COVERAGE = -g --coverage -fprofile-arcs -ftest-coverage
DEBUGFLAGS = -g -ggdb -O0 
VALGRINDFLAGS = -g -O1

L_valores = 32 64 128 256 512
p_valores = 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.56 0.57 0.58 0.59 0.6 0.61 0.62 0.63 0.64 0.65 0.7 0.73 0.76 0.79 0.82 0.85 0.88 0.91 0.94 0.97
semillas = $(shell seq 1 50)
OPTIMIZERS = O0 O1 O2 O3 Ofast 

BIN_DIR = bin
OPT_DIR = $(BIN_DIR)/opt
DIRS = $(BIN_DIR) $(OPT_DIR) profiling latex_output
SRC = main.cpp functions.cpp
OBJS = $(SRC:%.cpp=$(BIN_DIR)/%.o)

# Mensaje de uso de los argumentos
usage:
	@echo "Uso de ARGS: <L> <p> <seed> <¿Quiere imprimir malla?->(1=sí,0=no)>"
	@echo "Ejemplo: make profile ARGS=\"1000 0.7 10 1\""

#Crea las carpetas
$(DIRS):
	@mkdir -p $@

#Archivos objeto
$(BIN_DIR)/%.o: %.cpp | $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

#Ejecutables sin optimización
$(BIN_DIR)/percolacion.x: $(OBJS)
	@$(CXX) $(CXXFLAGS) $(COVERAGE) $^ -o $@

#Ejecutables con optimización
$(OPT_DIR)/percolacion_%.x: $(OBJS) | $(OPT_DIR)
	@$(CXX) -$* $(CXXFLAGS) $(COVERAGE) $^ -o $@

resultados:
	@mkdir -p resultados

ejecutar_%: $(OPT_DIR)/percolacion_%.x resultados
	@/usr/bin/time parallel "$(OPT_DIR)/percolacion_$*.x {1} {2} {3} 0 >> resultados/datos_{1}_{2}_$*.txt" ::: $(L_valores) ::: $(p_valores) ::: $(semillas)

ejecutar: $(foreach opt,$(OPTIMIZERS),ejecutar_$(opt))

ProbabilidadCluster.pdf TamanoCluster.pdf Tiempos.pdf:
	@echo "Hacer make ejecutar antes"
	@python3 probperc.py "$(L_valores)" "$(p_valores)" "$(OPTIMIZERS)"

analisis : ProbabilidadCluster.pdf TamanoCluster.pdf Tiempos.pdf

#Simulación. Ingresar los args desde línea de comandos
malla.pdf : $(BIN_DIR)/percolacion.x
ifndef ARGS
	@$(MAKE) usage
	@exit 1
endif
	@./$< $(ARGS)
	@python3 clusters.py

simul : malla.pdf

#Test 
$(BIN_DIR)/functions.o: functions.cpp | $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(COVERAGE) -c $< -o $@

$(BIN_DIR)/test_functions.o: test_functions.cpp | $(BIN_DIR)
	@bash -c "spack load catch2 > /dev/null 2>&1 && \
	  $(CXX) $(CXXFLAGS) $(COVERAGE) -c $< -o $@"

test_functions.x: $(BIN_DIR)/test_functions.o $(BIN_DIR)/functions.o
	@bash -c "spack load catch2 > /dev/null 2>&1 && \
	  $(CXX) $(CXXFLAGS) $(COVERAGE) $^ -o $@ -lCatch2Main -lCatch2"

test: test_functions.x
	@./$< 

coverage: test_functions.x
	./$<
	@gcovr --html --html-details -o coverage.html
	@echo "Coverage report generated at -> firefox coverage.html"

debug: 
	$(CXX) $(DEBUGFLAGS) main.cpp functions.cpp -o percolacion_debug.x
	gdb ./percolacion_debug.x

valgrind: 
ifndef ARGS
	$(MAKE) usage
	@exit 1
endif
	$(CXX) $(VALGRINDFLAGS) main.cpp functions.cpp -o percolacion_val.x
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes \
	    ./percolacion_val.x $(ARGS)

#Binarioss con profiling para cada versión de la función
percolacion_pg_functions.x: main.cpp functions.cpp #función nueva (recorre primera fila y columna)
	@$(CXX) $(CXXFLAGS) -O0 -pg -g -fno-inline $^ -o $@

percolacion_pg_functions_1.x: main.cpp functions_1.cpp #función original (recorre toda la malla)
	@$(CXX) $(CXXFLAGS) -O0 -pg -g -fno-inline $^ -o $@

####
#flat-profile crítico -> profiling-report.txt (L=128, pc \approx 0.59271)
#Con estos flat profiles se pueden comparar cambios entre ambas versiones

# Flat‐profile para functions.cpp → profiling-report.txt
profiling-report.txt: percolacion_pg_functions.x
	@mkdir -p profiling
	@perf record -g --output=profiling/functions.perf.data \
	    ./percolacion_pg_functions.x 128 0.59271 10 0
	@perf report --stdio --input=profiling/functions.perf.data \
	    > profiling-report.txt
	@echo "Wrote flat profile report to profiling-report.txt"

# Flat‐profile para functions_1.cpp → profiling-report_1.txt
profiling-report_1.txt: percolacion_pg_functions_1.x
	@mkdir -p profiling
	@perf record -g --output=profiling/functions_1.perf.data \
	    ./percolacion_pg_functions_1.x 128 0.59271 10 0
	@perf report --stdio --input=profiling/functions_1.perf.data \
	    > profiling-report_1.txt
	@echo "Wrote flat profile report to profiling-report_1.txt"

####

profile: percolacion_pg_functions.x #Falta arreglar y cambiarlo por gprof
ifndef ARGS
	@$(MAKE) usage
	@exit 1	
endif
	@mkdir -p profiling
	@./$< $(ARGS)
	@#Profiling con gprof
	@gprof percolacion_pg_functions.x gmon.out > profiling/gprof.txt
	@#Profiling con perf
	@perf record -g -F99 --call-graph dwarf --output=profiling/functions.perf.data ./$< $(ARGS)
	@perf report --stdio --input=profiling/functions.perf.data > profiling/perf.txt
	@echo "Wrote profile report made with gprof to profiling/gprof.txt"
	@echo "Wrote profile report made with perf to profiling/perf.txt"

reporte.pdf: ProbabilidadCluster.pdf TamanoCluster.pdf Tiempos.pdf malla.pdf
	latexmk -pdf reporte.tex
	rm -f reporteNotes.bib *.aux *.bbl *.blg *.fdb* *.fls *.log *.synctex.gz *.out 

report : reporte.pdf

clean:      #el @find ... evita borrar el profiling-report.txt, pero borra el resto de .txtc
	@find . -maxdepth 1 -type f -name '*.txt' ! -name 'profiling-report.txt' -delete
	rm -f *.x *.gcda *.gcno *.pdf *.gcov *.html *.css gmon.out perf.data* *.svg
	rm -rf $(BIN_DIR) resultados profiling latex_output
