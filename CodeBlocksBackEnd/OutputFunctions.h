#ifndef OUTPUTFUNC
#define OUTPUTFUNC

#include <string>
using namespace std;

#include "XMLParser.h"

string UserLocation(string);
void Print(Node*, string);
string SourceLocale();
string DefaultLocation();
void PrintNodeList(vector<Node>);
void PrintSPBox(Node);
void PrintXOR(Node);

#endif // OUTPUTFUNC
