/*
 * File:   GenericFunctions.cpp
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */

#include "GenericFunctions.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
using namespace std;

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

int PBoxOneToOne(int* tablepos, int input, int iosize) {
    int result;
    stringstream ss;
    string ins;

    /**< Turns int into string */
    ss << input;
    ss >> ins;

    /**< Makes it the correct length */
    while(ins.length() < iosize) {
        ins.insert(ins.begin(), '0');
    }

    /**< Creates the output by appending the value at the position of the input to the result string  */
    ss.str("");
    for(int i = 0; i < iosize; i++) {
        ss << ins[tablepos[i]];
    }

    /**< Transforms into int */
    ss >> result;

    /**< Returns result */
    return result;
}

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
        /**< Inserts into massive input stream and increases the size */
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
