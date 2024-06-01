class Directory
{
public:
    bool add_entry(std::string name, OperationFactory_t factory);
    const Directory_t* expose() const {return &m_directory;};

private:
    Directory_t m_directory;
};

Directory& getDirectory();

#define ADD_ENTRY(name) static bool name##_entry = getDirectory().add_entry(#name, OperationFactory<name>);
