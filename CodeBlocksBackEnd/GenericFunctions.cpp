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
#include <string>
#include <sstream>
using namespace std;


string CustomXOR(string A, string B) {
    string Result("");
    int length = A.length();
    stringstream ss;

    for (int i = 0; i < length; ++i) {
        ss << (A[i] ^ B[i]);
        Result = ss.str();
    }

    return Result;
}

int** CustomSBoxGeneration() {
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

int** CustomPBoxGeneration() {
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

int CustomSBoxSearch(int** Sbox, int input) {
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
                if (Sbox[0][colcount] == col) {
                    return Sbox[rowcount][colcount];
                }
                colcount++;
            }
        }
        rowcount++;
    }

}

int CustomPBoxSearch(int** Pbox, int input) {
    int counter = 0;

    while (true) {
        if (input == Pbox[0][counter]) {
            return Pbox[1][counter];
        }
        counter++;
    }

}
