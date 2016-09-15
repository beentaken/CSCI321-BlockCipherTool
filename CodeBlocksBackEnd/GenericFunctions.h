#ifndef GENFUNC
#define GENFUNC

// Generic Functions
#include <string>
using namespace std;

string CustomXOR(string, string);           // XOR Function
int** CustomPBoxGeneration();           // Permutation Box Function
int** CustomSBoxGeneration();           // Substitution Box Generation Function
int CustomSBoxSearch(int**, int);       // Searches the Substitution Box
int CustomPBoxSearch(int**, int);       // Searches the Permutation Box

#endif // GENFUNC
