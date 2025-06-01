#include <vector>
#include <iostream>
#include <random>
#include <algorithm>  // para std::max
#include <fstream>  // Para escribir en .txt

std::vector<bool> generar_malla_1D(int L, double p, int seed);
void imprimir_malla(const std::vector<bool>& malla, int L);
void imprimir_clusters(const std::vector<int>& etiquetas, const std::vector<bool>& malla, int L);

int fila(int id, int L);
int columna(int id, int L);
int index(int i, int j, int L);

bool hay_cluster_percolante(const std::vector<bool>& malla, int L, int& tamano_max, std::vector<int>& etiquetas, std::vector<int>& percolantes);
