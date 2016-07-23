/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GenericFunctions.h
 * Author: SirhCloud
 *
 * Created on 23 July 2016, 10:29 AM
 */

#ifndef GENERICFUNCTIONS_H
#define GENERICFUNCTIONS_H

class GenericFunctions {
public:
    GenericFunctions();
    GenericFunctions(const GenericFunctions& orig);
    virtual ~GenericFunctions();
    
    // Generic Functions
    int CustomXOR(int, int, int);    // XOR Function
    int** CustomPBoxGeneration(int, int);           // Permutation Box Function
    int** CustomSBoxGeneration(int, int);           // Substitution Box Generation Function
    int CustomSBoxSearch(int**, int);         // Searches the Substitution Box
    int CustomPBoxSearch(int**, int);          // Searches the Permutation Box
    
private:

};

#endif /* GENERICFUNCTIONS_H */

