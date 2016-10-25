/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: OutputFunctions.cpp
 *
 * Contains all functions necessary for outputting to standard out
 */
#include "OutputFunctions.h"        /**< OutputFunctions header file */
#include <iostream>                 /**< iostream library */
#include <fstream>                  /**< file input output stream library */
#include <string>                   /**< string library */
#include <Shlwapi.h>                /**< Windows library for creating and checking files and folders */
#include <windows.h>                /**< Windows library for creating and checking files and folders */

using namespace std;                /**< Uses the standard namespace */

/** \brief
 * PrintNodeList outputs all the nodes in the vector to standard out, for checking if the xml parser is working correctly
 *
 * \param
 * Head is the vector of nodes that will be output to standard out
 *
 */
void PrintNodeList(vector<Node> Head) {
    /**< Creates an iterator to go through all nodes in the vector */
    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        /**< Extracts the node from the iterator */
        Node temp = *it;

        /**< If the type of node is a 1 or 0, print an sbox or pbox */
        if (temp.type == 1 || temp.type == 0) {
            PrintSPBox(temp);

        } else if (temp.type == 2) {
            /**< If the node type is a 2, print an xor */
            PrintXOR(temp);

        } else if (temp.type == 3) {
            /**< If the type of ndoe is a 3, print the F function */
            cout << "F Function: " << temp.ID << endl;
            cout << "---------------------------------------------------------------------------------------" << endl;
            PrintNodeList(temp.Next);
            cout << "---------------------------------------------------------------------------------------" << endl;

        } else if (temp.type == 4) {
            /**< If the type of node is a subkey, print the subkey */
            cout << "Subkey: " << temp.ID << " is output from KeyGen Node ID: " << temp.inputs[0].InputConID << " of size: " << temp.inputs[0].InputSizes << endl;
        }
        cout << endl;
    }
}

/** \brief
 * PrintXOR prints the contents of an XOR node
 *
 * \param
 * temp is the node for output
 *
 */

void PrintXOR(Node temp) {
    /**< Output the XOR ID */
    cout << "XOR: " << temp.ID << endl;
    if (temp.NumInputs != (-1)) {
        /**< Output the Node inputs */
        cout << temp.NumInputs << "Inputs: " << endl;
        for (int i = 0; i < temp.NumInputs; i++) {
            cout << "\tInput" << i+1 << " size: " << temp.inputs[i].InputSizes << ", Connection ID: " << temp.inputs[i].InputConID << endl;
        }
    }

    /**< Output the node outputs */
    if (temp.NumOutputs != (-1)) {
        cout << temp.NumOutputs << "Outputs: " << endl;
        for (int i = 0; i < temp.NumOutputs; i++) {
            cout << "\tOutput" << i+1 << " size: " << temp.outputs[i].InputSizes << ", Connection ID: " << temp.outputs[i].InputConID << endl;
        }
    }
}

/** \brief
 * PrintSPBox prints a node containing an S Box or P Box
 *
 * \param
 * temp is the Node containing the PBox SBox details for output
 *
 */
