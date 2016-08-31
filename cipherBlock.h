#ifndef CIPHERBLOCK_H
#define CIPHERBLOCK_H

#include <string>
using namespace std;

class cipherBlock
{
    public:
        cipherBlock();
        string encryptBlock(string plain, int blocksize);

};

#endif // CIPHERBLOCK_H
