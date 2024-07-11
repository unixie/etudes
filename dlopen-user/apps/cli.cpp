#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include <CLI/CLI.hpp>

#include <dlfcn.h>
#include "operation.hpp"

using namespace std;


// --- from dlopen ----------------------------------------------------------
static struct Handles
{
   vector<void *> entries;
   ~Handles() {}
} SO_HANDLES;

void atexit_dlclose()
{
   for (auto h: SO_HANDLES.entries) auto eret = dlclose(h);
}

// --- FTXUI 5.0 -------------------------------------------------------------
// TUI based on examples/component/gallery.cpp
using namespace ftxui;

// Display a component nicely with a title on the left.
Component Wrap(string name, Component component) {
  return Renderer(component, [name, component] {
    return hbox({
               text(name) | size(WIDTH, EQUAL, 8),
               separator(),
               component->Render() | xflex,
           }) |
           xflex;
  });
}

// === main =================================================================
int
main(int argc, char *argv[])
{
   namespace fs = std::filesystem;

   // --- CLI argument parsing -----------------------------------------------
   CLI::App app{"tuiCalc: command line calculator"};
   app.footer("\n"
      "Notes:\n"
      " o When loading so from current directory, prepend filename with './'"
      "\n\n"
   );

   vector<string> load_dlls;
   app.add_option("-l,--load", load_dlls, "Operators DLL/SO to load")->required()->delimiter(' ');

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
      if (!fs::exists(path))
      {
         cout << "Couldn't find " << path << ", aborting!" << endl;
         encountered_error = true;
         break;
      }

      void *handle = dlopen(path.c_str(), RTLD_LAZY);
      if (!handle)
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


   // --- FTXUI --------------------------------------------------------------

   // Widgets
   vector<string> radiobox_entries;
   radiobox_entries.reserve(op_list.size());
   for (const auto &[key, value] : op_list) radiobox_entries.push_back(key);
   int radiobox_selected = 0;
   auto radiobox = Radiobox(&radiobox_entries, &radiobox_selected);
   radiobox = Wrap("Operators", radiobox);

   string arg_a_value;
   auto arg_a = Input(&arg_a_value, "Argument A");
   arg_a = Wrap("A", arg_a);

   string arg_b_value;
   auto arg_b = Input(&arg_b_value, "Argument B");
   arg_b = Wrap("B", arg_b);

   string result_value;
   auto result = Input(&result_value, "Result");
   result = Wrap("Result", result);

   string button_label = "Calculate";
   auto button = Button(&button_label, [&]
      {
         // Don't need the description strings here
         unique_ptr<Operation> op = op_list.at(radiobox_entries[radiobox_selected])("","","");
         result_value = to_string(op->operation(stod(arg_a_value), stod(arg_b_value)));
      }
   );
   button |= size(WIDTH, EQUAL, button_label.length()+2); // +2 to account for border

   // Navigation order
   auto navigation = Container::Vertical({
         radiobox,
         arg_a,
         arg_b,
         result,
         button,
   });

   // Layout
   auto components = Renderer(navigation, [&] {
      return vbox({
         hbox({
            separatorEmpty(),
            radiobox->Render() | yflex_grow,
            separatorEmpty(),
            separator(),
            separatorEmpty(),
            vbox({
                  arg_a->Render(),
                  separator(),
                  arg_b->Render(),
                  separatorDouble(),
                  result->Render()
            }),
            separatorEmpty()
         }) | xflex | size(WIDTH, GREATER_THAN, 40) | border,
         hbox({
            filler(),
            button->Render(),
            filler()
         })
      });
   });

   // Screen Loop
   auto screen = ScreenInteractive::FitComponent();

   components |= CatchEvent(
      [&](Event event) {
         if (event == Event::Character('q') || event == Event::Escape)
         {
            screen.ExitLoopClosure()();
            return true;
         }
         return false;
      });

   screen.Loop(components);

   return EXIT_SUCCESS;
}