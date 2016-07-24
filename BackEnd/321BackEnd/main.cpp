/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:27 AM
 */

#include <cstdlib>

#include "OutputCode.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    OutputCode * outs = new OutputCode();
    
    string temp = outs->setDefaultLocation();
    outs->createFile("secret.cpp");
    
    return 0;
}

