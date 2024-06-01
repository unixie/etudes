#include "operation.hpp"


Directory&
getDirectory()
{
    static Directory g_directory;
    return g_directory;
}


bool
Directory::add_entry(
    std::string name,
    OperationFactory_t factory
)
{
    m_directory.insert({name, factory});
    return true;
}


extern "C"
{
 __attribute__((visibility("default"))) const Directory_t* get_operations() {return getDirectory().expose();}
}