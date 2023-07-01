#include <iostream>
#include <string>

using namespace std;

struct Product {
    int stock;
    char accion[10];
    int cantidad;
    char nombre[30];
} producto;

struct VisualizacionCarrito {
    float subtotal;
    float total;
    int carrito;
    float descuento;
} carrito1;

//Prototipos 
int mostrarResumen(int stock, char accion[10], int cantidad, float subtotal, float total, float descuento);

//principal

int main() {
    cout << "Ingrese los productos del carrito: ";
    cin >> carrito1.carrito;

    cout << "Ingrese el subtotal: $";
    cin >> carrito1.subtotal;

    cout << "Ingrese el descuento: $";
    cin >> carrito1.descuento;

    carrito1.total = carrito1.subtotal - carrito1.descuento;

    mostrarResumen(producto.stock, producto.accion, producto.cantidad, carrito1.subtotal, carrito1.total, carrito1.descuento);

    return 0;
}

//subprograma

int mostrarResumen(int stock, char accion[10], int cantidad, float subtotal, float total, float descuento) {
	
	int menu;
	
	cout << "Desea continuar? 1.SI // 2. NO ";
    cin>>menu;
    
    cout << "Ingrese el nombre del producto: ";
    cin>>stock;

    cout << "Desea agregar o quitar productos? ";
    cin.getline(producto.accion,20);

    cout << "Ingrese la cantidad: ";
    cin >> cantidad;

    if (accion == "agregar")  {
        producto.stock += cantidad;
        cout << "Se agregaron " << cantidad << " unidades del producto " << producto.nombre << " al carrito." << endl;
    } else if (accion == "quitar"){
        if (cantidad <= producto.stock) {
            producto.stock -= cantidad;
            cout << "Se quitaron " << cantidad << " unidades del producto " << producto.nombre << " del carrito." << endl;
        } else {
            cout << "No se pueden quitar " << cantidad << " unidades del producto " << producto.nombre << " del carrito. Stock insuficiente." << endl;
        }
    } else {
        cout << "Acción invalida." << endl;
    }

    cout << "Resumen del Carrito" << endl;
    cout << endl;
    cout << "Carrito: " << carrito1.carrito << endl;
    cout << endl;
    cout << "Subtotal: $" << subtotal << endl;
    cout << endl;
    cout << "Descuento: $" << descuento << endl;
    cout << endl;
    cout << "Total a pagar: $" << total << endl;
    cout << endl;

    float pago, cambio;
    cout << "Ingrese el monto con el que pagara: $";
    cin >> pago;

    if (pago >= total) {
        cambio = pago - total;
        cout << "Pago exitoso. Su cambio es de $" << cambio << endl;
    } else {
        cout << "Monto insuficiente. Por favor, ingrese un monto igual o mayor al total." << endl;
    }
    
    return menu;
    
}

