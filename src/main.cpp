

#include <memory> // for allocator, __shared_ptr_access, shared_ptr
#include <string> // for string, basic_string
#include <vector> // for vector
#include <iostream>

#include "ftxui/component/captured_mouse.hpp"     // for ftxui
#include "ftxui/component/component.hpp"          // for Radiobox, Horizontal, Menu, Renderer, Tab
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp" // for ScreenInteractive
#include "ftxui/dom/elements.hpp"                 // for Element, separator, hbox, operator|, border
#include "ftxui/util/ref.hpp"                     // for Ref

using namespace ftxui;

int main(int argc, const char *argv[])
{
    std::vector<std::string> tab_values{
        "Sampling rate",
        "f factor",
        "Threshold",
    };
    int tab_selected = 0;
    auto tab_menu = Menu(&tab_values, &tab_selected);

    std::vector<std::string> tab_1_entries{
        "1 Hz",
        "5 Hz",
        "10 Hz",
        "19 Hz",
    };
    int tab_1_selected = 0;

    std::string f_factor;
    Component input_f_factor = Input(&f_factor, "8");

    std::string threshold;
    Component input_threshold = Input(&threshold, "8");

    // std::string btn1 = "Write to GIP";
    // auto button_stuff = printStuff();
    // Component button1 = Button(&btn1,&button_stuff );

    auto tab_container = Container::Tab(
        {Radiobox(&tab_1_entries, &tab_1_selected),
         input_f_factor,
         input_threshold},
        &tab_selected);

    auto container = Container::Horizontal({
        tab_menu,
        tab_container,
    });
    int sum = 8;
    auto settings = Renderer(container, [&]
                             {
                                 return hbox({
                                            tab_menu->Render(),
                                            separator(),

                                            vbox({
                                                tab_container->Render(),
                                            }) | flex,

                                        }) |
                                        border;
                             });
    auto value = 0;

    auto button = Button("[Send To Gip]", [&]
                         { value++; });
    auto colorred = bgcolor(Color::Red);
    
    if (std::stoi(f_factor))
    {
        /* code */
    }
    
    
    auto stat = Renderer(button, [&]
                         {
                             return vbox({hbox({
                                              button->Render(),
                                              separator(),
                                              vbox({
                                                  hbox(text(" SELECTED sampling rate: " + std::to_string(tab_1_selected))),

                                                  hbox( text(" f factor : ") | colorred  , input_f_factor->Render()),

                                                  hbox(text(" threshold : "), input_threshold->Render()),
                                              }),

                                          }),
                                          separator(),
                                          hbox({
                                              gauge(value * 0.01f),
                                          })}) |
                                    border;
                         });

    auto composition = Container::Vertical({settings, stat});

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(composition);
}
