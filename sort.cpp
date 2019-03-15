#include <iostream>
#include <string>


using namespace std;

string *lineas = new string[1];
int la=0;//la significa linea activa
int main(int argc, char *argv[]){

  cout << "Por favor digite un mensaje para ser analizado.\nPresione CTRL + D al finalizar de digitar el mensaje.\n" << endl;
  char c;
  while((c = getchar()) != EOF){
    if(c == '\n'){
      la++;
      // crear array temp
      string *tmp = new string[la+1];
      // hacer copia
      for(int i=0;i<la;i++){
        tmp[i]=lineas[i];
      }
      //volver a definir lineas
      lineas = new string[la+1];
      //volver a llenar lineas
      for(int i=0;i<la;i++){
        lineas[i]=tmp[i];
      }
    }else{
      // aqui agrego a la linea activa
      lineas[la]=lineas[la]+c;
    }
  }
  //primer parte del ejercicio lisa, ahora ocupo hacer un sort
}
