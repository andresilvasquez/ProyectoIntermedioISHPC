#include "functions.h"

// Genera una malla 1D de LxL con valores aleatorios booleanos segun la probabilidad p
std::vector<bool> generar_malla_1D(int L, double p){
    int N = L * L;
    std::vector<bool> malla(N, false);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0,1.0);

    for(int id = 0; id < N; ++id){
        malla[id] = (dist(gen) < p);
    }
    return malla;
}

int fila(int id, int L){
    return id / L;
}

int columna(int id, int L){
    return id % L;
}

int index(int i, int j, int L){
    return i * L + j;
}

// Funciona para detectar los clusters y etiquetarlos y determinar sus tamanos
static int dfs(int id, int L, int etiqueta, 
    const std::vector<bool>& malla, 
    std::vector<int>& etiquetas, bool& toca_arriba, 
    bool& toca_abajo, bool& toca_izquierda, bool& toca_derecha){
        if(id < 0 || id >= L * L) return 0;              // Controlar si el id de un elemento esta por fuera del rango
        if(!malla[id] || etiquetas[id] != 0) return 0;   // Si el elemento de la malla no esta ocupado (falso) o si ya pertenece a algun cluster

        // Si no pertenece a algun cluster, asignarle un numero e inicializar su tamano en 1
        etiquetas[id] = etiqueta;
        int tamano = 1;

        // Obtener la fila y columna del elemento dado su id en la malla 1D
        int i = fila(id, L);
        int j = columna(id, L);

        // Verificar si el elemento toca alguna frontera de la malla
        if(i == 0) toca_arriba = true;
        if(i == L - 1) toca_abajo = true;
        if(j == 0) toca_izquierda = true;
        if(j == L - 1) toca_derecha = true;
        
        // Definir las direcciones vecinas (Izquierda, Derecha, Abajo, Arriba)
        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0, 0, -1, 1};

        // Revisar los vecinos
        for(int dir = 0; dir < 4; ++dir){
            // Definir las coordenadas del vecino (fila y columna)
            int ni = i + dx[dir];
            int nj = j + dy[dir];
            
            // Verificar si el vecino esta en el rango de la malla
            if(ni >= 0 && ni < L && nj >= 0 && nj < L){
                int nid = index(ni, nj, L);  // id del elemento en la malla 1D

                // Anadir recursivamente el tamano del cluster del vecino
                tamano += dfs(nid, L, etiqueta, malla, etiquetas, toca_arriba, toca_abajo, toca_izquierda, toca_derecha);
            }
        }

        return tamano;
    }

bool hay_cluster_percolante(const std::vector<bool>& malla, int L, int& tamano_max){
    int N = L * L;
    std::vector<int> etiquetas(N, 0);  // Vector correspondiente a la malla 1D con numeros que etiqueten los clusters
    int etiqueta = 1;                  // Inicializar la etiqueta para el primer cluster
    tamano_max = 0;   
    bool percola = false;              // Variable boolena para registrar si el cluster percola o no

    // Iterar sobre todos los elementos de la malla
    for(int id = 0; id < N; ++id){
        if(malla[id] && etiquetas[id] == 0){  // Revisar si estan ocupados y si no pertenecen a algun cluster
            bool toca_arriba = false, toca_abajo = false;
            bool toca_izquierda = false, toca_derecha = false;
            
            // Detectar el cluster al que pertenece (todos sus elementos) y el tamano de este
            int tamano = dfs(id, L, etiqueta, malla, etiquetas, toca_arriba, toca_abajo, toca_izquierda, toca_derecha);

            // Determinar si el cluster es percolante y de serlo revisar si su tamano es maximo a los clusters precios
            if((toca_arriba && toca_abajo) || (toca_izquierda && toca_derecha)){
                percola = true;
                tamano_max = std::max(tamano_max, tamano);
            }
            etiqueta++;
        }
    }
    return percola;
}

void imprimir_malla(const std::vector<bool>& malla, int L){
    for(int i = 0; i < L; ++i){
        for(int j = 0; j < L; ++j){
            int id = index(i, j, L);
            std::cout << (malla[id] ? '#' : '.');
        }
        std::cout << "\n";
    }
}