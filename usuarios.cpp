#include<iostream>
#include <fstream>
/*
#ifndef usuarios_H
#define usuarios_H
*/
using namespace std;
static void NuevoUsuario(void);
static void LoginUsu(void);
/*
main()
{
	NuevoUsuario();
	return 0;
}
*/
static void NuevoUsuario(void){
	string NewUsu,NewContra;
	ofstream UsuariosText;
	UsuariosText.open("Usuarios.csv",ios::app);//ABRIENDO  BASE DE DATOS// PARA GUARDAR NUEVO USUARIO;
	if(UsuariosText.fail()){
		cout<<"ERROR,el archivo no se pudo crear";
		exit(1);
	}	
	cout<<"\t\t\tREGISTRESE\n";
	cout<<"Usuario: ";cin>>NewUsu;
	cout<<"Contraseña: ";cin>>NewContra;
	cout<<"Registrado Correctamente";
	UsuariosText<<NewUsu<<";"<<NewContra<<endl;
	UsuariosText.close();
}
static void LoginUsu(void){
	string usu, contra;
	char delimit = ';';
	ifstream UsuariosText;
	UsuariosText.open("Usuarios.csv",ios::in);//ABRIENDO BASE DE DATOS// PARA LEER USUARIOS
	if (!UsuariosText.is_open())
	{
	    cout << "Error al abrir ejemplo.dat\n";
		exit(1);
	}
	cout<<"\t\t\tINICIE SESION\n";
	cout<<"Usuario: ";cin>>usu;
	cout<<"Contraseña: ";cin>>contra;
}
