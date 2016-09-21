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
                            if (temp.ID == t.ID) {
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
        }
    }
}

bool OutputRound::OutputToFile(vector<Node> Head, Properties Props) {
    vector<Node> H;
    bool NodeTypes[3];  /**< Finds out which cipher node blocks have been used */

    for (int i = 0; i < 3; i++) {
        NodeTypes[i] = false;
    }

    CheckNode(Head, NodeTypes, H);

    H = SortVec(H, Props.NumKey);

    OutputGenerics(NodeTypes);
    OutputMain(H, Props);

    return true;
}

void OutputRound::OutputMain(vector<Node> Head, Properties Props) {
    bool addedXOR = false;
    int sizeID = 0;
    ofstream myfile;
    string fname = DestLocale;
    fname.append("\\block.cpp");

    myfile.open(fname.c_str());
    myfile << "#include <iostream>\n#include <string>\n#include <sstream>\n#include \"block.h\"\n#include \"GenericFunctions.h\"\nusing namespace std;\n\nstring Block(string initial, string* key) {\n";
    myfile << "\tint result0 = StringToNumber(initial);\n\tstring returnval;\n\tint result_1;\n\tint result_2;\n";
    if (Props.NumKey != 0) {
        for (int i = 1; i < Props.NumKey+1; i++) {
            myfile << "\tresult_" << i << " = StringToNumber(key[" << i-1 << "]);\n";
        }
        addedXOR = true;
        AppendConversions();
    }
    myfile << "\tfor (int round = 0; round < " << Props.NumRounds << "; round++) {\n";

    int lastID = AppendFunctionF(Head, myfile, addedXOR, sizeID);

    myfile << "\t\tstringstream ss;\n";
    myfile << "\t\tss << result" << KeyIDCheck(lastID) << ";\n";
    myfile << "\t\tss >> returnval;\n";
    myfile << "\t}";

    myfile << "\twhile (returnval.length() < " << sizeID << ") {\n";
    myfile << "\t\treturnval.insert(returnval.begin(), '0');\n";
    myfile << "\t}\n;";
    myfile << "\n\treturn returnval;\n}";
    myfile.close();

    ofstream hfile;
    string hname = DestLocale;
    hname.append("\\block.h");
    hfile.open(hname.c_str());
    hfile << "#include <iostream>\n#include <string>\n\nusing namespace std;\n\n";
    hfile << "string Block(string, string*);\n";
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

void OutputRound::AppendConversions() {
    string Dhfile = DestLocale;
    string Dcppfile = DestLocale;

    Dhfile.append("\\GenericFunctions.h");
    Dcppfile.append("\\GenericFunctions.cpp");

    ofstream headerfile;
    headerfile.open(Dhfile.c_str(), ios::out | ios::app);

    ofstream cppfile;
    cppfile.open(Dcppfile.c_str(), ios::out | ios::app);

    /**< Headerfile */
    headerfile << "int StringToNumber(string);\n";
    headerfile.close();

    /**< CPPfile */
    cppfile << "\nint StringToNumber(string input) {\tstringstream convert;\n";
    cppfile << "\tint result = (-1);\n";
    cppfile << "\tint len = input.length();\n";
    cppfile << "\tfor (int i = 0; i < len; i++) {\n";
    cppfile << "\t\tif (!isdigit(input[i])) {\n";
    cppfile << "\t\tinput[i] = ' ';\n";
    cppfile << "\t\t}\n";
    cppfile << "\t}\n";
    cppfile << "\tinput.erase(remove(input.begin(), input.end(), ' '), input.end());\n";
    cppfile << "\tbool emptycheck = false;\n";
    cppfile << "\tfor (size_t i = 0; i < input.length() && emptycheck == false; i++) {\n";
    cppfile << "\t\tif (isspace(input[i])) {\n";
    cppfile << "\t\temptycheck = true;\n";
    cppfile << "\t\t}";
    cppfile << "\t}";
    cppfile << "\tif (emptycheck == false) {\n";
    cppfile << "\tconvert << input;\n";
    cppfile << "\tconvert >> result;\n";
    cppfile << "\t}\n";
    cppfile << "\treturn result;\n";
    cppfile << "}";
    cppfile.close();
}

int OutputRound::AppendFunctionF(vector<Node> Head, ofstream& myfile, bool& addedXOR, int& sizeID) {
    int ID;

    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node temp = *it;
        if (temp.type == 0) {
            if (temp.NumInputs == temp.NumOutputs) {
                /**< Prints PBox with one to one input output */
                /**< Creates array for the function */
                myfile << "\t\tint * array" << KeyIDCheck(temp.ID) << " = new int[" << temp.outputs[0].positions[0] << "];\n";
                for (int i = 1; i < temp.outputs[0].positions[0]+1; i++) {
                    myfile << "\t\tarray" << KeyIDCheck(temp.ID) << "[" << i-1 << "] = " << temp.outputs[0].positions[i] << ";\n";
                }

                /**< Calls the one to one pbox function */
                myfile << "\t\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = PBoxOneToOne(array";
                myfile << KeyIDCheck(temp.ID) << ", result" << temp.inputs[0].InputConID << ", " << temp.inputs[0].InputSizes;
                myfile << ", " << temp.outputs[0].InputSizes << ");\n";

                /**< Deletes table */
                myfile << "\t\tdelete [] array" << KeyIDCheck(temp.ID) << ";\n";
                ID = temp.outputs[0].InputConID;
                sizeID = temp.outputs[0].InputSizes;
            } else {
                if (temp.NumInputs > temp.NumOutputs) {
                    /**< Prints PBox with multiple inputs to one output */
                    /**< Creates array for the function */
                    myfile << "\t\tint * array" << KeyIDCheck(temp.ID) << " = new int[" << temp.outputs[0].positions[0] << "];\n";
                    for (int i = 1; i < temp.outputs[0].positions[0]+1; i++) {
                        myfile << "\t\tarray" << KeyIDCheck(temp.ID) << "[" << i-1 << "] = " << temp.outputs[0].positions[i] << ";\n";
                    }

                    /**< Creates table for the inputs for the function */
                    myfile << "\t\tint * table" << KeyIDCheck(temp.ID) << " = new int[" << temp.NumInputs << "];\n";
                    for (int i = 0; i < temp.NumInputs; i++) {
                        myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "[" << i << "] = result" << temp.inputs[i].InputConID << ";\n";
                    }

                    /**< Calls the multiple inputs to single output function */
                    myfile << "\t\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = PBoxSingleOut(table";
                    myfile << KeyIDCheck(temp.ID) << ", " << temp.NumInputs << ", " << temp.inputs[0].InputSizes << ", ";
                    myfile << temp.outputs[0].InputSizes << ", array" << KeyIDCheck(temp.ID) << ");\n";

                    /**< Deletes the dynamic arrays and tables */
                    myfile << "\t\tdelete [] array" << KeyIDCheck(temp.ID) << ";\n";
                    myfile << "\t\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";
                    ID = temp.outputs[0].InputConID;
                    sizeID = temp.outputs[0].InputSizes;
                } else {
                    /**< Prints PBox with multiple outputs with one input */
                    /**< Create 2D array of permutated positions */
                    myfile << "\t\tint ** table" << KeyIDCheck(temp.ID) << " = new int*[" << temp.NumOutputs << "];\n";
                    myfile << "\t\tfor(int i = 0; i < " << temp.NumOutputs << "; i++) {\n";
                    myfile << "\t\t\ttable" << KeyIDCheck(temp.ID) << "[i] = new int[" << temp.outputs[0].InputSizes << "];\n";
                    myfile << "\t\t}\n";
                    for (int i = 0; i < temp.NumOutputs; i++) {
                        for (int l = 1; l < temp.outputs[0].InputSizes+1; l++) {
                            myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "[" << i << "][" << l-1 << "] = " << temp.outputs[i].positions[l] << ";\n";
                        }
                    }

                    /**< Calls Pbox Multiple outputs to single input function */
                    myfile << "\t\tint * array" << KeyIDCheck(temp.ID) << " = PBoxMultiOuts(result" << KeyIDCheck(temp.inputs[0].InputConID);
                    myfile << ", " << temp.NumOutputs << ", " << temp.inputs[0].InputSizes << ", " << temp.outputs[0].InputSizes;
                    myfile << ", table" << KeyIDCheck(temp.ID) << ");\n";

                    /**< Assign to multiple outputs */
                    for (int i = 0; i < temp.NumOutputs; i++) {
                        myfile << "\t\tint result" << temp.outputs[i].InputConID << " = array" << KeyIDCheck(temp.ID) << "[" << i << "];\n";
                    }

                    /**< delete dynamics */
                    myfile << "\t\tdelete [] array" << KeyIDCheck(temp.ID) << ";\n";
                    myfile << "\t\tfor (int i = 0; i < " << temp.NumOutputs << "; i++) {\n";
                    myfile << "\t\t\tdelete[] table" << KeyIDCheck(temp.ID) << "[i];\n";
                    myfile << "\t\t}\n;";
                    myfile << "\t\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";
                }
            }
        } else if (temp.type == 1) {
            /**< Prints SBox */
            /**< Prints SBox 2D table */
            myfile << "\t\tint ** table" << KeyIDCheck(temp.ID) << " = new int*[" << temp.rows << "];\n";
            myfile << "\t\tfor(int i = 0; i < " << temp.rows << "; i++) {\n";
            myfile << "\t\t\ttable" << KeyIDCheck(temp.ID) << "[i] = new int[" << temp.cols << "];\n";
            myfile << "\t\t}\n";
            for (int i = 0; i < temp.rows; i++) {
                for (int l = 0; l < temp.cols; l++) {
                    myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "["<< i << "][" << l << "] = " << temp.table[i][l] << ";\n";
                }
            }

            /**< Calls SBox function */
            myfile << "\t\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = CustomSBoxSearch(table" << KeyIDCheck(temp.ID);
            myfile << ", result" << KeyIDCheck(temp.inputs[0].InputConID) << ", " << KeyIDCheck(temp.rows);
            myfile << ", " << KeyIDCheck(temp.cols) << ");\n";

            /**< Deletes table for sbox */
            ID = temp.outputs[0].InputConID;
            myfile << "\t\tfor (int i = 0; i < " << temp.rows << "; i++) {\n";
            myfile << "\t\t\tdelete [] table" << KeyIDCheck(temp.ID) << "[i];\n";
            myfile << "\t\t}\n";
            myfile << "\t\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";

            ID = temp.outputs[0].InputConID;
            sizeID = temp.outputs[0].InputSizes;
        } else if (temp.type == 2) {
            /**< Prints XOR */
            /**< Calls XOR function */
            myfile << "\t\tstring temp" << KeyIDCheck(temp.ID) << " = CustomXOR(result" << KeyIDCheck(temp.inputs[0].InputConID) << ", result";
            myfile << KeyIDCheck(temp.inputs[1].InputConID) << ", " << KeyIDCheck(temp.inputs[0].InputSizes) << ", ";
            myfile << KeyIDCheck(temp.inputs[1].InputSizes) << ");\n";
            myfile << "\t\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = StringToNumber(temp" << KeyIDCheck(temp.ID) << ");\n";

            ID = temp.outputs[0].InputConID;
            sizeID = temp.outputs[0].InputSizes;
            /**< Appends a string to int conversion method to the generic functions */
            if (addedXOR == false) {
                AppendConversions();
                addedXOR = true;
            }
        } else if (temp.type == 3) {
            ID = AppendFunctionF(temp.Next, myfile, addedXOR, sizeID);
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
    for (int i = 0; i < 10; i++) {
        getline(hfile, str);
        headerfile << str;
        headerfile << "\n";
    }

    /**< Cpp file copy start */
    for (int i = 0; i < 14; i++) {
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
        for (int i = 0; i < 52; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skips the xor block */
        getline(hfile, str);

        for (int i = 0; i < 52; i++) {
            getline(cfile, str);
        }
    }

    if (NodeTypes[1] == true) {
        /**< Header file copy SBOX*/
        getline(hfile, str);
        headerfile << str;
        headerfile << "\n";

        /**< Cpp file copy */
        for (int i = 0; i < 78; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skips SBOX block */
        getline(hfile, str);

        for (int i = 0; i < 78; i++) {
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
        for (int i = 0; i < 164; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skip PBox */
        for (int i = 0; i < 3; i++) {
            getline(hfile, str);
        }

        for (int i = 0; i < 164; i++) {
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
