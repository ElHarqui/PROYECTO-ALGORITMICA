#include<iostream>
#include <sstream>
#include <fstream>
#include <string.h>

/*
#ifndef usuarios_H
#define usuarios_H
*/
using namespace std;
static void CargarEstructuras(void) ;
static void NuevoUsuario(void);
static void LoginUsu(void);
static void Menu();
struct Usuarios{
	string nombre ;
	string contra ;
	string tipo ;
	string moneda;
}usuario[100];
int num_usu;

static void CargarEstructuras(int num_usu)
{
	num_usu = 0;
	string linea;
	char delimit = ';';
	ifstream UsuariosText;
	//	ofstream UsuariosText;
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
		//cout<<usuario[num_usu].nombre<<endl;
		//cout<<usuario[num_usu].contra<<endl;
		if(num_usu == 0) {
			usuario[num_usu].tipo = "admin";
		}
		num_usu++;
	}
	UsuariosText.close();
	cout<<num_usu<<endl;
	//cout<<"Cargando..."<<endl;
	//
}


static void NuevoUsuario(void)
{
	CargarEstructuras(num_usu);
	//cout<<usuario[0].nombre ;
	//cout<<"HOLA"<<endl;
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
	cout<<"Contraseña: ";cin>>NewContra;
	for (int i = 0 ; i == num_usu ; i++){
		if( NewUsu == usuario[i].nombre)
		{
			RegExist = 1;
			break;			
		}
	}

	if (RegExist == 0){
		cout<<"Registrado Correctamente";
		UsuariosText<<NewUsu<<";"<<NewContra<<endl;
		UsuariosText.close();
	}
	else{
		cout<<"Usuario Ya existe. Intentelo denuevo"<<endl;
		UsuariosText.close();
		system("pause");
		system("CLS");
		NuevoUsuario();
	}
	
}
/////////////////////////////////////////////////////
static void LoginUsu(void)
{
	CargarEstructuras(num_usu);
	//cout<<usuario[1].nombre ;
	string logusu, logcontra;
	int LogExist = 0;
	
	cout<<"\t\t\tINICIE SESION\n";//Tomando datos para posterior comprobacion de existencia
	cout<<"Usuario: ";cin>>logusu;
	cout<<"Contraseña: ";cin>>logcontra;
	for (int i = 0 ; i ==num_usu; i++ )
	{
		if (logusu == usuario[i].nombre && logcontra == usuario[i].contra)
		{
			cout<<"Inicio sesion correctamente"<<endl;
			LogExist = 1;
			if (usuario[i].tipo == "admin")
			{
				//
				//Mostrar TIENDA DE ADMINISTRADOR()
				//
				//
				//
				//

				break;
			}
			else
			{
				//
				//
				//Mostrar TIENDA DE USUARIO()
				//
				//
				//
				//
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
void Menu()
{
	/////MENU 1
	char SelecMenu1,la;
	cout<<"\t\tMENU\n1.- Crear Usuario\n2.- Iniciar sesion\n\n \3.- Salir"<<endl;
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
	
	}

	system("pause");		
}
