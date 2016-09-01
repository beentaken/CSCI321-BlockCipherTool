#include <iostream>
#include <cstdlib>

#include "OutputFunctions.h"
#include "GenericFunctions.h"

using namespace std;

int main(int argc, char** argv) {

ReadXML("test.xml");

    // Driver Program
    int choice;
    string pathlocation = "";
    Node * Head = new Node;

    pathlocation = DefaultLocation();
    cout << "P: " << pathlocation << endl;
    cout << "Welcome to the Crypto to C++ Program!" << endl;
    do {
        cout << "Menu: " << endl;
        cout << "1: Create an S Box" << endl;
        cout << "2: Create a P Box" << endl;
        cout << "3: Create an XOR Function" << endl;
        cout << "4: Output all created cryptos into runnable C++ code" << endl;
        cout << "0: Exit" << endl;
        cin >> choice;

        if (choice <= 4 && choice >= 0) {
            if (choice == 1) {
                //CustomPBoxGeneration();
            }

            if (choice == 2) {
               // CustomSBoxGeneration();
            }

            if (choice == 3) {
               // CustomXOR(1, 1, 1);
            }

            if (choice == 4) {
//                Print(Head, pathlocation);
            }
        } else {
            cout << "Please input a number between and including 0 and 4!!" << endl;
        }

    } while (choice != 0);

    cout << "Thank you for using the program" << endl;

    return 0;
}