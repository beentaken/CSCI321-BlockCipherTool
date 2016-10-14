#include <iostream>
#include <string>
#include "benching.h"

using namespace std;

int main()
{
    string filename;
    cout << "Enter executable file path: ";
    getline(cin, filename, '\n');
    calculateTime(filename);

    return 0;
}
