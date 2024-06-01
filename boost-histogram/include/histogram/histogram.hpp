#pragma once
#include <vector>
#include <boost/histogram.hpp>

namespace Histogram {

class Histogram
{
  using hist_t = boost::histogram::histogram<std::vector<boost::histogram::axis::regular<>>>;
  hist_t m_histogram;
  double m_sample_min;
  double m_sample_max;

public:
    void operator()(double sample);
    void report();

    Histogram(unsigned steps, double lrange, double rrange);
    Histogram() = delete;                             // default constructor
    Histogram(const Histogram&) = delete;             // copy constructor
    Histogram& operator=(const Histogram&) = delete;  // copy assignment
    Histogram(Histogram&&) = delete;                  // move constructor
    Histogram& operator=(Histogram&&) = delete;       // move assignment
};

} // namespace Histogram
