#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct Producto {
    std::string nombre;
    float precio;
    int cantidad;
};

std::vector<Producto> leerProductos(std::ifstream& archivo) {
    std::vector<Producto> productos;
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre;
        float precio;
        int cantidad;
        std::getline(ss, nombre, ',');
        ss >> precio;
        ss.ignore();
        ss >> cantidad;
        productos.push_back({nombre, precio, cantidad});
    }
    return productos;
}

void imprimirProductos(const std::vector<Producto>& productos) {
    for (const auto& producto : productos) {
        std::cout << "\"" << producto.nombre << "\", " << producto.precio << ", " << producto.cantidad << std::endl;
    }
}

void guardarProductos(std::ofstream& archivo, const std::vector<Producto>& productos) {
    for (const auto& producto : productos) {
        archivo << "\"" << producto.nombre << "\", " << producto.precio << ", " << producto.cantidad << std::endl;
    }
}

int main() {
    std::ifstream archivoEntrada("lista_productos.txt");
    if (!archivoEntrada.is_open()) {
        std::cout << "No se pudo abrir el archivo lista_productos.txt." << std::endl;
        return 1;
    }

    std::vector<Producto> productos = leerProductos(archivoEntrada);
    archivoEntrada.close();

    std::cout << "Lista de productos actual:" << std::endl;
    imprimirProductos(productos);

    std::cout << "\nIngrese el número de producto que desea modificar (1-" << productos.size() << "): ";
    int opcion;
    std::cin >> opcion;
    std::cin.ignore();

    if (opcion < 1 || opcion > productos.size()) {
        std::cout << "Opción inválida." << std::endl;
        return 1;
    }

    Producto& productoSeleccionado = productos[opcion - 1];

    std::cout << "Producto seleccionado: " << productoSeleccionado.nombre << std::endl;
    std::cout << "Ingrese el nuevo precio: ";
    std::cin >> productoSeleccionado.precio;
    std::cout << "Ingrese la nueva cantidad: ";
    std::cin >> productoSeleccionado.cantidad;

    std::ofstream archivoSalida("lista_productos.txt");
    if (!archivoSalida.is_open()) {
        std::cout << "No se pudo abrir el archivo lista_productos.txt para guardar los cambios." << std::endl;
        return 1;
    }

    guardarProductos(archivoSalida, productos);
    archivoSalida.close();

    std::cout << "Se han guardado los cambios en el archivo lista_productos.txt." << std::endl;

    return 0;
}


