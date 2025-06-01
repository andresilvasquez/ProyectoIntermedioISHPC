#include "functions.h"

int main(int argc, char **argv){
    const int L = std::atoi(argv[1]);
    double p = std::atof(argv[2]);
    int seed = std::atoi(argv[3]);

    std::vector<bool> malla = generar_malla_1D(L, p, seed);

    std::vector<int> etiquetas(L * L, 0);  // Vector correspondiente a la malla 1D con numeros que etiqueten los clusters (0 es no revisado)
    std::vector<int> percolantes;          // Vector para almacenar las etiquetas de los clusters percolantes

    int tamano_max;
    bool percola = hay_cluster_percolante(malla, L, tamano_max, etiquetas, percolantes);
    std::cout << "Percola? " << (percola ? "Si" : "No") << "\n";
    if(percola){
        std::cout << "Tamaño del cluster percolante más grande: " << tamano_max << "\n";
    }

    imprimir_clusters(etiquetas, malla, L);

    return 0;
}