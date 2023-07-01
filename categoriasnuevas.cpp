#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <conio.h>
using namespace std;

const int MAX_CATEGORIAS = 11;	// PUEDE VARIAR A UN FUTURO
const int MAX_PRODUCTOS = 10;	// PUEDE VARIAR A UN FUTURO

struct Producto 
{
    string nombre;
    double precio;
    int stock;
};

struct Categoria 
{
    string nombre;
    Producto productos[MAX_PRODUCTOS];
    int numProductos;
};
void guardarCategorias(Categoria* categorias, int tam);
void mostrarListaCategorias( Categoria* categorias, int tam);
void mostrarListaProductos( Producto* productos, int tam);
void mostrarDetallesProducto( Producto& producto); 
int SeleccionCategoria(int tamCategorias); 
int SeleccionProducto(int tamProductos);
int IngreseCantidad();
void procesarSeleccion( Categoria* categorias, int eleccionCategoria);
void TiendaUsuario();

int main()
{
	TiendaUsuario();
}

void guardarCategorias(Categoria* categorias, int tam)
{
    ofstream archivo("catgorias.csv");
    if (!archivo)
    {
        cout << "Error al abrir el archivo de categorias." <<endl;
        return;
    }

    archivo << "Categoria;Producto;Precio;Stock" <<endl;

    for (int i = 0; i < tam; ++i)
    {
         Categoria& categoria = categorias[i];

        for (int j = 0; j < categoria.numProductos; ++j)
        {
            Producto& producto = categoria.productos[j];
            archivo << categoria.nombre << ";" << producto.nombre << ";"<< producto.precio << ";" << producto.stock <<endl;
        }
    }
    archivo.close();
}

void mostrarListaCategorias(Categoria* categorias, int tam) // Muestra por pantalla una lista de categorías
{
    cout<<"     ";
	cout << "LISTA DE CATEGORIAS:\n";
    for (int i = 0; i < tam; ++i) 
	{
         Categoria& categoria = categorias[i];
         cout<<"     ";
        cout << i + 1 << ". " << categoria.nombre << "\n";
    }
    cout << "\n";
}

void mostrarListaProductos(Producto* productos, int tam) // Recibe un arreglo de productos y su tamaño, y muestra por pantalla la lista de productos con su información 
{
    cout << "LISTA DE PRODUCTOS:\n";
    for (int i = 0; i < tam; ++i) 
	{
        Producto& producto = productos[i];
        cout<<"     ";
		cout << i + 1 << ". " << producto.nombre << " - S/. " << producto.precio << "  [Stock: " << producto.stock << "]\n";
    }
    cout << "\n";
}

void mostrarDetallesProducto( Producto& producto) 
{
	cout<<"   ";
	cout << "DETALLES DEL PRODUCTO:\n";
	cout<<"   ";
    cout << "Nombre: " << producto.nombre << "\n";
    cout<<"   ";
    cout << "Precio: S/." << producto.precio << "\n";
    cout<<"   ";
    cout << "Stock: " << producto.stock << "\n\n";
}

int SeleccionCategoria(int tamCategorias) 
{
    int eleccionCategoria;
    cout<<"-> ";
	cout << "Selecciona una categoria (1-" << tamCategorias << "): ";
    cin >> eleccionCategoria;
     while (eleccionCategoria>tamCategorias||eleccionCategoria<1) {
        cout << "Ha excedido el limite de categorias. Ingrese nuevamente: ";
        cin >> eleccionCategoria;
    }
    return eleccionCategoria;
}

int SeleccionProducto(int tamProductos) 
{
    int eleccionProducto;
    cout<<"-> ";
	cout << "Selecciona un producto (1-" << tamProductos << "): ";
    cin >> eleccionProducto;
    while (eleccionProducto>tamProductos||eleccionProducto<1) {
        cout << "Ha excedido el limite de productos permitidos. Ingrese nuevamente: ";
        cin >> eleccionProducto;
    }
    return eleccionProducto;
}

