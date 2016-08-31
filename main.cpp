#include <iostream>
#include <fstream>
#include <string>

#include <random>
#include <time.h>

#include <memory>
#include <stdio.h>

#include <windows.h>
#include <wincrypt.h>

#include "cipherBlock.h"

using namespace std;

/** \brief This is a driver program for a generic block cipher
 *
 *  This file drives an external block cipher, and implements various
 *  modes of operation (ECB, CBC, CFB, OFB, CTR)
 */






string ECB(string s, int bl, cipherBlock cipher)
{
    /** \fn ECB
     *  \brief  electronic codebook
     *  Does nothing, just encrypts each block
     *
     */
    return cipher.encryptBlock(s, bl);
}
string CBC(string s, int bl, unsigned char* iv, cipherBlock cipher)
{

    /** \fn CBC
     *  \brief  cipher block chaining
     *  each block of ciphertext is XORed into the
     *  next block of plaintext before encryption
     *
     */

    for (int j=0; j<bl; j++)
    {
        s[j] = s[j]^iv[j]; //XOR byte with IV (or last blocks ciphertext)
    }

    string ctb = cipher.encryptBlock(s, bl); //send to cipher

    for (int j=0; j<bl; j++) //write ciphertext into iv variable
    {
        iv[j] = ctb[j];
    }

    return ctb;
}
string CFB(string s, int bl, unsigned char* iv, cipherBlock cipher)
{

    /** \fn CFB
     *  \brief  cipher feedback
     *  the ciphertext of the previous block is encrypted
     *  then the plaintext is XORed in
     *
     */

    string ivString;
    ivString.resize(bl);
    for (int j=0; j<bl; j++)
    {
        ivString[j] = iv[j];
    }
    string ctb = cipher.encryptBlock(ivString, bl);

    for (int j=0; j<bl; j++)
    {
        //XORing in the plaintext
        ctb[j] = ctb[j]^s[j];

        //write ciphertext into iv variable
        iv[j] = ctb[j];
    }


    return ctb;
}
string OFB(string s, int bl, unsigned char* iv, cipherBlock cipher)
{
    /** \fn OFB
     *  \brief  output feedback
     *  almost the same as CFB, just a marginally different order
     *  This function is also used for decryption
     *
     */

    string ivString;
    ivString.resize(bl);
    for (int j=0; j<bl; j++)
    {
        ivString[j] = iv[j];
    }
    string ctb = cipher.encryptBlock(ivString, bl);

    for (int j=0; j<bl; j++)
    {
        //write ciphertext into iv variable
        //in OFB this happens first
        iv[j] = ctb[j];


        ctb[j] = ctb[j]^s[j];
    }

    return ctb;

}
string CTR(string s, int bl, unsigned char* iv, cipherBlock cipher)
{

    /** \fn CTR
     *  \brief  counter mode
     *  almost the same as CFB and OFB, with a different IV
     *  the IV is handled in the main program
     *  This function is also used for decryption
     *
     */

    string ivString;
    ivString.resize(bl);
    for (int j=0; j<bl; j++)
    {
        ivString[j] = iv[j];
    }
    string ctb = cipher.encryptBlock(ivString, bl);

    for (int j=0; j<bl; j++)
    {
        //almost the same as CFB and OFB
        //dont change the IV
        ctb[j] = ctb[j]^s[j];
    }

    return ctb;
}









