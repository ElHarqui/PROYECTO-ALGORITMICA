#include <iostream>
#include <string>
#include <fstream>
//#include "visualizar.cpp"
using namespace std;

//ESTRUCTURAS
struct Producto
{
    string nombre;
    double precio;
    int stock;
    int cantidad; // Nueva propiedad para almacenar la cantidad comprada
};

struct Categoria
{
    string nombre;
    Producto productos[100];
    int numProductos;
};
struct agregar
{
    string accion;
    int cantidad;
    string nombre;
    int stock;
    
} producto;

struct Resumen
{
    int carrito;
    float descuento;
} carrito1;

//PROTOTIPOS
void cargarDatos(Categoria categorias[], int& numCategorias);
void guardarDatos(Categoria categorias[], int numCategorias);
void mostrarCategorias(Categoria* categorias, int numCategorias);
void mostrarProductos(Categoria& categoria);
void agregarAlCarrito(Producto carrito[], int& numProductosCarrito, Producto producto, int cantidad);
void mostrarCarrito(Producto carrito[], int numProductosCarrito);
void realizarVenta(Categoria categorias[], int numCategorias);
void tiendausuario();
//void agregarQuitarProductos();
//void mostrarResumen(CarritoItem A, double& Total); //!FUNCION NO RECONOCIDA (CarritoItem no existe)


