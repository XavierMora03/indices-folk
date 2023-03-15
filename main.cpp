#define DELIMITADOR_REGISTRO '\n'
#define DELIMITADOR_CAMPO '|'
#define NOMBRE_ARCHIVO_DATOS "hacienda.txt"
#define NOMBRE_ARCHIVO_INDICE_PRIMARIO "indice.txt"
#define NOMBRE_ARCHIVO_INDICE_SECUNDARIO "indice.txt"

#include <iostream>

using namespace std;

struct contribuyente {
  char rfc[13];  // mascara (formato de captura) CCCCDDDDDDDCD
  char nombre[32];
  char apellido[2][32];
  char telefono[12];
  char direccion[45];
  char ciudad[32];
  char fechaNacimiento[10];  // formato AAAA/MM/DD: Año, mes y día
  char estadoCivil;
  int dependientes;
};
struct stIndiceRfc {
  char rfc[13];
  int indice;  // 2 bytes (NRR)
}