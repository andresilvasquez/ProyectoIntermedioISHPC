#include "functions.h"

int main(int argc, char **argv){
    const int L = std::atoi(argv[1]);
    double p = std::atof(argv[2]);
    int seed = std::atoi(argv[3]);

    std::vector<bool> malla = generar_malla_1D(L, p, seed);
    imprimir_malla(malla, L);

    int tamano_max;
    bool percola = hay_cluster_percolante(malla, L, tamano_max);
    std::cout << "Percola? " << (percola ? "Si" : "No") << "\n";
    if(percola){
        std::cout << "Tamaño del cluster percolante más grande: " << tamano_max << "\n";
    }
    return 0;
}