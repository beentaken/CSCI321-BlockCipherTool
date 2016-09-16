#ifndef OUTPUTROUND
#define OUTPUTROUND

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

    private:
        string SourceLocale;
        string DestLocale;
};

#endif // OUTPUTROUND
