#include <iostream>
using namespace std;

const int BYTES_EN_KBYTE = 1024;
const int KBYTES_EN_MBYTE = 1024;
const int BYTES_EN_MBYTE = BYTES_EN_KBYTE * KBYTES_EN_MBYTE;

int main()
{
    int bytes;

    cout << "introduce bytes: ";
    cin >> bytes;
    cout << "eso son " << bytes / BYTES_EN_MBYTE << endl;
}
