/**
 * Author: Christopher Mellon of CryptoScythe
 * Filename: OutputRound.cpp
 *
 * Contains all functions necessary for outputting the round to cpp files
 */

#include "OutputRound.h"        /**< Includes the OutputRound header file */
#include <iostream>             /**< iostream library */
#include <fstream>              /**< file io library */
#include <string>               /**< string library */
#include <sstream>              /**< stringstream library */
#include <algorithm>            /**< algorithm library */
using namespace std;            /**< Uses the standard namespace */

/** \brief
 * Constructor
 *
 */
OutputRound::OutputRound() {
    /**< Sets them to default values */
    SourceLocale = "";
    DestLocale = "";
}

/** \brief
 * Destructor
 *
 */
OutputRound::~OutputRound() {

}

/** \brief
 * ReadSource sets the SourceLocale variable
 *
 * \param
 * input is the variable to be passed in
 *
 * \return
 * Returns true for successful read in, false for unsuccessful read in
 *
 */
bool OutputRound::ReadSource(string input) {
    SourceLocale = input;

    return true;
}

/** \brief
 * ReadDest sets the DestLocale variable
 *
 * \param
 * input is the variable to be set
 *
 * \return
 * returns true for successful input, false for unsuccessful input
 *
 */
bool OutputRound::ReadDest(string input) {
    DestLocale = input;

    return true;
}

/** \brief
 * SorcVec sorts the vector according to the inputs already declared and are usable.
 *
 * \param
 * NumOfKeys is the number of subkeys for the cipher
 *
 * \param
 * Head is the vector to be sorted
 *
 * \return
 * Returns a vector of sorted nodes
 *
 */
vector<Node> OutputRound::SortVec(vector<Node> Head, int NumOfKeys) {
    vector<Node> result;    /**< The vector result */
    vector<int> ConnIDs;    /**< connection IDs created */

    /**< Stores the keys and starting input IDs into the ConnIDs vector */
    ConnIDs.push_back(0);
    int counter = 0;
    counter--;
    for (int i = 0; i < NumOfKeys; i++) {
        ConnIDs.push_back(counter);
        counter--;
    }
    int length = Head.size();

    /**< Cycles through all nodes */
    for (int i = 0; i < length; i++) {
        /**< Cycles through all nodes */
        for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
            /**< Gets Node */
            Node temp = *it;
            /**< Checks that input exists */
            if (temp.NumInputs != (-1)) {
                /**< Cycles through all connections and check that all input connections exist */
                bool AllConnections = true;

                for (int l = 0; l < temp.NumInputs; l++) {
                    /**< Checks current connection exists */
                    bool CurrentConnection = false;
                    for (vector<int>::iterator it2 = ConnIDs.begin(); it2 != ConnIDs.end(); it2++) {
                        int tmp = *it2;
                        if (tmp == temp.inputs[l].InputConID) {
                            /**< Current connection exists */
                            CurrentConnection = true;
                        }
                    }

                    if (CurrentConnection == false) {
                        /**< One or more connections did not exist */
                        AllConnections = false;
                    }
                }

                /**< If all input connections exist */
                if (AllConnections == true) {
                    /**< Add the node and the output connection IDs if they dont exist*/
                    bool added = false;
                    if (!result.empty()) {
                        for (vector<Node>::iterator it3 = result.begin(); it3 != result.end(); it3++) {
                            Node t = *it3;
                            /**< If the same ID and node type is not a Subkey */
                            if (temp.ID == t.ID && temp.type != 4) {
                                added = true;
                            }

                            /**< If the same ID and added node type is a subkey */
                            if (temp.ID == t.ID && t.type == 4) {
                                added = true;
                            }
                        }
                    }

                    /**< Add output IDs */
                    if (added == false) {
                        result.push_back(temp);
                        for (int l = 0; l < temp.NumOutputs; l++) {
                            ConnIDs.push_back(temp.outputs[l].InputConID);
                        }
                    }
                }
            }
        }
    }

    /**< Return vector of sorted nodes */
    return result;
}

/** \brief
 * CheckNode checks which nodetypes are present within the vector of nodes.
 * It also extracts nodes from functions and places them in a long vector of nodes, to make it easier to output
 *
 * \param
 * Head is the vector of nodes that are checked
 *
 * \param
 * NodeTypes is a boolean array signalling which nodetypes are present
 *
 * \param
 * H is the vector of Nodes that have been extracted from the original vector
 *
 */
