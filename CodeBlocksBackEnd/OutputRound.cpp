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

bool OutputRound(vector<Node> Head) {
    bool NodeTypes[5];  /**< Finds out which cipher node blocks have been used */

    for (int i = 0; i < 5; i++) {
        NodeTypes[i] = false;
    }

    string DefLocation = DefaultLocation();
    OutputMain(NodeTypes, Head);
    OutputGenerics(NodeTypes, Head);

    return true;
}

void OutputMain(bool NodeTypes[], vector<Node> Head) {

}

void OutputGenerics(bool NodeTypes[], vector<Node> Head) {

}

void createFile(string filename) {
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
