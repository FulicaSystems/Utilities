#pragma once

#include <string>

#include <Windows.h>

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