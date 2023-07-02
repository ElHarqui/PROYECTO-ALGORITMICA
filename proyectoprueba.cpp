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
void mostrarCarrito();
void mostrarResumen();

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
// CARRITO JOSS
struct CarritoItem
{
    string nombre;
    int cantidad;
    double precioUnitario;
};
// CARRITO JOSS
CarritoItem carrito[MAX_PRODUCTOS]; // arreglo para almacenar los elementos del carrito
int numItemsCarrito = 0; // Contador para realizar un seguimiento del número de elementos en el carrito
// CARRITO JOSS
void mostrarCarrito()
{
    cout <<"CARRITO DE COMPRAS:\n";
    double total = 0;

    for(int i=0;i<numItemsCarrito;i++)
    {
        const CarritoItem& item =carrito[i];
        double subtotal=item.precioUnitario * item.cantidad;
        total += subtotal;
        
        cout<<"Los productos del carrito son:"<<"\n";
        cout<<"Nombre: "<< item.nombre<< "\n";
        cout<<"Cantidad: "<< item.cantidad<<"\n";
        cout<<"Precio unitario: S/."<< item.precioUnitario<<"\n";
        cout<<"Subtotal: S/."<< subtotal <<"\n\n";
    }

    cout << "TOTAL: S/." << total <<"\n";
}


void procesarSeleccion(Categoria* categorias, int eleccionCategoria)
{
    Categoria& categoriaSeleccionada = categorias[eleccionCategoria - 1];
    cout << "CATEGORIA SELECCIONADA: '" << categoriaSeleccionada.nombre << "'\n\n";
    mostrarListaProductos(categoriaSeleccionada.productos, categoriaSeleccionada.numProductos);

    int eleccionProducto = SeleccionProducto(categoriaSeleccionada.numProductos);

    Producto& productoSeleccionado = categoriaSeleccionada.productos[eleccionProducto - 1];

    if (productoSeleccionado.stock <= 0)
    {
        cout << "El producto seleccionado está agotado.\n";
        return;
    }

    mostrarDetallesProducto(productoSeleccionado);
    int cantidadSeleccionada = IngreseCantidad();
    cout << "Cantidad seleccionada: " << cantidadSeleccionada << "\n";

    // Agregar el producto al carrito
    if (numItemsCarrito < MAX_PRODUCTOS)
    {
        CarritoItem& item = carrito[numItemsCarrito];
        item.nombre = productoSeleccionado.nombre;
        item.cantidad = cantidadSeleccionada;
        item.precioUnitario = productoSeleccionado.precio;

        numItemsCarrito++;
    }
    else
    {
        cout << "El carrito está lleno. No se puede agregar más elementos.\n";
    }

    // Reducir el stock del producto seleccionado
    productoSeleccionado.stock -= cantidadSeleccionada;

    // Verificar si el stock del producto llega a cero y mostrar un mensaje
    if (productoSeleccionado.stock == 0)
    {
        cout << "¡El producto seleccionado está agotado!\n";
    }

    guardarCategorias(categorias, MAX_CATEGORIAS);
}

void guardarCarritoEnArchivo()
{
    ofstream archivo("carritoJOSS.csv", ios::app);  // Abrir en modo de escritura al final del archivo

    if (archivo.is_open())
    {
        int numeroCompra = 1;

        archivo << "CONTENIDO DEL CARRITO " << numeroCompra << ":\n";

        for (int i = 0; i < numItemsCarrito; i++)
        {
            archivo<< "Nombre: " << carrito[i].nombre << "\n";
            archivo<< "Cantidad: " << carrito[i].cantidad << "\n";
            archivo<< "Precio unitario: S/." << carrito[i].precioUnitario << "\n";
            archivo<< "\n";
        }

        archivo.close();
        cout << "El carrito se ha guardado.\n";
    }
    else
    {
        cout<< "No se pudo abrir el archivo .\n";
    }
    
}


