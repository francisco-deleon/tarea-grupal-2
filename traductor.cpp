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

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <locale>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// Funci�n para cargar el diccionario desde el archivo
unordered_map<string, string> cargar_diccionario(const string& archivo_nombre) {
    unordered_map<string, string> diccionario;
    ifstream archivo(archivo_nombre);
    if (!archivo) {
        cerr << "Error al abrir el archivo para cargar el diccionario: " << archivo_nombre << endl;
        return diccionario;
    }

    string linea;
    bool es_encabezado = true; // Ignorar encabezados
    while (getline(archivo, linea)) {
        if (es_encabezado || linea.find('-') != string::npos) {
            es_encabezado = false;
            continue;
        }

        stringstream ss(linea);
        string palabra, traduccion, funcionalidad;

        getline(ss, palabra, '|');
        getline(ss, traduccion, '|');
        getline(ss, funcionalidad, '|');

        // Eliminar espacios adicionales
        palabra = palabra.substr(0, palabra.find_last_not_of(" ") + 1);
        traduccion = traduccion.substr(0, traduccion.find_last_not_of(" ") + 1);

        diccionario[palabra] = traduccion;
    }

    archivo.close();
    return diccionario;
}
