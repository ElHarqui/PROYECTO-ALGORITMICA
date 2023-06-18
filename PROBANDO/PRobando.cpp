#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct User {
    string username;
    string password;
};

struct Product {
    string name;
    int stock;
    double price;
};

struct Category {
    string name;
    vector<Product> products;
};

// Función para registrar un nuevo usuario
void registerUser(vector<User>& users) {
    User newUser;
    cout << "\n--- Registro de Usuario ---\n";
    cout << "Ingrese el nombre de usuario: ";
    cin.ignore();
    getline(cin, newUser.username);

    // Verificar si el usuario ya existe
    for (const User& user : users) {
        if (user.username == newUser.username) {
            cout << "El usuario ya existe. Por favor, elija otro nombre de usuario." << endl;
            return;
        }
    }

    cout << "Ingrese la contraseña: ";
    getline(cin, newUser.password);

    users.push_back(newUser);
    cout << "Usuario registrado exitosamente." << endl;
}

// Función para iniciar sesión
bool loginUser(const vector<User>& users, string& loggedInUser) {
    string username, password;
    cout << "\n--- Inicio de Sesión ---\n";
    cout << "Ingrese el nombre de usuario: ";
    cin.ignore();
    getline(cin, username);
    cout << "Ingrese la contraseña: ";
    getline(cin, password);

    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            loggedInUser = username;
            return true;
        }
    }

    cout << "Nombre de usuario o contraseña incorrectos." << endl;
    return false;
}

// Función para guardar los usuarios en un archivo CSV
void saveUsers(const vector<User>& users) {
    ofstream file("users.csv");
    if (!file) {
        cout << "No se pudo abrir el archivo users.csv" << endl;
        return;
    }

    for (const User& user : users) {
        file << user.username << "," << user.password << endl;
    }

    file.close();
}

// Función para leer los usuarios desde un archivo CSV
vector<User> loadUsers() {
    vector<User> users;
    ifstream file("users.csv");
    if (!file) {
        cout << "No se pudo abrir el archivo users.csv" << endl;
        return users;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;
        getline(ss, username, ',');
        getline(ss, password, ',');

        User user;
        user.username = username;
        user.password = password;

        users.push_back(user);
    }

    file.close();

    return users;
}

// Función para agregar una categoría
void addCategory(vector<Category>& categories) {
    Category newCategory;
    cout << "\n--- Agregar Categoría ---\n";
    cout << "Ingrese el nombre de la categoría: ";
    cin.ignore();
    getline(cin, newCategory.name);

    categories.push_back(newCategory);
    cout << "Categoría agregada exitosamente." << endl;
}

// Función para guardar las categorías en un archivo CSV
void saveCategories(const vector<Category>& categories) {
    ofstream file("categories.csv");
    if (!file) {
        cout << "No se pudo abrir el archivo categories.csv" << endl;
        return;
    }

    for (const Category& category : categories) {
        file << category.name << endl;

        for (const Product& product : category.products) {
            file << product.name << "," << product.stock << "," << product.price << endl;
        }

        file << endl; // Separador entre categorías
    }

    file.close();
}

// Función para leer las categorías desde un archivo CSV
vector<Category> loadCategories() {
    vector<Category> categories;
    ifstream file("categories.csv");
    if (!file) {
        cout << "No se pudo abrir el archivo categories.csv" << endl;
        return categories;
    }

    string line;
    while (getline(file, line)) {
        Category category;
        category.name = line;

        while (getline(file, line) && !line.empty()) {
            stringstream ss(line);
            string name, stockStr, priceStr;
            getline(ss, name, ',');
            getline(ss, stockStr, ',');
            getline(ss, priceStr, ',');

            Product product;
            product.name = name;
            product.stock = stoi(stockStr);
            product.price = stod(priceStr);

            category.products.push_back(product);
        }

        categories.push_back(category);
    }

    file.close();

    return categories;
}

// Función para mostrar el menú de opciones
void showMenu(const vector<Category>& categories, bool isDollarCurrency) {
    cout << "\n--- Menú Principal ---\n";
    cout << "1. Iniciar tienda\n";
    cout << "2. Configuración\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";

    int option;
    cin >> option;

    switch (option) {
        case 0:
            cout << "Saliendo del programa..." << endl;
            break;
        case 1:
            showCategories(categories, isDollarCurrency);
            break;
        case 2:
            showConfigurationMenu(isDollarCurrency);
            break;
        default:
            cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
            showMenu(categories, isDollarCurrency);
            break;
    }
}

