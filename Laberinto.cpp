#include <iostream>  // Para las funciones de entrada y salida
#include <vector>    // Vectores para manejar direcciones
#include <algorithm> // Para usar random_shuffle, que nos dará aleatoriedad en la generación del laberinto
#include <ctime>     // Para generar números aleatorios 
#include <cstdlib>   // Para funciones rand y srand

using namespace std; // Para evitar escribir std:: todo el tiempo

// Tamaño del laberinto configurable
int WIDTH;  // Ancho del laberinto
int HEIGHT; // Altura del laberinto

// Matriz del laberinto (Puntero doble para manejar tamaños dinámicos) 
char** labyrinth;

// Posibles movimientos: arriba, abajo, izquierda y derecha
pair<int, int> directions[4] = { {0, 2}, {0, -2}, {2, 0}, {-2, 0} }; // Define las posibles direcciones para moverse

// Inicialización del laberinto con muros
void initializeLabyrinth() {
    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) {
            labyrinth[i][j] = '#';
        }
    }
}

// Imprime cada carácter del laberinto en la consola
void printLabyrinth() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << labyrinth[i][j] << " ";
        }
        cout << endl;
    }
}

// Función recursiva para generar el laberinto usando Backtracking
void generateLabyrinth(int x, int y) {
    labyrinth[x][y] = ' '; // Marca la celda actual como camino

    vector<pair<int, int>> dir(directions, directions + 4); // Crea un vector de direcciones basado en el array 'directions'
    random_shuffle(dir.begin(), dir.end()); // Mezcla las direcciones para obtener aleatoriedad

    for (auto d : dir) { // Intenta moverse en cada dirección
        int nx = x + d.first, ny = y + d.second;
        int between_x = x + d.first / 2, between_y = y + d.second / 2;
        if (nx > 0 && nx < HEIGHT - 1 && ny > 0 && ny < WIDTH - 1 && labyrinth[nx][ny] == '#') {
            labyrinth[between_x][between_y] = ' '; // Rompe el muro intermedio
            generateLabyrinth(nx, ny); // Llama recursivamente para continuar generando el laberinto desde la nueva posición
        }
    }
}

// Función recursiva para resolver el laberinto usando Backtracking
bool solveLabyrinth(int x, int y) {
    if (x == HEIGHT - 2 && y == WIDTH - 2) { // Si llegamos a la salida
        labyrinth[x][y] = '*'; // Marca el camino
        return true;
    }

    if (labyrinth[x][y] == ' ' || labyrinth[x][y] == 'S') { // Si la celda es un camino
        labyrinth[x][y] = '*'; // Marca el camino

        // Intenta moverse en cada dirección
        for (auto d : directions) {
            int nx = x + d.first / 2, ny = y + d.second / 2;
            if (solveLabyrinth(nx, ny)) { // Si el camino es válido
                return true;
            }
        }

        labyrinth[x][y] = ' '; // Desmarca el camino si no es válido
    }

    return false;
}

// Función principal
int main() {
    cout << "Introduce el ancho del laberinto (debe ser un numero impar): "; 
    // Al usar valores impares, evitamos complicaciones en la generación y resolución del laberinto, asegurando que todo 
    // funcione correctamente.
    cin >> WIDTH;
    cout << "Introduce la altura del laberinto (debe ser un numero impar): ";
    cin >> HEIGHT;

    // Asegurarse de que las dimensiones sean impares
    if (WIDTH % 2 == 0) WIDTH++;
    if (HEIGHT % 2 == 0) HEIGHT++;

    // Crear el laberinto dinámicamente
    labyrinth = new char*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        labyrinth[i] = new char[WIDTH];
    }

    srand(time(0)); // Inicializar la semilla para la generación de números aleatorios

    initializeLabyrinth();   // Inicializar el laberinto con muros
    generateLabyrinth(1, 1); // Comenzar la generación desde la posición (1, 1)

    // Marcar entrada y salida
    labyrinth[1][1] = 'S';
    labyrinth[HEIGHT - 2][WIDTH - 2] = 'E';

    // Resolver el laberinto
    solveLabyrinth(1, 1);

    printLabyrinth(); // Imprimir el laberinto generado y resuelto

    // Liberar la memoria
    for (int i = 0; i < HEIGHT; i++) {
        delete[] labyrinth[i];
    }
    delete[] labyrinth;

    return 0;
}
