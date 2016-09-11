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

#include <string>
using namespace std;

#include "XMLParser.h"

void Print(Node*, string);
string DefaultLocation();
void PrintSBOX(int*, ifstream&, ofstream&);
void PrintPBOX(int*, ifstream&, ofstream&);
void PrintXOR(int*, ifstream&, ofstream&);
