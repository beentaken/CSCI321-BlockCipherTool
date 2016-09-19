/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GenericFunctions.h
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */


// Generic Functions
#include <string>
using namespace std;

string CustomXOR(string, string);           // XOR Function
int CustomSBoxSearch(int**, int);       // Searches the Substitution Box
int CustomPBoxSearch(int**, int);       // Searches the Permutation Box
int* PBoxSplit(int, int);                    // Splits the input evenly
int PBoxJoin(int*, int);                     // Joins the input sequentially
