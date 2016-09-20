/*
 * File:   GenericFunctions.h
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */


// Generic Functions
#include <string>
using namespace std;

string CustomXOR(int, int);                             // XOR Function
int CustomSBoxSearch(int**, int, int, int);                       // Searches the Substitution Box
int PBoxOneToOne(int*, int, int);                       // Searches the Permutation Box
int* PBoxMultiOuts(int , int , int , int , int**);      // One input to multiple outputs
int PBoxSingleOut(int* , int , int , int , int* );       // Multiple outputs to one input
