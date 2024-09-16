#include <iostream>

// Función para generar un número pseudoaleatorio
unsigned int pseudoAleatorio(unsigned int semilla) {
    semilla = (semilla ^ (semilla << 43)) ^ (semilla >> 57);
    semilla = (semilla ^ (semilla << 25));
    return semilla;
}

// Función para generar un ID aleatorio de una longitud dada
void generarID(int longitud, char* id) {
    // Semilla inicial
    unsigned int semilla = 3124823692; // Puedes cambiar esto para variar la secuencia

    // Definir los caracteres posibles para el ID
    const char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int numCaracteres = sizeof(caracteres) - 1;

    for (int i = 0; i < longitud; ++i) {
        // Generar un número aleatorio y mapearlo a un carácter
        semilla = pseudoAleatorio(semilla);
        int index = semilla % numCaracteres;
        id[i] = caracteres[index];
    }
    id[longitud] = '\0'; // Terminar la cadena
}

int main() {
    const int longitud = 10;
    char id[longitud + 1]; // +1 para el carácter nulo

    generarID(longitud, id);

    std::cout << "ID generado: " << id << std::endl;
    return 0;
}
