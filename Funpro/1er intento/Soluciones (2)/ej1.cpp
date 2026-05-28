/*
 * ej1.cpp
 *
 *  Nombre: Monica Pinto
 */

#include <iostream>
#include <array>

using namespace std;

const int N = 4;
const int M = 5;
typedef array<int,M> TFila;
typedef array<TFila, N> TMatriz;

bool sonEspejo(const TMatriz &m1, const TMatriz &m2){
    int i,j,k;
    bool sonEsp = true;

    i=0;
    while (i<N && sonEsp){
        j=0;
        k = M-1;
        while (j<M && sonEsp){
            if (m1[i][j] != m2[i][k]){
                sonEsp = false;
            }
            j++;
            k--;
        }
        i++;
    }
    return sonEsp;
}

int main() {
    TMatriz m1 = {{{{1,2,3,4,5}},
                   {{6,7,8,9,10}},
                   {{11,12,13,14,15}},
                   {{16,17,18,19,20}}}};

    TMatriz m2 = {{{{5,4,3,2,1}},
                   {{10,9,8,7,6}},
                   {{15,14,13,12,11}},
                   {{20,19,18,17,16}}}};

    TMatriz m3 = {{{{5,4,3,2,1}},
                   {{10,9,8,7,6}},
                   {{15,14,13,12,11}},
                   {{20,1,18,17,16}}}};

    if (sonEspejo(m1,m2)){
        cout << "Las matrices son espejo una de la otra" << endl;
    }else{
        cout << "Las matrices no son espejo una de la otra" << endl;
    }

    if (sonEspejo(m1,m3)){
        cout << "Las matrices son espejo una de la otra" << endl;
    }else{
        cout << "Las matrices no son espejo una de la otra" << endl;
    }
}




