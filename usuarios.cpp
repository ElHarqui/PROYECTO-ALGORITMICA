#include<iostream>
#include <sstream>
#include <fstream>
#include <string.h>
//#include "categorias.cpp"
#include "logo.cpp"


struct Usuarios{
	string nombre ;
	string contra ;
	string tipo ;
	string moneda;
}usuario[100];

//ESTRUCTURAS
struct Producto
{
    string nombre;
    double precio;
    int stock;
    int cantidad;
    double total; // Nueva propiedad para almacenar la cantidad comprada
}carrito[100];

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

using namespace std;
//PROTOTIPOS USUARIO
static void CargarEstructuras(void) ;
static void NuevoUsuario(void);
static void LoginUsu(int &num_usu);
static void menu2(int num_usu);
static void Menu(void);
static void menuDolar(void);
//PROTOTIPOS TIENDA
void cargarDatos(Categoria categorias, int& numCategorias);
void guardarDatos(Categoria categorias[], int numCategorias);
void mostrarCategorias(Categoria* categorias, int numCategorias);
void mostrarProductos(Categoria& categoria);
void agregarAlCarrito(Producto carrito[], int& numProductosCarrito,Producto producto, int cantidad);
void mostrarCarrito(Producto carrito[], int& numProductosCarrito);
void realizarVenta(Categoria categorias[], int numCategorias,int& numProductosCarrito ,Producto carrito[]);
void tiendausuario();
void agregarQuitarProductos(Producto carrito[], int& numProductosCarrito, Categoria categorias[], int numCategorias);
void mostrarResumen(Producto carrito[], int& numProductosCarrito );
//PROTOTIPOS BOLETA
void Boleta(Usuarios usuario[],int usu_num);

int num_usu;
int numProductosCarrito = 0;

static void CargarEstructuras(int &num_usu)
{
	num_usu = 0;
	string linea;
	char delimit = ';';
	ifstream UsuariosText;
	UsuariosText.open("Usuarios.csv",ios::in);
	if (!UsuariosText.is_open())
	{
	    cout << "Error al abrir ejemplo.dat\n";
		exit(1);
	}
	getline(UsuariosText, linea);
	while (getline(UsuariosText, linea))
	{
		stringstream stream(linea); 
		string Usuario,Contrasena;
		getline(stream, Usuario, delimit);
		getline(stream, Contrasena, delimit);
		usuario[num_usu].nombre = Usuario;
		usuario[num_usu].contra = Contrasena;

		if(num_usu == 0) {
			usuario[num_usu].tipo = "admin";
		}
		num_usu++;
	}
	UsuariosText.close();
	cout<<"N# Usuarios Existentes : "<<num_usu<<endl;
}


static void NuevoUsuario(void)
{
	CargarEstructuras(num_usu);
	string NewUsu,NewContra;
	int RegExist = 0;
	ofstream UsuariosText;
	UsuariosText.open("Usuarios.csv",ios::app);//ABRIENDO  BASE DE DATOS// PARA GUARDAR NUEVO USUARIO AL FINAL DE LA LISTA;
	if(UsuariosText.fail()){
		cout<<"ERROR,el archivo no se pudo crear";
		exit(1);
	}	
	cout<<"\t\t\tREGISTRESE\n";
	cout<<"Usuario: ";cin>>NewUsu;
	for (int i = 0 ; i < num_usu ; i++){
	if( NewUsu == usuario[i].nombre)
	{
		RegExist = 1;
		break;			
	}
	}

	if (RegExist != 0){
		cout<<"\nUsuario Ya existe. Intentelo denuevo"<<endl;
		UsuariosText.close();
		system("pause");
		system("CLS");
		NuevoUsuario();
	}
	cout<<"Contraseña: ";cin>>NewContra;
	cout<<"\nRegistrado Correctamente"<<endl;
	UsuariosText<<NewUsu<<";"<<NewContra<<endl;
	UsuariosText.close();
	system("pause");
	system("CLS");
	Menu();
	
}

