#pragma once

// override new operator to access potential leak details
#ifdef CHKLK_OVERRIDE_NEW_OP
    #define _CRTDBG_MAP_ALLOC
    #ifdef _DEBUG
    #define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
    // allocations to be of _CLIENT_BLOCK type
    #else
    #define new new
    #endif
#endif

#include <stdlib.h>
#include <crtdbg.h>

// init standard leak check
#define CHKLK_INIT _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

// take the entry snapshot of memory allocation
#define CHKLK_ENTRY_SNAP _CrtMemState entry; _CrtMemCheckpoint(&entry);

// take the exit snapshot of memory allocation
#define CHKLK_EXIT_SNAP _CrtMemState exit; _CrtMemCheckpoint(&exit);

// difference between entry state and exit state
// include Windows.h file to print to output log
#define CHKLK_DIFF_SNAP\
    _CrtMemState diff;\
    if (_CrtMemDifference(&diff, &entry, &exit))\
        OutputDebugString("\nMEMORY LEAKS DETECTED WITHIN THE SNAPSHOTS SCOPE\n");\
    else\
        OutputDebugString("\nNO MEMORY LEAKS DETECTED WITHIN THE SNAPSHOTS SCOPE\n");\
\
    OutputDebugString("\n----------_CrtMemDumpStatistics----------\n");\
    _CrtMemDumpStatistics(&diff);\
    OutputDebugString("-----------------------------------------\n\n");

// some memory could be leaked or freed outside of the snapshots take
// include Windows.h file to print to output log
#define CHKLK_APP\
    OutputDebugString("\nGENERAL APPLICATION MEMORY LEAK CHECK\n"); \
    OutputDebugString("\n-----------_CrtDumpMemoryLeaks-----------\n");\
    _CrtDumpMemoryLeaks();\
    OutputDebugString("-----------------------------------------\n\n");