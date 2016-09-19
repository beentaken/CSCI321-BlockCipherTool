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
        }
    }

    if (temp.rows != (-1)) {
        cout << "\tTable rows: " << temp.rows << " columns: " << temp.cols << endl;
        cout << "\t\tValues: " << endl;
        for (int i = 0; i < temp.rows; i++) {
            cout << "\t\t\t";
            for (int l = 0; l < temp.cols; l++) {
                cout << temp.table[i][l] << ", ";
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
