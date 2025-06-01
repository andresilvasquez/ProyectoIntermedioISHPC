CXXFLAGS = -fsanitize=address,undefined,leak -fprofile-arcs -ftest-coverage

simul:
	g++ -O3 $(CXXFLAGS) main.cpp functions.cpp -o percolacion.x
	./percolacion.x 4 0.6 10

profile:

debug:

valgrind:



clean:
	rm -f *.x *.gcda *.gcno