static void LoginUsu(int &num_usu)
{
	
	CargarEstructuras(num_usu);
	string logusu, logcontra;
	int LogExist = 0;
	
	cout<<"\t\t\tINICIE SESION\n";//Tomando datos para posterior comprobacion de existencia
	cout<<"Usuario: ";cin>>logusu;
	cout<<"Contraseña: ";cin>>logcontra;
	for (int i = 0 ; i < num_usu; i++ )
	{
		if (logusu == usuario[i].nombre && logcontra == usuario[i].contra)
		{
			cout<<"Inicio sesion correctamente"<<endl;
			num_usu = i;
			LogExist = 1;
			system("pause");
			system("CLS");
			if (usuario[i].tipo == "admin")
			{
				tiendausuario();
				//Mostrar TIENDA DE ADMINISTRADOR()
				break;
			}
			else
			{
				menu2(num_usu);
				break;
			}
		}
		else if(logusu == usuario[i].nombre && logcontra != usuario[i].contra)
		{
			cout<<"contraseña incorrecta. Intente denuevo"<<endl;
			LogExist = 2;
			break;
		}
	}
	if (LogExist == 0)
	{
		cout<<"Usuario no existe. Intente denuevo"<<endl;
	}
	if (LogExist != 1)
	{
		system("pause");
		system("CLS");
		LoginUsu(num_usu);
	}
}
void menu2(int num_usu)
{
	int option;
	cout << "\n--- Menu 2 ---\n";
    cout << "1. Iniciar tienda\n2. Configuracion\n\n0. Cerrar sesion"<<endl;
    cout << "-> ";
    cin >> option;
	system("CLS");
    if (option == 1) {
        cout << "\nIniciando tienda...\n";
        system("pause");
        system("CLS");
        // Lógica para iniciar la tienda
        tiendausuario();
    } 
	else if (option == 2) {
        menuDolar();
    } else if (option == 0) {
    	system("CLS");
        Menu(); // Cierra sesión
    } else {
        cout << "\nOpción inválida.\n";
        system("pause");
        menu2(num_usu);
    }
}
void menuDolar()
{
	int option;
	cout << "\n--- Configuracion ---\n";
    //cout << "Tipo de moneda actual: " << currencyType << endl;
    cout << "1. Cambiar a dolar\n";
    cout << "2. Cambiar a soles\n\n";
    cout << "0. Volver\n";
    cout << "-> ";
    cin >> option;

    if (option == 1) {
      //  updateCurrencyType("dólar");
        cout << "\nTipo de moneda cambiado a dólar.\n";
    } else if (option == 2) {
      //  updateCurrencyType("soles");
        cout << "\nTipo de moneda cambiado a soles.\n";
    } else if (option == 0) {
        system("CLS");
		menu2(num_usu); // Vuelve al menú principal
    } else {
        cout << "\nOpción inválida.\n";
        system("pause");
        system("CLS");
		menuDolar();
    }
}
void Menu()
{
	logo();
	//system("cls");
	/////MENU 1
	char SelecMenu1,la;
	cout<<"\n--- Menu 1 ---\n1.- Crear Usuario\n2.- Iniciar sesion\n\n0.- Salir"<<endl;
	cout << "-> ";
	cin>>SelecMenu1;
	switch(SelecMenu1)
	{
		case '1':
			//NUEVO USUARIO
			system("CLS");
			NuevoUsuario();
			break;
		case '2':
			//USUARIO EXISTENTE
			system("CLS");
			LoginUsu(num_usu);
			break;
		case '0':
			exit(1);
		default :
			cout<<"Error,Intente denuevo."<<endl;
			system("pause");
			system("CLS");
			Menu();
	
	}

	system("pause");		
}
/////
//SUBPROGRMAS
void cargarDatos(Categoria categorias[], int& numCategorias)
{
    ifstream archivo("datos.txt"); // Nombre del archivo con los datos
	numCategorias = 0;
    if (archivo)
    {
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
        for (int i = 0; i < numCategorias; i++)//Itera sobre las categor?as y sus productos
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

void mostrarCarrito(Producto carrito[], int& numProductosCarrito)
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

void realizarVenta(Categoria categorias[], int numCategorias,int& numProductosCarrito,Producto carrito[])
{

    numProductosCarrito = 0;
    double subtotal = 0.0;
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

        // Verificar si el n?mero de categor?a es v?lido
        while(categoriaSeleccionada < 1 || categoriaSeleccionada > numCategorias)
        {
            cout << "Ha excedido el limite de categorias. Ingrese nuevamente: ";
            cin >> categoriaSeleccionada;
        }

        // Obtener la categor?a seleccionada
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
    carrito[numProductosCarrito].total = subtotal;

    // Mostrar el carrito y los totales
    mostrarCarrito(carrito, numProductosCarrito);

    cout << "Subtotal: " << subtotal << endl;
    cout << "Total: " << carrito[numProductosCarrito].total << endl;
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
    realizarVenta(categorias, numCategorias,numProductosCarrito,carrito);
    guardarDatos(categorias, numCategorias);
	agregarQuitarProductos(carrito, numProductosCarrito, categorias, numCategorias);
    mostrarResumen(carrito,numProductosCarrito);
}

void agregarQuitarProductos(Producto carrito[], int& numProductosCarrito, Categoria categorias[], int numCategorias)
{
    cout << "1. Agregar producto" << endl;
    cout << "2. Quitar producto" << endl;
    cout << "3. Mostrar contenido del carrito" << endl;
    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;

    if (opcion == 1)
    {
        string producto;
        cout << "Ingrese el nombre del producto: ";
        cin.ignore();
        getline(cin, producto);

        int cantidad;
        cout << "Ingrese la cantidad: ";
        cin >> cantidad;

        bool productoEncontrado = false;
        for (int i = 0; i < numCategorias; i++)
        {
            for (int j = 0; j < categorias[i].numProductos; j++)
            {
                if (categorias[i].productos[j].nombre == producto)
                {
                    agregarAlCarrito(carrito, numProductosCarrito, categorias[i].productos[j], cantidad);
                    productoEncontrado = true;
                    break;
                }
            }
            if (productoEncontrado)
            {
                break;
            }
        }

        if (!productoEncontrado)
        {
            cout << "Producto no encontrado." << endl;
        }
    }
    else if (opcion == 2)
    {
        if (numProductosCarrito > 0)
        {
            mostrarCarrito(carrito, numProductosCarrito);
            cout << "Ingrese el numero del producto a quitar: ";
            int numero;
            cin >> numero;

            if (numero >= 1 && numero <= numProductosCarrito)
            {
                cout << "Producto quitado: " << carrito[numero - 1].nombre << endl;
                carrito[numProductosCarrito].total -= carrito[numero - 1].precio * carrito[numero - 1].cantidad;
                for (int i = numero - 1; i < numProductosCarrito - 1; i++)
                {
                    carrito[i] = carrito[i + 1];
                }
                numProductosCarrito--;
            }
            else
            {
                cout << "Numero de producto invalido." << endl;
            }
        }
        else
        {
            cout << "No hay productos en el carrito." << endl;
        }
    }
    else if (opcion == 3)
    {
        // Mostrar contenido del carrito
        mostrarCarrito(carrito, numProductosCarrito);
    }
    else
    {
        cout << "Opcion invalida. Por favor intente de nuevo." << endl;
    }
}

void mostrarResumen(Producto carrito[], int& numProductosCarrito)
{
    cout << "--------RESUMEN DE LA COMPRA--------" << endl;
    cout << "Productos comprados:" << endl;

    for (int i = 0; i < numProductosCarrito; i++)  //recorre los productos en el carrito
    {
        cout << "- " << carrito[i].nombre << " x " << carrito[i].cantidad << endl;
    }
    cout << "Subtotal: $" << carrito[numProductosCarrito].total << endl;

    // Proceso de cobro al cliente
    double pago;
    do
    {
        cout << "Ingrese la cantidad a pagar: $";
        cin >> pago;

        if (pago < carrito[numProductosCarrito].total)
        {
            cout << "El pago es insuficiente. Por favor, ingrese un monto igual o mayor al total." << endl;
        }
    } while (pago < carrito[numProductosCarrito].total);

    double cambio = pago - carrito[numProductosCarrito].total;
    cout << "Pago recibido: $" << pago << endl;
    cout << "Cambio: $" << cambio << endl;

    cout << "------------------------------------" << endl;
    system("pause");
    system("cls");
    Boleta(usuario,num_usu);
}
void Boleta(Usuarios usuario[],int num_usu){
	cout<<usuario[num_usu].nombre<<endl;
	
}
