/*
 * File:   GenericFunctions.cpp
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */

#include "GenericFunctions.h"       /**< Includes Generic Functions headers */
#include <iostream>                 /**< Includes iostream library */
#include <string>                   /**< Includes the string library */
#include <sstream>                  /**< Includes the string stream library */
using namespace std;                /**< Uses standard namespace */

/** \brief
 * CustomXOR takes in two inputs, makes them the same size and the XORs them together.
 * It uses strings to xor them together
 *
 * \param
 * A is input one
 *
 * \param
 * B is input two
 *
 * \param
 * ASize is input ones size
 *
 * \param
 * BSize is input twos size
 *
 * \return
 * Returns the string that has the result of A XOR B
 *
 */

string CustomXOR(int A, int B, int ASize, int BSize) {
    /**< Turn the ints into strings */
    string Result("");
    stringstream ss;
    ss << A;
    string AStr = ss.str();
    ss.str("");
    ss << B;
    string BStr = ss.str();
    ss.str("");

    int length = AStr.length();

    /**< Inserts 0s if the length of the strings are too small */
    while (AStr.length() < ASize) {
        AStr.insert(AStr.begin(), '0');
    }

    while (BStr.length() < BSize) {
        BStr.insert(BStr.begin(), '0');
    }

    /**< XORs each individual character */
    for (int i = 0; i < length; ++i) {
        ss << (AStr[i] ^ BStr[i]);
        Result = ss.str();
    }

    /**< Returns the result */
    return Result;
}

/** \brief
 * CustomSBoxSearch takes in the SBOX table, the input and the table rows and columns
 *
 * \param
 * Sbox is the table that holds all the values and look ups
 *
 * \param
 * input is the input used to look up the table
 *
 * \param
 * rows is the number of table rows
 *
 * \param
 * cols is the number of table columns
 *
 * \return
 * Returns an int with the value at the table position where the row value and column value meet
 *
 */

int CustomSBoxSearch(int** Sbox, int input, int rows, int cols) {
    /**< Extract first digit and last digit from the input */
    int tens = 1;
    int firstdigit = input;
    int lastdigit = firstdigit % 10;
    while (firstdigit > 10) {
        firstdigit = firstdigit / 10;
        tens = tens * 10;
    }

    /**< Create column ID by taking input and leaving out the final and starting digit */
    int colID = (input/10) - firstdigit * tens;
    /**< Create row ID by using the final and starting digit of the input */
    int rowID = (firstdigit * 10) + lastdigit;
    int rowpos = 0;
    int colpos = 0;

    /**< Find the row position in the table where the ID is */
    for (int i = 0; i < rows; i++) {
        if (Sbox[i][0] == rowID) {
            rowpos = i;
        }
    }

    /**< Find the column position in the table where the col ID is */
    for (int i = 0; i < cols; i++) {
        if (Sbox[0][i] == colID) {
            colpos = i;
        }
    }

    /**< Return the value at the table position */
    return Sbox[rowpos][colpos];
}

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
 * insize is the size of the input
 *
 * \param
 * outsize is the size of the output
 *
 * \return
 * Returns an int with the permutated input
 *
 */

int PBoxOneToOne(int* tablepos, int input, int insize, int outsize) {
    int result;
    stringstream ss;
    string ins;

    /**< Turns int into string */
    ss << input;
    ss >> ins;

    /**< Makes it the correct length */
    while(ins.length() < insize) {
        ins.insert(ins.begin(), '0');
    }

    /**< Creates the output by appending the value at the position of the input to the result string  */
    ss.str("");
    for(int i = 0; i < outsize; i++) {
        ss << ins[tablepos[i]];
    }

    /**< Transforms into int */
    ss >> result;

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
 * inputsize is the size of the input
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

int* PBoxMultiOuts(int input, int numofOutputs, int inputsize, int outputsize, int** tablepos) {
    /**< Creates multiple output array */
    int* result = new int[numofOutputs];
    /**< Checks input length */
    stringstream ss;
    ss << input;

    string str = ss.str();

    /**< If smaller add 0s to the front */
    while (str.length() < inputsize) {
        str.insert(str.begin(), '0');
    }

    /**< Cycles through all outputs */
    for (int i = 0; i < numofOutputs; i++) {
        /**< Clear stringstream */
        ss.str("");
        for (int l = 0; l < outputsize; l++) {
            /**< Append the string character at the position */
            ss << str[tablepos[i][l]];
        }
        /**< Insert into return result */
        ss >> result[i];
    }

    /**< Return result */
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
int PBoxSingleOut(int* inputs, int numofInputs, int inputsize, int outputsize, int* tablepos) {
    stringstream ss;
    stringstream si;
    string singleinput;
    int result;

    /**< Creates one massive input */
    for (int i = 0; i < numofInputs; i++) {
        /**< Clears stream and inserts next input */
        ss.str("");
        ss << inputs[i];
        ss >> singleinput;
        /**< Inserts 0 at start if not the right length */
        while (singleinput.length() < inputsize) {
            singleinput.insert(singleinput.begin(), '0');
        }
        /**< Inserts into massive input stream */
        si << singleinput;
    }

    /**< Turns massive input into string */
    si >> singleinput;

    ss.str("");
    /**< Goes through the length of the output value */
    for (int i = 0; i < outputsize; i++) {
        /**< Appends/inserts the bit at the position of the massive input */
        ss << singleinput[tablepos[i]];
    }

    /**< Converts to int */
    ss >> result;

    return result;
}