// Función para mostrar la lista de categorías y sus productos
void showCategories(const vector<Category>& categories, bool isDollarCurrency) {
    cout << "\n--- Categorías ---\n";

    int categoryNum = 1;
    for (const Category& category : categories) {
        cout << categoryNum << ". " << category.name << endl;
        categoryNum++;
    }

    cout << categoryNum << ". Agregar categoría" << endl;

    cout << "Seleccione una categoría (0 para volver al menú principal): ";
    int selectedCategory;
    cin >> selectedCategory;

    if (selectedCategory == 0) {
        showMenu(categories, isDollarCurrency);
    } else if (selectedCategory == categoryNum) {
        addCategory(categories);
        showCategories(categories, isDollarCurrency);
    } else if (selectedCategory > 0 && selectedCategory < categoryNum) {
        const Category& selectedCategoryObj = categories[selectedCategory - 1];
        showProducts(selectedCategoryObj, isDollarCurrency);
    } else {
        cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
        showCategories(categories, isDollarCurrency);
    }
}

// Función para mostrar los productos de una categoría
void showProducts(const Category& category, bool isDollarCurrency) {
    cout << "\n--- Productos de " << category.name << " ---\n";

    int productNum = 1;
    for (const Product& product : category.products) {
        cout << productNum << ". " << product.name;
        if (isDollarCurrency) {
            cout << " | Stock: " << product.stock << " | Precio: $" << product.price << endl;
        } else {
            cout << " | Stock: " << product.stock << " | Precio: S/." << product.price << endl;
        }
        productNum++;
    }

    cout << productNum << ". Agregar producto" << endl;

    cout << "Seleccione un producto (0 para volver a la lista de categorías): ";
    int selectedProduct;
    cin >> selectedProduct;

    if (selectedProduct == 0) {
        showCategories(categories, isDollarCurrency);
    } else if (selectedProduct == productNum) {
        addProduct(category);
        showProducts(category, isDollarCurrency);
    } else if (selectedProduct > 0 && selectedProduct < productNum) {
        // Acciones adicionales para un producto seleccionado (opcional)
    } else {
        cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
        showProducts(category, isDollarCurrency);
    }
}

// Función para agregar un producto a una categoría
void addProduct(Category& category) {
    Product newProduct;
    cout << "\n--- Agregar Producto ---\n";
    cout << "Ingrese el nombre del producto: ";
    cin.ignore();
    getline(cin, newProduct.name);
    cout << "Ingrese la cantidad de stock: ";
    cin >> newProduct.stock;
    cout << "Ingrese el precio: ";
    cin >> newProduct.price;

    category.products.push_back(newProduct);
    cout << "Producto agregado exitosamente." << endl;
}

// Función para mostrar el menú de configuración
void showConfigurationMenu(bool& isDollarCurrency) {
    cout << "\n--- Configuración ---\n";
    cout << "1. Cambiar tipo de moneda\n";
    cout << "0. Volver al menú principal\n";
    cout << "Seleccione una opción: ";

    int option;
    cin >> option;

    switch (option) {
        case 0:
            showMenu(categories, isDollarCurrency);
            break;
        case 1:
            isDollarCurrency = !isDollarCurrency;
            cout << "Tipo de moneda cambiado exitosamente." << endl;
            showConfigurationMenu(isDollarCurrency);
            break;
        default:
            cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
            showConfigurationMenu(isDollarCurrency);
            break;
    }
}

int main() {
    vector<User> users = loadUsers();
    string loggedInUser;

    bool isDollarCurrency = true;
    vector<Category> categories = loadCategories();

    cout << "--- Bienvenido a la Tienda Virtual ---" << endl;

    while (true) {
        if (loggedInUser.empty()) {
            cout << "\n1. Iniciar sesión\n";
            cout << "2. Registrarse\n";
            cout << "0. Salir\n";
            cout << "Seleccione una opción: ";

            int option;
            cin >> option;

            if (option == 0) {
                break;
            } else if (option == 1) {
                if (loginUser(users, loggedInUser)) {
                    cout << "Inicio de sesión exitoso. ¡Hola, " << loggedInUser << "!" << endl;
                }
            } else if (option == 2) {
                registerUser(users);
            } else {
                cout << "Opción inválida. Por favor, seleccione nuevamente." << endl;
            }
        } else {
            showMenu(categories, isDollarCurrency);
            break;
        }
    }

    saveUsers(users);
    saveCategories(categories);

    return 0;
}

