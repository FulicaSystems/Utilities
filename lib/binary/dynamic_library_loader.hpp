#pragma once

#include <string>

#include <Windows.h>

// declare a function pointer
#define PFN_DECLARE(prefix, funcName) prefix##funcName funcName
// load the function from the lib
#define GET_PROC_ADDR(loaderRef, prefix, funcName) funcName = (prefix##funcName)(loaderRef).getProcAddr(#funcName)

namespace Utils::bin
{
    class DynamicLibraryLoader
    {
    private:
        // TODO : other platforms
        static constexpr const std::string_view suffix = ".dll";

    private:
        std::string m_name;

        HMODULE m_module = nullptr;

    public:
        DynamicLibraryLoader(const std::string& name);
        ~DynamicLibraryLoader();

        void* getProcAddr(const char* proc);
    };
}