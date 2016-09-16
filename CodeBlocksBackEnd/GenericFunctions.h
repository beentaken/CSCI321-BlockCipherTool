/**
 * Author: Christopher M
 * Filename: GenericFunctions.cpp
 * Functions that are used to create a cipher
 */

#ifndef GENFUNC
#define GENFUNC

/**< Generic Functions */
#include <string>
using namespace std;

string CustomXOR(string, string);       /**< XOR Function */
int CustomSBoxSearch(int**, int);       /**< Searches the Substitution Box */
int CustomPBoxSearch(int**, int);       /**< Searches the Permutation Box */

#endif // GENFUNC
