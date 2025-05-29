#include "functions.h"

int main(int argc, char **argv) {
    const int L = std::atoi(argv[1]);            // Tamaño de la malla
    double p = std::atof(argv[2]);        // Probabilidad de llenado

    std::random_device rd;
    std::mt19937 gen(rd());  // Generador aleatorio

    std::vector<bool> malla = generar_malla_1D(L, p);  // usa versión 1D
    imprimir_malla(malla, L);

    int tamano_max;
    bool percola = hay_cluster_percolante(malla, L, tamano_max);
    std::cout << "¿Percola? " << (percola ? "Sí" : "No") << "\n";
    if (percola) {
        std::cout << "Tamaño del cluster percolante más grande: " << tamano_max << "\n";
    }

    return 0;
}