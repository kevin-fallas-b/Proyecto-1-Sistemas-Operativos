#include <iostream>
#include <vector>
#include <limits>
#include <semaphore.h>
#include <pthread.h>
#include <cstdint>

using namespace std;

vector<int> depositos; //vector que contiene la cantidad a depositar
int cont=0; //cantidad de depositos que se hacen, maximo 10
int balance=0; //balance de dinero en la cuenta
sem_t mutex;


void* depositar(void* cantidad){
  sem_wait(&mutex);
  balance+=(intptr_t)cantidad;
  sem_post(&mutex);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  string seguir="y";
  int cantidad;

  while(seguir=="y"){
    seguir="a";
    cantidad=0;
    cout << "Por favor digite la cantidad de dinero que quiere depositar." << endl;
    while(!(cin>>cantidad)){
      cout << "Error. Debe ingresar unicamente un numero entero." <<endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    depositos.push_back(cantidad);
    cont++;
    if(cont==10){
      cout<< "Cantidad maxima de depositos alcanzados. Continuando." << endl;
      break;
    }
    while(seguir!="y" && seguir!="n"){
      cout<<"Desea hacer otro deposito?\ty/n"<< endl;
      cin >> seguir;
      if(seguir!="y"&&seguir!="n"){
        cout<<"Error. Por favor intente de nuevo." << endl;
      }
    }
  }
  //La captura de datos ya quedo perfecta, ahora hacer los depositos
  sem_init(&mutex,0,1);
  //crear la cantidad necesaria de pthreads y mandarles la cantidad de dinero a depositar
  pthread_t hijos[cont];
  for(int i=0;i<cont;i++){
    pthread_create(&hijos[i], NULL, depositar, (void*)depositos.at(i));
    pthread_join(hijos[i], NULL);
  }
  sem_destroy(&mutex);
  cout << "Balance disponible despues de los depositos: " << balance << endl;
  return 0;
}