void OutputRound::CheckNode(vector<Node> Head, bool NodeTypes[], vector<Node>& H) {

    /**< Cycles through the vector of nodes */
    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node Temp = *it;

        if (Temp.type == 0) {
            /**< Adds the node to the H vector and assigns the Pbox NodeTypes to true */
            H.push_back(Temp);
            NodeTypes[0] = true;
        } else if (Temp.type == 1) {
            /**< Adds the node to the H vector and assigns the Sbox NodeTypes to true */
            NodeTypes[1] = true;
            H.push_back(Temp);
        } else if (Temp.type == 2) {
            /**< Adds the node to the H vector and assigns the XOR NodeTypes to true */
            NodeTypes[2] = true;
            H.push_back(Temp);
        } else if (Temp.type == 3) {
            /**< Cycles through the function vector of nodes */
            CheckNode(Temp.Next, NodeTypes, H);
        } else if (Temp.type == 4) {
            /**< Adds the node to the H vector */
            H.push_back(Temp);
        }
    }
}

/** \brief
 * OutputToFile outputs the encypt, decrypt and keygen vectors to created files.
 *
 * \param
 * Encrypt holds the encryption nodes
 *
 * \param
 * Decrypt holds the decryption nodes
 *
 * \param
 * KeyGen holds the key generation nodes
 *
 * \param
 * Props holds the cipher properties
 *
 * \return
 * Returns true if successully output, false if not successfully output
 *
 */
bool OutputRound::OutputToFile(vector<Node> Encrypt, vector<Node> Decrypt, vector<Node> KeyGen, Properties Props) {
    vector<Node> E;
    vector<Node> D;
    vector<Node> K;
    bool NodeTypes[3];  /**< Finds out which cipher node blocks have been used */

    for (int i = 0; i < 3; i++) {
        NodeTypes[i] = false;
    }

    /**< Checks which nodes are present in the vectors */
    CheckNode(Encrypt, NodeTypes, E);
    CheckNode(Decrypt, NodeTypes, D);
    CheckNode(KeyGen, NodeTypes, K);

    /**< Sorts the vectors */
    E = SortVec(E, Props.NumRounds);
    D = SortVec(D, Props.NumRounds);
    K = SortVec(K, Props.NumRounds);

    /**< Copies the Generics files */
    OutputGenerics(NodeTypes);
    /**< Creates the main file */
    OutputMain(E, D, K, Props);

    return true;
}

/** \brief
 * OutputMain outputs the main file for the cipher that runs the round encryption, decryption and keygeneration
 *
 * \param
 * Encrypt holds the encryption nodes
 *
 * \param
 * Decrypt holds the decryption nodes
 *
 * \param
 * KeyGen holds the key generation nodes
 *
 * \param
 * Props holds the cipher properties
 *
 */
