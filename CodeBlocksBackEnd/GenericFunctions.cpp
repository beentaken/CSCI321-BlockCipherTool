/**
 * Author: Christopher M
 * Filename: GenericFunctions.cpp
 * Functions that are used to create a cipher
 */

#include "GenericFunctions.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
using namespace std;

/** \brief
 * CustomXOR reads in two strings and XORs the bits together. They inputs should be in binary (0, 1)
 * If the strings are not the same length. It will return an empty output.
 *
 * \param
 * A is the first input to be xor
 *
 * \param
 * B is the second input to be xor
 *
 * \return
 * Returns the result of xor A and B
 *
 */
string CustomXOR(string A, string B) {
    string Result("");
    int length = A.length();
    stringstream ss;

    /**< Checks string length */
    if (A.length() != B.length()) {
        /**< Returns error */
        cout << "XOR strings not the same length!" << endl;
        return Result;
    }

    /**< Cycles through the strings */
    for (int i = 0; i < length; ++i) {
        /**< Stores the unsigned ints into a string stream and then converts the string stream to a string */
        ss << (A[i] ^ B[i]);
        Result = ss.str();
    }

    /**< Returns result */
    return Result;
}

/** \brief
 * CustomSBoxSearch takes in the sbox 2d array and the input.
 * It takes the first digit and last digit of the input and uses that as the row identifier.
 * The rest of the input is used the column identifier.
 * The value that is in this position of the sbox will be the result that is returned
 *
 * \param
 * Sbox is the 2d array that holds all the sbox values and column and row identifier values.
 *
 * \param
 * input is the value that is used to look up the sbox table and return the value in the table.
 *
 * \return
 * Returns the sbox look up value
 *
 */
int CustomSBoxSearch(int** Sbox, int input) {
    /**< Extracts the row identifier and column identifier */
    int tens = 1;
    int firstdigit = input;
    int lastdigit = firstdigit % 10;
    while (firstdigit > 10) {
        firstdigit = firstdigit / 10;
        tens = tens * 10;
    }

    int col = input - lastdigit - firstdigit * tens;
    int row = (firstdigit * 10) + lastdigit;
    int rowcount = 0;
    int colcount = 0;

    /**< Cycles through the sbox and returns the correct value */
    while (true) {
        /**< Searches for the row value */
        if (Sbox[rowcount][0] == row) {
            while (true) {
                /**< Searchers the column value */
                if (Sbox[0][colcount] == col) {
                    /**< Returns the sbox value */
                    return Sbox[rowcount][colcount];
                }
                colcount++;
            }
        }
        rowcount++;
    }

}

/** \brief
 * CustomPBoxSearch looks up the pbox and returns value in the pbox
 *
 * \param
 * Pbox is the 2d array that holds all the values
 *
 * \param
 * input is the value used to look up the pbox
 *
 * \return
 * Returns the value in the pbox that corresponds to the look up value
 *
 */
int CustomPBoxSearch(int** Pbox, int input) {
    int counter = 0;

    /**< Cycles through the pbox */
    while (true) {
        if (input == Pbox[0][counter]) {
            /**< Returns the pbox value */
            return Pbox[1][counter];
        }
        counter++;
    }

}
