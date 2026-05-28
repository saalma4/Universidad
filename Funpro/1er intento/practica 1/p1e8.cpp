#include <iostream>

using namespace std;

int main()
{
    char l1, l2, l3, l4;
    cout << "introduzca la palabra de 4 letras minusculas: ";
    cin >> l1 >> l2 >> l3 >> l4;
    int distancia1 = int(l1) - int('a');
    char l1_minus = char(int('A') + distancia1);
    int distancia2 = int(l2) - int('a');
    char l2_minus = char(int('A') + distancia2);
    int distancia3 = int(l3) - int('a');
    char l3_minus = char(int('A') + distancia3);
    int distancia4 = int(l4) - int('a');
    char l4_minus = char(int('A') + distancia4);
    cout << "la palabra " << l1 << l2 << l3 << l4 << " transformada es " 
    << l1_minus << l2_minus << l3_minus << l4_minus << endl;

}