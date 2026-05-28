#include <iostream>

using namespace std;

const double PST_1_EUR = 166.386;
int main()
{
    cout << "introduzca el numero de peseas que desea convertir a euros: ";
    double pesetas;
    cin >> pesetas;
    double euros;
    euros = pesetas / PST_1_EUR;
    cout << pesetas << " equivalen a " << euros << " euros" << endl;
}