int IngreseCantidad() 
{
    int cantidad;
    cout<<"-> ";
	cout << "Ingrese la cantidad de productos que desea comprar (Maximo 3 productos por persona): ";
    cin >> cantidad;
    
    // Verificar si la cantidad ingresada excede el límite máximo
    while (cantidad > 3) {
        cout << "Ha excedido el limite de productos permitidos. Ingrese nuevamente: ";
        cin >> cantidad;
    }
    return cantidad;
}
void procesarSeleccion(Categoria* categorias, int eleccionCategoria)
{
    Categoria& categoriaSeleccionada = categorias[eleccionCategoria - 1]; //Obtiene la categoría seleccionada por el usuario a partir del arreglo de categorías, utilizando el índice correspondiente.
	cout << "CATEGORIA SELECCIONADA: '" << categoriaSeleccionada.nombre << "'\n\n";
    mostrarListaProductos(categoriaSeleccionada.productos, categoriaSeleccionada.numProductos);

    int eleccionProducto = SeleccionProducto(categoriaSeleccionada.numProductos);//: Permite al usuario seleccionar un producto llamando a la función SeleccionProducto y almacenando la elección 

    Producto& productoSeleccionado = categoriaSeleccionada.productos[eleccionProducto - 1];// Obtiene el producto seleccionado por el usuario a partir del arreglo de productos de la categoría, utilizando el índice correspondiente.

    if (productoSeleccionado.stock <= 0) //Verifica si el producto seleccionado tiene stock disponible.
    {
        cout << "El producto seleccionado esta agotado.\n";
        return;
    }

    mostrarDetallesProducto(productoSeleccionado);
    int cantidadSeleccionada = IngreseCantidad(); //Solicita al usuario ingresar la cantidad de productos que desea comprar y almacena
    cout << "Cantidad seleccionada: " << cantidadSeleccionada << "\n";
    // Operaciones adicionales con el producto
}


