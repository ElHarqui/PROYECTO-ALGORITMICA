#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct User {
    string username;
    string password;
};

// Función para agregar un nuevo usuario
void addUser(const string& username, const string& password, ofstream& file) {
    file << username << "," << password << endl;
}

// Función para buscar un usuario en el archivo
bool findUser(const string& username, const string& password, ifstream& file) {
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string storedUsername, storedPassword;
        if (getline(iss, storedUsername, ',') && getline(iss, storedPassword, ',')) {
            if (username == storedUsername && password == storedPassword) {
                return true; // Usuario y contraseña coinciden
            }
        }
    }
    return false; // Usuario no encontrado
}

// Función para verificar si un usuario ya existe en el archivo
bool userExists(const string& username, ifstream& file) {
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string storedUsername;
        if (getline(iss, storedUsername, ',')) {
            if (username == storedUsername) {
                return true; // Usuario ya existe
            }
        }
    }
    return false; // Usuario no encontrado
}

// Función para obtener el tipo de moneda desde el archivo de configuración
string getCurrencyType() {
    ifstream config("configuracion.txt");
    string currencyType;
    if (config.is_open()) {
        getline(config, currencyType);
        config.close();
    }
    return currencyType;
}

// Función para actualizar el tipo de moneda en el archivo de configuración
void updateCurrencyType(const string& currencyType) {
    ofstream config("configuracion.txt");
    if (config.is_open()) {
        config << currencyType << endl;
        config.close();
    }
}

int main() {
    while (true) {
        ofstream file("usuarios.csv", ios::app); // Abre el archivo en modo adjuntar (append)
        ifstream fileRead("usuarios.csv"); // Abre el archivo en modo lectura

        int option;
        string username, password;

        cout << "1. Agregar usuario\n2. Iniciar sesión\n";
        cout << "Seleccione una opción (0 para salir): ";
        cin >> option;

        if (option == 1) {
            cout << "\n--- Agregar usuario ---\n";
            cout << "Ingrese el nombre de usuario: ";
            cin >> username;

            if (userExists(username, fileRead)) {
                cout << "El nombre de usuario ya existe. Intente con otro nombre.\n";
                continue; // Vuelve al inicio del bucle sin agregar el usuario
            }

            cout << "Ingrese la contraseña: ";
            cin >> password;

            addUser(username, password, file);
            cout << "\nUsuario agregado correctamente.\n";
        } else if (option == 2) {
            cout << "\n--- Iniciar sesión ---\n";
            cout << "Ingrese el nombre de usuario: ";
            cin >> username;
            cout << "Ingrese la contraseña: ";
            cin >> password;

            if (findUser(username, password, fileRead)) {
                cout << "\nInicio de sesión exitoso.\n";

                while (true) {
                    string currencyType = getCurrencyType();

                    
            } else {
                cout << "\nNombre de usuario o contraseña incorrectos.\n";
            }
        } else if (option == 0) {
            break; // Salir del programa si se selecciona la opción 0
        } else {
            cout << "\nOpción inválida.\n";
        }

        file.close();
        fileRead.close();
    }

    return 0;
}

