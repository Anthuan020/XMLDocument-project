#include "XMLDocument.hpp"
#include <iostream>

int main() {
    // Crear un documento XML
    XMLDocument doc;

    // Establecer el nodo raíz
    if (doc.Root("root") == 0) {
        std::cout << "Root node created successfully.\n";
    } else {
        std::cout << "Failed to create root node.\n";
        return 1;
    }

    // Seleccionar el nodo raíz
    if (doc.Select("_")) {
        std::cout << "Root node selected successfully.\n";
    } else {
        std::cout << "Failed to select root node.\n";
        return 1;
    }

    // Añadir un hijo al nodo raíz con contenido
    if (doc.Child("child1", "This is child 1") == 0) {
        std::cout << "Child node added successfully.\n";
    } else {
        std::cout << "Failed to add child node.\n";
        return 1;
    }

    // Añadir otro hijo al nodo raíz sin contenido
    if (doc.Child("child2") == 0) {
        std::cout << "Another child node added successfully.\n";
    } else {
        std::cout << "Failed to add another child node.\n";
        return 1;
    }

    return 0;
}
