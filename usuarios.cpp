#include<iostream>
#include <fstream>
using namespace std;
void NuevoUsuario();
main()
{
	NuevoUsuario();
	return 0;
}
void NuevoUsuario(){
	string NewUsu,NewContra;
	ofstream UsuariosText;
	UsuariosText.open("Usuarios.csv",ios::app);//ABRIENDO  BASE DE DATOS;
	if(UsuariosText.fail()){
		cout<<"ERROR,el archivo no se pudo crear";
		exit(1);
	}	
	cout<<"\t\t\tREGISTRESE\n";
	cout<<"Usuario: ";cin>>NewUsu;
	cout<<"Contraseņa: ";cin>>NewContra;
	UsuariosText<<NewUsu<<";"<<NewContra<<endl;
	UsuariosText.close();
}
