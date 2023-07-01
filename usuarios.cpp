#include<iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "categorias.cpp"

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
static void Menu();

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
	cout<<"Contraseņa: ";cin>>NewContra;
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
	cout<<"Contraseņa: ";cin>>logcontra;
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
				TiendaUsuario();
				break;
			}
		}
		else if(logusu == usuario[i].nombre && logcontra != usuario[i].contra)
		{
			cout<<"contraseņa incorrecta. Intente denuevo"<<endl;
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
void Menu()
{
	/////MENU 1
	char SelecMenu1,la;
	cout<<"\n\t\tMENU\n1.- Crear Usuario\n2.- Iniciar sesion\n\n \3.- Salir"<<endl;
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
		default :
			cout<<"Error,Intente denuevo."<<endl;
			system("pause");
			system("CLS");
			Menu();
	
	}

	system("pause");		
}
