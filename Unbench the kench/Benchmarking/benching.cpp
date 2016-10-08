#include <iostream>
#include <time.h>
#include <Windows.h>
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
        CloseHandle(ProcessInfo.hThread);
        CloseHandle(ProcessInfo.hProcess);
    } else {
        cout << "Process could not be created!" << endl;
    }

    cout << "Time taken: " << ((clock() - tStart)/CLOCKS_PER_SEC) << endl;
}
