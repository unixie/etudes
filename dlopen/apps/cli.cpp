#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <dlfcn.h>
#include "operation.hpp"
#include <CLI/CLI.hpp>
using namespace std;

static struct Handles
{
   vector<void *> entries;
   ~Handles() {cout << "Handles dtor called" << endl;}
} SO_HANDLES;

/*
  Declaring a separate function has the benefit of ensuring that
atexit handler is checked to be AFTER the static structure during
compile-time.
   Order is crucial to ensure that atexit is called BEFORE the
static structure's dtor for proper RAII.
*/

void atexit_dlclose()
{
   for (auto h: SO_HANDLES.entries)
   {
      cout << "Closing " << h;
      auto eret = dlclose(h);
      auto cout_eret = [=]{return eret ? to_string(eret) : "success";};
      cout << " with code: " << cout_eret() << endl;
   }
}


int main( int argc, char *argv[])
{
   namespace fs = std::filesystem;

   // --- CLI argument parsing -----------------------------------------------
   CLI::App app{"uCalc: command line calculator"};
   app.footer("\n"
      "Notes:\n"
      " o When loading so from current directory, prepend filename with './'"
      "\n\n"
   );

   vector<string> load_dlls;
   app.add_option("-l,--load", load_dlls, "DLL/SO to load")->required()->delimiter(' ');

   string operator_name{};
   app.add_option("-o,--operator", operator_name, "Name of operator to execute")->capture_default_str();

   double arg_a{0};
   app.add_option("-a", arg_a, "argument A")->capture_default_str();

   double arg_b{0};
   app.add_option("-b", arg_b, "argument B")->capture_default_str();

   CLI11_PARSE(app, argc, argv);

   // --- Register atexit here for unloading at deterministic order ----------
   auto res = atexit(atexit_dlclose);
   if (res != 0)
   {
      cout << "atexit() registration failed!" << endl;
      cout << "Not continuing since SO cannot be safely unloaded" << endl;
      return EXIT_FAILURE;
   }

   // --- Load the available operations --------------------------------------
   Directory_t op_list;
   bool encountered_error = false;
   for(auto const& dll : load_dlls)
   {
      fs::path path(dll);
      if (fs::exists(path))
      {
         cout << "Found " << path << ", loading... ";
      }
      else
      {
         cout << "Couldn't find " << path << ", aborting!" << endl;
         encountered_error = true;
         break;
      }

      void *handle = dlopen(path.c_str(), RTLD_LAZY);
      if (handle)
      {
         SO_HANDLES.entries.push_back(handle);
         cout << "as " << handle << endl;
      }
      else
      {
         cout << "Error loading " << path << "!" << endl;
         encountered_error = true;
         break;
      }

      auto operations_list = dlsym(handle, "get_operations");
      auto handle_error = dlerror();
      if (handle_error)
      {
         cout << "Encountered dlsym error: " << handle_error << endl;
         encountered_error = true;
         break;
      }
      auto get_operations = reinterpret_cast<Directory_t *(*)()>(operations_list);
      op_list.merge(*get_operations());
   }
   if (encountered_error) return EXIT_FAILURE;

   cout << "Available operators:" << endl;
   for (const auto &[key, value] : op_list)
   {
      cout << "  " << key << endl;
   }
   if (operator_name.empty())
   {
      cout << "No operator requested, finishing here." << endl;
      return EXIT_SUCCESS;
   }

   // --- Execute selected operation -----------------------------------------
   {
      // Only location where a ptr to SO is allocated
      // Scoping ensures that op dtor is called while SO is still loaded
      //  otherwise risking a segfault
      unique_ptr<Operation> op;

      if ("Addition" == operator_name)
      {
         op = op_list.at("Addition")("A", "B", "A + B");
      }
      else if ("Subtraction" == operator_name)
      {
         op = op_list.at("Subtraction")("A", "B", "A - B");
      }
      else if ("Multiplication" == operator_name)
      {
         op = op_list.at("Multiplication")("A", "B", "A x B");
      }
      else if ("Division" == operator_name)
      {
         op = op_list.at("Division")("A", "B", "A : B");
      }
      else if ("Ln" == operator_name)
      {
         op = op_list.at("Ln")("A", "", "Natural log(A)");
      }
      else if ("Log10" == operator_name)
      {
         op = op_list.at("Log10")("A", "", "log10(A)");
      }
      else if ("Log2" == operator_name)
      {
         op = op_list.at("Log2")("A", "", "log2(A)");
      }
      else
      {
         cout << "Unrecognized operator -- rerun with no selection to see list" << endl;
         return EXIT_FAILURE;
      }

      auto res = op->operation(arg_a, arg_b);
      cout << "Result of " << op->describe() << " is " << res << endl;
   }

   cout << "Normal ending" << endl;
   return EXIT_SUCCESS;
}