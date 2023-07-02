#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
struct Producto {
    string nombre;
    float precio;
    int cantidad;
};

std::vector<Producto> leerProductos(std::ifstream& archivo) {
    vector<Producto> productos;
    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre;
        float precio;
        int cantidad;
        getline(ss, nombre, ',');
        ss >> precio;
        ss.ignore();
        ss >> cantidad;
        productos.push_back({nombre, precio, cantidad});
    }
    return productos;
}

void imprimirProductos(const vector<Producto>& productos) {
    for (const auto& producto : productos) {
        cout << "\"" << producto.nombre << "\", " << producto.precio << ", " << producto.cantidad << endl;
    }
}

void guardarProductos(ofstream& archivo, const vector<Producto>& productos) {
    for (const auto& producto : productos) {
        archivo << "\"" << producto.nombre << "\", " << producto.precio << ", " << producto.cantidad << endl;
    }
}

int main() {
    ifstream archivoEntrada("lista_productos.txt");
    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo lista_productos.txt." << endl;
        return 1;
    }

    vector<Producto> productos = leerProductos(archivoEntrada);
    archivoEntrada.close();

    cout << "Lista de productos actual:" << endl;
    imprimirProductos(productos);

    cout << "\nIngrese el número de producto que desea modificar (1-" << productos.size() << "): ";
    int opcion;
    cin >> opcion;
    cin.ignore();

    if (opcion < 1 || opcion > productos.size()) {
        cout << "Opción inválida." << endl;
        return 1;
    }

    Producto& productoSeleccionado = productos[opcion - 1];

    cout << "Producto seleccionado: " << productoSeleccionado.nombre << endl;
    cout << "Ingrese el nuevo precio: ";
    cin >> productoSeleccionado.precio;
    cout << "Ingrese la nueva cantidad: ";
    cin >> productoSeleccionado.cantidad;

    std::ofstream archivoSalida("lista_productos.txt");
    if (!archivoSalida.is_open()) {
        cout << "No se pudo abrir el archivo lista_productos.txt para guardar los cambios." << endl;
        return 1;
    }

    guardarProductos(archivoSalida, productos);
    archivoSalida.close();

    cout << "Se han guardado los cambios en el archivo lista_productos.txt." << std::endl;

    return 0;
}

