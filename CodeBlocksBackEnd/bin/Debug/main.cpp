#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <random>
#include <time.h>

#include <memory>
#include <stdio.h>

#include <windows.h>
#include <wincrypt.h>

#include "block.h"
#include "keygen.h"
#include "GenericFunctions.h"

#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <cstdlib>

using namespace std;
using namespace boost;



/** \brief This is a driver program for a generic block cipher
 *
 *  This file drives an external block cipher, and implements various
 *  modes of operation (ECB, CBC, CFB, OFB, CTR)
 *
 *  Aidan Pond
 */




//long binconv(long num){
//long bin, dec = 0, rem, base = 1;
//bin = num;
//    while (num > 0)
//    {
//        rem = num % 10;
//        dec = dec + rem * base;
//        base = base * 2;
//        num = num / 10;
//    }
//
//    return dec;
//
//};

string ECB_Encrypt(string s, int bl, cipherBlock cipher, string* keys)
{
    /** \fn ECB
     *  \brief  electronic codebook
     *  Does nothing, just encrypts each block
     *
     */


    return cipher.encryptBlock(s, keys);
}

string ECB_Decrypt(string s, int bl, cipherBlock cipher, string* keys)
{
    /** \fn ECB
     *  \brief  electronic codebook
     *  Does nothing, just decrypts each block
     *
     */
    return cipher.decryptBlock(s, keys);
}





string CBC_Encrypt(string s, int bl, unsigned char* iv, cipherBlock cipher, string* keys)
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

    string ctb = cipher.encryptBlock(s, keys); //send to cipher

    for (int j=0; j<bl; j++) //write ciphertext into iv variable
    {
        iv[j] = ctb[j];
    }

    return ctb;
}

string CBC_Decrypt(string s, int bl, unsigned char* iv, cipherBlock cipher, string* keys)
{

    /** \fn CBC
     *  \brief  cipher block chaining
     *  each block of ciphertext is XORed into the
     *  next block of plaintext after decryption
     *
     */


    string ctb = cipher.decryptBlock(s, keys); //send to cipher

    for (int j=0; j<bl; j++)
    {
        ctb[j] = ctb[j]^iv[j]; //XOR byte with IV (or last blocks ciphertext)
    }


    for (int j=0; j<bl; j++) //write ciphertext into iv variable
    {
        iv[j] = s[j];
    }

    return ctb;
}










string CFB_Encrypt(string s, int bl, unsigned char* iv, cipherBlock cipher, string* keys)
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
    string ctb = cipher.encryptBlock(ivString, keys);

    for (int j=0; j<bl; j++)
    {
        //XORing in the plaintext
        ctb[j] = ctb[j]^s[j];

        //write ciphertext into iv variable
        iv[j] = ctb[j];
    }


    return ctb;
}

string CFB_Decrypt(string s, int bl, unsigned char* iv, cipherBlock cipher, string* keys)
{

    /** \fn CFB
     *  \brief  cipher feedback
     *  the ciphertext of the previous block is encrypted
     *  then the ciphertext is XORed in
     *
     */

    string ivString;
    ivString.resize(bl);
    for (int j=0; j<bl; j++)
    {
        ivString[j] = iv[j];
    }
    string ctb = cipher.encryptBlock(ivString, keys);

    for (int j=0; j<bl; j++)
    {
        //XORing in the plaintext
        ctb[j] = ctb[j]^s[j];

        //write ciphertext into iv variable
        iv[j] = s[j];
    }


    return ctb;
}





string OFB(string s, int bl, unsigned char* iv, cipherBlock cipher, string* keys)
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
    string ctb = cipher.encryptBlock(ivString, keys);

    for (int j=0; j<bl; j++)
    {
        //write ciphertext into iv variable
        //in OFB this happens first
        iv[j] = ctb[j];


        ctb[j] = ctb[j]^s[j];
    }

    return ctb;

}
string CTR(string s, int bl, unsigned char* iv, cipherBlock cipher, string* keys)
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
    string ctb = cipher.encryptBlock(ivString, keys);

    for (int j=0; j<bl; j++)
    {
        //almost the same as CFB and OFB
        //dont change the IV
        ctb[j] = ctb[j]^s[j];
    }

    return ctb;
}




string paddingEncrypt(int pad, int blocksize, int paddingMode)
{
    string block;
    block.clear();
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
    return block;
}










int encrypt(string filename, int blocksize, int mode, int paddingMode, string* keys)
{

    string block; ///< used to store plaintext blocks

    block.resize(blocksize);

    unsigned char * iv = NULL; ///< used to store Initialization Vector
    if (mode != 1)
    {
        //generating initialization vector
        //https://msdn.microsoft.com/en-us/library/windows/desktop/aa379942(v=vs.85).aspx

        HCRYPTPROV hCryptProv;
        iv = new unsigned char[blocksize];

///well seems like cryptgenrandom refuses to work
///i hate microsoft
///
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
        //classic microsoft stitch up

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


    dynamic_bitset<> blockSet(blocksize*8);
    dynamic_bitset<> fileSet(blocksize*8);


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
            cipherTextBlock = ECB_Encrypt(block, blocksize, cipher, keys);
        }
        else if (mode==2)
        {///CBC
            cipherTextBlock = CBC_Encrypt(block, blocksize, iv, cipher, keys);
        }
        else if (mode==3)
        {///CFB
            cipherTextBlock = CFB_Encrypt(block, blocksize, iv, cipher, keys);
        }
        else if (mode==4)
        {///OFB
            cipherTextBlock = OFB(block, blocksize, iv, cipher, keys);
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

            cipherTextBlock = CTR(block, blocksize, ivCounter, cipher, keys);
        }



        //add the encrypted block to the out string
        for (int k=0; k<blocksize; k++)
        {
            out.push_back(cipherTextBlock[k]);
        }
    }





    ///process last block
    //the last block needs padding before it can be encrypted
