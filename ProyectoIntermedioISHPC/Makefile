CXX = g++
CXXFLAGS = -fsanitize=address,undefined,leak -fprofile-arcs -ftest-coverage
L_valores = 32 64 128 256 512
p_valores = 0.1 0.15 0.2 0.25 0.3 0.35 0.4 0.45 0.5 0.55 0.56 0.57 0.58 0.59 0.6 0.61 0.62 0.63 0.64 0.65 0.7 0.73 0.76 0.79 0.82 0.85 0.88 0.91 0.94 0.97
semillas = 10 20 30 40 50 60 70 80 90 100
OPTIMIZERS = O0 O1 O2 O3 Ofast

percolacion_%.x : main.cpp functions.cpp
	$(CXX) -$* $(CXXFLAGS) $^ -o $@

resultados:
	mkdir -p resultados

ejecutar_%: percolacion_%.x resultados
	/usr/bin/time parallel "./percolacion_$*.x {1} {2} {3} >> resultados/datos_{1}_{2}_$*.txt" ::: $(L_valores) ::: $(p_valores) ::: $(semillas)

ejecutar: 
# $(OPTIMIZERS:%=ejecutar_%)

analisis:
	python3 probperc.py --L "$(L_valores)" --P "$(p_valores)" --OPT "$(OPTIMIZERS)"

simul : percolacion.x
	./percolacion.x 512 0.6 10

profile:

debug:

valgrind:

clean:
	rm -f *.x *.gcda *.gcno *.txt *.pdf
	rm -r resultados