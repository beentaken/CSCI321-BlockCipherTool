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

#include <iostream>
#include <cstdlib>

#include "OutputFunctions.h"

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    // Driver Program
    int choice;
    Node * Head = new Node;
    
    DefaultLocation();
    cout << "Welcome to the Crypto to C++ Program!" << endl;
    do {
        cout << "Menu: " << endl;
        cout << "1: Create an S Box" << endl;
        cout << "2: Create a P Box" << endl;        
        cout << "3: Create an XOR Function" << endl;
        cout << "4: Output all created cryptos into runnable C++ code" << endl;
        cout << "0: Exit" << endl;
        cin >> choice;
        
        if (choice <= 4 && choice >= 0) {
            if (choice == 1) {
                
            }
            
            if (choice == 2) {
                
            }
            
            if (choice == 3) {
                
            }
            
            if (choice == 4) {
                Print(Head);
            }
        }
        
    } while (choice != 0);
    
    cout << "Thank you for using the program" << endl;
    
    return 0;
}

