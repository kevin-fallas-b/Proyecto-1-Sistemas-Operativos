#include <iostream>
#include <string.h>
#include <cstdlib>
#include <unistd.h>       //se incluye para poder usar fork
#include <signal.h>       //se incluye para usar kill

using namespace std;

int main(int argc, char *argv[]){
  //validacion de argumentos recibidos
  if( argc != 2 || (isdigit(*argv[1])) ){
    cout << "Argumento invalido.\nPor favor ejecute el programa con un mensaje de parametro.\nUtilice el backslash para indicar espacio.\nejm: ./pipes hola\\ mundo\n" << endl;
    return 0;
  }
  string mensaje = argv[1];
  cout << "Mensaje recibido por parametro: " << mensaje << endl;
  int fd[2]; //0 se usa para leer, 1 para escribir
  if(pipe(fd) == -1){
    cout << "Error en el pipe";
    return 0;
  }
  //guardo el mensaje en el pipe y cierro la escritura
  write(fd[1],mensaje.c_str(),mensaje.length()+1);
  close(fd[1]);
  pid_t hijo;
  if((hijo = fork()) == -1){
    cout << "Error en el fork";
    return 0;
  }
  if(hijo == 0){
    string copia;
    char aux;
    //leer de char en char hasta que read retorne 0. read retorna 0 cuando lee EOF
    while(read(fd[0],&aux,1) > 0){
      if(aux !=0 ){
        copia.push_back(aux);
      }
    }
    //cierro lectura de pipe
    close(fd[0]);
    cout<<"Mensaje que llego por medio del pipe: "<< copia << endl;
    kill(getpid(),SIGTERM);
  }
  return 0;
}
