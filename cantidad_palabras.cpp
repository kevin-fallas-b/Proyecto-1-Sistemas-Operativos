#include <iostream>
#include <string>
using namespace std;

string mensaje;
int encontrarEspacios(string texto, int inicio, int contador){
  size_t pos = texto.find(" ",inicio);
  if(pos != string::npos){
    //significa que encontro un espacio, buscar nuevamente pero empezando a partir de ese espacio
    return encontrarEspacios(texto,pos+1,contador+1);
  }else{
    return contador;
  }
}
int main(){
  cout << "Por favor digite un mensaje para ser analizado." << endl;
  cin >> mensaje;
  cout << "El mensaje contiene " << encontrarEspacios(mensaje,0,0) << " espacios." << endl;
  getchar();
}
