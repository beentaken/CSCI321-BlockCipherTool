/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "OutputFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <Shlwapi.h>
#include <windows.h>

using namespace std;

void PrintNodeList(vector<Node> Head) {
    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node temp = *it;

        if (temp.type == 1 || temp.type == 0) {
            PrintSPBox(temp);

        } else if (temp.type == 2) {
            PrintXOR(temp);

        } else if (temp.type == 3) {
            PrintConnection(temp);

        } else if (temp.type == 4) {
            cout << "F Function: " << temp.ID << endl;
            cout << "---------------------------------------------------------------------------------------" << endl;
            PrintNodeList(temp.Next);
            cout << "---------------------------------------------------------------------------------------" << endl;

        }

        cout << endl;
    }
}

void PrintConnection(Node temp) {
    cout << "Connection: " << temp.ID << endl;
    cout << "Coordinates1: (" << temp.XPos << ", " << temp.YPos << ")" << endl;
    cout << "Coordinates2: (" << temp.XPos2 << ", " << temp.YPos2 << ")" << endl;
    cout << "From ID: " << temp.from << ", To ID: " << temp.to << endl;
}

void PrintXOR(Node temp) {
    cout << "XOR: " << temp.ID << endl;
    cout << "Coordinates: (" << temp.XPos << ", " << temp.YPos << ")" << endl;
    if (temp.NumInputs != (-1)) {
        cout << temp.NumInputs << "Inputs: " << endl;
        for (int i = 0; i < temp.NumInputs; i++) {
            cout << "\tInput" << i+1 << " size: " << temp.inputs->InputSizes << ", Connection ID: " << temp.inputs->InputConID << endl;

            cout << "\t\t" << temp.inputs->values[0] << "Values: ";
            for (int l = 1; l < temp.inputs->values[0]; l++) {
                cout << temp.inputs->values[l] << ", ";
            }
            cout << endl;
        }
    }
}

void PrintSPBox(Node temp) {
    if (temp.type == 0) {
        cout << "PBOX: " << temp.ID << endl;
    } else if (temp.type == 1) {
        cout << "SBOX: " << temp.ID << endl;
    }
    cout << "Coordinates: (" << temp.XPos << ", " << temp.YPos << ")" << endl;
    if (temp.NumInputs != (-1)) {
        cout << temp.NumInputs << "Inputs: " << endl;
        for (int i = 0; i < temp.NumInputs; i++) {
            cout << "\tInput" << i+1 << " size: " << temp.inputs->InputSizes << ", Connection ID: " << temp.inputs->InputConID << endl;
        }
    }

    if (temp.NumOutputs != (-1)) {
        cout << temp.NumOutputs << "Outputs: " << endl;
        for (int i = 0; i < temp.NumOutputs; i++) {
            cout << "\tOutput" << i+1 << " size: " << temp.outputs->InputSizes << ", Connection ID: " << temp.outputs->InputConID << endl;
            cout << "\t\t" << temp.outputs->values[0] << "Values: ";
            for (int l = 1; l < temp.outputs->values[0]; l++) {
                cout << temp.outputs->values[l] << ", ";
            }
            cout << endl;
        }
    }
}
/*
void Print(Node* Head, string pathlocation) {
    Node* Temp = Head;

    // Checks for the storage location of the c++ files
    if (pathlocation.compare(NULL) == 0) {
        pathlocation = DefaultLocation();
    }

    // Gets the current working directory
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName(Current, 1024, Current, 0);
    cout << Current << endl;

    // Write functions to files
    if (Temp != NULL) {
        ifstream GenericsFile("GenericFunctions.cpp");
        int func = Head->option;

        // Open the Generic Functions File
        if (GenericsFile.is_open()) {
            // Create and open the c++ file containing all the custom created function code
            ofstream OutputFile("MyProgram.cpp");
            if (OutputFile.is_open()) {
                while (Temp != NULL) {
                    // XOR Function
                    if (func == 1) {
                        PrintXOR(Temp->variables, GenericsFile, OutputFile);
                    }

                    // S Box Function
                    if (func == 2) {
                        PrintSBOX(Temp->variables, GenericsFile, OutputFile);
                    }

                    // P Box Function
                    if (func == 3) {
                        PrintPBOX(Temp->variables, GenericsFile, OutputFile);
                    }

                    // Print out newline
                    OutputFile << endl;

                    // Goes to Next Node
                    Temp = Temp->Next;
                }
                OutputFile.close();
            }
            GenericsFile.close();
        }

    }
}
*/

string DefaultLocation() {
    // Gets the current working directory
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName(Current, 1024, Current, 0);

    // Gets the home path directory
    char* HomePath = getenv("HOMEPATH");
    char* HomeDrive = getenv("HOMEDRIVE");
    string TempHome = HomePath;
    string HD = HomeDrive;
    TempHome = HD + TempHome + "\\Documents";
    string DefaultPath = TempHome + "\\Crypto C++ Code";

    // Checks if the default location exists
    DWORD exists = GetFileAttributes(DefaultPath.c_str());

    if (exists == INVALID_FILE_ATTRIBUTES) {
        // It Doesn't Exist

        // Change to Documents
        HomePath = new char[TempHome.length() + 1];
        strcpy(HomePath, TempHome.c_str());

        SetCurrentDirectory(HomePath);

        // Create Directory
        CreateDirectory("Crypto C++ Code", NULL);

        // Set Directory back to Program Directory
        SetCurrentDirectory(Current);
    }

    return DefaultPath;
}
