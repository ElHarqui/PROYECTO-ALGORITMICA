#include<iostream>
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;


static struct Usuarios{
	string nombre = "";
	string contra = "";
	string tipo = "usuario";
	string moneda = "soles";
}usuario[100];

void CargarEstructuras()
{
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
	//cout<<linea<<endl;
	int num_usu = 0;
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
	cout<<num_usu<<endl;
}
