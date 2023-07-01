/*Administracion de usuarios (administrador)-Chris
Visualizacion del total de compras realizadas
Visualizacion de usuarios
Quitar usuarios*/

#include<iostream>
#include<string.h>
using namespace std;

void admin_usuarios(){
	
	struct admin{
		
		int visua_compras[20];
		string visua_usuarios[20];
		string quit_usuarios[20];
	};
	
	admin tiendita;
	tiendita.visua_compras[1]=3;
	tiendita.visua_usuarios[1]="Carlos_Perez";
	tiendita.quit_usuarios[1]="Carlos_Perez";
	
	cout<<"Cantidad de compras: "<<tiendita.visua_compras[1]<<endl;
	cout<<"Usuario: "<<tiendita.visua_usuarios[1]<<endl;
	cout<<"Eliminar al usuario: "<<tiendita.quit_usuarios[1]<<endl;
	
}

int main(){
	string palabra;
	cout<<"escribe algo \n";
	getline(cin,palabra);
	
	
	
	return(1);
}
