/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: main.cpp
 *
 * Driver file
 */
#include <iostream>         /**< Includes the iostream library */
#include <string>           /**< Includes the string library */

#include "OutputRound.h"    /**< Includes the functions from the file OutputRound.h */

using namespace std;        /**< Uses the standard namespace */

int main(int argc, char** argv) {
    /**< Driver program */
    int choice = (-1);
    Properties Props;
    /**< Vectors for encrypt, decrypt and key generation nodes */
    vector<Node> Encrypt;
    vector<Node> Decrypt;
    vector<Node> KeyGen;
    /**< Class to output nodes to cpp files */
    OutputRound OR;
    /**< Strings to hold the file location and the xml file name */
    string xmlfile;
    string filelocation = "";

    /**< If arguments present automate without a menu */
    if (argc > 1) {
        /**< Assigned xml file to the first argument */
        xmlfile = argv[1];
        if (argc > 2) {
            /**< Assigned file location to the second argument */
            filelocation = argv[2];

            /**< Reads in and stores the nodes from the xml file for encryption, decryption and key generation */
            Encrypt = ReadXML(xmlfile, Props, Decrypt, KeyGen);
            /**< Stores the source location */
            OR.ReadSource(SourceLocale());
            /**< Stores the destination location */
            filelocation = UserLocation(filelocation);
            OR.ReadDest(filelocation);
            cout << "Using user location: " << filelocation << endl;
            /**< Outputs the files to the users location */
            OR.OutputToFile(Encrypt, Decrypt, KeyGen, Props);
        } else {
            /**< If no file location supplied */
            Encrypt = ReadXML(xmlfile, Props, Decrypt, KeyGen);
            /**< Reads in the source location */
            OR.ReadSource(SourceLocale());
            /**< Sets the destination location to the default location */
            filelocation = DefaultLocation();
            OR.ReadDest(filelocation);
            cout << "Using default location: " << filelocation << endl;
            /**< Outputs the files to the users location */
            OR.OutputToFile(Encrypt, Decrypt, KeyGen, Props);
        }
    } else {
        /**< Notifies the users that arguments can be used */
        cout << "Arguments can be used by CodeBlocksBackEnd xmlfile filelocation" << endl;
        /**< Menu for the C++ program */
        cout << "Welcome to the Crypto to C++ Program!" << endl;
        do {
            cout << "Menu: " << endl;
            cout << "1: Read in XML file store" << endl;
            cout << "2: Output all nodes into runnable C++ code" << endl;
            cout << "3: Print Node List" << endl;
            cout << "0: Exit" << endl;
            /**< Prompts user for a choice */
            if (choice == (-1)) {
                cin >> choice;
            }

            /**< Will ask the user to input a proper choice if not within the range of choices */
            if (choice <= 3 && choice >= 0) {
                /**< Reads in the XML file nodes */
                if (choice == 1) {
                    /**< Prompts user for xmlfile */
                    cout << "Please insert the name of the XML file to be read in!" << endl;
                    cin >> xmlfile;
                    Encrypt = ReadXML(xmlfile, Props, Decrypt, KeyGen);
                    choice = (-1);
                }

                /**< Outputs the nodes to the users location */
                if (choice == 2) {
                    /**< Checks there are nodes for output */
                    if (Encrypt.empty()) {
                        cout << "There are no crypto nodes to output!" << endl;
                    } else {
                        /**< Gets the filelocation for output */
                        cout << "Enter filelocation to store output: (Leave empty for default location)" << endl;
                        cin.ignore(5, '\n');
                        getline(cin, filelocation, '\n');

                        /**< Stores the source location */
                        OR.ReadSource(SourceLocale());
                        /**< If no file location specified uses default location as destination location */
                        if (filelocation.empty()) {
                            filelocation = DefaultLocation();
                            cout << "Using default location: " << filelocation << endl;
                        } else {
                            /**< Uses users specified destination location */
                            filelocation = UserLocation(filelocation);
                            cout << "Using location: " << filelocation << endl;
                        }
                        /**< Stores the destination location */
                        OR.ReadDest(filelocation);

                        /**< Outputs the files to the location */
                        OR.OutputToFile(Encrypt, Decrypt, KeyGen, Props);
                    }
                    choice = (-1);
                }

                /**< Outputs the stored information of the nodes */
                if (choice == 3) {
                    /**< Outputs the properties */
                    cout << "Properties -----------------------------------<>" << endl;
                    cout << "Number of Rounds: " << Props.NumRounds << endl;
                    cout << "Block Size: " << Props.BlockSize << ", Key Size: " << Props.KeySize << endl;
                    cout << "End of Properties ------------------------------<>" << endl;

                    /**< Checks the encryption nodes are not empty */
                    if (Encrypt.empty()) {
                        /**< Error message */
                        cout << "There are no crypto nodes to output for encrypt!" << endl;
                    } else {
                        /**< Prints the node list of the encryption */
                        cout << "ENCRYPT --------------------------------------<>" << endl;
                        PrintNodeList(Encrypt);
                    }
                    if (Decrypt.empty()) {
                        /**< Error message */
                        cout << "There are no crypto nodes to output for encrypt!" << endl;
                    } else {
                        /**< Prints the node list for decryption */
                        cout << "DECRYPT --------------------------------------<>" << endl;
                        PrintNodeList(Decrypt);
                    }
                    if (KeyGen.empty()) {
                        /**< Error message */
                        cout << "There are no crypto nodes to output for encrypt!" << endl;
                    } else {
                        /**< Print the node list for the key generation */
                        cout << "KEYGEN --------------------------------------<>" << endl;
                        PrintNodeList(KeyGen);
                    }
                    choice = (-1);
                }
            } else {
                /**< Error mesage for choices */
                cout << "Please input a number between and including 0 and 3!!" << endl;
                choice = (-1);
            }

            /**< Continues to cycle until the user tells the program to exit */
        } while (choice != 0);

        cout << "Thank you for using the program" << endl;

    }

    return 0;
}
