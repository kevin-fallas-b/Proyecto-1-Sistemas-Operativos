#include <iostream>
#include <stdlib.h>       //se incluye para poder usar atoi
#include <unistd.h>       //se incluye para usar getpid && fork
#include <signal.h>       //se incluye para usar kill

using namespace std;

int cantHijos = 0;
int PPID = getpid();    //PID del hilo principal, al hacer fork se copia al hilo hijo

int main(int argc, char *argv[]){
  //validacion de argumentos recibidos
  if( argc != 2 || !(isdigit(*argv[1])) ){
    cout << "Argumento invalido.\nPor favor ejecute el programa con un numero de argumento.\nejm: ./phijos 3\n" << endl;
    return 0;
  }
  //para facilidad, meto lo recibido como argumento en una variable global, atoi convierte *char a int
  cantHijos = atoi(argv[1]);
  //hago magia
  for(int i=0;i<cantHijos;i++){
    pid_t hijo = fork();  //creo el proceso hijo
    if(hijo == 0){        //fork() me devuelve un int, si es 0 solo el proceso hijo ejecuta el codigo, lo cual me elimina el comportamiento de que tanto el hilo padre e hilo hijo ejecuten lineas de codigo
      cout << "Hijo #" << i+1 << " PID = " << getpid() << "   PPID = " << PPID << endl;
      kill(getpid(),SIGTERM); //termino el hilo hijo para evitar comportamientos no deseados. como lectura doble de lineas de codigo
    }
  }
  return 0;
}
