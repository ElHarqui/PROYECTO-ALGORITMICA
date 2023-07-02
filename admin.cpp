#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;
struct Producto {
    string nombre;
    float precio;
    int cantidad;
};

void imprimirListaProductos(const std::vector<Producto>& listaProductos) {
    for (vector<Producto>::const_iterator it = listaProductos.begin(); it != listaProductos.end(); ++it) {
        cout << "Nombre: " << it->nombre << endl;
        cout << "Precio: " << it->precio << endl;
        cout << "Cantidad: " << it->cantidad << endl;
        cout << endl;
    }
}

int main() {
    ifstream archivo;
    archivo.open("lista_productos.txt",ios::in);
    
    vector<Producto> listaProductos;
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            Producto producto;
            string nombre;
            string precio;
            string cantidad;

            size_t pos1 = linea.find("\"");
            size_t pos2 = linea.find("\"", pos1 + 1);
            size_t pos3 = linea.find("\"", pos2 + 1);
            size_t pos4 = linea.find("\"", pos3 + 1);
            size_t pos5 = linea.find(",", pos4 + 1);

            nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            precio = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            cantidad = linea.substr(pos5 + 1);

            producto.nombre = nombre;
            producto.precio = atof(precio.c_str());
            producto.cantidad = atoi(cantidad.c_str());

            listaProductos.push_back(producto);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    imprimirListaProductos(listaProductos);

    return 0;
}

