/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: OutputRound.h
 *
 * Contains all functions necessary for outputting the round to cpp files
 */

#ifndef OUTPUTROUND             /**< Header Guard for Output Round */
#define OUTPUTROUND             /**< Define Header Guard for Output Round */

#include <string>               /**< String library */
#include "OutputFunctions.h"    /**< OutputFunctions header file */

using namespace std;            /**< Uses the standard namespace */

/** \brief
 * OutputRound class handles all actions for creating files for round calculations for the ciphers
 *
 */
class OutputRound {
    /**< Public members */
    public:
        OutputRound();                                                                  /**< Constructor */
        ~OutputRound();                                                                 /**< Destructor */
        bool ReadSource(string);                                                        /**< Stores the Source Location */
        bool ReadDest(string);                                                          /**< Stores the Destination */
        bool OutputToFile(vector<Node>, vector<Node>, vector<Node>, Properties);        /**< Outputs the vectors to files */
        void OutputMain(vector<Node>, vector<Node>, vector<Node>, Properties);          /**< Outputs the main file */
        void OutputGenerics(bool[]);                                                    /**< Outputs the Generic Function files */
        int AppendFunctionF(vector<Node>, ofstream&, vector<int>&, int);                /**< AppendFunctionF appends any Nodes found within the vector to the created files */
        vector<Node> SortVec(vector<Node>, int);                                        /**< SortVec sorts the vector in order of inputs available at the current time */
        string KeyIDCheck(int);                                                         /**< KeyIDCheck turns negative numbers into appropriate output when declaring variables */
        void CheckNode(vector<Node>, bool[], vector<Node>&);                            /**< CheckNode checks which node types are present and extracts all nodes into one big vector*/

    /**< Private members */
    private:
        string SourceLocale;                                                            /**< SourceLocale is the Location of where the files to be copied originally are */
        string DestLocale;                                                              /**< DestLocale is the location where the files are to be copied and created */
};

#endif                          /**< End of the Header Guard for Output Round */
