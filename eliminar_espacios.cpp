#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<char> mensaje;


int main(){
  cout << "Por favor digite el mensaje el cual quiere modificar.\nPresione CTRL + D al finalizar de digitar el mensaje.\n" << endl;
  char c;
  while((c = getchar()) != EOF){
    if(c != ' ' && c != '\n' && c != '\t'){
      mensaje.push_back(c);
    }
  }
  cout << "\n\nEl mensaje modificado lee de la siguiente manera:\n";
  for(int i=0;i<mensaje.size();i++){
    cout << mensaje.at(i);
  }
  cout << endl;
}