//SUBPROGRMAS
void cargarDatos(Categoria categorias[], int& numCategorias)
{
    ifstream archivo("datos.txt"); // Nombre del archivo con los datos

    if (archivo)
    {
        numCategorias = 0;

        string linea;
        while (getline(archivo, linea)) //itera sobre las líneas del archivo para obtener la información
        {
            categorias[numCategorias].nombre = linea;
            archivo >> categorias[numCategorias].numProductos;
            archivo.ignore();// Ignorar el salto de línea después de leer el número de productos

            for (int i = 0; i < categorias[numCategorias].numProductos; i++)
            {
                getline(archivo, categorias[numCategorias].productos[i].nombre);
                archivo >> categorias[numCategorias].productos[i].precio;
                archivo >> categorias[numCategorias].productos[i].stock;
                archivo.ignore(); // Ignorar el salto de línea después de cada categoría
            }
            numCategorias++;//Aumenta el contador para saber cuantas categorias se cargan
        }

        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}


void guardarDatos(Categoria categorias[], int numCategorias)
{
    ofstream archivo("datos.txt"); // Nombre del archivo para guardar los datos

    if (archivo)
    {
        for (int i = 0; i < numCategorias; i++)//Itera sobre las categorías y sus productos
        {
            archivo << categorias[i].nombre << endl;
            archivo << categorias[i].numProductos << endl;

            for (int j = 0; j < categorias[i].numProductos; j++)
            {
                archivo << categorias[i].productos[j].nombre << endl;
                archivo << categorias[i].productos[j].precio << endl;
                archivo << categorias[i].productos[j].stock << endl;
            }
        }
        archivo.close();
        cout<<"\n";
        cout << "[Se actualizo el stock]" << endl;
    }
    else
    {
        cout << "No se pudo abrir el archivo para guardar los datos." << endl;
    }
}

void mostrarCategorias(Categoria* categorias, int numCategorias)
{
    cout << "CATEGORIAS DISPONIBLES:" << endl;
    cout<<endl;

    for (int i = 0; i < numCategorias; i++)
    {
        cout<<"  ";
		cout << i + 1 << ". " << categorias[i].nombre << endl;
    }
}

void mostrarProductos(Categoria& categoria)
{
    cout << "PRODUCTOS DE LA CATEGORIA [" << categoria.nombre << "]:" << endl;

    for (int i = 0; i < categoria.numProductos; i++)
    {
        cout << i + 1 << ". " << categoria.productos[i].nombre << " - S/. " << categoria.productos[i].precio<< "  [Stock: " << categoria.productos[i].stock<< "]\n";
    }
}

void agregarAlCarrito(Producto carrito[], int& numProductosCarrito, Producto producto, int cantidad)
{
    carrito[numProductosCarrito] = producto;
    carrito[numProductosCarrito].cantidad = cantidad;
    numProductosCarrito++;
}

void mostrarCarrito(Producto carrito[], int numProductosCarrito)
{
    cout << "----- CARRITO DE COMPRAS -----" << endl;

    for (int i = 0; i < numProductosCarrito; i++)
    {
        cout << "Producto: " << carrito[i].nombre << endl;
        cout << "Cantidad: " << carrito[i].cantidad << endl;
        cout << "Precio: " << carrito[i].precio << endl;
    }

    cout << "-----------------------------" << endl;
}

void realizarVenta(Categoria categorias[], int numCategorias)
{
    Producto carrito[100]; // Arreglo para almacenar los productos comprados
    int numProductosCarrito = 0;
    double subtotal = 0.0;
    double total = 0.0;
    char opcion;

    do
    {
        int categoriaSeleccionada;
        int productoSeleccionado;
        int cantidad;

        mostrarCategorias(categorias, numCategorias);

        cout<<endl;
		cout<<" ->";
		cout << "Selecciona una categoria: ";
        cin >> categoriaSeleccionada;

        // Verificar si el número de categoría es válido
        while(categoriaSeleccionada < 1 || categoriaSeleccionada > numCategorias)
        {
            cout << "Ha excedido el limite de categorias. Ingrese nuevamente: ";
            cin >> categoriaSeleccionada;
        }

        // Obtener la categoría seleccionada
        Categoria& categoria = categorias[categoriaSeleccionada - 1];
		system("cls");	
        mostrarProductos(categoria);

		do
		{
			cout<<endl;
			cout<<" ->";
			cout << "Selecciona un producto: ";
        	cin >> productoSeleccionado;
		}while(productoSeleccionado < 1 || productoSeleccionado > categoria.numProductos);
        
        // Obtener el producto seleccionado
        Producto& producto = categoria.productos[productoSeleccionado - 1];

		cout<<endl;
		cout<<" ->";
        cout << "Ingrese la cantidad a comprar: ";
        cin >> cantidad;

        // Verificar si hay suficiente stock
        while (cantidad > producto.stock)
        {
            cout << "Ha excedido el limite de categorias. Ingrese nuevamente: ";
            cin >>cantidad;
        }

        // Realizar la venta y actualizar el stock
        producto.stock -= cantidad;

        // Agregar el producto al carrito con la cantidad seleccionada
        agregarAlCarrito(carrito, numProductosCarrito, producto, cantidad);

        subtotal += producto.precio * cantidad;

		cout<<endl;
		cout<<"   ";
        cout << "[Eleccion realizada exitosamente]" << endl;

        cout << "\nDesea agregar otro producto al carrito? (s/n): ";
        cin >> opcion;
        system("cls");
    } while (opcion == 's' || opcion == 'S');

    // Calcular el total
    total = subtotal;

    // Mostrar el carrito y los totales
    mostrarCarrito(carrito, numProductosCarrito);

    cout << "Subtotal: " << subtotal << endl;
    cout << "Total: " << total << endl;
}
void tiendausuario()
{
	cout<<"               ";
		cout<< "***********************************************************" << endl;
		cout<<"               ";
    	cout<< "*                                                         *" << endl;
    	cout<<"               ";
    	cout<< "*        BIENVENIDO A NUESTRA TIENDA VIRTUAL INNOU        *" << endl;
   		cout<<"               ";
    	cout<< "*                                                         *" << endl;
      	cout<<"               ";
    	cout<< "***********************************************************" << endl;
	Categoria categorias[100];
    int numCategorias = 0;
    cargarDatos(categorias, numCategorias);
    realizarVenta(categorias, numCategorias);
    guardarDatos(categorias, numCategorias);
	//agregarQuitarProductos();
    //mostrarResumen(item, total);
}
/////////////////////////////////////////////////////
////////////////////////////////////////////////////
//////////////////////////////////////////////////
/*
void agregarQuitarProductos()
{
    cout << "¿Desea agregar o quitar productos ? // si no desea ninguno(continuar) ";
    cin.ignore(); // Ignorar el salto de línea anterior
    getline(cin, producto.accion);

    if (producto.accion == "agregar")
    {
        cout << "Ingrese el nombre del producto: ";
        cin >> producto.nombre; //agregar los nuevos productos que desee el cliente

        cout << "Ingrese la cantidad: ";
        cin >> producto.cantidad;//la cantidad del nuevo producto que desee

        producto.stock += producto.cantidad;

        cout << "Se agregaron " << producto.cantidad << " unidades del producto " << producto.nombre << " al carrito." << endl;
    }
    else if (producto.accion == "quitar")
    {
        cout << "Ingrese el nombre del producto: ";
        cin >> producto.nombre; //quitar el producto que desee el cliente

        cout << "Ingrese la cantidad: ";
        cin >> producto.cantidad;//quitar la cantidad de dicho producto 

        if (producto.cantidad <= producto.stock)
        {
            producto.stock -= producto.cantidad;
            cout << "Se quitaron " << producto.cantidad << " unidades del producto " << producto.nombre << " del carrito." << endl;
        }
        else
        {
            cout << "No se pueden quitar " << producto.cantidad << " unidades del producto " << producto.nombre << " del carrito. Stock insuficiente." << endl;
        }
    }else if (producto.accion == "continuar")
    {
        cout<< "Continuamos . . .";
	}
    else
    {
        cout << "Opción inválida." << endl;
    }
}

void mostrarResumen(CarritoItem A, double& Total)
{

    int menu ,final;
    system("cls");
    cout << "\n ";
    cout << "Ingrese su descuento: $";
    cin >> carrito1.descuento; // el descuento que tiene el cliente

    final = Total - carrito1.descuento; //El monto total - descuento para ver el pago en total que hara

    cout << "¿Le alcanza el monto para pagar? 1. SI // 2. NO ";
    cin >> menu;

    if (menu == 1)
    {
        cout << "\n";
		cout << "Resumen del Carrito" << endl;
        cout << endl;
        cout << "Carrito: " << item.nombre << endl;
        cout << endl;
        cout << "La cantidad de productos es : " << item.cantidad << endl;// no se Guardo 
        cout << endl;
        cout << "Subtotal: S/." << Total << endl;
        cout << endl;
        cout << "Descuento: S/." << carrito1.descuento << endl;// no se Guardo 
        cout << endl;
        cout << "Total a pagar: S/." << final<< endl;
        cout << endl;

        float pago, cambio;
        cout << "Ingrese el monto con el que pagará: S/.";
        cin >> pago; //monto con el que pagara el cliente

        if (pago >= final)
        {
            cambio = pago - final;
            cout << "Pago exitoso. Su cambio es de S/." << cambio << endl; //vuelto
        }
        else
        {
            cout << "Monto insuficiente. Por favor, ingrese un monto igual o mayor al total." << endl;
        }
    }
    else
    {
        cout << "No alcanza el monto para pagar." << endl;
        cout << "Hasta la próxima, sus productos quedarán guardados en el carrito." << endl;
    }
}
*/


