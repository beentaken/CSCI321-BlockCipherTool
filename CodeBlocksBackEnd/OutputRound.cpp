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

bool OutputRound::OutputToFile(vector<Node> Head, Properties Props) {
    bool NodeTypes[3];  /**< Finds out which cipher node blocks have been used */
    bool check = false;

    for (int i = 0; i < 3; i++) {
        NodeTypes[i] = false;
    }

    for (vector<Node>::iterator it = Head.begin(); it != Head.end() && check == false; it++) {
        if (NodeTypes[0] == true && NodeTypes[1] == true && NodeTypes[2] == true) {
            check = true;
        }

        Node Temp = *it;

        if (Temp.type == 0) {
            NodeTypes[0] = true;
        } else if (Temp.type == 1) {
            NodeTypes[1] = true;
        } else if (Temp.type == 2) {
            NodeTypes[2] = true;
        }
    }

    OutputGenerics(NodeTypes);
    OutputMain(Head, Props);

    return true;
}

void OutputRound::OutputMain(vector<Node> Head, Properties Props) {
    ofstream myfile;
    string fname = DestLocale;
    fname.append("\\main.cpp");

    myfile.open(fname.c_str());
    myfile << "#include <iostream>\n#include \"GenericsFunctions.h\"\nusing namespace std;\n\nint main() {\n";

    bool addedXOR = false;
    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node temp = *it;

        if (temp.type == 0) {
            myfile << "\tint result";
            myfile << temp.ID;
            myfile << " = CustomPBoxSearch(result";
            myfile << temp.inputs[0].InputConID;
            myfile << ", result";
            myfile << temp.inputs[1].InputConID;
            myfile << ");\n";
        } else if (temp.type == 1) {
            myfile << "\tint result";
            myfile << temp.ID;
            myfile << " = CustomSBoxSearch(result";
            myfile << temp.inputs[0].InputConID;
            myfile << ", result";
            myfile << temp.inputs[1].InputConID;
            myfile << ");\n";
        } else if (temp.type == 2) {
            myfile << "\tstring temp";
            myfile << temp.ID;
            myfile << " = CustomXOR(result";
            myfile << temp.inputs[0].InputConID;
            myfile << ", result";
            myfile << temp.inputs[1].InputConID;
            myfile << ");\n";
            myfile << "\tint result";
            myfile << temp.ID;
            myfile << " = StringToNumber(temp";
            myfile << temp.ID;
            myfile << ");\n";

            if (addedXOR == false) {
                AppendConversions();
                addedXOR = true;
            }
        } else if (temp.type == 3) {
            AppendFunctionF(temp.Next, myfile);
        }
    }
    myfile << "\nreturn 0;\n}";
    myfile.close();
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

void OutputRound::AppendFunctionF(vector<Node> Head, ofstream& myfile) {
    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node temp = *it;

        if (temp.type == 0) {
            myfile << "\tint result";
            myfile << temp.ID;
            myfile << " = CustomPBoxSearch(result";
            myfile << temp.inputs[0].InputConID;
            myfile << ", result";
            myfile << temp.inputs[1].InputConID;
            myfile << ");\n";
        } else if (temp.type == 1) {
            myfile << "\tint result";
            myfile << temp.ID;
            myfile << " = CustomSBoxSearch(result";
            myfile << temp.inputs[0].InputConID;
            myfile << ", result";
            myfile << temp.inputs[1].InputConID;
            myfile << ");\n";
        } else if (temp.type == 2) {
            myfile << "\tstring result";
            myfile << temp.ID;
            myfile << " = CustomXOR(result";
            myfile << temp.inputs[0].InputConID;
            myfile << ", result";
            myfile << temp.inputs[1].InputConID;
            myfile << ");\n";
            myfile << "\tint result";
            myfile << temp.ID;
            myfile << " = StringToNumber(temp";
            myfile << temp.ID;
            myfile << ");\n";
        }
    }
}

void OutputRound::OutputGenerics(bool NodeTypes[]) {
    char * c = new char[2048];
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
cout << Dhfile << endl;
cout << Dcppfile << endl;
cout << Shfile << endl;
cout << Scppfile << endl;
    /**< Header file copy start */
    hfile.get(c, 213);
    headerfile << c;

    /**< Cpp file copy start */
    cfile.get(c, 241);
    codefile << c;

    /**< Check Node present and outputs related function */
     if (NodeTypes[2] == true) {
        /**< Header file copy XOR*/
        hfile.get(c, 61);
        headerfile << c;

        /**< Cpp file copy */
        cfile.get(c, 933);
        codefile << c;
    } else {
        /**< Skips the xor block */
        hfile.seekg(61, ios::cur);
        cfile.seekg(933, ios::cur);
    }

    if (NodeTypes[1] == true) {
        /**< Header file copy SBOX*/
        hfile.get(c, 78);
        headerfile << c;

        /**< Cpp file copy */
        cfile.get(c, 1511);
        codefile << c;
    } else {
        /**< Skips SBOX block */
        hfile.seekg(78, ios::cur);
        cfile.seekg(1511, ios::cur);
    }

    if (NodeTypes[0] == true) {
        /**< Header file copy PBOX*/
        hfile.get(c, 77);
        headerfile << c;

        /**< Cpp file copy */
        cfile.get(c, 576);
        codefile << c;
    } else {
        /**< Skip PBox */
        hfile.seekg(77, ios::cur);
        cfile.seekg(576, ios::cur);
    }

    /**< Header file copy end*/
    while(!hfile.eof()) {
        hfile.get(c, 2048);
        headerfile << c;
    }

    /**< Cpp file copy */
    while (!cfile.eof()) {
        cfile.get(c, 2048);
        codefile << c;
    }

    hfile.close();
    headerfile.close();
    cfile.close();
    codefile.close();

    delete [] c;
}
