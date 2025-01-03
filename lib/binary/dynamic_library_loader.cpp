#include "dynamic_library_loader.hpp"

using namespace Utils;

bin::DynamicLibraryLoader::DynamicLibraryLoader(const std::string& name)
    : m_name(name)
{
    m_name = name;
    m_module = LoadLibraryA((m_name + std::string(suffix)).c_str());
}

bin::DynamicLibraryLoader::~DynamicLibraryLoader()
{
    FreeLibrary(m_module);
}

void* bin::DynamicLibraryLoader::getProcAddr(const char* proc)
{
    void (*addr) = GetProcAddress((HMODULE)m_module, proc);
    return addr;
}
