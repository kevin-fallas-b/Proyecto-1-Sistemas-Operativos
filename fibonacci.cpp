#include <iostream>
#include <stdlib.h>       //se incluye para poder usar atoi
#include <unistd.h>       //se incluye para poder usar fork
#include <signal.h>       //se incluye para usar kill
#include <sys/mman.h>     //se incluye para poder usar mmap

using namespace std;

int main(int argc, char *argv[]){
  //validacion de argumentos recibidos
  if( argc != 2 || !(isdigit(*argv[1])) ){
    cout << "Argumento invalido.\nPor favor ejecute el programa con un numero de argumento.\nejm: ./fibonacci 3\n" << endl;
    return 0;
  }
  int numero = atoi(argv[1])+1;              //guardo el numero para facilidad de lectura
  // la siguiente linea es donde sucede la magia, creo dinamicamente el array donde voy a guardar la secuencia
  // ademas de eso, uso mmap para mapear en memoria ese array, lo que me permite trabajar como si fuera una variable global entre todos los hilos
  // ver la pagina man de mmap para detalles de parametros.
  int *secuencia = (int*)mmap(NULL, numero,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,-1, 0);
  pid_t hijo = fork();                       //creo el proceso hijo

  if(hijo == 0){
    //calculo fibonacci
    for(int i=0;i<numero;i++){
      if(i>1){
        int valor = secuencia[i-1] + secuencia[i-2];
        secuencia[i] = valor;
      }else{
        //casos base
        secuencia[0]=0;
        secuencia[1]=1;
      }
    }
    kill(getpid(),SIGTERM);                  //kill al hilo hijo para que no me duplique la impresion en pantalla
  }
  cout << "La secuencia es la siguiente:" << endl;
  for(int i=0;i<numero;i++){
    cout << secuencia[i] << endl;
  }
  return 0;
}
