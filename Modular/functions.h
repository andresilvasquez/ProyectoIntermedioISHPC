#include <vector>
#include <iostream>
#include <random>
#include <algorithm> //para std::max

std::vector<bool> generar_malla_1D(int L, double p);
void imprimir_malla(const std::vector<bool>& malla, int L);

int fila(int id, int L);
int columna(int id, int L);
int index(int i, int j, int L);

bool hay_cluster_percolante(const std::vector<bool>& malla, int L, int& tamano_max);
