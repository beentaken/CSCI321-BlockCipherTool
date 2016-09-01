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


// Generic Functions
int CustomXOR(int, int, int);           // XOR Function
int** CustomPBoxGeneration();           // Permutation Box Function
int** CustomSBoxGeneration();           // Substitution Box Generation Function
int CustomSBoxSearch(int**, int);       // Searches the Substitution Box
int CustomPBoxSearch(int**, int);       // Searches the Permutation Box
