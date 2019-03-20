#include <iostream>
#include <stdlib.h>       //se incluye para poder usar atoi
#include <unistd.h>       //se incluye para poder usar fork
#include <signal.h>       //se incluye para usar kill
#include <sys/mman.h>     //se incluye para poder usar mmap
#include <vector>

using namespace std;


int main(int argc, char *argv[]){
  //validacion de argumentos recibidos
  cout << "inicio programa";
  if( argc != 2 || !(isdigit(*argv[1])) ){
    cout << "Argumento invalido.\nPor favor ejecute el programa con un numero de argumento.\nejm: ./collatz 8\n" << endl;
    return 0;
  }
  int numero = atoi(argv[1]);                //guardo el numero en una variable para facilidad de lectura
  cout << "se hizo atoi";
  //int fd[2]; //0 se usa para leer, 1 para escribir
  //if(pipe(fd) == -1){
    //cout << "Error en el pipe";
    //return 0;
  //}
  //pipe(fd);
  pid_t hijo = fork();                       //creo el proceso hijo
  if(hijo == 0){
    cout << "se entro a hijo";
    //vector<int> secuencia;
    cout << numero;
    //secuencia.push_back(numero);
    while (numero > 1){
      cout << numero;
      if(numero % 2 == 0){
        numero = numero/2;
      }else{
        numero = (numero *3)+1;
      }
      cout << "se va a intentar push back de: " << numero;
      //secuencia.push_back(numero);
    }
    cout << "termino de encontrar la secuencia";
    //aqui escribo el vector por medio de pipe
    //write(fd[1],(void*)&secuencia,secuencia.size()+1);
    //close(fd[1]);
    kill(getpid(),SIGTERM);
  }
  //recibe el pipe, imprime
  //vector<int> resultado;
  //read(fd[0],&resultado,1);
  //close(fd[0]);
  //for(int i=0;i<resultado.size();i++){
    //cout << resultado.at(i);
  //}
  return 0;
}
