#include <iostream>
#include <stdlib.h>       //se incluye para poder usar atoi
#include <unistd.h>       //se incluye para poder usar fork
#include <signal.h>       //se incluye para usar kill
#include <sys/mman.h>     //se incluye para poder usar mmap

using namespace std;

int main(int argc, char *argv[]){
  //validacion de argumentos recibidos
  if( argc != 2 || !(isdigit(*argv[1])) ){
    cout << "Argumento invalido.\nPor favor ejecute el programa con un numero de argumento.\nejm: ./Collatz 3\n" << endl;
    return 0;
  }
  int numero = atoi(argv[1]);              //guardo el numero para facilidad de lectura
  // la siguiente linea es donde sucede la magia, creo dinamicamente el array donde voy a guardar la secuencia
  // ademas de eso, uso mmap para mapear en memoria ese array, lo que me permite trabajar como si fuera una variable global entre todos los hilos
  // ver la pagina man de mmap para detalles de parametros.
  int *secuencia = (int*)mmap(NULL, 100,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED,-1, 0);
  pid_t hijo = fork();                       //creo el proceso hijo

  if(hijo == 0){
    int cont=0;
    while (numero > 1){
      secuencia[cont]=numero;
      if(numero % 2 == 0){
        numero = numero/2;
      }else{
        numero = (numero *3)+1;
      }
      cont++;
    }
    secuencia[cont]=numero;
    kill(getpid(),SIGTERM);                  //kill al hilo hijo para que no me duplique la impresion en pantalla
  }
  cout << "La secuencia es la siguiente:" << endl;
  for(int i=0;i>=0;i++){
    cout << secuencia[i] << endl;
    if(secuencia[i]==1){
      break;
    }
  }
  return 0;
}
