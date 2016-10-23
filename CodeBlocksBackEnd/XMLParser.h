/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: XMLParser.h
 *
 * Parses the custom XML file created from the Front End
 */

#ifndef XMLPARSE            /**< Header Guards */
#define XMLPARSE            /**< Define Header Guard XMLPARSE */

#include <iostream>         /**< includes iostream library */
#include <string>           /**< includes string library */
#include <vector>           /**< includes vector library */
using namespace std;        /**< Uses a standard namespace */

/** \brief
 * Properties is the struct that contains all the properties for the output
 *
 */
struct Properties {
    int StartID;        /**< The start nodes ID */
    int EndID;          /**< The end nodes ID */
    int NumRounds;      /**< The number of rounds to perform the block encryption/decryption and is the number of keys used */
    int BlockSize;      /**< The size of the block in bits */
    int KeySize;        /**< The size of the keys in bits */
};

/** \brief
 * InOuts is the struct that contains the inputs and outputs for various xml nodes
 *
 */
struct InOuts {
    int InputConID;     /**< The Input/Output ConnectionID */
    int InputSizes;     /**< The Input/Output Sizes */
    int * positions;    /**< The Output Positions */
};

/** \brief
 * Node contains all the information for the possible nodes in the XML file.
 * The possible nodes include S Box, P Box, XOR, Connection, F Function and Subkey
 *
 */
struct Node {
    int type;           /**< 0 is PBox, 1 is SBox, 2 is XOR, 3 is F Function, 4 is Subkey */
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

vector<Node> ReadXML(string, Properties&, vector<Node>&, vector<Node>&);        /**< This function reads the XML file and parses all the nodes into the program */
vector<Node> Cycle(ifstream&);                                            /**< Is responsible for reading in encryption, decryption and keygen blocks */
int StringToNumber(string);                                                     /**< The function converts the String to a number(int) */
int* StringToIntArr(string, char);                                              /**< This function converts the String to an integer array */
Node ParseSPBox(ifstream&, string, int);                                        /**< This function parses in a P Box or an S Box */
Node ParseXOR(ifstream&, string, int);                                          /**< This function parses in an xor block */
Node ParseFFunc(ifstream&, string, int);                                  /**< This function parses in an F Function */
Properties ParseProps(ifstream&, string);                                       /**< This function parses in a Properties node */
Node ParseSubkey(ifstream&, string, int);                                 /**< This function parses in the subkey */

#endif /**< Header Guard end for XMLPARSE */
