#include <iostream>
using namespace std;
int main()
{
int num11 = -7;
int num12 = 4;
double num13 = num11 + num12;
cout << "Valor de número11 (int): " << num11 << endl;
cout << "Valor de número12 (int): " << num12 << endl;
cout << "Valor de número13 (double) (num11 + num12): " << num13 << " CORRECTO" << endl;
//-------------------------------
int num21 = -7;
unsigned num22 = 4;
double num23 = num21 + num22;
cout << "Valor de número21 (int): " << num21 << endl;
cout << "Valor de número22 (unsigned): " << num22 << endl;
cout << "Valor de número23 (double) (num21 + num22): " << num23 << " ERROR" << endl;
}
// el programa suma dos valores, en el primer caso lo hace sin problema ya que ambos valores estan definidos con int,
// pero en el segundo caso, al estar unsigned el segundo valor, el resultado se queda unsigned, por lo que solo puede
// ser positivo, y como no es el caso, da error.
