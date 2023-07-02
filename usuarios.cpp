#include<iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "categorias.cpp"
#include "logo.cpp"

/*
#ifndef usuarios_H
#define usuarios_H
*/
struct Usuarios{
	string nombre ;
	string contra ;
	string tipo ;
	string moneda;
}usuario[100];

using namespace std;
static void CargarEstructuras(void) ;
static void NuevoUsuario(void);
static void LoginUsu(void);
static void menu2();
static void Menu();
static void menuDolar();


int num_usu;

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
	//cout<<"Cargando..."<<endl;
	//
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
/////////////////////////////////////////////////////
static void LoginUsu(void)
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
			LogExist = 1;
			system("pause");
			system("CLS");
			if (usuario[i].tipo == "admin")
			{
				TiendaUsuario();
				//Mostrar TIENDA DE ADMINISTRADOR()
				break;
			}
			else
			{
				menu2();
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
		LoginUsu();
	}
}
void menu2()
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
        TiendaUsuario();
    } 
	else if (option == 2) {
        menuDolar();
    } else if (option == 0) {
    	system("CLS");
        Menu(); // Cierra sesión
    } else {
        cout << "\nOpción inválida.\n";
        system("pause");
        menu2();
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
		menu2(); // Vuelve al menú principal
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
			LoginUsu();
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
