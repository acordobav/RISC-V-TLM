#include <iostream>
#include "../../../inc/ProjectAddress.h"
using namespace std;


#define ENABLE (*(int *)(PROJECT_ADDRESS))
#define REG (*(int *)(PROJECT_ADDRESS + 0x4))

int main(void) {

  int aux[5] = {0, 1, 2, 3, 4};
  int aux2[5];
  int counter = 0;
  
  cout << "Test Start" << endl;

  // Asi es como se escribe en una direccion especifica
  // Ojo que arriba se declara como el puntero de un puntero

  for ( const auto &x : aux ) std::cout << x << ' ';
    std::cout << std::endl;

  ENABLE = 1;
  int i = 0;

  while (true)
  {
    REG = i; 
    cout << "value: " << REG << endl;
    i++;
  }
  

  cout << "Test End" << endl;
  asm volatile ("ecall");

  return 0;
}
