/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: GenericFunctions.cpp
 *
 * Contains all generic functions for the cipher
 */

#include "GenericFunctions.h"       /**< Includes Generic Functions headers */
#include <iostream>                 /**< Includes iostream library */
#include <string>                   /**< Includes the string library */
#include <sstream>                  /**< Includes the string stream library */
#include <algorithm>                /**< Includes the algorithm library */
#include <boost/dynamic_bitset.hpp> /**< Includes the dynamic_bitset library */
using namespace std;                /**< Uses standard namespace */
using namespace boost;              /**< Uses the boost namespace */

/** \brief
 * PBoxOneToOne switches the bits of a PBox with one input and one output
 *
 * \param
 * tablepos is the table that holds the positions of the new string relative to the input
 *
 * \param
 * input is the value used to be permutated
 *
 * \param
 * outsize is the size of the output
 *
 * \return
 * Returns an int with the permutated input
 *
 */

dynamic_bitset<> PBoxOneToOne(unsigned long* tablepos, dynamic_bitset<> input, int outsize) {
    /**< Creates a bitset of appropriate length */
    dynamic_bitset<> result(outsize);

    /**< Creates the output by appending the value at the position of the input to the result string  */
    int counter = result.size();
    counter--;
    for(int i = 0; i < outsize; i++) {
        result[counter] = input[input.size() - tablepos[i] - 1];
        counter--;
    }

    /**< Returns result */
    return result;
}

/** \brief
 * PBoxMultiOuts takes in the input, number of outputs, inputsize, outputsize and table of swapped positions
 * and creates multiple outputs with the permutated bits
 *
 * \param
 * input is the input holding the original bits
 *
 * \param
 * numofOutputs is the total number of outputs
 *
 * \param
 * outputsize is the length of the output
 *
 * \param
 * tablepos holds all the positions of the permutated outputs
 *
 * \return
 * Returns an array holding the multiple outputs
 *
 */

unsigned long* PBoxMultiOuts(dynamic_bitset<> input, int numofOutputs, int outputsize, unsigned long** tablepos) {
    /**< Creates multiple output array */
    unsigned long* result = new unsigned long[numofOutputs];

    /**< Cycles through all outputs */
    for (int i = 0; i < numofOutputs; i++) {
        dynamic_bitset<>temp (outputsize);
        int counter = temp.size();
        counter--;
        for (int l = 0; l < outputsize; l++) {
            /**< Append the string character at the position */
            temp[counter] = input[input.size() - tablepos[i][l] - 1];
            counter--;
        }
        /**< Insert into return result */
        result[i] = temp.to_ulong();
    }

    /**< Returns result */
    return result;
}

/** \brief
 * PBoxSingleOut takes in multiple inputs, the number of inputs, the input size, the output size and the table of positions
 * and permutates the inputs into one output
 *
 * \param
 * inputs is the multiple inputs to be used
 *
 * \param
 * numofInputs if the number of inputs to be used
 *
 * \param
 * inputsize is the size of the input
 *
 * \param
 * outputsize is the size of the output
 *
 * \param
 * tablepos is the array of positions for the output int
 *
 * \return
 * returns an integer that has been permutated with the bits from all the inputs
 *
 */
dynamic_bitset<> PBoxSingleOut(unsigned long* inputs, int numofInputs, int inputsize, int outputsize, unsigned long* tablepos) {
    /**< Creates dynamic bitset with appropriate size */
    dynamic_bitset<> result (outputsize);
    /**< A position counter of where to insert the bits */
    int counter = result.size();
    counter--;

    /**< Creates one massive input */
    for (int i = 0; i < numofInputs; i++) {
        /**< Creates new bitset with the next input */
        dynamic_bitset<> temp(inputsize, inputs[i]);
        /**< Inserts 0 at start if not the right length */
        for (long i = temp.size()-1; i >= 0; i--) {
            result[counter] = temp[i];
            counter--;
        }
    }

    /**< Returns result */
    return result;
}



