#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"

#include "functions.h"

TEST_CASE("Malla de solo ceros no percola") {
    int L = 10;
    double p = 0.0;
    int seed = 42;

    auto malla = generar_malla_1D(L, p, seed);
    std::vector<int> etiquetas(L * L, 0);
    std::vector<int> percolantes;
    int tamano_max = 0;

    bool resultado = hay_cluster_percolante(malla, L, tamano_max, etiquetas, percolantes);
    REQUIRE_FALSE(resultado);
    REQUIRE(tamano_max == 0);
    REQUIRE(percolantes.empty());
}

TEST_CASE("Malla de solo unos siempre percola") {
    int L = 10;
    double p = 1.0;
    int seed = 42;

    auto malla = generar_malla_1D(L, p, seed);
    std::vector<int> etiquetas(L * L, 0);
    std::vector<int> percolantes;
    int tamano_max = 0;

    bool resultado = hay_cluster_percolante(malla, L, tamano_max, etiquetas, percolantes);
    REQUIRE(resultado);
    REQUIRE(tamano_max == L * L);
    REQUIRE_FALSE(percolantes.empty());
}

TEST_CASE("Malla con línea horizontal de unos", "[horizontal]") {
    int L = 10;
    std::vector<bool> malla(L * L, false); // malla inicial de ceros

    // Línea horizontal en la fila central
    int fila = L / 2;
    for (int j = 0; j < L; ++j) {
        malla[fila * L + j] = true;
    }

    std::vector<int> etiquetas(L * L, 0);
    std::vector<int> percolantes;
    int tamano_max = 0;

    bool hay = hay_cluster_percolante(malla, L, tamano_max, etiquetas, percolantes);
    
    // debería haber percolación horizontal
    REQUIRE(hay);
    REQUIRE(tamano_max == L);
}

TEST_CASE("Malla con línea vertical de unos", "[vertical]") {
    int L = 10;
    std::vector<bool> malla(L * L, false);

    // Línea vertical en la primera columna
    for (int i = 0; i < L; ++i) {
        malla[i * L + 0] = true;
    }

    std::vector<int> etiquetas(L * L, 0);
    std::vector<int> percolantes;
    int tamano_max = 0;

    bool hay = hay_cluster_percolante(malla, L, tamano_max, etiquetas, percolantes);
    
    // Sí debería haber percolación vertical
    REQUIRE(hay);
    REQUIRE(tamano_max == L);
}