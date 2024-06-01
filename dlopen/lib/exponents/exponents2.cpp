#include <cmath>
#include "operation.hpp"

class Log2 : public Operation
{
public:
    Log2(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        Operation(arg_a, arg_b, arg_desc) {};
    ~Log2() {};

    double operation(double arg_a, double arg_b) override
    {
        (void) arg_b;
        return (arg_a <=0) ? std::nan("") : std::log2(arg_a);
    }
};

ADD_ENTRY(Log2)