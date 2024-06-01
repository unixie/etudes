#include <cmath>
#include "operation.hpp"

class Addition : public Operation
{
public:
    Addition(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        Operation(arg_a, arg_b, arg_desc) {};
    ~Addition() {};

    double operation(double arg_a, double arg_b) override {return arg_a + arg_b;}
};

class Subtraction : public Operation
{
public:
    Subtraction(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        Operation(arg_a, arg_b, arg_desc) {};
    ~Subtraction() {};

    double operation(double arg_a, double arg_b) override {return arg_a - arg_b;}
};

class Multiplication : public Operation
{
public:
    Multiplication(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        Operation(arg_a, arg_b, arg_desc) {};
    ~Multiplication() {};

    double operation(double arg_a, double arg_b) override {return arg_a * arg_b;}
};

class Division : public Operation
{
public:
    Division(const std::string arg_a, const std::string arg_b, const std::string arg_desc) :
        Operation(arg_a, arg_b, arg_desc) {};
    ~Division() {};

    double operation(double arg_a, double arg_b) override {return (arg_b == 0) ? std::nan("") : arg_a / arg_b;}
};


ADD_ENTRY(Addition)
ADD_ENTRY(Subtraction)
ADD_ENTRY(Multiplication)
ADD_ENTRY(Division)