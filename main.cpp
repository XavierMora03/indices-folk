/*
Todos los programas deberán contener en el
encabezado código y nombres de los alumnos, nombre de la material,
sección y nombre del profesor.
*/

// Constantes que vamos a usar en el programa, para entender mejor el programa
#define DELIMITADOR_REGISTRO '\n'
#define DELIMITADOR_CAMPO '|'
#define NOMBRE_ARCHIVO_DATOS "hacienda.txt"
#define NOMBRE_ARCHIVO_INDICE_PRIMARIO "indice_primario.txt"
#define NOMBRE_ARCHIVO_INDICE_SECUNDARIO "indice_secundario.txt"
#define TAMANIO_LISTA_CONTRIBUYENTES 1000

// Definiendo tamaños del registro de contribuyentes en caso de
// cambiarlos en el futuro
#define T_RFC 13
#define T_NOMBRE 32
#define T_APELLIDO 32
#define T_TELEFONO 12
#define T_DIRECCION 45
#define T_CIUDAD 32
#define T_FECHA_NACIMIENTO 10
#define T_ESTADO_CIVIL 1
#define T_DEPENDIENTES 1

#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void normalizarYGuardar(char*, string, int);
string normalizarFecha(int, int, int);
struct contribuyente {
  char rfc[T_RFC];  // mascara (formato de captura) CCCCDDDDDDDCD
  char nombre[T_NOMBRE];
  char apellido[2][T_APELLIDO];
  char telefono[T_TELEFONO];
  char direccion[T_DIRECCION];
  char ciudad[T_CIUDAD];
  char fechaNacimiento[T_FECHA_NACIMIENTO];  // formato AAAA/MM/DD: Año, mes y
                                             //  día
  char estadoCivil;
  int dependientes;
} arregloContribuyentes[TAMANIO_LISTA_CONTRIBUYENTES];

struct stIndiceRfc {
  char rfc[T_RFC];
  int indice;  // 2 bytes (NRR)
};

const void mostrarRegistro(const contribuyente& contr) {
  cout << "RFC: " << contr.rfc << endl;
  cout << "Nombre: " << contr.nombre << endl;
  cout << "Apellido paterno: " << contr.apellido[0] << endl;
  cout << "Apellido materno: " << contr.apellido[1] << endl;
  cout << "Telefono: " << contr.telefono << endl;
  cout << "Direccion: " << contr.direccion << endl;
  cout << "Ciudad: " << contr.ciudad << endl;
  cout << "Fecha nacimiento: " << contr.fechaNacimiento << endl;
  cout << "Estado civil: " << contr.estadoCivil << endl;
  cout << "Dependientes: " << contr.dependientes << endl;
}
int indice = 0;
void altaRegistro() {
  contribuyente auxContribuyente;
  string auxString;
  cout << "ALTA REGISTRO" << endl;
  cout << "Ingrese RFC: ";
  getline(cin, auxString);
  normalizarYGuardar(auxContribuyente.rfc, auxString, T_RFC);
  cout << "Ingrese el nombre: ";
  getline(cin, auxString);
  normalizarYGuardar(auxContribuyente.nombre, auxString, T_NOMBRE);
  cout << "Ingrese apellido paterno: ";
  getline(cin, auxString);
  normalizarYGuardar(auxContribuyente.apellido[0], auxString, T_APELLIDO);
  cout << "Ingrese apellido materno: ";
  getline(cin, auxString);
  normalizarYGuardar(auxContribuyente.apellido[1], auxString, T_APELLIDO);
  cout << "Ingrese el telefono: ";
  getline(cin, auxString);
  normalizarYGuardar(auxContribuyente.telefono, auxString, T_TELEFONO);
  cout << "Ingrese direccion: ";
  getline(cin, auxString);
  normalizarYGuardar(auxContribuyente.direccion, auxString, T_DIRECCION);
  cout << "Ingrese ciudad: ";
  getline(cin, auxString);
  normalizarYGuardar(auxContribuyente.ciudad, auxString, T_CIUDAD);

  int dia, mes, anio;
  cout << "Ingrese dia de nacimiento: ";
  cin >> dia;
  getchar();
  cout << "Ingrese mes de nacimiento: ";
  cin >> mes;
  getchar();
  cout << "Ingrese año de nacimiento: ";
  cin >> anio;
  getchar();

  auxString = normalizarFecha(dia, mes, anio);
  normalizarYGuardar(auxContribuyente.fechaNacimiento, auxString,
                     T_FECHA_NACIMIENTO);
  cout << "Ingrese estado civil (C ó S): ";
  getline(cin, auxString);
  // se tiene que referenciar con &, porque es solo un caracter
  normalizarYGuardar(&auxContribuyente.estadoCivil, auxString, T_ESTADO_CIVIL);
  int ndependientes;
  cout << "Ingresa el numero de dependientes: ";
  cin >> ndependientes;
  getchar();
  if (ndependientes > 9) ndependientes = 9;
  auxContribuyente.dependientes = ndependientes;

  arregloContribuyentes[indice++] = auxContribuyente;
}

void normalizarYGuardar(char* lugarAGuardar, string cadena, int tamanio) {
  // Llenamos de espacio, hasta que tenga la longitud de tamanio con metodo
  // resize, y le indicamos el tamanio
  cadena.resize(tamanio);
  // hay que obener la letra en mayuscula de nuestra posicion i, lo metemos
  // dentro de el metodo touuper, y lo asiganmos a cacter mayucula
  for (int i = 0; i < tamanio; i++) {
    char caracter_mayuscula = toupper(cadena[i]);
    lugarAGuardar[i] = caracter_mayuscula;
  }
}

string normalizaNumero(int numero, int digitos) {
  stringstream ss;
  ss << setw(digitos) << setfill('0') << numero;
  return ss.str();
}

string normalizarFecha(int d, int m, int a) {
  string dia = normalizaNumero(d, 2);
  string mes = normalizaNumero(m, 2);
  string anio = normalizaNumero(a, 4);

  return dia + '/' + mes + '/' + anio;
}

void inicializaArchivo(string nombre_archivo) {
  fstream archivo;
  archivo.open(nombre_archivo, ios::out);
  archivo.close();
}

char* generarTextoRegistro(contribuyente contr) { return "jja"; }
void escribirRegistro(char* registro) {
  ofstream data(NOMBRE_ARCHIVO_DATOS);
  data.write(registro, sizeof(registro));
}

int main(int argc, char const* argv[]) {
  inicializaArchivo(NOMBRE_ARCHIVO_DATOS);
  altaRegistro();
  altaRegistro();
  mostrarRegistro(arregloContribuyentes[0]);
  mostrarRegistro(arregloContribuyentes[1]);
  return 0;
}
