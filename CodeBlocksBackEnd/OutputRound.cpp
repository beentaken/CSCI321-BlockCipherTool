/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   OutputCode.cpp
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 12:48 PM
 */

#include "OutputRound.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
using namespace std;

OutputRound::OutputRound() {

}

OutputRound::~OutputRound() {

}

bool OutputRound::ReadSource(string input) {
    SourceLocale = input;

    return true;
}

bool OutputRound::ReadDest(string input) {
    DestLocale = input;

    return true;
}

vector<Node> OutputRound::SortVec(vector<Node> Head, int NumOfKeys) {
    vector<Node> result;
    vector<int> ConnIDs;    /**< connection IDs created */

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
                            if (temp.ID == t.ID && temp.type != 4) {
                                added = true;
                            }
                            if (temp.ID == t.ID && t.type == 4) {
                                added = true;
                            }
                        }
                    }

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

    return result;
}

void OutputRound::CheckNode(vector<Node> Head, bool NodeTypes[], vector<Node>& H) {

    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node Temp = *it;

        if (Temp.type == 0) {
            H.push_back(Temp);
            NodeTypes[0] = true;
        } else if (Temp.type == 1) {
            NodeTypes[1] = true;
            H.push_back(Temp);
        } else if (Temp.type == 2) {
            NodeTypes[2] = true;
            H.push_back(Temp);
        } else if (Temp.type == 3) {
            CheckNode(Temp.Next, NodeTypes, H);
        } else if (Temp.type == 4) {
            H.push_back(Temp);
        }
    }
}

bool OutputRound::OutputToFile(vector<Node> Encrypt, vector<Node> Decrypt, vector<Node> KeyGen, Properties Props) {
    vector<Node> E;
    vector<Node> D;
    vector<Node> K;
    bool NodeTypes[3];  /**< Finds out which cipher node blocks have been used */

    for (int i = 0; i < 3; i++) {
        NodeTypes[i] = false;
    }

    CheckNode(Encrypt, NodeTypes, E);
    CheckNode(Decrypt, NodeTypes, D);
    CheckNode(KeyGen, NodeTypes, K);

    E = SortVec(E, Props.NumKey);
    D = SortVec(D, Props.NumKey);
    K = SortVec(K, Props.NumKey);

    OutputGenerics(NodeTypes);
    OutputMain(E, D, K, Props);

    return true;
}

void OutputRound::OutputMain(vector<Node> Encrypt, vector<Node> Decrypt, vector<Node> KeyGen, Properties Props) {
    vector<int> ExistingIDs;
    int counts = 0;
    ofstream myfile;
    string fname = DestLocale;
    fname.append("\\block.cpp");

    ExistingIDs.push_back(counts);
    counts--;
    myfile.open(fname.c_str());
    /**< ENCRYPT */

    myfile << "#include <iostream>\n#include <string>\n#include <boost/dynamic_bitset.hpp>\n#include \"block.h\"\n#include \"GenericFunctions.h\"\nusing namespace std;\nusing namespace boost;\n\nstring Encrypt(string initial, string initialkey) {\n";
    /**< Convert string to bitset */
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
    if (Props.NumKey != 0) {
        for (int i = 1; i < Props.NumKey+1; i++) {
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

    myfile << "\tfor (int round = 0; round < " << Props.NumRounds << "; round++) {\n";

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

    /**< DECRYPT */
    ExistingIDs.clear();
    counts = 0;

    ExistingIDs.push_back(counts);
    counts--;

    myfile << "\nstring Decrypt(string initial, string initialkey) {\n";
    /**< Convert string to bitset */
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
    if (Props.NumKey != 0) {
        for (int i = 1; i < Props.NumKey+1; i++) {
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

    myfile << "\tfor (int round = 0; round < " << Props.NumRounds << "; round++) {\n";

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

    /**< KEYGEN */
    ExistingIDs.clear();
    counts = 0;

    ExistingIDs.push_back(counts);
    counts--;

    myfile << "\nstring* Keygen(string initial) {\n";
    /**< Convert string to bitset */
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

    myfile << "\tresult0.resize(initial.length()*8);\n\tstring * returnval = new string[" << Props.NumKey << "];\n";
    myfile << "\tint counter = 0;\n";

    lastID = AppendFunctionF(KeyGen, myfile, ExistingIDs, Props.KeySize);

    myfile << "\n\treturn returnval;\n}\n";

    myfile.close();

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

string OutputRound::KeyIDCheck(int ID) {
    string result;
    stringstream ss;
    ss << ID;
    result = ss.str();

    if (ID < 0) {
        replace(result.begin(), result.end(), '-', '_');
    }

    return result;
}

int OutputRound::AppendFunctionF(vector<Node> Head, ofstream& myfile, vector<int>& ExistingIDs, int KeySize) {
    int ID;

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
                myfile << "dynamic_bitset<> ";
                ExistingIDs.push_back(temp.outputs[0].InputConID);
            }
            /**< Calls XOR function */
            myfile << "result" << KeyIDCheck(temp.ID) << " = CustomXOR(result" << KeyIDCheck(temp.inputs[0].InputConID) << ", result";
            myfile << KeyIDCheck(temp.inputs[1].InputConID) << ");\n";

            ID = temp.outputs[0].InputConID;
        } else if (temp.type == 3) {
            ID = AppendFunctionF(temp.Next, myfile, ExistingIDs, KeySize);
        } else if (temp.type == 4) {
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

    return ID;
}

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
        for (int i = 0; i < 117; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skip PBox */
        for (int i = 0; i < 3; i++) {
            getline(hfile, str);
        }

        for (int i = 0; i < 117; i++) {
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

    hfile.close();
    headerfile.close();
    cfile.close();
    codefile.close();
}
