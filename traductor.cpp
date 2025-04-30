/*	
*	Tarea grupal #2 del curso Programación I
*	
*	Universidad Mariano Gálvez de Guatemala
*	Facultad de Ingeniería en Sistemas
*	
*	Autores:
*	Josseline Adriana Catalán Juárez
*	José David Mazariegos Ortega
*	Mynor Alexander Gómez Pedro
*	Erick Manuel Fuentes Miranda
*	Francisco Antonio De León Natareno
*/















































// Función para traducir el texto multilínea
void traducir_codigo(const unordered_map<string, string>& diccionario) {
    cout << "Ingrese el código C++ a traducir (finalice con una línea vacía):" << endl;

    string linea;
    vector<string> codigo_original;

    // Ignorar el primer salto de línea
    cin.ignore();

    while (getline(cin, linea) && !linea.empty()) {
        codigo_original.push_back(linea);
    }

    cout << "\nCódigo traducido:\n" << endl;

    bool es_funcion = false; // Bandera para identificar si estamos dentro de una función

    for (const auto& linea : codigo_original) {
        stringstream ss(linea);
        string palabra;

        while (ss >> palabra) {
            // Detectar funciones (si hay paréntesis al final)
            if (palabra.find("()") != string::npos) {
                es_funcion = true;
            }

            // Traducir palabras clave
            if (diccionario.find(palabra) != diccionario.end()) {
                cout << diccionario.at(palabra) << " ";
            } else if (palabra == "{") {
                if (es_funcion) {
                    cout << "{ ";
                } else {
                    cout << "inicio ";
                }
            } else if (palabra == "}") {
                if (es_funcion) {
                    cout << "} ";
                    es_funcion = false; // Salimos de la función
                } else {
                    cout << "fin ";
                }
            } else {
                cout << palabra << " ";
            }
        }
        cout << endl;
    }
}

// Función principal
void traductor() {
    system("color fd"); // Cambiar el color de la consola a verde
    system("cls"); // Limpiar la consola al iniciar
    // Configurar la consola para UTF-8
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    locale::global(locale(""));

    string archivo_nombre = "palabras.txt";

    // Cargar el diccionario desde el archivo
    unordered_map<string, string> diccionario = cargar_diccionario(archivo_nombre);

    if (diccionario.empty()) {
        cerr << "El diccionario está vacío. Verifique el archivo." << endl;
        return;
    }

    char opcion;
    do {
        // Traducir el código ingresado por el usuario
        traducir_codigo(diccionario);

        cout << "\n¿Desea traducir otro código? (s/n): ";
        cin >> opcion;
        opcion = tolower(opcion); // Convertir a minúscula para evitar problemas con mayúsculas
        cin.ignore(); // Ignorar el salto de línea después de la entrada
    } while (opcion == 's');

    cout << "Saliendo del traductor...\n";
    system("color 0A"); // Cambiar el color de la consola a verde
}

