/*
 * File:   GenericFunctions.h
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */


// Generic Functions
#include <string>
using namespace std;

string CustomXOR(int, int);           // XOR Function
int CustomSBoxSearch(int**, int);       // Searches the Substitution Box
int CustomPBoxSearch(int**, int);       // Searches the Permutation Box
int* PBoxSplit(int, int);                    // Splits the input evenly
int PBoxJoin(int[], int);                     // Joins the input sequentially