void OutputRound::OutputMain(vector<Node> Encrypt, vector<Node> Decrypt, vector<Node> KeyGen, Properties Props) {
    vector<int> ExistingIDs;
    int counts = 0;
    /**< Creates the file for the output of the round */
    ofstream myfile;
    string fname = DestLocale;
    fname.append("\\block.cpp");

    ExistingIDs.push_back(counts);
    counts--;
    myfile.open(fname.c_str());
    /**< ENCRYPT output*/

    myfile << "#include <iostream>\n#include <string>\n#include <boost/dynamic_bitset.hpp>\n#include \"block.h\"\n#include \"GenericFunctions.h\"\nusing namespace std;\nusing namespace boost;\n\nstring Encrypt(string initial, string initialkey) {\n";
    /**< Convert string to bitset for the initial input and the keys*/
    myfile << "\tdynamic_bitset<> result0 (initial.length()*8);\n\n";
    myfile << "\tstring * key = Keygen(initialkey);\n";
    myfile << "\tfor (int i = 0; i < initial.length(); i++) {\n";
    myfile << "\t\tunsigned char c = initial[i];\n";
    myfile << "\t\tfor (int j = 7; j >= 0 && c; j--) {\n";
    myfile << "\t\t\tif (c & 0x1) {\n";
    myfile << "\t\t\t\tresult0.set(8*i+j);\n";
    myfile << "\t\t\t}\n";
    myfile << "\t\t\tc >>= 1;\n";
    myfile << "\t\t}\n";
    myfile << "\t}\n";

    myfile << "\tresult0.resize(" << Props.BlockSize*8 << ");\n\tstring returnval;\n";
    if (Props.NumRounds != 0) {
        for (int i = 1; i < Props.NumRounds+1; i++) {
            myfile << "\tdynamic_bitset<> result_" << i << "(key[" << i-1 << "].length()*8);\n";
            myfile << "\tfor (int i = 0; i < key[" << i-1 << "].length(); i++) {\n";
            myfile << "\t\tunsigned char c = key[" << i-1 << "][i];\n";
            myfile << "\t\tfor (int j = 7; j >= 0 && c; j--) {\n";
            myfile << "\t\t\tif (c & 0x1) {\n";
            myfile << "\t\t\t\tresult_" << i << ".set(8*i+j);\n";
            myfile << "\t\t\t}\n";
            myfile << "\t\t\tc >>= 1;\n";
            myfile << "\t\t}\n";
            myfile << "\t}\n";
            myfile << "\tresult_" << i << ".resize(" << Props.KeySize*8 << ");\n";
            ExistingIDs.push_back(counts);
            counts--;
        }
    }

    /**< Create RoundKey */
    myfile << "\tdynamic_bitset<> resultKey;\n\n";

    /**< Specifies a for loop for the number of rounds */
    myfile << "\tfor (int round = 0; round < " << Props.NumRounds << "; round++) {\n";

    /**< Assign Key for each Round */
    for (int i = 0; i < Props.NumRounds; i++) {
        myfile << "\t\tif (round == " << i << ") {\n";
        myfile << "\t\t\t resultKey = result_" << i+1 << ";\n";
        myfile << "\t\t}\n";
    }

    /**< Outputs the encrypt nodes to the file */
    int lastID = AppendFunctionF(Encrypt, myfile, ExistingIDs, Props.KeySize);

    /**< Convert string to bitset */
    myfile << "\t\treturnval.erase(returnval.begin(), returnval.end());\n";
    myfile << "\t\tfor (int i = 0; i < initial.length(); i++) {\n";
    myfile << "\t\t\tdynamic_bitset<> tmp;\n";
    myfile << "\t\t\tfor (int l = 0; l < 8; l++) {\n";
    myfile << "\t\t\t\ttmp.push_back(result" << KeyIDCheck(lastID) << "[result" << KeyIDCheck(lastID) << ".size() - l - 1]);\n";
    myfile << "\t\t\t}\n";
    myfile << "\t\t\tunsigned long temp = tmp.to_ulong();\n";
    myfile << "\t\t\tunsigned char ctemp = (unsigned char)temp;\n";
    myfile << "\t\t\treturnval.insert(returnval.begin(), ctemp);\n";
    myfile << "\t\t\tdynamic_bitset<> rtemp = result" << KeyIDCheck(lastID) << ";\n";
    myfile << "\t\t\trtemp.resize(result" << KeyIDCheck(lastID) << ".size() - 8);\n";
    myfile << "\t\t\tfor (int l = 0; l < rtemp.size(); l++) {\n";
    myfile << "\t\t\t\trtemp[rtemp.size() - l - 1] = result" << KeyIDCheck(lastID) << "[result" << KeyIDCheck(lastID) << ".size() - l - 1];\n";
    myfile << "\t\t\t}\n";
    myfile << "\t\t\tresult" << KeyIDCheck(lastID) << " = rtemp;\n";
    myfile << "\t\t}\n";
    myfile << "\t}\n";

    myfile << "\n\treturn returnval;\n}\n";

    /**< DECRYPT block*/
    ExistingIDs.clear();
    counts = 0;

    ExistingIDs.push_back(counts);
    counts--;

    myfile << "\nstring Decrypt(string initial, string initialkey) {\n";
    /**< Convert string to bitset for initial input and keys */
    myfile << "\tdynamic_bitset<> result0 (initial.length()*8);\n\n";
    myfile << "\tstring * key = Keygen(initialkey);\n";
    myfile << "\tfor (int i = 0; i < initial.length(); i++) {\n";
    myfile << "\t\tunsigned char c = initial[i];\n";
    myfile << "\t\tfor (int j = 7; j >= 0 && c; j--) {\n";
    myfile << "\t\t\tif (c & 0x1) {\n";
    myfile << "\t\t\t\tresult0.set(8*i+j);\n";
    myfile << "\t\t\t}\n";
    myfile << "\t\t\tc >>= 1;\n";
    myfile << "\t\t}\n";
    myfile << "\t}\n";

    myfile << "\tresult0.resize(" << Props.BlockSize*8 << ");\n\tstring returnval;\n";
    if (Props.NumRounds != 0) {
        for (int i = 1; i < Props.NumRounds+1; i++) {
            myfile << "\tdynamic_bitset<> result_" << i << "(key[" << i-1 << "].length()*8);\n";
            myfile << "\tfor (int i = 0; i < key[" << i-1 << "].length(); i++) {\n";
            myfile << "\t\tunsigned char c = key[" << i-1 << "][i];\n";
            myfile << "\t\tfor (int j = 7; j >= 0 && c; j--) {\n";
            myfile << "\t\t\tif (c & 0x1) {\n";
            myfile << "\t\t\t\tresult_" << i << ".set(8*i+j);\n";
            myfile << "\t\t\t}\n";
            myfile << "\t\t\tc >>= 1;\n";
            myfile << "\t\t}\n";
            myfile << "\t}\n";
            myfile << "\tresult_" << i << ".resize(" << Props.KeySize*8 << ");\n";
            ExistingIDs.push_back(counts);
            counts--;
        }
    }

    /**< Create RoundKey */
    myfile << "\tdynamic_bitset<> resultKey;\n\n";

    /**< Specifies a for loop for the number of rounds */
    myfile << "\tfor (int round = 0; round < " << Props.NumRounds << "; round++) {\n";

    /**< Assign Key for each Round */
    for (int i = 0; i < Props.NumRounds; i++) {
        myfile << "\t\tif (round == " << i << ") {\n";
        myfile << "\t\t\t resultKey = result_" << i+1 << ";\n";
        myfile << "\t\t}\n";
    }

    /**< Output Decrypt Nodes */
    lastID = AppendFunctionF(Decrypt, myfile, ExistingIDs, Props.KeySize);

    /**< Convert string to bitset */
    myfile << "\t\treturnval.erase(returnval.begin(), returnval.end());\n";
    myfile << "\t\tfor (int i = 0; i < initial.length(); i++) {\n";
    myfile << "\t\t\tdynamic_bitset<> tmp;\n";
    myfile << "\t\t\tfor (int l = 0; l < 8; l++) {\n";
    myfile << "\t\t\t\ttmp.push_back(result" << KeyIDCheck(lastID) << "[result" << KeyIDCheck(lastID) << ".size() - l - 1]);\n";
    myfile << "\t\t\t}\n";
    myfile << "\t\t\tunsigned long temp = tmp.to_ulong();\n";
    myfile << "\t\t\tunsigned char ctemp = (unsigned char)temp;\n";
    myfile << "\t\t\treturnval.insert(returnval.begin(), ctemp);\n";
    myfile << "\t\t\tdynamic_bitset<> rtemp = result" << KeyIDCheck(lastID) << ";\n";
    myfile << "\t\t\trtemp.resize(result" << KeyIDCheck(lastID) << ".size() - 8);\n";
    myfile << "\t\t\tfor (int l = 0; l < rtemp.size(); l++) {\n";
    myfile << "\t\t\t\trtemp[rtemp.size() - l - 1] = result" << KeyIDCheck(lastID) << "[result" << KeyIDCheck(lastID) << ".size() - l - 1];\n";
    myfile << "\t\t\t}\n";
    myfile << "\t\t\tresult" << KeyIDCheck(lastID) << " = rtemp;\n";
    myfile << "\t\t}\n";
    myfile << "\t}\n";

    myfile << "\n\treturn returnval;\n}\n";

    /**< KEYGEN Block */
    ExistingIDs.clear();
    counts = 0;

    ExistingIDs.push_back(counts);
    counts--;

    myfile << "\nstring* Keygen(string initial) {\n";
    /**< Convert string to bitset for input*/
    myfile << "\tdynamic_bitset<> result0 (initial.length()*8);\n\n";
    myfile << "\tfor (int i = 0; i < initial.length(); i++) {\n";
    myfile << "\t\tunsigned char c = initial[i];\n";
    myfile << "\t\tfor (int j = 7; j >= 0 && c; j--) {\n";
    myfile << "\t\t\tif (c & 0x1) {\n";
    myfile << "\t\t\t\tresult0.set(8*i+j);\n";
    myfile << "\t\t\t}\n";
    myfile << "\t\t\tc >>= 1;\n";
    myfile << "\t\t}\n";
    myfile << "\t}\n";

    myfile << "\tresult0.resize(initial.length()*8);\n\tstring * returnval = new string[" << Props.NumRounds << "];\n";
    myfile << "\tint counter = 0;\n";

    /**< Outputs key generation functions */
    lastID = AppendFunctionF(KeyGen, myfile, ExistingIDs, Props.KeySize);

    myfile << "\n\treturn returnval;\n}\n";

    /**< Closes the created file */
    myfile.close();

    /**< Outputs the header file for the main driver cpp file */
    ofstream hfile;
    string hname = DestLocale;
    hname.append("\\block.h");
    hfile.open(hname.c_str());
    hfile << "#include <iostream>\n#include <string>\n#include <boost/dynamic_bitset.hpp>\nusing namespace boost;\nusing namespace std;\n\n";
    hfile << "string Encrypt(string, string);\n";
    hfile << "string Decrypt(string, string);\n";
    hfile << "string* Keygen(string);\n";
    hfile.close();
}

