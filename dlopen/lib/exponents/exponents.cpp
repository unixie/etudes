#include <cmath>
#include "operation.hpp"

class Ln : public Operation
{
public:
    Ln(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        Operation(arg_a, arg_b, arg_desc) {};
    ~Ln() {};

    double operation(double arg_a, double arg_b) override
    {
        (void) arg_b;
        return (arg_a <=0) ? std::nan("") : std::log(arg_a);
    }
};

class Log10 : public Operation
{
public:
    Log10(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        Operation(arg_a, arg_b, arg_desc) {};
    ~Log10() {};

    double operation(double arg_a, double arg_b) override
    {
        (void) arg_b;
        return (arg_a <=0) ? std::nan("") : std::log10(arg_a);
    }
};


ADD_ENTRY(Ln)
ADD_ENTRY(Log10)