/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenericFunctions.cpp
 * Author: SirhCloud
 * 
 * Created on 23 July 2016, 10:29 AM
 */

#include "GenericFunctions.h"
#include <iostream>
#include <limits>
using namespace std;

GenericFunctions::GenericFunctions() {
}

GenericFunctions::GenericFunctions(const GenericFunctions& orig) {
}

GenericFunctions::~GenericFunctions() {
}

int GenericFunctions::CustomXOR(int A, int B, int Length) {
    int Result = (-1);
    int RDigit;
    
    int ALastDigit;
    int BLastDigit;
    int tens = 1;
    int position = 0;
    
    while (position < Length) {
        ALastDigit = A % 10;
        A = A / 10;
        
        BLastDigit = B % 10;
        B = B / 10;
        
        RDigit = (ALastDigit + BLastDigit) % 2;
        
        if (Result == (-1)) {
            Result = RDigit;
        } else {
            Result = Result + (RDigit * tens);
        }
        
        tens = tens * 10;
        position++;
    }
    
    return Result;
}

int** GenericFunctions::CustomSBoxGeneration() {
    int rows;
    int columns;
    do {
        cout << "Please input the number of rows of the SBOX" << endl;
        cin >> rows;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number!!" << endl;
        }
    } while (cin.fail());
    
    do {
        cout << "Please input the number of columns of the SBOX" << endl;
        cin >> columns;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number!!" << endl;
        }
    } while (cin.fail());
    
    int ** result = new int*[rows+1];
    
    result[0] = new int[2];
    result[0][0] = rows;
    result[0][1] = columns;
    for (int i = 1; i < rows; i++) {
        result[i] = new int[columns];
        for (int l = 0; l < columns; l++) {
            int ins;
            do {
                cout << "Please input the bit at position (" << i-1 << ", " << l << ").";
                cin >> ins;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number!!" << endl;
                }
            } while (cin.fail());
            result[i][l] = ins; //INPUT
        }
    }
    
    return result;
}

int** GenericFunctions::CustomPBoxGeneration() {
    int rows;
    int columns;
    do {
        cout << "Please input the number of rows of the PBOX" << endl;
        cin >> rows;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number!!" << endl;
        }
    } while (cin.fail());
    
    do {
        cout << "Please input the number of columns of the PBOX" << endl;
        cin >> columns;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number!!" << endl;
        }
    } while (cin.fail());
    
    int ** result = new int*[rows+1];
    
    result[0] = new int[2];
    result[0][0] = rows;
    result[0][1] = columns;
    for (int i = 1; i < rows; i++) {
        result[i] = new int[columns];
        for (int l = 0; l < columns; l++) {
            int ins;
            do {
                cout << "Please input the bit at position (" << i-1 << ", " << l << ").";
                cin >> ins;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number!!" << endl;
                }
            } while (cin.fail());
            result[i][l] = ins; //INPUT
        }
    }
    
    return result;
}

int GenericFunctions::CustomSBoxSearch(int** Sbox, int input) {
    int tens = 1;
    int firstdigit = input;
    int lastdigit = firstdigit % 10;
    while (firstdigit > 10) {
        firstdigit = firstdigit / 10;
        tens = tens * 10;
    }
    
    int col = input - lastdigit - firstdigit * tens;
    int row = (firstdigit * 10) + lastdigit;
    int rowcount = 0;
    int colcount = 0;
    
    while (true) {
        if (Sbox[rowcount][0] == row) {
            while (true) {
                if (Sbox[0][colcount]) {
                    return Sbox[rowcount][colcount];
                }
                colcount++;
            }
        }
        rowcount++;
    }
    
}

int GenericFunctions::CustomPBoxSearch(int** Pbox, int input) {
    int counter = 0;
        
    while (true) {
        if (input == Pbox[0][counter]) {
            return Pbox[1][counter];
        }
        counter++;
    }
    
}