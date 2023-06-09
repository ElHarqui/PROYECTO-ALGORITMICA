#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "usuarios.cpp"
using namespace std;

/*string solve( string s );*/
int main()
{
/////MENU 1
	char SelecMenu1,la;
	cout<<"\t\tMENU\n1.- Crear Usuario\n2.- Iniciar sesion\n\n\3.- Salir"<<endl;
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
	cout<<SelecMenu1<<endl;
	cout<<SelecMenu1<<endl;
//MENU 2
	
	system("color 52");
	system("pause");		
}
/*string solve( string s ) {
   for( int i = 0; i < s.length(); i++ ) {
      if( !isdigit( s[i] )) {
         return "False";
      }
   }
   return "True";
}*/