/*
    block.clear();
    for (int j=0; j<pad; j++)
    {//reading the rest of the file
        block.push_back(infile.get());
    }



    block.append(paddingEncrypt(pad, blocksize, paddingMode));
*/
    string lastCipherBlock = block;

//
//    ///kludge
//        block.clear();
//        block.push_back(infile.get());
//        string s2 = block;
//        block.clear();
//        for (int i=0; i<s2.length(); i++)
//        {
//            bitset<8> b(s2.c_str()[i]);
//            block+=b.to_string();
//        }
////        cout << block << " | " << s2 << endl;
//    ///end kludge

    if (mode==1)
        block = ECB_Encrypt(lastCipherBlock, blocksize, cipher, keys);
    else if (mode==2)
        block = CBC_Encrypt(lastCipherBlock, blocksize, iv, cipher, keys);
    else if (mode==3)
        block = CFB_Encrypt(lastCipherBlock, blocksize, iv, cipher, keys);
    else if (mode==4)
        block = OFB(lastCipherBlock, blocksize, iv, cipher, keys);
    else if (mode==5)
    {
        unsigned char counter = i;
        unsigned char* ivCounter = new unsigned char[blocksize];
        memcpy(ivCounter, iv, blocksize);
        ivCounter[(blocksize-1)] = ivCounter[(blocksize-1)]^counter;

        block = CTR(lastCipherBlock, blocksize, ivCounter, cipher, keys);
    }


    for (int k=0; k<blocksize; k++)
    {
        out.push_back(block[k]);
    }

    ///write ciphertext to file
    ofstream outfile;
    outfile.open("out.bin", ios::trunc | ios::binary);
    outfile << out;

}






int decrypt(string filename, int blocksize, int mode, int paddingMode, string* keys)
{

    string block; ///< used to store ciphertext blocks

    block.resize(blocksize);

    unsigned char * iv = NULL; ///< used to store Initialization Vector
    if (mode != 1)
    {
        iv = new unsigned char[blocksize];
        cout << "IV file: ";
        string ivfilename;
        cin >> ivfilename;
        ifstream ivFile; ///< file for storing the IV
        ivFile.open(ivfilename, ios::binary);
        for (int i=0; i<blocksize; i++)
        {
            char c;
            ivFile.get(c);
            iv[i] = c;
        }

        ivFile.close();
    }

    //open file with ciphertext
    ifstream infile;
    infile.open(filename.c_str(), ios::binary);

    //check infile is valid
    if (!infile.good())
    {
        cerr << "Error opening file" << endl;
        return -1;
    }

    int fileLen=0;
    infile.seekg(0, ios::end);
    fileLen = infile.tellg();
    infile.seekg(0, ios::beg);

    string out = ""; ///< string for output

    cipherBlock cipher; ///< a single block of a cipher

    ///process each full sized block
    unsigned int i=0;
    for (i; i<(fileLen/blocksize); i++)
    {
        string plainTextBlock; ///< stores a single block of plaintext


        block.clear();
        for (int j=0; j<blocksize; j++)
        {
            block.push_back(infile.get());
        }


        if (mode==1)
        {///ECB
            plainTextBlock = ECB_Decrypt(block, blocksize, cipher, keys);
        }
        else if (mode==2)
        {///CBC
            plainTextBlock = CBC_Decrypt(block, blocksize, iv, cipher, keys);
        }
        else if (mode==3)
        {///CFB
            plainTextBlock = CFB_Decrypt(block, blocksize, iv, cipher, keys);
        }
        else if (mode==4)
        {///OFB
            plainTextBlock = OFB(block, blocksize, iv, cipher, keys);
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

            plainTextBlock = CTR(block, blocksize, ivCounter, cipher, keys);
        }

        //add the encrypted block to the out string
        for (int k=0; k<blocksize; k++)
        {
            out.push_back(plainTextBlock[k]);
        }
    }


    ///write ciphertext to file
    ofstream outfile;
    outfile.open("plaintext_out.txt", ios::trunc | ios::binary);
    outfile << out;

}






int main(int argc, char** argv)
{

    int blocksize = 0; ///< used to store the size of each block in bytes
    int mode=0; ///< selects mode of operation
    int paddingMode=0; ///< selects mode of padding
    int ED;
    string filename;
    string mainKey;

    if (argc==1)
    {
        cout << "1) Encrypt" << endl;
        cout << "2) Decrypt" << endl;
        cout << ">> ";
        cin >> ED;

        cout << "Block Size (bytes): ";
        cin >> blocksize;

        //open file
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

        if (ED == 1)
        {
            cout << "1) ANSI X.923" << endl;
            cout << "2) ISO 10126" << endl;
            cout << "3) PKCS7" << endl;
            cout << "4) ISO/IEC 7816-4" << endl;
            cout << "5) Zero padding" << endl;
            cout << "Padding mode: ";
            cin >> paddingMode;
        }

        cout << "Enter Key: ";
        cin >> mainKey;
    }
    else if (argc == 7)
    {
        stringstream ss;
        string sString;
        for (int i=1; i<7; i++)
        {
            sString.append(argv[i]);
            ss << sString << " ";
            sString.clear();
        }
        ss >> ED >> blocksize >> filename >> mode >> paddingMode >> mainKey;

    }

    string* keys;
    keygen k;
    keys = k.keySchedule(mainKey);

    if (ED==1)
    {
        encrypt(filename, blocksize, mode, paddingMode, keys);
    }
    else if (ED==2)
    {
        decrypt(filename, blocksize, mode, paddingMode, keys);
    }


    return 0;
}
