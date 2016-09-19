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

int* PBoxSplit(int input, int numofInputs) {
    int* result = new int[numofInputs];
    stringstream ss;
    ss << input;

    string str = ss.str();
    int totallength = str.length();

    int divisiblelength = totallength / numofInputs;

    for (int i = 0; i < numofInputs; i++) {
        string temp = str.substr(0, divisiblelength);
        ss.str("");
        ss << temp;
        ss >> result[i];
    }

    return result;
}

int PBoxJoin(int* inputs, int numofInputs) {
    stringstream ss;
    int result;

    for (int i = 0; i < numofInputs; i++) {
        ss << inputs[i];
    }

    ss >> result;

    return result;
}
