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

    myfile.open("main.cpp");
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
    ofstream headerfile;
    ofstream codefile;

    headerfile.open("GenericFunctions.h");
    codefile.open("GenericFunctions.h");

    headfile << "#include <iostream>\nusing namespace std;\n";

    codefile << "#include <iostream>\n#include \"GenericFunctions.h\"\nusing namespace std;\nint main() {\n";

    for (int i = 0; i < 5; i++) {
        if (NodeTypes[i] == true) {
            if (i == 0) {
                headerfile << "\n\tPBOX();";
            } else if (i == 1) {
                headerfile << "\n\tSBOX();";
            } else if (i == 2) {
                headerfile << "\n\tXOR();";
            } else if (i == 3) {
                headerfile << "\n\tFFUNCTION();";
            } else if (i == 4) {
                headerfile << "\n\tCONNECTION();";
            }
        }
    }
}

void OutputRound::createFile(string filename) {
    // Gets the current working directory
    const int cwdbuff = 1024;
    char cwd[cwdbuff];
    GetCurrentDirectory(cwdbuff, cwd);

    cout << cwd << endl;

    fstream myfile;
    myfile.open(filename.c_str(), ios::out);
    myfile << "#include <iostream>\\nusing namespace std;\\nint main() {\\n\\nreturn 0;\\n}";
    myfile.close();


}
