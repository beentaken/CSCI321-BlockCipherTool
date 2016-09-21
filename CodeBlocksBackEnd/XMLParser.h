#ifndef XMLPARSE
#define XMLPARSE

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/** \brief
 * Properties is the node that contains all the properties for the output
 *
 */
struct Properties {
    int StartID;
    int EndID;
    int NumRounds;
    int BlockSize;
    int KeySize;
    int NumKey;
};

/** \brief
 * InOuts is the node that contains the inputs and outputs for various xml nodes
 *
 */
struct InOuts {
    int InputConID;     /**< The Input/Output ConnectionID */
    int InputSizes;     /**< The Input/Output Sizes */
    int * positions;    /**< The Output Positions */
};

/** \brief
 * Node contains all the information for the possible nodes in the XML file.
 * The possible nodes include S Box, P Box, XOR, Connection, F Function
 *
 */
struct Node {
    int type;           /**< 0 is PBox, 1 is SBox, 2 is XOR, 3 is F Function */
    int ID;             /**< The Node ID */

    int NumInputs;      /**< The Number of Inputs */
    InOuts * inputs;    /**< The Inputs for the Node */

    int NumOutputs;     /**< The Number of Outputs */
    InOuts * outputs;   /**< The Outputs for the Node */

    int ** table;       /**< Table for sbox when necessary */
    int rows;           /**< Table rows */
    int cols;           /**< Table columns */

    vector<Node> Next;  /**< This is for the F Function to specify all parts of the F Function */
};

vector<Node> ReadXML(string, Properties&);               /**< This function reads the XML Parser */
int StringToNumber(string);                 /**< The function converts the String to a number(int) */
int* StringToIntArr(string, char);          /**< This function converts the String to an integer array */
Node ParseSPBox(ifstream&, string, int, int&);    /**< This function parses in a P Box or an S Box */
Node ParseXOR(ifstream&, string, int, int&);      /**< This function parses in an xor block */
Node ParseFFunc(ifstream&, string, int, int&);    /**< This function parses in an F Function */
Properties ParseProps(ifstream&, string);

#endif // XMLPARSE
