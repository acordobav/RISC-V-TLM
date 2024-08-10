#include <iostream>
#include "../../../inc/ProjectAddress.h"
using namespace std;


#define SYSTEMC (*(int *)(PROJECT_ADDRESS))

int main(void) {

  int aux[5] = {0, 1, 2, 3, 4};
  int aux2[5];
  int counter = 0;
  
  cout << "Test Start" << endl;

  // Asi es como se escribe en una direccion especifica
  // Ojo que arriba se declara como el puntero de un puntero
  SYSTEMC = 10; 

  for ( const auto &x : aux ) std::cout << x << ' ';
    std::cout << std::endl;

  cout << "Test End" << endl;
  asm volatile ("ecall");

  return 0;
}
