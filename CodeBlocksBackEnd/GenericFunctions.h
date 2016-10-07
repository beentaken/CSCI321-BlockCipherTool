/*
 * File:   GenericFunctions.h
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */

#include <string>                                       /**< Includes string library */
#include <boost/dynamic_bitset.hpp>
using namespace std;                                    /**< Uses standard namespace */
using namespace boost;

dynamic_bitset<> CustomXOR(dynamic_bitset<>, dynamic_bitset<>);                   /**< XOR Function that brings in input A and B and their sizes */
dynamic_bitset<> CustomSBoxSearch(unsigned long**, dynamic_bitset<>, int, int, int);            /**< Searches the Substitution Box and outputs the table value */
dynamic_bitset<> PBoxOneToOne(unsigned long*, dynamic_bitset<>, int);                  /**< Brings in the swapped positions and the input and input/output size and switches the bits around */
unsigned long* PBoxMultiOuts(dynamic_bitset<>, int, int, unsigned long**);      /**< Uses one input, number of outputs and their sizes and switches the bits according to the table which outputs multiple ints */
dynamic_bitset<> PBoxSingleOut(unsigned long*, int, int, int, unsigned long*);      /**< Brings in multiple inputs, the number of inputs, input size and output size as well as the array positions of the output and outputs a single int */


