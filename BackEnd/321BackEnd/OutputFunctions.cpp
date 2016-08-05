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
    Node* Temp = Head;
    
    // Checks for the storage location of the c++ files
    cout << "P" << pathlocation << endl;
    if (pathlocation.empty()) {
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

string DefaultLocation() {
    // Gets the directory of the file containing all the standard functions
    char Standard[1024];
    int counter = 1023;
    for (int i = 0; i < 1024; i++) {
        Standard[i] = '\0';
    }
    GetFullPathName("GenericFunctions.cpp", 1024, Standard, 0);
    while (counter >= 0 && Standard[counter] != '\\') {
        Standard[counter] = '\0';
        counter--;        
    }
    Standard[counter] = '\0';
    
    // Gets the home path directory
    char* HomePath = getenv("HOMEPATH");
    char* HomeDrive = getenv("HOMEDRIVE");
    string TempHome = HomePath;
    string HD = HomeDrive;
    TempHome = HD + TempHome + "\\My Documents";
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
        SetCurrentDirectory(Standard);
    }

    return DefaultPath;
}

void PrintSBOX(int* variables, ifstream& ins, ofstream& outs) {
    // Seek to SBOX position
    
    
    // At certain positions insert the variables and skip the defaults
    
    
}

void PrintPBOX(int* variables, ifstream& ins, ofstream& outs) {
    
}

void PrintXOR(int* variables, ifstream& ins, ofstream& outs) {
    
}

// ReadXMLFile
bool ReadXML() {
    
}