int main()
{

    int blocksize = 0; ///< used to store the size of each block in bytes
    cout << "block size: ";
    cin >> blocksize;
    string block; ///< used to store plaintext blocks

    block.resize(blocksize);



    int mode=0; ///< selects mode of operation
    int paddingMode=0; ///< selects mode of padding

    //open file
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    //select chaining mode
    cout << "1) ECB" << endl;
    cout << "2) CBC" << endl;
    cout << "3) CFB" << endl;
    cout << "4) OFB" << endl;
    cout << "5) CTR" << endl;
    cout << "Mode: ";
    cin >> mode;


    cout << "1) ANSI X.923" << endl;
    cout << "2) ISO 10126" << endl;
    cout << "3) PKCS7" << endl;
    cout << "4) ISO/IEC 7816-4" << endl;
    cout << "5) Zero padding" << endl;
    cout << "Padding mode: ";
    cin >> paddingMode;


    unsigned char * iv = NULL; ///< used to store Initialization Vector
    if (mode != 1)
    {
        //generating initialization vector
        //https://msdn.microsoft.com/en-us/library/windows/desktop/aa379942(v=vs.85).aspx

        HCRYPTPROV hCryptProv;
        iv = new unsigned char[blocksize];

///well seems like cryptgenrandom hates me and refuses to work
///i fucking hate microsoft
///fuck this bullshit
///rand() it is

//        if (!CryptGenRandom(hCryptProv, blocksize, iv))
//        {
//            cerr << "Error Generating IV" << endl;
//            LPVOID lpMsgBuf;
//            LPVOID lpDisplayBuf;
//            DWORD dw = GetLastError();
//
//            cerr << dw << endl;
//            HRESULT h = HRESULT_FROM_WIN32(dw);
//            cerr << h << endl;
//        }

        //not cryptographically secure
        //but more secure than CryptGenRandom not actually working
        //and giving nonrandom output
        //
        //fucking microsoft
        srand(time(NULL));
        for (int i=0; i<blocksize; i++)
            iv[i] = rand()%255;



        ofstream ivFile; ///< file for storing the IV
        ivFile.open("iv", ios::binary | ios::trunc);
        for (int i=0; i<blocksize; i++)
            ivFile << iv[i];
        ivFile.close();
    }



    //open file with plaintext
    ifstream infile;
    infile.open(filename.c_str(), ios::binary);

    //check infile is valid
    if (!infile.good())
    {
        cerr << "Error opening file" << endl;
        return -1;
    }

    //find the length of the file
    int fileLen=0;
    infile.seekg(0, ios::end);
    fileLen = infile.tellg();
    infile.seekg(0, ios::beg);

    //determine how much padding needs to be done
    int pad = fileLen % blocksize;  ///< stores how many characters of the final block exist
                                    ///< NB: the number of bytes to add is BlockLength - pad
    string out = ""; ///< string for output

    cipherBlock cipher; ///< a single block of a cipher

    ///process each full sized block
    unsigned int i=0;
    for (i; i<(fileLen/blocksize); i++)
    {
        string cipherTextBlock; ///< stores a single block of ciphertext
        block.clear();
        for (int j=0; j<blocksize; j++)
        {
            block.push_back(infile.get());
        }

        if (mode==1)
        {///ECB
            cipherTextBlock = ECB(block, blocksize, cipher);
        }
        else if (mode==2)
        {///CBC
            cipherTextBlock = CBC(block, blocksize, iv, cipher);
        }
        else if (mode==3)
        {///CFB
            cipherTextBlock = CFB(block, blocksize, iv, cipher);
        }
        else if (mode==4)
        {///OFB
            cipherTextBlock = OFB(block, blocksize, iv, cipher);
        }
        else if (mode==5)
        {///CTR
            //XOR a counter into the rightmost bit of the IV
            //downside: only supports up to 255 blocks
            //shit
            unsigned char counter = i;
            unsigned char* ivCounter = new unsigned char[blocksize];
            memcpy(ivCounter, iv, blocksize);
            ivCounter[(blocksize-1)] = ivCounter[(blocksize-1)]^counter;

            cipherTextBlock = CTR(block, blocksize, ivCounter, cipher);
        }

        //add the encrypted block to the out string
        for (int k=0; k<blocksize; k++)
        {
            out.push_back(cipherTextBlock[k]);
        }
    }





    ///process last block
    //the last block needs padding before it can be encrypted

    block.clear();
    for (int j=0; j<pad; j++)
    {//reading the rest of the file
        block.push_back(infile.get());
    }


    for (int k=pad; k<blocksize; k++)
    {
        if (paddingMode==1)
        {///ANSI X.923
            if (k==(blocksize-1))
            {
                unsigned char c = (blocksize-pad); //how many bytes were added
                block.push_back(c);
            }
            else
            {
                block.push_back('\0');
            }
        }
        else if (paddingMode==2)
        {///ISO 10126
            if (k==(blocksize-1))
            {
                unsigned char c = (blocksize-pad); //how many bytes were added
                block.push_back(c);
            }
            else
            {
                unsigned char c = rand()%255; //random byte
                block.push_back(c);
            }
        }
        else if (paddingMode==3)
        {///PKCS7
            unsigned char c = (blocksize-pad); //how many bytes were added
            block.push_back(c);
        }
        else if (paddingMode==4)
        {///ISO/IEC 7816-4
            if (k==pad)
            {
                unsigned char c = 128;
                block.push_back(c);
            }
            else
            {
                block.push_back('\0');
            }
        }
        else if (paddingMode==5)
        {///Zero padding
            block.push_back('\0');
        }
    }
    string lastCipherBlock = block;

    if (mode==1)
        block = ECB(lastCipherBlock, blocksize, cipher);
    else if (mode==2)
        block = CBC(lastCipherBlock, blocksize, iv, cipher);
    else if (mode==3)
        block = CFB(lastCipherBlock, blocksize, iv, cipher);
    else if (mode==4)
        block = OFB(lastCipherBlock, blocksize, iv, cipher);
    else if (mode==5)
    {
        unsigned char counter = i;
        unsigned char* ivCounter = new unsigned char[blocksize];
        memcpy(ivCounter, iv, blocksize);
        ivCounter[(blocksize-1)] = ivCounter[(blocksize-1)]^counter;

        lastCipherBlock = CTR(block, blocksize, ivCounter, cipher);
    }

    for (int k=0; k<blocksize; k++)
    {
        out.push_back(lastCipherBlock[k]);
    }

    ///write ciphertext to file
    ofstream outfile;
    outfile.open("out.txt", ios::trunc | ios::binary);
    outfile << out;

    return 0;
}
