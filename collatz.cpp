#include <iostream>
#include <stdlib.h>       //se incluye para poder usar atoi
#include <unistd.h>       //se incluye para poder usar fork
#include <signal.h>       //se incluye para usar kill
#include <sys/mman.h>     //se incluye para poder usar mmap
#include <vector>

using namespace std;


int main(int argc, char *argv[]){
  //validacion de argumentos recibidos
  if( argc != 2 || !(isdigit(*argv[1])) ){
    cout << "Argumento invalido.\nPor favor ejecute el programa con un numero de argumento.\nejm: ./collatz 8\n" << endl;
    return 0;
  }
  int numero = atoi(argv[1]);                //guardo el numero en una variable para facilidad de lectura
  vector<int> *secuencia = (vector<int>*) mmap(NULL, numero*2,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,-1, 0);
  bool seguir = false;
  pid_t hijo = fork();                       //creo el proceso hijo
  if(hijo == 0){
    while (numero > 1){
      cout << numero << endl;
      secuencia->push_back(numero);
      if(numero % 2 == 0){
        numero = numero/2;
      }else{
        numero = (numero *3)+1;
      }
    }
    seguir = true;
    kill(getpid(),SIGTERM);
  }
  cout << "imprimiendo secuencia 0 afuera del hijo:  " << secuencia->at(0);
  while(seguir == false)
  {
    //aqui espero
  }
  for(int i=0;i<secuencia->size();i++){
    cout << secuencia->at(i) << "\t";
  }
  return 0;
}
