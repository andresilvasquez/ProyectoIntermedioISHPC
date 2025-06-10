#include "functions.h"

int main(int argc, char **argv){
    const int L = std::atoi(argv[1]);
    double p = std::atof(argv[2]);
    int seed = std::atoi(argv[3]);
    bool imprimir = std::atoi(argv[4]);
    auto wstart{std::chrono::steady_clock::now()};   // Wall time
    std::clock_t cstart = std::clock();              // CPU time

    std::vector<bool> malla = generar_malla_1D(L, p, seed);

    std::vector<int> etiquetas(L * L, 0);  // Vector correspondiente a la malla 1D con numeros que etiqueten los clusters (0 es no revisado)
    std::vector<int> percolantes;          // Vector para almacenar las etiquetas de los clusters percolantes

    int tamano_max;
    bool percola = hay_cluster_percolante(malla, L, tamano_max, etiquetas, percolantes);

    auto wend{std::chrono::steady_clock::now()};
    std::clock_t cend = std::clock();

    std::chrono::duration<double> elapsed{wend - wstart};
    double wduration = elapsed.count();
    double cduration = cend - cstart;

    std::cout << percola << "\t" << tamano_max << "\t" << wduration << "\t" << cduration << "\n";

    if(imprimir){
        imprimir_clusters(etiquetas, malla, percolantes, L);
    }
    
    return 0;
}