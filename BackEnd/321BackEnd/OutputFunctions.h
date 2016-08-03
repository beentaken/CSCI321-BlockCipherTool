/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutputFunctions.h
 * Author: SirhCloud
 *
 * Created on 2 August 2016, 10:31 PM
 */

#ifndef OUTPUTFUNCTIONS_H
#define OUTPUTFUNCTIONS_H

#include <string>
using namespace std;

struct Node {
    int option;
    int* variables;
    Node* Next;
};

void Print(Node*, string);
string DefaultLocation();
void PrintSBOX(int*);
void PrintPBOX(int*);
void PrintXOR(int*);


#endif /* OUTPUTFUNCTIONS_H */

