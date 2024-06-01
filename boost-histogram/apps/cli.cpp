#include <fmt/core.h>
#include <fmt/color.h>
#include <CLI/CLI.hpp>
#include "histogram/histogram.hpp"

int
main(int argc, char *argv[])
{
   using namespace std;

   CLI::App app{"Learn Histogram"};

   double lrange;
   app.add_option("-l,--l-range", lrange, "Left-hand side of range")->required();

   double rrange;
   app.add_option("-r,--r-range", rrange, "Right-hand side of range")->required();

   unsigned bins{10};
   app.add_option("-b,--bins", bins, "Number of bins")->capture_default_str();

   vector<double> measurements;
   app.add_option("-m,--measurements", measurements, "Fill the histogram")->delimiter(',')->expected(0,-1);

   pair<double, double> range{0,0};
   app.add_option("--range", range, "Range")->capture_default_str();

   CLI11_PARSE(app, argc, argv);

   auto h = Histogram::Histogram(bins, lrange, rrange);

   fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic, "Hello world!\n");
   if (measurements.empty())
   {
      fmt::print("no measurements\n");
      return 0;
   }
   else
   {
      fmt::print("filling histogram with measurements\n");
      for (auto& sample : measurements) h(sample);
      h.report();
   }
}