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

bool OutputRound::OutputToFile(vector<Node> Head) {
    bool NodeTypes[5];  /**< Finds out which cipher node blocks have been used */

    for (int i = 0; i < 5; i++) {
        NodeTypes[i] = false;
    }

    string DefLocation = DefaultLocation();
    OutputMain(NodeTypes, Head);
    OutputGenerics(NodeTypes);

    return true;
}

void OutputRound::OutputMain(bool NodeTypes[], vector<Node> Head) {
    ofstream myfile;
    string fname = DestLocale;
    fname.append("\\main.cpp");

    myfile.open(fname.c_str());
    myfile << "#include <iostream>\n#include \"GenericsFunctions.h\"\nusing namespace std;\n\nint main() {\n";

    for (vector<Node>::iterator it = Head.begin(); it != Head.end(); it++) {
        Node temp = *it;

        if (temp.type == 0) {
            myfile << "\tPBOX();\n";
            NodeTypes[0] = true;
        } else if (temp.type == 1) {
            myfile << "\tSBOX();\n";
            NodeTypes[1] = true;
        } else if (temp.type == 2) {
            myfile << "\tXOR();\n";
            NodeTypes[2] = true;
        } else if (temp.type == 3) {
            myfile << "\tFFunction();";
            NodeTypes[3] = true;
        } else if (temp.type == 4) {
            myfile << "\tConnection();";
            NodeTypes[4] = true;
        }
    }

    myfile << "\nreturn 0;\n}";
    myfile.close();
}

void OutputRound::OutputGenerics(bool NodeTypes[]) {
    char c;
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
    for (int i = 0; i < 213; i++) {
        hfile >> c;
        headerfile << c;
    }

    /**< Cpp file copy start */
    for (int i = 0; i < 241; i++) {
        cfile >> c;
        codefile << c;
    }

    /**< Check Node present and outputs related function */
     if (NodeTypes[2] == true) {
        /**< Header file copy XOR*/
        for (int i = 0; i < 61; i++) {
            hfile >> c;
            headerfile << c;
        }

        /**< Cpp file copy */
        for (int i = 0; i < 933; i++) {
            cfile >> c;
            codefile << c;
        }
    } else {
        /**< Skips the xor block */
        hfile.seekg(61, ios::cur);
        cfile.seekg(933, ios::cur);
    }

    if (NodeTypes[1] == true) {
        /**< Header file copy SBOX*/
        for (int i = 0; i < 78; i++) {
            hfile >> c;
            headerfile << c;
        }

        /**< Cpp file copy */
        for (int i = 0; i < 1511; i++) {
            cfile >> c;
            codefile << c;
        }
    } else {
        /**< Skips SBOX block */
        hfile.seekg(78, ios::cur);
        cfile.seekg(1511, ios::cur);
    }

    if (NodeTypes[0] == true) {
        /**< Header file copy PBOX*/
        for (int i = 0; i < 77; i++) {
            hfile >> c;
            headerfile << c;
        }

        /**< Cpp file copy */
        for (int i = 0; i < 576; i++) {
            cfile >> c;
            codefile << c;
        }
    } else {
        /**< Skip PBox */
        hfile.seekg(77, ios::cur);
        cfile.seekg(77, ios::cur);
    }

    /**< Header file copy end*/
    while(!hfile.eof()) {
        hfile >> c;
        headerfile << c;
    }

    /**< Cpp file copy */
    while (!cfile.eof()) {
        cfile >> c;
        codefile << c;
    }
}
