#include <iostream>
#include <string>


using namespace std;

string *lineas = new string[1];
int la=0;//la significa linea activa

void quickSort(string *array, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = (int)array[(i + j) / 2].at(0);
    string temp;

    while (i <= j)
    {
        while ((int)array[i].at(0) < pivot)
            i++;
        while ((int)array[j].at(0) > pivot)
            j--;
        if (i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}


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
  cout << "\n\nMensaje Recibido por el sistema:" << endl;
  for(int i=0;i<=la;i++){
    cout << lineas[i] << endl;
    //cout << (int)lineas[i].at(0)<< endl;
  }
  //hacer sort, codigo tomado de https://gist.github.com/christophewang/ad056af4b3ab0ceebacf
  int n = sizeof(lineas)/sizeof(lineas[0]);
  quickSort(lineas,0,n);
  cout << "\nMensaje despues de haberse aplicado el quicksort:" << endl;
  for(int i=0;i<=la;i++){
    cout << lineas[i] << endl;
  }
}
