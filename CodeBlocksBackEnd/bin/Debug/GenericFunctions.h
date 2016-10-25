/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: GenericFunctions.h
 *
 * Contains all generic functions for the cipher
 */

#include <string>                      /**< Includes string library */
#include <boost/dynamic_bitset.hpp>    /**< Uses boost dynamic bitset library - better than normal bitset as you can pass it through functions */
using namespace std;                   /**< Uses standard namespace */
using namespace boost;                 /**< Uses boost namespace */

dynamic_bitset<> PBoxOneToOne(unsigned long*, dynamic_bitset<>, int);                   /**< Brings in the swapped positions and the input and input/output size and switches the bits around */
unsigned long* PBoxMultiOuts(dynamic_bitset<>, int, int, unsigned long**);              /**< Uses one input, number of outputs and their sizes and switches the bits according to the table which outputs multiple ints */
dynamic_bitset<> PBoxSingleOut(unsigned long*, int, int, int, unsigned long*);          /**< Brings in multiple inputs, the number of inputs, input size and output size as well as the array positions of the output and outputs a single int */

