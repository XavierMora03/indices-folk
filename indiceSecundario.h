#ifndef INDICE_SECUNDARIO_H
#define INDICE_SECUNDARIO_H
#include "contribuyentes_struct.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define T_INDICE_SECUNDARIO T_CIUDAD + T_RFC * 4 + 5
using namespace std;
struct stIndiceCiudad {
  char ciudad[T_CIUDAD + 1];
  char rfc[4][T_RFC + 1];

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
  IndiceSecundario(string s) : SimpleArchivo(s) {
    cargarIndices();
    inicializaArchivo();
  }
  ~IndiceSecundario() {}

private:
  vector<stIndiceCiudad> list;

public:
  void insertar(const char *ciudad, const char *rfc, int dir) {
    // buscamos si esta la ciudad
    // llamamos al constructor de indice, solo le pasamos la ciudad, para
    // comparar si existen ciudades
    cout << "CIUDAD: " << ciudad << ";rfc:" << rfc << endl;
    stIndiceCiudad ind;
    normalizarYGuardar(ind.ciudad, ciudad, T_CIUDAD);
    normalizarYGuardar(ind.rfc[0], rfc, T_RFC);
    llenarEspacios(ind.rfc[1], T_RFC);
    llenarEspacios(ind.rfc[2], T_RFC);
    llenarEspacios(ind.rfc[3], T_RFC);

    bool ciudadEnlista = binary_search(list.begin(), list.end(), ind);

    if (ciudadEnlista == true) {
      cout << "SI ESTA EN LISTA MI REGISTRO " << registroAtexto(ind);
      // encontramos la posicion donde esta, usando upper_bound, retorna un
      // puntero pa saber donde esta
      auto posicionCiudad = upper_bound(list.begin(), list.end(), ind);

      for (int i = 0; i < 4; i++) {
        // if (posicionCiudad->rfc[i][0] == '\0')
        char c = posicionCiudad->rfc[i][0];
        cout << "ESTE ES EL CARACTER i:" << i << " " << c << ";" << int(c)
             << endl;
        if (posicionCiudad->rfc[i][0] == ' ') {
          cout << "SE ENCONTRO UN LUGAR DISPONIBLE PARA " << rfc << endl;
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
    stIndiceCiudad ind;
    normalizarYGuardar(ind.ciudad, ciudad, T_CIUDAD);
    llenarEspacios(ind.rfc[0], T_RFC);
    llenarEspacios(ind.rfc[1], T_RFC);
    llenarEspacios(ind.rfc[2], T_RFC);
    llenarEspacios(ind.rfc[3], T_RFC);
    // vemos si se encuentra con la busqueda binaria
    bool existe = binary_search(list.begin(), list.end(), ind);

    if (existe == true) {
      // encontramos la posicion
      auto pos = upper_bound(list.begin(), list.end(), ind);
      // y MOSTRAMOS SU CONTENIDO
      cout << "INDICE CIUDAD: " << pos->ciudad << endl;
      cout << "RFC1: " << pos->rfc[0] << endl;
      cout << "RFC2: " << pos->rfc[1] << endl;
      cout << "RFC3: " << pos->rfc[2] << endl;
    } else {
      cout << "NO EXSISTE LA CIUDAD " << ciudad << endl;
    }

    return 0;
  }

private:
  void actualizaIndices() {
    archivo.open(nombre_archivo, ios::out);
    for (int i = 0; i < list.size(); i++)
      archivo << registroAtexto(list.at(i));
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
      if (aux[0] == ' ' or aux.empty())
        break;
      cout << "AGARRE: " << aux << endl;
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
    archivo.close();
  }

public:
  void verLista() {
    for (int i(0); i < list.size(); i++)
      cout << registroAtexto(list.at(i));
  }
};

#endif // INDICE_SECUNDARIO_H
