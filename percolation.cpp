#include <iostream>
#include <vector>
#include <random>

// Alias para la malla
using Grid = std::vector<std::vector<bool>>;

// Función para generar una malla aleatoria LxL con probabilidad de llenado p
Grid generar_malla(int L, double p, std::mt19937 &gen) {
    Grid malla(L, std::vector<bool>(L, false));
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            malla[i][j] = (dis(gen) < p);  // Ocupa el sitio con probabilidad p
        }
    }

    return malla;
}

// Función auxiliar para imprimir la malla (útil para pruebas)
void imprimir_malla(const Grid &malla) {
    for (const auto &fila : malla) {
        for (bool celda : fila) {
            std::cout << (celda ? '#' : '.');
        }
        std::cout << '\n';
    }
}

int main() {
    int L = 10;             // Tamaño de la malla
    double p = 0.6;         // Probabilidad de llenado

    std::random_device rd;
    std::mt19937 gen(rd());  // Generador aleatorio

    Grid malla = generar_malla(L, p, gen);
    imprimir_malla(malla);

    return 0;
}
