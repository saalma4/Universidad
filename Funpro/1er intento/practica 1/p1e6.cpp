#include <iostream>

using namespace std;

const int BYT_1_KBY = 1024;
const int KYB_1_MIBY = 1024;
const int BYT_1_MIBY = BYT_1_KBY * KYB_1_MIBY;

int main()
{
    cout << "introduzca la cantidad de Bytes: ";
    
    int bytes, mibytes, kibytes, bytes_totales, resto_bytes;
    cin >> bytes_totales;
    mibytes = bytes_totales / BYT_1_MIBY;
    resto_bytes = bytes_totales % BYT_1_MIBY;
    kibytes = resto_bytes / BYT_1_KBY;
    bytes = resto_bytes % BYT_1_KBY;
     
    cout << bytes_totales << " Bytes corresponden a: " << endl;
    cout << "Mibytes =  " << mibytes << endl;
    cout << "Kibytes = " << kibytes << endl;
    cout << "Bytes = " << bytes << endl;
}