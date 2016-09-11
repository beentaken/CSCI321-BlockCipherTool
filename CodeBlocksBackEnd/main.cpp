#include <iostream>
#include <cstdlib>
#include <string>

#include "OutputRound.h"

using namespace std;

int main(int argc, char** argv) {
    // Driver Program
    int choice;
    vector<Node> Head;

    cout << "Welcome to the Crypto to C++ Program!" << endl;
    do {
        cout << "Menu: " << endl;
        cout << "1: Read in XML file store" << endl;
        cout << "2: Output all nodes into runnable C++ code" << endl;
        cout << "3: Print Node List" << endl;
        cout << "0: Exit" << endl;
        cin >> choice;

        if (choice <= 3 && choice >= 0) {
            if (choice == 1) {
                Head = ReadXML("test.xml");
            }

            if (choice == 2) {
                if (Head.empty()) {
                    cout << "There are no crypto nodes to output!" << endl;
                } else {
                    OutputRound(Head);
                }
            }

            if (choice == 3) {
                if (Head.empty()) {
                    cout << "There are no crypto nodes to output!" << endl;
                } else {
                    PrintNodeList(Head);
                }
            }
        } else {
            cout << "Please input a number between and including 0 and 2!!" << endl;
        }

    } while (choice != 0);

    cout << "Thank you for using the program" << endl;

    return 0;
}
