#include <iostream>
using namespace std;

const unsigned TAM = 10;

typedef int TArray[TAM];

// funcion que comprueba si el array a esta ordenado
bool ordenado(const TArray& a) 
{
	bool res = true;
	for (int i=0;i<TAM;i++)
	{
		if (a[i]>a[i+1])
		{
			res=false;
		}
	}
	return res;
}


int main() {
    TArray a1 = {-4,-4,-3,2,3,3,3,5,8,10},
           a2 = {-3,-3,2,3,2,3,1,3,3,1};

    if (ordenado(a1)) {
        cout << "El primer array SI esta ordenado" << endl;
    } else {
        cout << "El primer array NO esta ordenado" << endl;
    }

    if (ordenado(a2)) {
        cout << "El segundo array SI esta ordenado" << endl;
    } else {
        cout << "El segundo array NO esta ordenado" << endl;
    }

    return 0;
}
