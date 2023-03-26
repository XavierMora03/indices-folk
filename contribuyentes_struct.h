#ifndef CONTR_STRUCT_H
#define CONTR_STRUCT_H

// tamaños de todos los campos, así si cambia alguno el programa seguira
// funcionando con los nuevos valores.
//
#define DELIMITADOR_REGISTRO '\n'
#define DELIMITADOR_CAMPO '|'

#define NOMBRE_ARCHIVO_DATOS "HACIENDA.txt"

#define T_RFC 13
#define T_NOMBRE 32
#define T_APELLIDO 32
#define T_TELEFONO 12
#define T_DIRECCION 45
#define T_CIUDAD 32
#define T_FECHA_NACIMIENTO 10
#define T_ESTADO_CIVIL 1
#define T_DEPENDIENTES 1

#define NOMBRE_ARCHIVO_INDICE_PRIMARIO "INDICE_PRIMARIO.txt"
#define NOMBRE_ARCHIVO_INDICE_SECUNDARIO "INDICE_SECUNDARIO.txt"
#define T_INDICE_DIRECCION 4

// sumamos 10, 9 delimitadores de campo 1 de registro
#define T_REGISTRO_CONTRIBUYENTE                                               \
  T_RFC + T_NOMBRE + T_APELLIDO * 2 + T_TELEFONO + T_DIRECCION + T_CIUDAD +    \
      T_FECHA_NACIMIENTO + T_ESTADO_CIVIL + T_DEPENDIENTES + 10

// sumamos 2, 1 delimitador de campo, 1 de registro
#define T_REGISTRO_INDICE_PRIMARIO T_RFC + T_INDICE_DIRECCION + 2

// sumamos 5, 4 delimitadores de campo, 1 de registro
#define T_REGISTRO_INDICE_SECUNDARIO T_CIUDAD + T_INDICE_DIRECCION * 4 + 5

#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
using namespace std;

struct contribuyente {
  char rfc[T_RFC + 1]; // mascara (formato de captura) CCCCDDDDDDDCD
  char nombre[T_NOMBRE + 1];
  char apellido[2][T_APELLIDO + 1];
  char telefono[T_TELEFONO + 1];
  char direccion[T_DIRECCION + 1];
  char ciudad[T_CIUDAD + 1];

  char
      fechaNacimiento[T_FECHA_NACIMIENTO + 1]; // formato AAAA/MM/DD: Año, mes y
                                               //  día
  char estadoCivil;
  int dependientes;
};

string generateKey(contribuyente &contr) {
  /// Crear una función con la forma canónica de la llave (RFC) CCCCDDDDDDDCD
  const char id1[29] = {'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R',
                        'Q', 'P', 'O', 'N', 'M', 'L', 'K', 'J', 'I',
                        'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};
  string keyFinal;
  default_random_engine generador(
      chrono::system_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> distribucion(0, 9);
  auto randomNum = bind(distribucion, generador);

  default_random_engine generador2(
      chrono::system_clock::now().time_since_epoch().count());
  uniform_int_distribution<int> distribucion2(0, 26);
  auto randomNum2 = bind(distribucion, generador);

  keyFinal = contr.apellido[0][0];
  keyFinal += contr.apellido[0][1];
  keyFinal += contr.apellido[1][0];
  keyFinal += contr.nombre[0];
  keyFinal += contr.fechaNacimiento[2];
  keyFinal += contr.fechaNacimiento[3];
  keyFinal += contr.fechaNacimiento[5];
  keyFinal += contr.fechaNacimiento[6];
  keyFinal += contr.fechaNacimiento[8];
  keyFinal += contr.fechaNacimiento[9];
  keyFinal += to_string(randomNum());
  keyFinal += id1[randomNum2()];
  keyFinal += to_string(randomNum());

  return keyFinal;
}

// pone ceros a la izquiera de numero hasta llenar n digitos
string normalizaNumero(int numero, int digitos) {
  stringstream ss;
  ss << setw(digitos) << setfill('0') << numero;
  return ss.str();
}

void normalizarYGuardar(char *lugarAGuardar, string cadena, int tamanio) {
  // Llenamos de espacio, hasta que tenga la longitud de tamanio con metodo
  // resize, y le indicamos el tamanio
  cadena.resize(tamanio);
  // hay que obener la letra en mayuscula de nuestra posicion i, lo metemos
  // dentro de el metodo touuper, y lo asiganmos a cacter mayucula
  for (int i = 0; i < tamanio; i++) {
    // lo toupper nos devuelve la mayuscula y lo guardamos
    char caracter_mayuscula = toupper(cadena[i]);
    // nuestro default en donde vamos a guardar es el espacio
    lugarAGuardar[i] = ' ';
    // reescribimos el caracter, pero ahora en mayuscula
    lugarAGuardar[i] = caracter_mayuscula;

    // esto es para que no nos corte la cadena, y sigamos poniendo espacios
    // '\0' es un caracter que indica cuando se acaba la cadena, si lo
    // encontramos lo reemplazamos por un espacio
    if (lugarAGuardar[i] == '\0')
      lugarAGuardar[i] = ' ';
  }
  lugarAGuardar[tamanio] = '\0';
}

class SimpleArchivo {
protected:
  const string nombre_archivo;
  fstream archivo;

public:
  SimpleArchivo(string n) : nombre_archivo(n){};
  ~SimpleArchivo(){};

  void inicializaArchivo() {
    // checar si existe ios::in
    archivo.open(nombre_archivo, ios::in);
    // si falla, no existe, entonces lo creamos iso::out
    if (archivo.fail())
      archivo.open(nombre_archivo, ios::out);
    archivo.close();
  }

protected:
  void escribirArchivo(const string &registro) {
    archivo.open(nombre_archivo, ios::app);
    if (archivo.fail() || archivo.bad()) {
      cout << "ERROR EN ARCHIVO " << nombre_archivo << endl;
      return;
    }
    archivo << registro;
    archivo.close();
  }
};
#endif // CONTR_STRUCT_H
