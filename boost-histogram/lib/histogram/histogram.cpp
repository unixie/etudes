#include <limits>
#include <fmt/core.h>
#include "histogram/histogram.hpp"

namespace Histogram {

Histogram::Histogram(unsigned steps, double lrange, double rrange) :
    m_sample_min(std::numeric_limits<double>::max()),
    m_sample_max(std::numeric_limits<double>::min())
{
    namespace bh = boost::histogram;
    auto axis_argh = std::vector<bh::axis::regular<>>();
    axis_argh.emplace_back(steps, lrange, rrange);
    m_histogram = bh::make_histogram(std::move(axis_argh));
}


void Histogram::operator()(double sample)
{
    if (sample <= m_sample_min) m_sample_min = sample;
    if (sample >= m_sample_max) m_sample_max = sample;
    m_histogram(sample);
}

void Histogram::report()
{
    namespace bh = boost::histogram;
    fmt::print("min={}  max={}\n", m_sample_min, m_sample_max);
    fmt::print("histogram\n");
    for (auto&& x : bh::indexed(m_histogram, bh::coverage::all))
    {
        fmt::print("bin {:2d} [{:4.1f}, {:4.1f}): {}\n" , x.index() , x.bin().lower() , x.bin().upper() , *x);
    }
}

} // namespace Histogram