/** \brief
 * KeyIDCheck checks whether the ID is negative and fixes it so it can be used as a variable identifier
 *
 * \param
 * ID is the id to be checked
 *
 * \return
 * The string of the fixed ID
 *
 */
string OutputRound::KeyIDCheck(int ID) {
    string result;
    stringstream ss;
    /**< Converts the ID to a string */
    ss << ID;
    result = ss.str();

    /**< Replaces - with _ */
    if (ID < 0) {
        result = "Key";
    }

    return result;
}

/** \brief
 * AppendFunctionF outputs the nodes from the vector to the main cpp file
 *
 * \param
 * Head is the vector of nodes to output
 *
 * \param
 * myfile is the file output stream to the created cpp file
 *
 * \param
 * ExistingIDs is a vector of IDs that already exist, so the same ID is not declared multiple times
 *
 * \param
 * KeySize is the size of the key
 *
 * \return
 *
 */
int OutputRound::AppendFunctionF(vector<Node> Head, ofstream& myfile, vector<int>& ExistingIDs, int KeySize) {
    int ID;

    /**< Cycles through the vector of nodes */
    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node temp = *it;

        if (temp.type == 0) {
            if (temp.NumInputs == temp.NumOutputs) {
                /**< Prints PBox with one to one input output */
                /**< Creates array for the function */
                myfile << "\t\tunsigned long * array" << KeyIDCheck(temp.ID) << " = new unsigned long[" << temp.outputs[0].positions[0] << "];\n";
                for (int i = 1; i < temp.outputs[0].positions[0]+1; i++) {
                    myfile << "\t\tarray" << KeyIDCheck(temp.ID) << "[" << i-1 << "] = " << temp.outputs[0].positions[i] << ";\n";
                }

                /**< Calls the one to one pbox function */
                bool ExistCheck = false;
                for (vector<int>::iterator it2 = ExistingIDs.begin(); it2 != ExistingIDs.end(); it2++) {
                    int EID = *it2;
                    /**< Checks if output exists already */
                    if (EID == temp.outputs[0].InputConID) {
                        ExistCheck = true;
                    }
                }
                myfile << "\t\t";
                if (ExistCheck == false) {
                    /**< If it doesnt exist, declare it */
                    myfile << "dynamic_bitset<> ";
                    ExistingIDs.push_back(temp.outputs[0].InputConID);
                }
                myfile << "result" << KeyIDCheck(temp.outputs[0].InputConID) << " = PBoxOneToOne(array";
                myfile << KeyIDCheck(temp.ID) << ", result" << temp.inputs[0].InputConID << ", ";
                myfile << temp.outputs[0].InputSizes << ");\n";

                /**< Deletes table */
                myfile << "\t\tdelete [] array" << KeyIDCheck(temp.ID) << ";\n";
                ID = temp.outputs[0].InputConID;
            } else {
                if (temp.NumInputs > temp.NumOutputs) {
                    /**< Prints PBox with multiple inputs to one output */
                    /**< Creates array for the function */
                    myfile << "\t\tunsigned long * array" << KeyIDCheck(temp.ID) << " = new unsigned long[" << temp.outputs[0].positions[0] << "];\n";
                    for (int i = 1; i < temp.outputs[0].positions[0]+1; i++) {
                        myfile << "\t\tarray" << KeyIDCheck(temp.ID) << "[" << i-1 << "] = " << temp.outputs[0].positions[i] << ";\n";
                    }

                    /**< Creates table for the inputs for the function */
                    myfile << "\t\tunsigned long * table" << KeyIDCheck(temp.ID) << " = new unsigned long[" << temp.NumInputs << "];\n";
                    for (int i = 0; i < temp.NumInputs; i++) {
                        myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "[" << i << "] = result" << temp.inputs[i].InputConID << ".to_ulong();\n";
                    }

                    /**< Calls the multiple inputs to single output function */
                    bool ExistCheck = false;
                    for (vector<int>::iterator it2 = ExistingIDs.begin(); it2 != ExistingIDs.end(); it2++) {
                        int EID = *it2;
                        /**< Checks if output exists already */
                        if (EID == temp.outputs[0].InputConID) {
                            ExistCheck = true;
                        }
                    }
                    myfile << "\t\t";
                    if (ExistCheck == false) {
                        /**< If it doesnt exist declare it */
                        myfile << "dynamic_bitset<> ";
                        ExistingIDs.push_back(temp.outputs[0].InputConID);
                    }
                    myfile << "result" << KeyIDCheck(temp.outputs[0].InputConID) << " = PBoxSingleOut(table";
                    myfile << KeyIDCheck(temp.ID) << ", " << temp.NumInputs << ", " << temp.inputs[0].InputSizes << ", ";
                    myfile << temp.outputs[0].InputSizes << ", array" << KeyIDCheck(temp.ID) << ");\n";

                    /**< Deletes the dynamic arrays and tables */
                    myfile << "\t\tdelete [] array" << KeyIDCheck(temp.ID) << ";\n";
                    myfile << "\t\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";
                    ID = temp.outputs[0].InputConID;
                } else {
                    /**< Prints PBox with multiple outputs with one input */
                    /**< Create 2D array of permutated positions */
                    myfile << "\t\tunsigned long ** table" << KeyIDCheck(temp.ID) << " = new unsigned long*[" << temp.NumOutputs << "];\n";
                    myfile << "\t\tfor(int i = 0; i < " << temp.NumOutputs << "; i++) {\n";
                    myfile << "\t\t\ttable" << KeyIDCheck(temp.ID) << "[i] = new unsigned long[" << temp.outputs[0].InputSizes << "];\n";
                    myfile << "\t\t}\n";
                    for (int i = 0; i < temp.NumOutputs; i++) {
                        for (int l = 1; l < temp.outputs[0].InputSizes+1; l++) {
                            myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "[" << i << "][" << l-1 << "] = " << temp.outputs[i].positions[l] << ";\n";
                        }
                    }

                    /**< Calls Pbox Multiple outputs to single input function */
                    myfile << "\t\tunsigned long * array" << KeyIDCheck(temp.ID) << " = PBoxMultiOuts(result" << KeyIDCheck(temp.inputs[0].InputConID);
                    myfile << ", " << temp.NumOutputs << ", " << temp.outputs[0].InputSizes;
                    myfile << ", table" << KeyIDCheck(temp.ID) << ");\n";

                    /**< Assign to multiple outputs */
                    for (int i = 0; i < temp.NumOutputs; i++) {
                        bool ExistCheck = false;
                        for (vector<int>::iterator it2 = ExistingIDs.begin(); it2 != ExistingIDs.end(); it2++) {
                            int EID = *it2;
                            /**< Checks if output exists already */
                            if (EID == temp.outputs[i].InputConID) {
                                ExistCheck = true;
                            }
                        }
                        myfile << "\t\t";
                        if (ExistCheck == false) {
                            /**< If it doesnt exist declare it */
                            myfile << "dynamic_bitset<> ";
                            ExistingIDs.push_back(temp.outputs[i].InputConID);
                        }
                        myfile << "result" << temp.outputs[i].InputConID << " (" << temp.outputs[0].InputSizes << ", array" << KeyIDCheck(temp.ID) << "[" << i << "]);\n";
                    }

                    /**< delete dynamics */
                    myfile << "\t\tdelete [] array" << KeyIDCheck(temp.ID) << ";\n";
                    myfile << "\t\tfor (int i = 0; i < " << temp.NumOutputs << "; i++) {\n";
                    myfile << "\t\t\tdelete[] table" << KeyIDCheck(temp.ID) << "[i];\n";
                    myfile << "\t\t}\n";
                    myfile << "\t\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";
                }
            }
        } else if (temp.type == 1) {
            /**< Prints SBox */
            /**< Prints SBox 2D table */
            myfile << "\t\tunsigned long ** table" << KeyIDCheck(temp.ID) << " = new unsigned long*[" << temp.rows << "];\n";
            myfile << "\t\tfor(int i = 0; i < " << temp.rows << "; i++) {\n";
            myfile << "\t\t\ttable" << KeyIDCheck(temp.ID) << "[i] = new unsigned long[" << temp.cols << "];\n";
            myfile << "\t\t}\n";
            for (int i = 0; i < temp.rows; i++) {
                for (int l = 0; l < temp.cols; l++) {
                    myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "["<< i << "][" << l << "] = " << temp.table[i][l] << ";\n";
                }
            }

            /**< Calls SBox function */
            bool ExistCheck = false;
            for (vector<int>::iterator it2 = ExistingIDs.begin(); it2 != ExistingIDs.end(); it2++) {
                int EID = *it2;
                /**< Checks if output exists already */
                if (EID == temp.outputs[0].InputConID) {
                    ExistCheck = true;
                }
            }
            myfile << "\t\t";
            if (ExistCheck == false) {
                /**< If it doesnt exist, declare it */
                myfile << "dynamic_bitset<> ";
                ExistingIDs.push_back(temp.outputs[0].InputConID);
            }
            myfile << "result" << KeyIDCheck(temp.outputs[0].InputConID) << " = CustomSBoxSearch(table" << KeyIDCheck(temp.ID);
            myfile << ", result" << KeyIDCheck(temp.inputs[0].InputConID) << ", " << KeyIDCheck(temp.rows);
            myfile << ", " << KeyIDCheck(temp.cols) << ", " << temp.outputs[0].InputSizes << ");\n";

            /**< Deletes table for sbox */
            ID = temp.outputs[0].InputConID;
            myfile << "\t\tfor (int i = 0; i < " << temp.rows << "; i++) {\n";
            myfile << "\t\t\tdelete [] table" << KeyIDCheck(temp.ID) << "[i];\n";
            myfile << "\t\t}\n";
            myfile << "\t\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";

            ID = temp.outputs[0].InputConID;
        } else if (temp.type == 2) {
            /**< Prints XOR */
            bool ExistCheck = false;
            for (vector<int>::iterator it2 = ExistingIDs.begin(); it2 != ExistingIDs.end(); it2++) {
                int EID = *it2;
                /**< Checks if output exists already */
                if (EID == temp.outputs[0].InputConID) {
                    ExistCheck = true;
                }
            }
            myfile << "\t\t";
            if (ExistCheck == false) {
                /**< If it doesnt exist, declare it */
                myfile << "dynamic_bitset<> ";
                ExistingIDs.push_back(temp.outputs[0].InputConID);
            }
            /**< Calls XOR function */
            myfile << "result" << KeyIDCheck(temp.ID) << " = CustomXOR(result" << KeyIDCheck(temp.inputs[0].InputConID) << ", result";
            myfile << KeyIDCheck(temp.inputs[1].InputConID) << ");\n";

            ID = temp.outputs[0].InputConID;
        } else if (temp.type == 3) {
            /**< Call the function */
            ID = AppendFunctionF(temp.Next, myfile, ExistingIDs, KeySize);
        } else if (temp.type == 4) {
            /**< Assign subkey to a string */
            /**< Convert string to bitset */
            myfile << "\t\tdynamic_bitset<> temporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << " = result" << KeyIDCheck(temp.inputs[0].InputConID) << ";\n";
            myfile << "\t\tfor (int i = 0; i < " << KeySize << "; i++) {\n";
            myfile << "\t\t\tdynamic_bitset<> tmp;\n";
            myfile << "\t\t\tfor (int l = 0; l < 8; l++) {\n";
            myfile << "\t\t\t\ttmp.push_back(temporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << "[temporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << ".size() - l - 1]);\n";
            myfile << "\t\t\t}\n";
            myfile << "\t\t\tunsigned long temp = tmp.to_ulong();\n";
            myfile << "\t\t\tunsigned char ctemp = (unsigned char)temp;\n";
            myfile << "\t\t\treturnval[counter].insert(returnval[counter].begin(), ctemp);\n";
            myfile << "\t\t\tdynamic_bitset<> rtemp = temporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << ";\n";
            myfile << "\t\t\trtemp.resize(temporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << ".size() - 8);\n";
            myfile << "\t\t\tfor (int l = 0; l < rtemp.size(); l++) {\n";
            myfile << "\t\t\t\trtemp[rtemp.size() - l - 1] = temporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << "[temporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << ".size() - l - 1];\n";
            myfile << "\t\t\t}\n";
            myfile << "\t\t\ttemporaryres" << KeyIDCheck(temp.inputs[0].InputConID) << " = rtemp;\n";
            myfile << "\t\t}\n";
            myfile << "\t\tcounter++;\n";
        }
    }

    /**< Returns the last node outputted ID */
    return ID;
}

