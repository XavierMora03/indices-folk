#ifndef INDICE_SECUNDARIO_H
#define INDICE_SECUNDARIO_H
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "contribuyentes_struct.h"

#define T_INDICE_SECUNDARIO T_CIUDAD + T_RFC * 4 + 5
const char ESPACIOS_CADENA_60[60] =
    "                                                           ";
using namespace std;
struct stIndiceCiudad {
  char ciudad[T_CIUDAD + 1];
  char rfc[4][T_RFC + 1];

  stIndiceCiudad(const char *ciudad = ESPACIOS_CADENA_60,
                 const char *rfc = ESPACIOS_CADENA_60) {
    llenarEspacios();
    normalizarYGuardar(this->ciudad, ciudad, T_CIUDAD);
    normalizarYGuardar(this->rfc[0], rfc, T_RFC);
  }
  bool operator<(const stIndiceCiudad &a) const {
    int res = strcmp(this->ciudad, a.ciudad);
    if (0 < res) return true;
    return false;
  }
  bool operator==(const stIndiceCiudad &a) const {
    int res = strcmp(this->ciudad, a.ciudad);
    if (res == 0) return true;
    return false;
  }
  void llenarEspacios() {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < T_RFC; j++) this->rfc[i][j] = ' ';
      rfc[i][T_RFC] = '\0';
    }
  }
};

class IndiceSecundario : public SimpleArchivo {
 public:
  IndiceSecundario(string s) : SimpleArchivo(s) {
    cargarIndices();
    inicializaArchivo();
  }
  ~IndiceSecundario() {}

 private:
  vector<stIndiceCiudad> list;

 public:
  void insertar(const char *ciudad, const char *rfc) {
    // buscamos si esta la ciudad
    // llamamos al constructor de indice, solo le pasamos la ciudad, para
    // comparar si existen ciudades
    stIndiceCiudad ind((char *)ciudad, (char *)rfc);
    cout << "SE CREO IN CON " << ind.ciudad << endl;
    bool ciudadEnlista = binary_search(list.begin(), list.end(), ind);
    cout << "TENGO QUE BUSCAR ESTA LLAVE" << ciudad
         << " Y ESTE RESULTADO ME DIO " << ciudadEnlista << endl;
    if (ciudadEnlista == true) {
      // encontramos la posicion donde esta, usando upper_bound, retorna un
      // puntero pa saber donde esta
      auto posicionCiudad = lower_bound(list.begin(), list.end(), ind);
      cout << "Y ENTONCES TENEMOS ESTA CIUDAD " << ciudad << " QUE COINCIDE? "
           << posicionCiudad->ciudad << endl;
      for (int i = 0; i < 4; i++) {
        // if (posicionCiudad->rfc[i][0] == '\0')
        if (posicionCiudad->rfc[i][0] == ' ') {
          // si hay algun espacio disponible, ponemos el rfc,depues de ponerlo
          // salimos con break;
          normalizarYGuardar(posicionCiudad->rfc[i], ind.rfc[0], T_RFC);
          // ahora que actualizamos en memoria ram, tenemos que actualizar en
          // archivo
          actualizaIndices();
          break;
        }
      }

    } else {
      // si no esta en la lista, agregamos a lista ordenada
      insertarAListaOrdenada(ind);
      // y agregamos hasta el final del archivo
      escribirArchivo(registroAtexto(ind));
    }
  }

  int consultaIndice(const string &ciudad) const {
    char auxCiudad[T_CIUDAD + 1];
    normalizarYGuardar(auxCiudad, ciudad.c_str(), T_CIUDAD);
    // vamos a crear un registro con la ciudad, y veremos si se encuentra, le
    // pasamos la ciudad, y una cadena vacia para el primer rfc, ya que no lo
    // necesitamos para comparar
    stIndiceCiudad ind((char *)ciudad.c_str());
    // vemos si se encuentra con la busqueda binaria
    bool existe = binary_search(list.begin(), list.end(), ind);

    if (existe == true) {
      // encontramos la posicion
      auto pos = lower_bound(list.begin(), list.end(), ind);
      // y MOSTRAMOS SU CONTENIDO
      cout << "INDICE CIUDAD: " << pos->ciudad << endl;
      cout << "RFC1: " << pos->rfc[0] << endl;
      cout << "RFC2: " << pos->rfc[1] << endl;
      cout << "RFC3: " << pos->rfc[2] << endl;
      cout << "RFC4: " << pos->rfc[3] << endl;
    } else {
      cout << "NO EXSISTE LA CIUDAD " << ciudad << endl;
    }

    return 0;
  }

 private:
  void actualizaIndices() {
    archivo.open(nombre_archivo, ios::out);
    for (int i = 0; i < list.size(); i++) archivo << registroAtexto(list.at(i));
    archivo.close();
  }
  string registroAtexto(stIndiceCiudad &ind) {
    string buffer;

    buffer += ind.ciudad;
    buffer += DELIMITADOR_CAMPO;
    buffer += ind.rfc[0];
    buffer += DELIMITADOR_CAMPO;
    buffer += ind.rfc[1];
    buffer += DELIMITADOR_CAMPO;
    buffer += ind.rfc[2];
    buffer += DELIMITADOR_CAMPO;
    buffer += ind.rfc[3];
    buffer += DELIMITADOR_REGISTRO;

    return buffer;
  }

  void insertarAListaOrdenada(const stIndiceCiudad &ind) {
    list.insert(upper_bound(list.cbegin(), list.cend(), ind), ind);
  }

  void cargarIndices() {
    archivo.open(nombre_archivo, ios::in);
    string aux;
    // mientras no se termine el archivo, y capturemos algo, (vamos a capturar
    // de archivo, lo vamos a guardar en aux, y le pasamos delimitador de campo
    // que es lo que indica que terminamos de guardar)

    while (!archivo.eof() and getline(archivo, aux, DELIMITADOR_CAMPO)) {
      stIndiceCiudad ind;
      strcpy(ind.ciudad, aux.c_str());
      getline(archivo, aux, DELIMITADOR_CAMPO);
      strcpy(ind.rfc[0], aux.c_str());
      getline(archivo, aux, DELIMITADOR_CAMPO);
      strcpy(ind.rfc[1], aux.c_str());
      getline(archivo, aux, DELIMITADOR_CAMPO);
      strcpy(ind.rfc[2], aux.c_str());
      getline(archivo, aux, DELIMITADOR_REGISTRO);
      strcpy(ind.rfc[3], aux.c_str());

      insertarAListaOrdenada(ind);
    }
    archivo.close();
  }

 public:
  void verLista() {
    for (int i(0); i < list.size(); i++) cout << registroAtexto(list.at(i));
  }
};

#endif  // INDICE_SECUNDARIO_H
