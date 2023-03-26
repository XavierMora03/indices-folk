#ifndef INDICE_SECUNDARIO_H
#define INDICE_SECUNDARIO_H
#include "contribuyentes_struct.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
struct stIndiceCiudad {
  char ciudad[T_CIUDAD];
  char rfc[4][T_RFC + 1];
  stIndiceCiudad(const char *city, const char *rfc1) {
    strcpy(ciudad, city);
    strcpy(rfc[0], rfc1);
  }
  stIndiceCiudad() {}
  bool operator<(const stIndiceCiudad &a) const {
    int res = strcmp(this->ciudad, a.ciudad);
    if (0 < res)
      return true;
    return false;
  }
  bool operator==(const stIndiceCiudad &a) const {
    int res = strcmp(this->ciudad, a.ciudad);
    if (res == 0)
      return true;
    return false;
  }
};

class IndiceSecundario : public SimpleArchivo {
public:
  IndiceSecundario(string s) : SimpleArchivo(s) { cargarIndices(); }
  ~IndiceSecundario() {}

private:
  vector<stIndiceCiudad> list;

public:
  void insertar(const char *ciudad, const char *rfc) {
    // buscamos si esta la ciudad
    // llamamos al constructor de indice, solo le pasamos la ciudad, para
    // comparar si existen ciudades
    stIndiceCiudad ind(ciudad, rfc);
    bool ciudadEnlista = binary_search(list.begin(), list.end(), ind);

    if (ciudadEnlista == true) {
      // encontramos la posicion donde esta, usando upper_bound, retorna un
      // puntero pa saber donde esta
      auto posicionCiudad = upper_bound(list.begin(), list.end(), ind);

      for (int i = 0; i < 4; i++) {
        // if (posicionCiudad->rfc[i][0] == '\0')
        if (posicionCiudad->rfc[i][0] == '\0') {
          // si hay algun espacio disponible, ponemos el rfc,depues de ponerlo
          // salimos con break;
          strcpy(posicionCiudad->rfc[i], rfc);
          break;
        }
      }

    } else {
      // si no esta en la lista, agregamos la
      insertarAListaOrdenada(ind);
    }
    string registroString = registroAtexto(ind);
    escribirArchivo(registroString);
  }
  /*
  int consultaIndice(const string &llave) const {
    stIndiceCiudad ind(llave.c_str(), 0);
    if (!existe(llave)) {
      cout << "La llave " << llave << " no existe";
      return -1;
    }
    // encontramos el registro con upper bound, le pasamos el inicio
    // list.begin(),hasta el final list.end(), y queremos buscar la posicion de
    // ind
    auto registro = upper_bound(list.begin(), list.end(), ind);
    // como nos retoruna un puntero, usamos la flechita -> y retornamos el
    // registro->indice
    return registro->indice;
  }
*/
private:
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
      // como entramos al while, entonces tenemos algo en aux, en este caso es
      // la ciudad por que es el primer campo del registro
      //  guardamos aux en ciudad de un registro  de indice de ciudad nuevo
      stIndiceCiudad ind;
      // guardamos la ciudad que esta en aux, hacia el registro, para eso usamos
      // strcpy y lo guardamos, pero le pasamos el string en cadena usando
      // aux.c_str()
      strcpy(ind.ciudad, aux.c_str());
      // como tomamamos la ciudad, tenemos que tomar el resto del registro, (los
      // demas rfc)

      // primer RFC
      getline(archivo, aux, DELIMITADOR_CAMPO);
      strcpy(ind.rfc[0], aux.c_str());
      // segundo
      getline(archivo, aux, DELIMITADOR_CAMPO);
      strcpy(ind.rfc[1], aux.c_str());
      // tercero
      getline(archivo, aux, DELIMITADOR_CAMPO);
      strcpy(ind.rfc[2], aux.c_str());
      // cuarto y ultimo, OJO QUE buscamos hasta el delimitadorde registro
      getline(archivo, aux, DELIMITADOR_REGISTRO);
      strcpy(ind.rfc[0], aux.c_str());

      // lo agregamos a la lista
      insertarAListaOrdenada(ind);
    }
  }
};

#endif // INDICE_SECUNDARIO_H
