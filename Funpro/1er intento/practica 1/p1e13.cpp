#include <iostream>
using namespace std;
int main()
{
bool ok = (3.0 * (0.1 / 3.0)) == ((3.0 * 0.1) / 3.0);
cout << "Resultado de (3.0 * (0.1 / 3.0)) == ((3.0 * 0.1) / 3.0): "
<< boolalpha << ok << " -> ERROR" << endl;
}
//comprueba si las dos operaciones son iguales, y como no lo son, el resultado de ok es false.