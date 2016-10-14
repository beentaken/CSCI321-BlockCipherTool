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
            cout << "F Function: " << temp.ID << endl;
            cout << "---------------------------------------------------------------------------------------" << endl;
            PrintNodeList(temp.Next);
            cout << "---------------------------------------------------------------------------------------" << endl;

        } else if (temp.type == 4) {
            cout << "Subkey: " << temp.ID << " is output from KeyGen Node ID: " << temp.inputs[0].InputConID << " of size: " << temp.inputs[0].InputSizes << endl;
        }
        cout << endl;
    }
}

void PrintXOR(Node temp) {
    cout << "XOR: " << temp.ID << endl;
    if (temp.NumInputs != (-1)) {
        cout << temp.NumInputs << "Inputs: " << endl;
        for (int i = 0; i < temp.NumInputs; i++) {
            cout << "\tInput" << i+1 << " size: " << temp.inputs[i].InputSizes << ", Connection ID: " << temp.inputs[i].InputConID << endl;
        }
    }

    if (temp.NumOutputs != (-1)) {
        cout << temp.NumOutputs << "Outputs: " << endl;
        for (int i = 0; i < temp.NumOutputs; i++) {
            cout << "\tOutput" << i+1 << " size: " << temp.outputs[i].InputSizes << ", Connection ID: " << temp.outputs[i].InputConID << endl;
        }
    }
}

void PrintSPBox(Node temp) {
    if (temp.type == 0) {
        cout << "PBOX: " << temp.ID << endl;
    } else if (temp.type == 1) {
        cout << "SBOX: " << temp.ID << endl;
    }
    if (temp.NumInputs != (-1)) {
        cout << temp.NumInputs << "Inputs: " << endl;
        for (int i = 0; i < temp.NumInputs; i++) {
            cout << "\tInput" << i+1 << " size: " << temp.inputs[i].InputSizes << ", Connection ID: " << temp.inputs[i].InputConID << endl;
        }
    }

    if (temp.NumOutputs != (-1)) {
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

string SourceLocale() {
    // Gets the current working directory
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName("GenericFunctions.cpp", 1024, Current, 0);

    int counter = 1023;
    while (Current[counter] != '\\') {
        Current[counter] = '\0';
        counter--;
    }
    Current[counter] = '\0';

    return string (Current);
}

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

string UserLocation(string Folder) {
    // Gets the current working directory
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName(Current, 1024, Current, 0);

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
        DefaultPath = Folder;
    } else {
        // Gets the home path directory
        HomePath = getenv("HOMEPATH");
        HomeDrive = getenv("HOMEDRIVE");
        TempHome = HomePath;
        HD = HomeDrive;
        TempHome = HD + TempHome + "\\Documents";
        DefaultPath = TempHome + "\\" + Folder;
    }

    // Checks if the default location exists
    DWORD exists = GetFileAttributes(DefaultPath.c_str());

    if (exists == INVALID_FILE_ATTRIBUTES) {
        // It Doesn't Exist

        // Change to Documents
        HomePath = new char[TempHome.length() + 1];
        strcpy(HomePath, TempHome.c_str());

        SetCurrentDirectory(HomePath);

        // Create Directory
        CreateDirectory(Folder.c_str(), NULL);

        // Set Directory back to Program Directory
        SetCurrentDirectory(Current);
    }

    return DefaultPath;
}