void TiendaUsuario() // Se define un arreglo de categorías con sus respectivos productos y cantidades en stock, proporcionando una estructura de datos para representar una tienda virtual con diferentes categorías de productos.
{
	bool realizarOtraCompra = true;
	while (realizarOtraCompra)
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
            	    {"Manzana(1kg)", 2.99, 25},
            	    {"Pera(1kg)", 4.99, 25},
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
		cout<< "*********************" << endl;
		cout<<"               ";
    	cout<< "*                                                         *" << endl;
    	cout<<"               ";
    	cout<< "*        BIENVENIDO A NUESTRA TIENDA VIRTUAL INNOU        *" << endl;
   		cout<<"               ";
    	cout<< "*                                                         *" << endl;
      	cout<<"               ";
    	cout<< "*********************" << endl;
    	mostrarListaCategorias(categorias, MAX_CATEGORIAS);
    	guardarCategorias(categorias, MAX_CATEGORIAS);
    	int eleccionCategoria = SeleccionCategoria(MAX_CATEGORIAS);
    	system("CLS");
    	procesarSeleccion(categorias, eleccionCategoria);
   	 	cout << "¿Desea realizar otra compra? [Si(s)/no(n)] ";
        char opcion;
        cin >> opcion;

        if (opcion != 's' && opcion != 'S')
        {
            realizarOtraCompra = false;
        }

        system("cls");
    }
    mostrarCarrito();
    guardarCarritoEnArchivo();
    mostrarResumen();
    getch();
}

struct Product
{
    string accion;
    int cantidad;
    string nombre;
    int stock;
    
} producto;

struct VisualizacionCarrito
{
    float subtotal;
    float total;
    int carrito;
    float descuento;
} carrito1;


void mostrarResumen( )
{
    int menu;

    cout << "Ingrese su descuento: $";
    cin >> carrito1.descuento;

    carrito1.total = carrito1.subtotal - carrito1.descuento;
    
    cout << "¿Le alcanza el monto para pagar? 1. SI // 2. NO ";
    cin >> menu;

    if (menu == 1)
    {
        cout << "¿Desea agregar o quitar productos? ";
        cin.ignore(); // Ignorar el salto de línea anterior

        getline(cin, producto.accion);

        if (producto.accion == "agregar")
        {
            cout << "Ingrese el nombre del producto: ";
            cin >> producto.nombre;

            cout << "Ingrese la cantidad: ";
            cin >> producto.cantidad;

            producto.stock += producto.cantidad;

            cout << "Se agregaron " << producto.cantidad << " unidades del producto " << producto.nombre << " al carrito." << endl;
        }
        else if (producto.accion == "quitar")
        {
            cout << "Ingrese el nombre del producto: ";
            cin >> producto.nombre;

            cout << "Ingrese la cantidad: ";
            cin >> producto.cantidad;

            if (producto.cantidad <= producto.stock)
            {
                producto.stock -= producto.cantidad;
                cout << "Se quitaron " << producto.cantidad << " unidades del producto " << producto.nombre << " del carrito." << endl;
            }
            else
            {
                cout << "No se pueden quitar " << producto.cantidad << " unidades del producto " << producto.nombre << " del carrito. Stock insuficiente." << endl;
            }
        }
        else
        {
            cout << "Opción inválida." << endl;
        }

        cout << "Resumen del Carrito" << endl;
        cout << endl;
        cout << "Carrito: " << carrito1.carrito << endl;
        cout << endl;
        cout << "Subtotal: $" << carrito1.subtotal << endl;
        cout << endl;
        cout << "Descuento: $" << carrito1.descuento << endl;
        cout << endl;
        cout << "Total a pagar: $" << carrito1.total << endl;
        cout << endl;

        float pago, cambio;
        cout << "Ingrese el monto con el que pagará: $";
        cin >> pago;

        if (pago >= carrito1.total)
        {
            cambio = pago - carrito1.total;
            cout << "Pago exitoso. Su cambio es de $" << cambio << endl;
        }
        else
        {
            cout << "Monto insuficiente. Por favor, ingrese un monto igual o mayor al total." << endl;
        }
    }
    else
    {
        cout << "No alcanza el monto para pagar." << endl;
        cout << "Hasta la proxima, sus productos quedaran guardados en el carrito." << endl;
    }
}
