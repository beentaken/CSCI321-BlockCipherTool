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

int** GenericFunctions::CustomSBoxGeneration(int columns, int rows) {
    int ** result = new int*[rows];
    
    for (int i = 0; i < rows; i++) {
        result[i] = new int[columns];
        for (int l = 0; l < columns; l++) {
            result[i][l] = 0; //INPUT
        }
    }
    
    return result;
}

int** GenericFunctions::CustomPBoxGeneration(int columns, int rows) {
    int ** result = new int*[rows];
    
    for (int i = 0; i < rows; i++) {
        result[i] = new int[columns];
        for (int l = 0; l < columns; l++) {
            result[i][l] = 0; //INPUT
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