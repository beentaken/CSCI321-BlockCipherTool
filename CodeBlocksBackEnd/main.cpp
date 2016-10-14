#include <iostream>
#include <cstdlib>
#include <string>

#include "OutputRound.h"

using namespace std;

int main(int argc, char** argv) {
    // Driver Program
    int choice = (-1);
    Properties Props;
    vector<Node> Encrypt;
    vector<Node> Decrypt;
    vector<Node> KeyGen;
    OutputRound OR;
    string xmlfile;
    string filelocation = "";

    if (argc > 1) {
        xmlfile = argv[1];
        if (argc > 2) {
            filelocation = argv[2];

            Encrypt = ReadXML(xmlfile, Props, Decrypt, KeyGen);
            OR.ReadSource(SourceLocale());
            filelocation = UserLocation(filelocation);
            OR.ReadDest(filelocation);
            cout << "Using user location: " << filelocation << endl;
            OR.OutputToFile(Encrypt, Props);
        } else {
            Encrypt = ReadXML(xmlfile, Props, Decrypt, KeyGen);
            OR.ReadSource(SourceLocale());
            filelocation = DefaultLocation();
            OR.ReadDest(filelocation);
            cout << "Using default location: " << filelocation << endl;
            OR.OutputToFile(Encrypt, Props);
        }
    } else {
        cout << "Arguments can be used by CodeBlocksBackEnd xmlfile filelocation" << endl;
        cout << "Welcome to the Crypto to C++ Program!" << endl;
        do {
            cout << "Menu: " << endl;
            cout << "1: Read in XML file store" << endl;
            cout << "2: Output all nodes into runnable C++ code" << endl;
            cout << "3: Print Node List" << endl;
            cout << "0: Exit" << endl;
            if (choice == (-1)) {
                cin >> choice;
            }

            if (choice <= 3 && choice >= 0) {
                if (choice == 1) {
                    cout << "Please insert the name of the XML file to be read in!" << endl;
                    cin >> xmlfile;
                    Encrypt = ReadXML(xmlfile, Props, Decrypt, KeyGen);
                    choice = (-1);
                }

                if (choice == 2) {
                    if (Encrypt.empty()) {
                        cout << "There are no crypto nodes to output!" << endl;
                    } else {
                        cout << "Enter filelocation to store output: (Leave empty for default location)" << endl;
                        cin.ignore(5, '\n');
                        getline(cin, filelocation, '\n');

                        OR.ReadSource(SourceLocale());
                        if (filelocation.empty()) {
                            filelocation = DefaultLocation();
                            cout << "Using default location: " << filelocation << endl;
                        } else {
                            filelocation = UserLocation(filelocation);
                            cout << "Using location: " << filelocation << endl;
                        }
                        OR.ReadDest(filelocation);

                        OR.OutputToFile(Encrypt,Props);
                    }
                    choice = (-1);
                }

                if (choice == 3) {
                    cout << "Properties -----------------------------------<>" << endl;
                    cout << "Number of Rounds: " << Props.NumRounds << endl;
                    cout << "Block Size: " << Props.BlockSize << ", Key Size: " << Props.KeySize << endl;
                    cout << "End of Properties ------------------------------<>" << endl;
                    if (Encrypt.empty()) {
                        cout << "There are no crypto nodes to output for encrypt!" << endl;
                    } else {
                        cout << "ENCRYPT --------------------------------------<>" << endl;
                        PrintNodeList(Encrypt);
                    }
                    if (Decrypt.empty()) {
                        cout << "There are no crypto nodes to output for encrypt!" << endl;
                    } else {
                        cout << "DECRYPT --------------------------------------<>" << endl;
                        PrintNodeList(Decrypt);
                    }
                    if (KeyGen.empty()) {
                        cout << "There are no crypto nodes to output for encrypt!" << endl;
                    } else {
                        cout << "KEYGEN --------------------------------------<>" << endl;
                        PrintNodeList(KeyGen);
                    }
                    choice = (-1);
                }
            } else {
                cout << "Please input a number between and including 0 and 2!!" << endl;
                choice = (-1);
            }

        } while (choice != 0);

        cout << "Thank you for using the program" << endl;
    }

    return 0;
}
