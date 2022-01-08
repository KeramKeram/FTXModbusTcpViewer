#include "MainView.h"
#include <memory>  // for allocator, __shared_ptr_access
#include <stdlib.h>// for EXIT_SUCCESS
#include <string>  // for string, operator+, basic_string, to_string, char_traits
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"    // for ftxui
#include "ftxui/component/component.hpp"         // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"    // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"// for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                // for text, Element, operator|, window, flex, vbox


#include "ftxui/dom/node.hpp"    // for Render
#include "ftxui/screen/box.hpp"  // for ftxui
#include "ftxui/screen/color.hpp"// for Color, Color::Blue, Color::Cyan, Color::White

#include <ftxui/dom/elements.hpp>// for color, Fit, LIGHT, align_right, bold, DOUBLE
#include <ftxui/dom/table.hpp>   // for Table, TableSelection

namespace views {
    using namespace ftxui;
    void MainView::show() {
        float focus_x = 0.0f;
        float focus_y = 0.0f;

        auto slider_x = Slider("x", &focus_x, 0.f, 1.f, 0.01f);
        auto slider_y = Slider("y", &focus_y, 0.f, 1.f, 0.01f);

        auto renderer = Renderer(
                Container::Vertical({
                        slider_x,
                        slider_y,
                }),
                [&] {
                    auto title = "focusPositionRelative(" +      //
                                 std::to_string(focus_x) + ", " +//
                                 std::to_string(focus_y) + ")";  //
                    return vbox({
                                   text(title),
                                   separator(),
                                   slider_x->Render(),
                                   slider_y->Render(),
                                   separator(),
                                   make_grid() | focusPositionRelative(focus_x, focus_y) |
                                           frame | flex,
                           }) |
                           border;
                });

        auto screen = ScreenInteractive::Fullscreen();
        screen.Loop(renderer);
    }

    Element MainView::make_box(int x, int y) {
        std::string title = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        return text(title) | center | size(WIDTH, EQUAL, 6) |
               size(HEIGHT, EQUAL, 3) | border |
               bgcolor(Color::HSV(x * 255 / 15, 255, y * 255 / 15));
    };

    Element MainView::make_grid() {
        std::vector<Elements> rows;
        for (int i = 0; i < 15; i++) {
            std::vector<Element> cols;
            for (int j = 0; j < 15; j++) {
                cols.push_back(make_box(i, j));
            }
            rows.push_back(cols);
        }

        return gridbox(rows);
    };

}// namespace views