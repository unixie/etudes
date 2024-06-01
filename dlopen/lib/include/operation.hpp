#include <string>
#include <functional>
#include <memory>
#include <unordered_map>


class Operation
{
protected:
    const std::string m_arg_a_description;
    const std::string m_arg_b_description;
    const std::string m_description;

public:
    virtual double operation(double arg_a, double arg_b) = 0;
    const std::string& describe_arg_a() const {return m_arg_a_description;}
    const std::string& describe_arg_b() const {return m_arg_b_description;}
    const std::string& describe() const {return m_description;}

    Operation(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        m_arg_a_description(arg_a),
        m_arg_b_description(arg_b),
        m_description(arg_desc)
    {};

    Operation() = delete;                             // default constructor
    virtual ~Operation() = default;                   // destructor
    Operation(const Operation&) = delete;             // copy constructor
    Operation& operator=(const Operation&) = delete;  // copy assignment
    Operation(Operation&&) = delete;                  // move constructor
    Operation& operator=(Operation&&) = delete;       // move assignment
};


template <typename T>
std::unique_ptr<Operation> OperationFactory(const std::string arg_a, const std::string arg_b, const std::string arg_desc)
{
    // Object is moved and dynamically casted by the compiler
    return std::unique_ptr<T>(new T(arg_a, arg_b, arg_desc));
}

using OperationFactory_t = std::function<std::unique_ptr<Operation>(const std::string, const std::string, const std::string)>;
using Directory_t = std::unordered_map<std::string, OperationFactory_t>;


#ifdef __LIB_DEVELOPMENT__
#include "directory.hpp"
#endif