void TiendaUsuario() // Se define un arreglo de categorías con sus respectivos productos y cantidades en stock, proporcionando una estructura de datos para representar una tienda virtual con diferentes categorías de productos.
{
    Categoria categorias[MAX_CATEGORIAS] = 
	{
        {
            "ALIMENTOS BASICOS",
            {
                {"Arroz(1kg)", 5.50, 50},
                {"Leche(1Lt)", 20.50, 50},
                {"Aceite(1Lt)", 10.50, 50},
                {"Pan(unidad)", 0.5, 50},
                {"Azucar", 7.80, 50},
                {"Fideos(1kg)",7.50 , 50},
                {"Manteca(1kg)", 4.5, 50},
                {"Huevo(1kg)", 7, 50},
                {"Sal(1kg)", 8, 50},
                {"Harina(1kg)", 7.80, 50}
            },
            10
        },
        {
            "FRUTAS",
            {
                {"Manzana(1kg)", 12.99, 25},
                {"Pera(1kg)", 29.99, 25},
                {"Uva(1kg)", 7, 25},
                {"Arandanos(1kg)", 14.5, 25},
                {"Platanos(1kg)", 8.2, 25},
                {"Mandarina(1kg)", 4, 25},
                {"Granadilla(1kg)", 6.5, 25},
                {"Naranja(1kg)", 4.5, 25},
                {"Papaya(1kg)", 17.99, 25},
                {"Pinia(Unidad)", 5.5, 25}
               
            },
            10
        },
        {
   			 "VERDURAS",
   			 {
        		{"Zanahoria (1kg)", 6.99, 25},
        		{"Lechuga (unidad)", 3.99, 25},
        		{"Tomate (1kg)", 8.50, 25},
        		{"Cebolla (1kg)", 5.25, 25},
        		{"Pimiento (1kg)", 12.75, 25},
        		{"Espinaca (1kg)", 9.99, 25},
        		{"Papa (1kg)", 4.50, 25},
        		{"Brocoli (unidad)", 6.25, 25},
        		{"Coliflor (unidad)", 7.99, 25},
        		{"Pepino (1kg)", 7.50, 25}
    		},
    		10
		},

        {
            "BEBIDAS",
    		{
        		{"Inca Kola (2L)", 6.99, 50},
        		{"Chicha Morada (1L)", 8.50, 50},
        		{"Emoliente (500ml)", 5.99, 50},
        		{"Cerveza Cusqueña (355ml)", 4.50, 50},
        		{"Pisco (750ml)", 35.99, 10},
        		{"Jugo de Maracuya (1L)", 7.25, 50},
        		{"Agua Mineral (500ml)", 2.99, 50},
        		{"Coca-Cola (2L)", 7.99, 50},
        		{"Jugo de Naranja (1L)", 6.50, 50},
        		{"Sprite (500ml)", 4.99, 50}
    		},
    		10
        },
        {
            "GOLOSINAS",
    		{
        		{"Choclo Pop (100g)", 3.99, 50},
        		{"Galletas de Soda (200g)", 2.50, 50},
        		{"Chocolatito (30g)", 1.25, 50},
       			{"Caramelos de Limon (50g)", 1.99, 50},
       			{"Chicles Bazooka (5 unidades)", 0.75,50},
        		{"Paleta de Caramelo (1 unidad)", 1.50, 50},
        		{"Alfajor de Manjar Blanco", 2.75, 50},
        		{"Confitados (80g)", 4.25, 50},
        		{"Chocolate Sublime (40g)", 2.99, 50},
        		{"Gomitas Frutales (100g)", 3.50, 50}
    		},
    		10
        },
        {
            "CARNES",
    		{
        		{"Pollo Entero (1kg)", 12.99, 25},
        		{"Carne de Res (1kg)", 24.99, 25},
        		{"Cerdo (1kg)", 18.99, 25},
        		{"Pavo (1kg)", 15.99, 25},
       			{"Chorizo (500g)", 8.99, 25},
        		{"Jamon (200g)", 6.50, 25},
        		{"Lomo de Cerdo (1kg)", 22.99, 25},
        		{"Costillas de Res (1kg)", 19.99, 25},
        		{"Picana de Pollo (1kg)", 11.99, 25},
        		{"Chuletas de Cordero (1kg)", 28.99, 25}
    		},
    		10
        },
        {
    		"LACTEOS",
    		{
    		    {"Leche Entera (1Lt)", 5.99, 50},
     		    {"Queso Parmesano (200g)", 8.50, 50},
      		  	{"Mantequilla (250g)", 4.99, 50},
      		    {"Yogur Natural (500g)", 3.50, 50},
      			{"Crema de Leche (200ml)", 3.99, 50},
      			{"Leche Condensada (395g)", 5.25, 50},
      			{"Queso Mozzarella (400g)", 7.99, 50},
      			{"Yogur de Frutas (150g)", 1.75, 50},
      			{"Helado de Vainilla (1Lt)", 10.99, 50},
      			{"Leche Descremada (1Lt)", 5.99, 50}
    		},
    		10
		},
		{
    		"LICORES",
    		{
     			{"Pisco (750ml)", 35.99, 50},
        		{"Vodka (750ml)", 29.99, 50},
        		{"Ron Añejo (750ml)", 27.50, 50},
        		{"Whisky Escocés (750ml)", 49, 50},
        		{"Tequila (750ml)", 45, 50},
        		{"Ginebra (750ml)", 38, 50},
       			{"Vino Tinto (750ml)", 50, 50},
        		{"Champan (750ml)", 42.50, 50},
        		{"Cerveza (500ml)", 8, 50},
        		{"Licor de Cafe (500ml)", 15.99, 50}
    		},
   		 	10
		},
		{
    		"PRODUCTOS DE LIMPIEZA",
    		{
        		{"Detergente (1L)", 10.99, 50},
        		{"Cloro (1L)", 7.50, 40},
        		{"Limpiavidrios (500ml)", 9, 50},
        		{"Desinfectante (500ml)", 10, 50},
        		{"Jabon en Polvo (1kg)", 12.50, 50},
        		{"Suavizante de Telas (1L)", 16, 50},
        		{"Lavaplatos (500ml)", 8.5, 50},
        		{"Esponjas (Pack de 3)", 5.50, 50},
        		{"Desodorante de Ambientes (250ml)", 7, 50},
        		{"Papel Higienico (Pack de 4 rollos)", 8.50, 50}
    		},
    		10
		},
		{
    		"HELADOS",
    		{
        		{"Helado de Vainilla (500ml)", 12.90, 50},
        		{"Helado de Chocolate (500ml)", 12.90, 50},
        		{"Helado de Fresa (500ml)", 12.90, 15},
        		{"Helado de Cookies and Cream (500ml)", 14.90, 50},
        		{"Helado de Mango (500ml)", 13.5, 50},
        		{"Helado de Menta (500ml)", 13.5, 50},
        		{"Helado de Dulce de Leche (500ml)", 15, 50},
        		{"Helado de Nuez (500ml)", 13.99, 15},
        		{"Helado de Fudge Brownie (500ml)", 16, 50},
        		{"Helado de Stracciatella (500ml)", 14, 50}
    		},
    		10
		},
		{
    		"CUIDADO PERSONAL",
    		{
        		{"Shampoo (500ml)", 15.99, 50},
        		{"Acondicionador (500ml)", 15.99, 50},
        		{"Jabon de Baño (Pack de 3)", 9.99, 50},
        		{"Desodorante (50ml)", 12.99,50},
        		{"Crema Hidratante (200ml)", 19.99, 50},
        		{"Cepillo de Dientes", 4.99, 50},
        		{"Pasta Dental (100g)", 7.99, 50},
        		{"Cortauñas", 3.99, 35},
        		{"Locion Corporal (250ml)", 16.99, 50},
        		{"Protector Solar (SPF 50)", 24.99, 50}
    		},
    		10
		},
		
    };
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
    mostrarListaCategorias(categorias, MAX_CATEGORIAS);
    guardarCategorias(categorias, MAX_CATEGORIAS);
    int eleccionCategoria = SeleccionCategoria(MAX_CATEGORIAS);
    system("CLS");
    procesarSeleccion(categorias, eleccionCategoria);
    getch();
}


