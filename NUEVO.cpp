#include <iostream>
#include <string>
#include <fstream>

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
//PROTOTIPOS
void cargarDatos(Categoria categorias[], int& numCategorias);
void guardarDatos(Categoria categorias[], int numCategorias);
void mostrarCategorias(Categoria* categorias, int numCategorias);
void mostrarProductos(Categoria& categoria);
void agregarAlCarrito(Producto carrito[], int& numProductosCarrito, Producto producto, int cantidad);
void mostrarCarrito(Producto carrito[], int numProductosCarrito);
void realizarVenta(Categoria categorias[], int numCategorias);
void tiendausuario();


//FUNCION PRINCIPAL
int main()
{
    tiendausuario();
    return 0;
}

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
}



