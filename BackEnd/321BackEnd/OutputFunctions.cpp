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

void Print(Node* Head, string pathlocation) {
    // Checks for the storage location of the c++ files
    if (pathlocation == NULL) {
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
    while (Head != NULL) {
        ifstream GenericsFile("GenericFunctions.cpp");
        int func = Head->option;
        
        // Open the Generic Functions File
        if (GenericsFile.is_open()) {
            // Create and open the c++ file containing all the custom created function code
            ofstream OutputFile("MyProgram.cpp");
            if (OutputFile.is_open()) {
            
                // XOR Function
                if (func == 1) {

                }

                // S Box Function
                if (func == 2) {

                }

                // P Box Function
                if (func == 3) {

                }
            }
            GenericsFile.close();
        }
        
    }
}

string DefaultLocation() {
    // Gets the current working directory
    char Current[1024];
    for (int i = 0; i < 1024; i++) {
        Current[i] = '\0';
    }
    GetFullPathName(Current, 1024, Current, 0);
    cout << Current << endl;
    
    // Gets the home path directory
    char* HomePath = getenv("HOMEPATH");
    char* HomeDrive = getenv("HOMEDRIVE");
    string TempHome = HomePath;
    string HD = HomeDrive;
    TempHome = HD + "\\" + TempHome + "\\My Documents";
    string DefaultPath = TempHome + "\\Crypto C++ Code";
    
    cout << TempHome << endl;
/*    
    // Checks if the default location exists
    DWORD exists = GetFileAttributes(DefaultPath.c_str());
    
    if (exists == INVALID_FILE_ATTRIBUTES) {
        // It Doesn't Exist
        
        // Change to Documents
        HomePath = new char[TempHome.length() + 1];
        strcpy(HomePath, TempHome.c_str());    
        cout << HomePath << endl;

        SetCurrentDirectory(HomePath);
        
        // Create Directory
        CreateDirectory("Crypto C++ Code", NULL);
    
        // Set Directory back to Program Directory
        SetCurrentDirectory(Current);
    }

    return DefaultPath;
*/

}

void PrintSBOX(int*) {
    
}

void PrintPBOX(int*) {
    
}

void PrintXOR(int*) {
    
}