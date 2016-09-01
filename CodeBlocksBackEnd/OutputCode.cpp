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

#include "OutputCode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
using namespace std;

string setDefaultLocation() {
    /* WINDOWS ONLY!!!!!!!! */

    // Gets the home path of the directory
    char* path = getenv ("HOMEPATH");

    // Appends the drive id and the my documents folder
    string temp = path;
    temp = "C:" + temp + "\\My Documents";

    //Print Check
    //cout << temp << endl;

    // Converts the concatenated string back to char *
    const char * sets = temp.c_str();

    // Sets the current directory
    SetCurrentDirectory(sets);

    // Gets the current working directory
    const int cwdbuff = 1024;
    char cwd[cwdbuff];
    GetCurrentDirectory(cwdbuff, cwd);

    // Print Check
    // cout << cwd << endl;

    return temp;
}
/*
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
*/
