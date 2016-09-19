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
        bool OutputToFile(vector<Node>, Properties);
        void OutputMain(vector<Node>, Properties);
        void OutputGenerics(bool[]);
        void AppendConversions();
        void AppendFunctionF(vector<Node>, ofstream&, bool&);

    private:
        string SourceLocale;
        string DestLocale;
};

#endif // OUTPUTROUND
