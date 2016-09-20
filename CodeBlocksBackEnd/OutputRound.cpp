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

vector<Node> OutputRound::SortVec(vector<Node> Head) {
    vector<Node> result;
    vector<int> ConnIDs;    /**< connection IDs created */

    ConnIDs.push_back(0);
    ConnIDs.push_back(-1);
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
    bool check = false;

    for (vector<Node>::iterator it = Head.begin(); it != Head.end() && check == false; it++) {
        if (NodeTypes[0] == true && NodeTypes[1] == true && NodeTypes[2] == true) {
            check = true;
        }
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

    H = SortVec(H);

    OutputGenerics(NodeTypes);
    OutputMain(H, Props);

    return true;
}

void OutputRound::OutputMain(vector<Node> Head, Properties Props) {
    ofstream myfile;
    string fname = DestLocale;
    fname.append("\\main.cpp");

    myfile.open(fname.c_str());
    myfile << "#include <iostream>\n#include \"GenericFunctions.h\"\nusing namespace std;\n\nint main() {\n";
    myfile << "\tint result0;\n";
    myfile << "\tcout << \"Please enter the input in binary!\" << endl;\n";
    myfile << "\tcin >> result0;\n\n";

    bool addedXOR = false;
    AppendFunctionF(Head, myfile, addedXOR);

    myfile << "\n\treturn 0;\n}";
    myfile.close();
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

void OutputRound::AppendFunctionF(vector<Node> Head, ofstream& myfile, bool& addedXOR) {
    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node temp = *it;
        if (temp.type == 0) {
            if (temp.NumInputs == temp.NumOutputs) {
                /**< Prints PBox 2D table */
                myfile << "\tint ** table" << KeyIDCheck(temp.ID) << " = new int*[" << temp.rows << "];\n";
                myfile << "\tfor(int i = 0; i < " << temp.rows << "; i++) {\n";
                myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "[i] = new int[" << temp.cols << "];\n";
                myfile << "\t}\n";
                for (int i = 0; i < temp.rows; i++) {
                    for (int l = 0; l < temp.cols; l++) {
                        myfile << "\ttable" << KeyIDCheck(temp.ID) << "["<< i << "][" << l << "] = " << temp.table[i][l] << ";\n";
                    }
                }

                myfile << "\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = CustomPBoxSearch(table" << KeyIDCheck(temp.ID);
                myfile << ", result" << KeyIDCheck(temp.inputs[0].InputConID) << ");\n";

                myfile << "\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";
            } else {
                if (temp.NumInputs > temp.NumOutputs) {
                    /**< Prints PBox 1D table of inputs */
                    myfile << "\tint table" << KeyIDCheck(temp.ID) << "[" << temp.NumInputs << "] = {";
                    for (int i = 0; i < temp.NumInputs; i++) {
                        myfile << "result" << KeyIDCheck(temp.inputs[i].InputConID);
                        if (i == (temp.NumInputs-1)) {
                            myfile << "};\n";
                        } else {
                            myfile << ",";
                        }
                    }

                    myfile << "\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = PBoxJoin(table" << KeyIDCheck(temp.ID);
                    myfile << ", " << temp.NumInputs << ");\n";
                } else {
                    myfile << "\tint * table" << KeyIDCheck(temp.ID) << " = PBoxSplit(result" << KeyIDCheck(temp.inputs[0].InputConID);
                    myfile << ", " << temp.NumOutputs << ");\n";
                    for (int i = 0; i < temp.NumOutputs; i++) {
                        myfile << "\tint result" << KeyIDCheck(temp.outputs[i].InputConID) << " = table" << KeyIDCheck(temp.ID) << "[" << i << "];\n";
                    }

                    myfile << "\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";
                }
            }
        } else if (temp.type == 1) {
            /**< Prints SBox 2D table */
            myfile << "\tint ** table" << KeyIDCheck(temp.ID) << " = new int*[" << temp.rows << "];\n";
            myfile << "\tfor(int i = 0; i < " << temp.rows << "; i++) {\n";
            myfile << "\t\ttable" << KeyIDCheck(temp.ID) << "[i] = new int[" << temp.cols << "];\n";
            myfile << "\t}\n";
            for (int i = 0; i < temp.rows; i++) {
                for (int l = 0; l < temp.cols; l++) {
                    myfile << "\ttable" << KeyIDCheck(temp.ID) << "["<< i << "][" << l << "] = " << temp.table[i][l] << ";\n";
                }
            }

            myfile << "\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = CustomSBoxSearch(table" << KeyIDCheck(temp.ID);
            myfile << ", result" << KeyIDCheck(temp.inputs[0].InputConID) << ");\n";

            myfile << "\tdelete [] table" << KeyIDCheck(temp.ID) << ";\n";
        } else if (temp.type == 2) {
            myfile << "\tstring temp" << KeyIDCheck(temp.ID) << " = CustomXOR(result" << KeyIDCheck(temp.inputs[0].InputConID) << ", result";
            myfile << KeyIDCheck(temp.inputs[1].InputConID) << ");\n";
            myfile << "\tint result" << KeyIDCheck(temp.outputs[0].InputConID) << " = StringToNumber(temp" << KeyIDCheck(temp.ID) << ");\n";

            if (addedXOR == false) {
                AppendConversions();
                addedXOR = true;
            }
        } else if (temp.type == 3) {
            AppendFunctionF(temp.Next, myfile, addedXOR);
        }
    }
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
    for (int i = 0; i < 15; i++) {
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
        for (int i = 0; i < 13; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skips the xor block */
        getline(hfile, str);

        for (int i = 0; i < 13; i++) {
            getline(cfile, str);
        }
    }

    if (NodeTypes[1] == true) {
        /**< Header file copy SBOX*/
        getline(hfile, str);
        headerfile << str;
        headerfile << "\n";

        /**< Cpp file copy */
        for (int i = 0; i < 28; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skips SBOX block */
        getline(hfile, str);

        for (int i = 0; i < 28; i++) {
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
        for (int i = 0; i < 45; i++) {
            getline(cfile, str);
            codefile << str;
            codefile << "\n";
        }
    } else {
        /**< Skip PBox */
        for (int i = 0; i < 3; i++) {
            getline(hfile, str);
        }

        for (int i = 0; i < 45; i++) {
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
