#include <iostream>
#include <string>
#include "benching.h"

using namespace std;

int main()
{
    string filename;
    cout << "Enter executable file path: ";
    cin >> filename;
    calculateTime(filename);

    return 0;
}
