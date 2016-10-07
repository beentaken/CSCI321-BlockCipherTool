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
        int AppendFunctionF(vector<Node>, ofstream&, vector<int>&);
        vector<Node> SortVec(vector<Node>, int);
        string KeyIDCheck(int);
        void CheckNode(vector<Node>, bool[], vector<Node>&);

    private:
        string SourceLocale;
        string DestLocale;
};

#endif // OUTPUTROUND
