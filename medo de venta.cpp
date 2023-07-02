#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <conio.h>
using namespace std;

struct Venta 
{
	char nombre[10];
	char dir_actual[30];
	char dir_nueva[30];
	char m_pago[15];
	int hora;
	float monto_pago;
	float vuelto;
}*V;

void modo_de_despacho(Venta V[], int n );
void mostrar(Venta V[], int n );
	
void modo_de_despacho(Venta V[], int n )
{
	int d, m;
		
	for ( int i = 0 ; i <= n ; i++ )
	{
		cout<<"ingrese nombre de cliente: "<<endl;
		cin>>V[i].nombre;	
		cout<<"escoja su modo de despacho: ( 1 = Recojo en tienda / 2 = Delivery ) "<<endl;
		cin>>m;
		if( m = 1 )
		{
			cout<<"escoja su metodo de pago: ( tarjeta / efectivo ) "<< endl;
			cin>>V[i].m_pago;
			cout<<"indique su hora de recojo: "<<endl;
			cin>>V[i].hora;
			if ( m = 2 )
			{
				cout<<"¿su dirección "<<V[i].dir_actual<<" es correcta? ( 1 = si / 2 = no )"<< endl;
				cin>>d;
				if( d = 1 )
				{
					cin>>V[i].dir_actual;
				
					if ( d = 2 )
					{
						cout<<"escribir dirección nueva: "<<endl;
						cin>>V[i].dir_nueva;
					}
				}
				cout<<"escoja su metodo de pago: ( tarjeta / efectivo ) "<< endl;
				cin>>V[i].m_pago;
				cout<<"indique su hora de entrega: "<<endl;
				cin>>V[i].hora;
			}
		}
			
	}
}
	
void mostrar(Venta V[], int n )
{
	for ( int i = 0 ; i <= n ; i++ )
	{
		cout<<"su nombre es: "<<V[i].nombre<<endl;
		cout<<"su direccion actual es: "<<V[i].dir_actual<<endl;
		cout<<"su dirección nueva es: "<<V[i].dir_nueva<<endl;
		cout<<"su metodo de pago es: "<<V[i].m_pago<<endl;
		cout<<"su hora de entrega es: "<<V[i].hora<<endl; 
			
	}
}
	
int main()
{
	int n;
	modo_de_despacho(V, n);
	mostrar(V, n);	
}


