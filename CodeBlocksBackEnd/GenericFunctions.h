/*
 * File:   GenericFunctions.h
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */

#include <string>                                       /**< Includes string library */
using namespace std;                                    /**< Uses standard namespace */

string CustomXOR(int, int, int, int);                   /**< XOR Function that brings in input A and B and their sizes */
int CustomSBoxSearch(int**, int, int, int, int);             /**< Searches the Substitution Box and outputs the table value */
int PBoxOneToOne(int*, int, int, int);                  /**< Brings in the swapped positions and the input and input/output size and switches the bits around */
int* PBoxMultiOuts(int , int , int , int , int**);      /**< Uses one input, number of outputs and their sizes and switches the bits according to the table which outputs multiple ints */
int PBoxSingleOut(int* , int , int , int , int* );      /**< Brings in multiple inputs, the number of inputs, input size and output size as well as the array positions of the output and outputs a single int */
