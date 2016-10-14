#include <iostream>
#include <time.h>
#include <Windows.h>
#include <psapi.h>
#include <string>

using namespace std;

void calculateTime(string filename) {
    clock_t tStart = clock();

    PROCESS_INFORMATION ProcessInfo;

    STARTUPINFO StartupInfo;

    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof StartupInfo;

    if (CreateProcess(filename.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)) {
        WaitForSingleObject(ProcessInfo.hProcess, INFINITE);

        PROCESS_MEMORY_COUNTERS_EX pmc;
        if (GetProcessMemoryInfo(ProcessInfo.hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)) != 0) {
            /**< RAM */
            SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

            cout << "RAM used: " << physMemUsedByMe << endl;

            /**< Virtual Memory */
            SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

            cout << "Virtual Memory used: " << virtualMemUsedByMe << endl;
        }

        CloseHandle(ProcessInfo.hThread);
        CloseHandle(ProcessInfo.hProcess);
    } else {
        cout << "Process could not be created!" << endl;
    }

    /**< Time taken to run */
    cout << "Time taken: " << ((clock() - tStart)/CLOCKS_PER_SEC) << endl;
}
