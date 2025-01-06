#pragma once

// override new operator to access potential leak details
#ifdef CHKLK_OVERRIDE_NEW_OP
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif
#endif

#include <crtdbg.h>
#include <stdlib.h>

static _CrtMemState chklk_open;
static _CrtMemState chklk_close;
static _CrtMemState chklk_diff;

// init standard leak check
#define CHKLK_INIT _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG | _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

// take the entry snapshot of memory allocation
#define CHKLK_ENTRY_SNAP _CrtMemCheckpoint(&chklk_open);

// take the exit snapshot of memory allocation
#define CHKLK_EXIT_SNAP _CrtMemCheckpoint(&chklk_close);

// general leak state
#define CHKLK_LEAK_VERBOSE                                                                                             \
    OutputDebugString("\n_CrtDumpMemoryLeaks\n");                                                                      \
    _CrtDumpMemoryLeaks();                                                                                             \
    OutputDebugString("\n\n");

#define CHKLK_MEMORY_STATE(state)                                                                                      \
    OutputDebugString("\n_CrtMemDumpStatistics\n");                                                                    \
    _CrtMemDumpStatistics(&state);                                                                                     \
    OutputDebugString("\n\n");

// difference between entry state and exit state
#define CHKLK_DIFF_SNAP                                                                                                \
    if (_CrtMemDifference(&chklk_diff, &chklk_open, &chklk_close))                                                     \
        OutputDebugString("\nMemory leaks detected\n");                                                                \
    else                                                                                                               \
        OutputDebugString("\nNo memory leaks detected\n");                                                             \
    CHKLK_MEMORY_STATE(chklk_diff)

#define CHKLK_DIFF_VERBOSE                                                                                             \
    CHKLK_DIFF_SNAP                                                                                                    \
    CHKLK_LEAK_VERBOSE

// exit snap and directly show diff
#define CHKLK_EXIT_DIFF                                                                                                \
    CHKLK_EXIT_SNAP                                                                                                    \
    CHKLK_DIFF_SNAP

// exit snap and directly show diff (verbose)
#define CHKLK_EXIT_DIFF_VERBOSE                                                                                        \
    CHKLK_EXIT_SNAP                                                                                                    \
    CHKLK_DIFF_VERBOSE

// some memory could be leaked or freed outside of the snapshots take
#define CHKLK_APP                                                                                                      \
    OutputDebugString("\nGeneral application memory leak check\n");                                                    \
    CHKLK_LEAK_VERBOSE

#ifdef WIN32
// https://learn.microsoft.com/en-us/windows/win32/winprog/using-the-windows-headers#faster-builds-with-smaller-header-files
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define NOCOMM
#include <Windows.h>
#endif