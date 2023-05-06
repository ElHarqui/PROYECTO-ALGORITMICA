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
	UsuariosText.open("Usuarios.csv");	
	cout<<"\t\t\tREGISTRESE\n";
	cout<<"Usuario: ";cin>>NewUsu;
	cout<<"Contraseña: ";cin>>NewContra;
}
