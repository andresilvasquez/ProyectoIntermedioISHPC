#include "functions.h"

// Genera una malla 1D de LxL con valores aleatorios booleanos segun la probabilidad p
std::vector<bool> generar_malla_1D(int L, double p, int seed){
    int N = L * L;
    std::vector<bool> malla(N, false);

    std::mt19937 gen(seed);
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

bool es_percolante(const std::vector<int>& percolantes , int etiqueta){
    return std::find(percolantes.begin(), percolantes.end(), etiqueta) != percolantes.end(); // true si la etiqueta se encuentra en el vector de percolantes
}

// Funciona para detectar los clusters y etiquetarlos y determinar sus tamanos
static int dfs(int id, int L, int etiqueta, 
    const std::vector<bool>& malla, 
    std::vector<int>& etiquetas, bool& toca_arriba, 
    bool& toca_abajo, bool& toca_izquierda, bool& toca_derecha)
{
    if (id < 0 || id >= L * L) return 0;
    if (!malla[id] || etiquetas[id] != 0) return 0;

    std::stack<int> pila;   //crea una pila de enteros para evitar hacer llamados recursivos a dfs
    pila.push(id);          //se añade la posición id de la malla a la pila
    etiquetas[id] = etiqueta; //se le asigna una etiqueta

    int tamano = 0;

    const int dx[4] = {-1, 1, 0, 0};  //se definen las direcciones de busqueda de vecinos
    const int dy[4] = {0, 0, -1, 1};

    while (!pila.empty()) {         //mientras la pila no esté vacía 
        int actual = pila.top();      //se pasa el valor de id a actual
        pila.pop();                   //se vacía el valor id de la pila

        int i = fila(actual, L);        //con el valor actual se definen las coordenadas i y j
        int j = columna(actual, L);

        tamano++;                       //aumentamos en 1 el tamaño

        if (i == 0) toca_arriba = true;         //revisamos si i y j cumplen con condiciones de percolación
        if (i == L - 1) toca_abajo = true;      //para actualizar el valor de los booleanos
        if (j == 0) toca_izquierda = true;
        if (j == L - 1) toca_derecha = true;

        for (int dir = 0; dir < 4; ++dir) {     //ahora revisamos para cada uno de los cuatro vecinos
            int ni = i + dx[dir];
            int nj = j + dy[dir];

            if (ni >= 0 && ni < L && nj >= 0 && nj < L) {
                int nid = index(ni, nj, L);
                if (malla[nid] && etiquetas[nid] == 0) {  //si está ocupado en la malla y sin etiqueta
                    etiquetas[nid] = etiqueta;
                    pila.push(nid);                     //y agregamos su valor a la pila de nuevo para repetir el ciclo
                }
            }
        }
    }
}

bool hay_cluster_percolante(const std::vector<bool>& malla, int L, int& tamano_max, std::vector<int>& etiquetas, std::vector<int>& percolantes){
    int N = L * L; 
    int etiqueta = 2;                  // Inicializar la etiqueta para el primer cluster
    tamano_max = 0;   
    bool percola = false;              // Variable boolena para registrar si el cluster percola o no

    // Iterar sobre los elementos de la primera fila
    for(int id = 0; id < L; ++id){
        if(malla[id] && etiquetas[id] == 0){  // Revisar si estan ocupados y si no pertenecen a algun cluster
            bool toca_arriba = false, toca_abajo = false;
            bool toca_izquierda = false, toca_derecha = false;

            // Detectar el cluster al que pertenece (todos sus elementos) y el tamano de este
            int tamano = dfs(id, L, etiqueta, malla, etiquetas, toca_arriba, toca_abajo, toca_izquierda, toca_derecha);

            // Determinar si el cluster es percolante y de serlo revisar si su tamano es maximo a los clusters precios
            if((toca_arriba && toca_abajo) || (toca_izquierda && toca_derecha)){
                percola = true;
                tamano_max = std::max(tamano_max, tamano);
                percolantes.push_back(etiqueta);
            }
            etiqueta++;
        }
    }

    // Iterar sobre los elementos de la primera columna
    for(int id = 0; id < N; id += L){
        if(malla[id] && etiquetas[id] == 0){  // Revisar si estan ocupados y si no pertenecen a algun cluster
            bool toca_arriba = false, toca_abajo = false;
            bool toca_izquierda = false, toca_derecha = false;

            // Detectar el cluster al que pertenece (todos sus elementos) y el tamano de este
            int tamano = dfs(id, L, etiqueta, malla, etiquetas, toca_arriba, toca_abajo, toca_izquierda, toca_derecha);

            // Determinar si el cluster es percolante y de serlo revisar si su tamano es maximo a los clusters previos
            if((toca_arriba && toca_abajo) || (toca_izquierda && toca_derecha)){
                percola = true;
                tamano_max = std::max(tamano_max, tamano);
                percolantes.push_back(etiqueta);  // Agregar la etiqueta al vector que almacena las etiquetas de los percolantes
            }
            etiqueta++;
        }
    }
    return percola;
}

// Solo colorea los clusters percolantes, los otros clusters los etiqueta como 1 (blanco) y los no ocupados con 0 (negro)
void imprimir_clusters(const std::vector<int>& etiquetas, const std::vector<bool>& malla, const std::vector<int>& percolantes, int L){
    int id;
    std::ofstream malla_etiquetada("malla_etiquetada.txt");  // Crear el objeto sobre el que se realizaran modificaciones para el .txt
    for(int i = 0; i < L; ++i){
        for(int j = 0; j < L; ++j){
            id = index(i, j, L);
            // Si el elemento de la malla no esta ocupado, llenar con 0 la malla etiquetada
            if(!malla[id]){
                malla_etiquetada << 0 << "\t";
            }
            // Si el elemento de la malla pertenece a un cluster percolante, llenar con la etiqueta del cluster correspondiente
            else if(etiquetas[id] != 0 && es_percolante(percolantes, etiquetas[id])){
                malla_etiquetada << etiquetas[id] << "\t";
            }
            // Si el elemento de la malla pertenece a un cluster pero no es percolante, colocar 1 en la malla etiquetada
            else{
                malla_etiquetada << 1 << "\t";
            }
        }
        malla_etiquetada << "\n";
    }

    malla_etiquetada.close();  // Cerrar el objeto del .txt
}