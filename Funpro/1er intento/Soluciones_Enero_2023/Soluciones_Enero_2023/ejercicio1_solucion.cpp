#include <iostream>
#include <array>

using namespace std;

const int TAM = 10;
typedef array<int,TAM> TArray;

void menorEstricto(const TArray& a, bool& hayME, int& mE) {

	mE = a[0];
	hayME = true;

	for (int i = 1; i < TAM; i++) {
		if (a[i] == mE) {
			hayME = false;
		} else if (a[i] < mE) {
			mE = a[i];
			hayME = true;
		}
	}
}


int main()
{
	TArray a1 = {{4,7,5,3,5,7,9,32,45,8}};
	TArray a2 = {{4,7,5,3,5,7,3,32,45,8}};
	TArray a3 = {{4,7,5,3,5,7,3,32,2,8}};
	bool hayME;
	int mE;

	menorEstricto(a1,hayME,mE);

	if (hayME) {
		cout << "El menor estricto del primer array es: " << mE << endl;
	} else {
		cout << "El primer array no tiene menor estricto\n";
	}

	menorEstricto(a2,hayME,mE);

	if (hayME) {
		cout << "El menor estricto del segundo array es: " << mE << endl;
	} else {
		cout << "El segundo array no tiene menor estricto\n";
	}

	menorEstricto(a3,hayME,mE);

	if (hayME) {
		cout << "El menor estricto del tercer array es: " << mE << endl;
	} else {
		cout << "El tercer array no tiene menor estricto\n";
	}

    return 0;
}
