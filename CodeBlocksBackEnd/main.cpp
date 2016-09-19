#include <iostream>
#include <cstdlib>
#include <string>

#include "OutputRound.h"

using namespace std;

int main(int argc, char** argv) {
    // Driver Program
    int choice;
    Properties Props;
    vector<Node> Head;
    OutputRound OR;

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
                string xmlfile;
                cout << "Please insert the name of the XML file to be read in!" << endl;
                cin >> xmlfile;
                Head = ReadXML(xmlfile, Props);
            }

            if (choice == 2) {
                if (Head.empty()) {
                    cout << "There are no crypto nodes to output!" << endl;
                } else {
                    string filelocation;
                    cout << "Enter filelocation to store output: (Leave empty for default location)" << endl;
                    cin.ignore(5, '\n');
                    getline(cin, filelocation, '\n');

                    OR.ReadSource(SourceLocale());
                    if (filelocation.empty()) {
                        filelocation = DefaultLocation();
                        cout << "Using default location: " << filelocation << endl;
                    }
                    OR.ReadDest(filelocation);

                    OR.OutputToFile(Head,Props);
                }
            }

            if (choice == 3) {
                if (Head.empty()) {
                    cout << "There are no crypto nodes to output!" << endl;
                } else {
                    cout << "Properties -----------------------------------<>" << endl;
                    cout << "Start ID: " << Props.StartID << ", End ID: " << Props.EndID << endl;
                    cout << "Number of Rounds: " << Props.NumRounds << endl;
                    cout << "Block Size: " << Props.BlockSize << ", Key Size: " << Props.KeySize << endl;
                    cout << "End of Properties ------------------------------<>" << endl;
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