void PrintSPBox(Node temp) {
    if (temp.type == 0) {
        /**< Outputs the pbox ID */
        cout << "PBOX: " << temp.ID << endl;
    } else if (temp.type == 1) {
        /**< Outputs the sbox ID */
        cout << "SBOX: " << temp.ID << endl;
    }
    if (temp.NumInputs != (-1)) {
        /**< Outputs the inputs */
        cout << temp.NumInputs << "Inputs: " << endl;
        for (int i = 0; i < temp.NumInputs; i++) {
            cout << "\tInput" << i+1 << " size: " << temp.inputs[i].InputSizes << ", Connection ID: " << temp.inputs[i].InputConID << endl;
        }
    }

    if (temp.NumOutputs != (-1)) {
        /**< Outputs the outputs */
        cout << temp.NumOutputs << "Outputs: " << endl;
        for (int i = 0; i < temp.NumOutputs; i++) {
            cout << "\tOutput" << i+1 << " size: " << temp.outputs[i].InputSizes << ", Connection ID: " << temp.outputs[i].InputConID << endl;

            if (temp.outputs[i].positions[0] != (-1)) {
                cout << "\t\tOutput Positions: ";
                for (int l = 1; l < temp.outputs[i].positions[0]+1; l++) {
                    cout << temp.outputs[i].positions[l];
                    if (temp.outputs[i].positions[0] != l) {
                        cout  << ", ";
                    }
                }
                cout << endl;
            }
        }
    }

    if (temp.rows != (-1)) {
        /**< Outputs the table */
        cout << "\tTable rows: " << temp.rows << " columns: " << temp.cols << endl;
        cout << "\t\tValues: " << endl;
        for (int i = 0; i < temp.rows; i++) {
            cout << "\t\t\t";
            for (int l = 0; l < temp.cols; l++) {
                cout << temp.table[i][l];
                if (l != (temp.cols-1)) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }
}

/** \brief
 * SourceLocale gets the current location of the files to be copied
 *
 * \return
 * Returns a string with the location
 *
 */
string SourceLocale() {
    /**< Gets the current working directory */
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName("GenericFunctions.cpp", 1024, Current, 0);

    /**< Deletes the file off the source location */
    int counter = 1023;
    while (Current[counter] != '\\') {
        Current[counter] = '\0';
        counter--;
    }
    Current[counter] = '\0';

    /**< Returns a string of the location */
    return string (Current);
}

/** \brief
 * DefaultLocation returns a string with the programs default location to copy files
 *
 * \return
 * Returns a string of the default location
 *
 */
string DefaultLocation() {
    /**< Gets the current working directory */
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName(Current, 1024, Current, 0);

    /**< Gets the home path directory */
    char* HomePath = getenv("HOMEPATH");
    char* HomeDrive = getenv("HOMEDRIVE");
    string TempHome = HomePath;
    string HD = HomeDrive;
    TempHome = HD + TempHome + "\\Documents";
    string DefaultPath = TempHome + "\\Crypto C++ Code";

    /**< Checks if the default location exists */
    DWORD exists = GetFileAttributes(DefaultPath.c_str());

    if (exists == INVALID_FILE_ATTRIBUTES) {
        /**< It Doesn't Exist */

        /**< Change to Documents */
        HomePath = new char[TempHome.length() + 1];
        strcpy(HomePath, TempHome.c_str());

        /**< Change directory to destinatino path to create the directory */
        SetCurrentDirectory(HomePath);

        /**< Create Directory */
        CreateDirectory("Crypto C++ Code", NULL);

        /**< Set Directory back to Program Directory */
        SetCurrentDirectory(Current);
    }

    /**< Returns the default location */
    return DefaultPath;
}

/** \brief
 * UserLocation gets the users destination folder and checks whether it exists.
 * If it exists it doesnt create the directory, if it doesnt it creates it
 *
 * \param
 * Folder is the pathname passed in the user
 *
 * \return
 * Returns a string of the users destination location
 *
 */
string UserLocation(string Folder) {
    /**< Gets the current working directory */
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName(Current, 1024, Current, 0);

    /**< Checks if it is a relative path or an absolute path */
    bool check = false;
    if (Folder.find("\\") != string::npos) {
        check = true;
    }

    string DefaultPath;
    char* HomePath;
    char* HomeDrive;
    string TempHome;
    string HD;

    if (check == true) {
        /**< Absolute path */
        DefaultPath = Folder;
    } else {
        /**< Relative path to Documents */
        /**< Gets the home path directory */
        HomePath = getenv("HOMEPATH");
        HomeDrive = getenv("HOMEDRIVE");
        TempHome = HomePath;
        HD = HomeDrive;
        TempHome = HD + TempHome + "\\Documents";
        DefaultPath = TempHome + "\\" + Folder;
    }

    /**< Checks if the default location exists */
    DWORD exists = GetFileAttributes(DefaultPath.c_str());

    if (exists == INVALID_FILE_ATTRIBUTES) {
        /**< It Doesn't Exist */

        /**< Change to Documents */
        HomePath = new char[TempHome.length() + 1];
        strcpy(HomePath, TempHome.c_str());

        /**< Set directory to destination */
        SetCurrentDirectory(HomePath);

        /**< Create Directory */
        CreateDirectory(Folder.c_str(), NULL);

        /**< Set Directory back to Program Directory */
        SetCurrentDirectory(Current);
    }

    /**< Returns the path */
    return DefaultPath;
}
