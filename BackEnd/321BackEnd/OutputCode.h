/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutputCode.h
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 12:48 PM
 */

#ifndef OUTPUTCODE_H
#define OUTPUTCODE_H

#include <string>
using namespace std;

class OutputCode {
public:
    OutputCode();
    OutputCode(const OutputCode& orig);
    virtual ~OutputCode();
    
    string setDefaultLocation();
    void createFile(string);
private:

};

#endif /* OUTPUTCODE_H */

