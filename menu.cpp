#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
using namespace std;

/*string solve( string s );*/
int main()
{
/////MENU 1
	char SelecMenu1,la;
	cout<<"\t\tMENU\n1.-Nuevo Usuario\n2.- Usuario Existente\n3.- Administrador "<<endl;
	cin>>SelecMenu1;
	switch(SelecMenu1)
	{
		case '1':
			//NUEVO USUARIO
			break;
		case '2':
			//USUARIO EXISTENTE
			break;
		case '3':
			//ADMINISRADOR
			break;
		default :
			cout<<"Error,Intente denuevo."<<endl;
			system("pause");
			system("CLS");
	
	}
	cout<<SelecMenu1;
	cout<<SelecMenu1;
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
