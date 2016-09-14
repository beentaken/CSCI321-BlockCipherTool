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

#include <string>
#include "OutputFunctions.h"

using namespace std;

class OutputRound {
    public:
        OutputRound();
        ~OutputRound();
        bool ReadSource(string);
        bool ReadDest(string);
        bool OutputToFile(vector<Node>);
        void OutputMain(bool[], vector<Node>);
        void OutputGenerics(bool[]);
        void createFile(string);

    private:
        string SourceLocale;
        string DestLocale;
};
