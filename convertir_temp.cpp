#include <iostream>
using namespace std;

float convertirFAC(int fa){
  float c = (5.0f/9) * (fa-32);
  return c;
}
int main()
{
    for(int i=0;i<=300;i++){
      cout << "Farenheit: " << i << "   =    " << convertirFAC(i) << " Celcius." << endl;
    }

    return 0;
}
