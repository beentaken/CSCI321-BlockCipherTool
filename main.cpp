#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <stdlib.h>
#include <time.h>

#include <Windows.h>
#include <psapi.h>

#include "timeMs64.h"


using namespace std;



void cryptanalysis(int blocksize)
{

    /** \brief function for cryptanalysis
     *
     * \param takes blocksize (in bytes) as an int
     *
     *  Aidan Pond
     */

    //generate random input file (1 block size)
    fstream cleartext;
    cleartext.open("plaintext.bin", ios::trunc | fstream::out | ios::binary);
    srand(time(NULL));

    for (int i=0; i<blocksize; i++)
    {
        unsigned char c = rand()%256;
        cleartext.put(c);
    }
    cleartext.close();


    //run file through cipher
    string systemcall;
    stringstream ss;
    ss << "cipher.exe 1 " << blocksize << " plaintext.bin 1 1 11";
    systemcall = ss.str();

    system(systemcall.c_str());

    //save output file
    system("COPY /B out.bin out1.bin");

    //modify 1 bit of input file
    cleartext.open("plaintext.bin");
    cleartext.seekg(ios::beg);
    char c = cleartext.get();
    c ^= 1 << (0);
    cleartext.seekp(ios::beg);
    cleartext.put(c);
    cleartext.close();

    //run through cipher
    system(systemcall.c_str());
    system("COPY /B out.bin out2.bin");


    ifstream out1stream, out2stream;
    out1stream.open("out1.bin");
    out2stream.open("out2.bin");

    string out1, out2;
    string finalCount;

    //calculate number of changed bits
    for (int i=0; i<blocksize; i++)
    {
        out1.push_back(out1stream.get());
        out2.push_back(out2stream.get());
        finalCount[i] = out1[i]^out2[i];  ///XORing bits should only set the bits that have been changed
    }



    ofstream ofs;
    ofs.open("cryptanalysis.log");
    //output both ciphertexts
    cout << endl << endl << endl;
    cout << "========================" << endl;
    cout << "AVALANCHE EFFECT TESTING" << endl;
    cout << "========================" << endl << endl << endl;


    cout << "Ciphertext 1:\n\t";
    ofs << "Ciphertext 1:\n\t";
    for (int i=0; i<blocksize; i++)
    {
        unsigned char uChar = out1[i];
        unsigned int c=0 + uChar;
        cout << setw(2) << setfill('0') << hex << uppercase << c << " ";
        ofs << setw(2) << setfill('0') << hex << uppercase << c << " ";
    }
    cout << "\nCiphertext 2:\n\t";
    ofs << "\nCiphertext 2:\n\t";
    for (int i=0; i<blocksize; i++)
    {
        unsigned char uChar = out2[i];
        unsigned int c=0 + uChar;
        cout << setw(2) << setfill('0') << hex << uppercase << c << " ";
        ofs << setw(2) << setfill('0') << hex << uppercase << c << " ";
    }
    cout << dec << endl;

    //count number of bits in finalCount
    unsigned int total = 0;
    for (int i=0; i<blocksize; i++)
    {
        unsigned char uChar = finalCount[i];
        unsigned int c;
        for (c = 0; uChar; uChar >>= 1)
        {
            c += uChar & 1;
        }
        total += c;
    }
    cout << endl << "Number of changed bits: " << total << endl;
    ofs << endl << "Number of changed bits: " << total << endl;
    float percent = 0.0;
    percent = ( (float) total * 100) / ( (float) blocksize * 8);
    cout << fixed << setprecision(2) << "\t" << percent << "% of bits were changed" << endl;
    ofs << fixed << setprecision(2) << "\t" << percent << "% of bits were changed" << endl;
};


void benchmarking(int blocksize)
{

    /** \brief function for running benchmarking
     *
     * \param takes in blocksize as int
     *
     *  Aidan Pond and Chris Mellon
     */

    uint64 startTime =GetTimeMs64(); //start time


    //generate random input file (1 block size)
    fstream cleartext;
    cleartext.open("plaintext.bin", ios::trunc | fstream::out | ios::binary);
    srand(time(NULL));

    for (int i=0; i<blocksize; i++)
    {
        unsigned char c = rand()%256;
        cleartext.put(c);
    }
    cleartext.close();


    //run file through cipher
    string systemcall;
    stringstream ss;
    ss << "cipher.exe 1 " << blocksize << " plaintext.bin 1 1 11";
    systemcall = ss.str();

    system(systemcall.c_str());


    ///code for memory and cpu usage - currently not working
    ///Chris Kun

//    PROCESS_INFORMATION ProcessInfo;
//
//    STARTUPINFO StartupInfo;
//
//    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
//    StartupInfo.cb = sizeof StartupInfo;
//
//    if (CreateProcess("cipher.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)) {
//        WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
//
//        PROCESS_MEMORY_COUNTERS_EX pmc;
//        if (GetProcessMemoryInfo(ProcessInfo.hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)) != 0) {
//            /**< RAM */
//            SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
//
//            cout << "RAM used: " << physMemUsedByMe << endl;
//
//            /**< Virtual Memory */
//            SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
//
//            cout << "Virtual Memory used: " << virtualMemUsedByMe << endl;
//        }
//
//        CloseHandle(ProcessInfo.hThread);
//        CloseHandle(ProcessInfo.hProcess);
//    } else {
//        cout << "Process could not be created!" << endl;
//    }

    /**< Time taken to run */
    uint64 endTime = GetTimeMs64();
    ofstream ofs;
    ofs.open("benchmarking.log");
    cout << "Runtime: " << (endTime - startTime) << "ms" << endl;
    ofs << "Runtime: " << (endTime - startTime) << "ms" << endl;
}



int main(int argc, char** argv)
{
    int blocksize = -1;
    int mode = -1;
    if (argc==1)
    {
        cout << "Enter Block Size (bytes): ";
        cin >> blocksize;
        cout << "1) Cryptanalysis" << endl;
        cout << "2) Benchmarking" << endl;
        cout << ">> ";
        cin >> mode;
    }
    else if (argc == 3)
    {
        stringstream ss;
        ss.str(argv[1]);
        ss >> mode;

        ss.str(argv[2]);
        ss >> blocksize;
    }

    if (mode == 1)
        cryptanalysis(blocksize);
    else if (mode == 2)
        benchmarking(blocksize);
    else
        cerr << "INVALID ARGUMENT" << endl;

    return 0;
}