/** \brief
 * OutputGenerics copies the generic files from the source path to the  destination path
 *
 * \param
 * NodeTypes tells us which parts of the Generics file we can copy
 *
 */
void OutputRound::OutputGenerics(bool NodeTypes[]) {
    string str;
    ifstream hfile;
    ifstream cfile;

    ofstream headerfile;
    ofstream codefile;

    /**< Copy Destination and Source folder locations */
    string Dhfile = DestLocale;
    string Dcppfile = DestLocale;

    string Shfile = SourceLocale;
    string Scppfile = SourceLocale;

    /**< Append filename */
    Dhfile.append("\\GenericFunctions.h");
    Dcppfile.append("\\GenericFunctions.cpp");

    Shfile.append("\\GenericFunctions.h");
    Scppfile.append("\\GenericFunctions.cpp");

    headerfile.open(Dhfile.c_str());
    codefile.open(Dcppfile.c_str());

    hfile.open(Shfile.c_str());
    cfile.open(Scppfile.c_str());

    /**< Header file copy start */
    for (int i = 0; i < 12; i++) {
        getline(hfile, str);
        headerfile << str;
        headerfile << "\n";
    }

    /**< Cpp file copy start */
    for (int i = 0; i < 16; i++) {
        getline(cfile, str);
        codefile << str;
        codefile << "\n";
    }

    /**< Check Node present and outputs related function */
     if (NodeTypes[2] == true) {
        /**< Header file copy XOR*/
        getline(hfile, str);
        headerfile << str;
        headerfile << "\n";

        /**< Cpp file copy */
        for (int i = 0; i < 19; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skips the xor block */
        getline(hfile, str);

        for (int i = 0; i < 19; i++) {
            getline(cfile, str);
        }
    }

    if (NodeTypes[1] == true) {
        /**< Header file copy SBOX*/
        getline(hfile, str);
        headerfile << str;
        headerfile << "\n";

        /**< Cpp file copy */
        for (int i = 0; i < 71; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skips SBOX block */
        getline(hfile, str);

        for (int i = 0; i < 71; i++) {
            getline(cfile, str);
        }
    }

    if (NodeTypes[0] == true) {
        /**< Header file copy PBOX*/
        for (int i = 0; i < 3; i++) {
            getline(hfile, str);
            headerfile << str;
            headerfile << "\n";
        }

        /**< Cpp file copy */
        for (int i = 0; i < 121; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skip PBox */
        for (int i = 0; i < 3; i++) {
            getline(hfile, str);
        }

        for (int i = 0; i < 121; i++) {
            getline(cfile, str);
        }
    }

    /**< Header file copy end*/
    while(!hfile.eof()) {
        getline(hfile, str);
        headerfile << str;
        headerfile << "\n";
    }

    /**< Cpp file copy */
    while (!cfile.eof()) {
        getline(cfile, str);
        codefile << str;
        codefile << "\n";
    }

    /**< Closes all files */
    hfile.close();
    headerfile.close();
    cfile.close();
    codefile.close();
}
