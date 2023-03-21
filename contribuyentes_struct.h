#define T_RFC 13
#define T_NOMBRE 32
#define T_APELLIDO 32
#define T_TELEFONO 12
#define T_DIRECCION 45
#define T_CIUDAD 32
#define T_FECHA_NACIMIENTO 10
#define T_ESTADO_CIVIL 1
#define T_DEPENDIENTES 1

#include <iostream>

using namespace std;

void normalizarYGuardar(char *, string, int);
string normalizarFecha(int, int, int);
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

struct stIndiceRfc {
  char rfc[T_RFC];
  int indice; // 2 bytes (NRR)
};
