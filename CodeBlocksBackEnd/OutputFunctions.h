/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: OutputFunctions.h
 *
 * Contains all functions necessary for outputting to standard out
 */

#ifndef OUTPUTFUNC                          /**< Header Guard for Output Functions */
#define OUTPUTFUNC                          /**< Define Header Guard for output functions */

#include <string>                           /**< String library */
using namespace std;                        /**< Uses standard namespace */

#include "XMLParser.h"                      /**< Includes the header file for XMLParser */

string UserLocation(string);                /**< UserLocation creates the users destination path */
string SourceLocale();                      /**< SourceLocale gets the path to the copy files */
string DefaultLocation();                   /**< DefaultLocation creates the default location path */
void PrintNodeList(vector<Node>);           /**< Prints the entire vector of nodes out */
void PrintSPBox(Node);                      /**< Prints an S or P Box */
void PrintXOR(Node);                        /**< Prints an XOR */

#endif                                      /**< End of the Header Guard for the Output Functions */
