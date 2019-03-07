#include <iostream>
#include <string>

using namespace std;

string mensaje;

int contPalabras(string texto){
  int palabras = 0;
  int pos = 0;
  bool sumar = true;
  while(pos < texto.size()){
    if(texto.at(pos)!= ' ' && sumar == true){
      palabras++;
      sumar=false;
    }else if(texto.at(pos)== ' ' && sumar == false )
    {
      sumar=true;
    }
    pos++;
  }
  return palabras;
}

int main(){

  cout << "Por favor digite un mensaje para ser analizado.\nPresione CTRL + D al finalizar de digitar el mensaje.\n" << endl;
  char c;
  while((c = getchar()) != EOF){
    if(c == '\n' || c=='\t'){
      mensaje += ' ';
    }else{
      mensaje += c;
    }
  }
  cout << "\n\nEl mensaje contiene " << contPalabras(mensaje) << " palabras." << endl;
}
