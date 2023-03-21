#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "contribuyentes_struct.h"
#include "interfaz.h"

using namespace std;
int main(int argc, char *argv[]) {
  contribuyente contr;
  Interfaz InterfazObj;
  contr = InterfazObj.altaRegistro();
  InterfazObj.mostrarRegistro(contr);
  return 0;
}
