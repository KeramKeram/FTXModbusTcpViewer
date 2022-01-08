#pragma once
#include "IView.h"

#include <memory>  // for allocator, __shared_ptr_access
#include <stdlib.h>// for EXIT_SUCCESS
#include <string>  // for string, operator+, basic_string, to_string, char_traits
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"    // for ftxui
#include "ftxui/component/component.hpp"         // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"    // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"// for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                // for text, Element, operator|, window, flex, vbox

namespace views {
    using namespace ftxui;

    constexpr int VIEW_COLUMNS = 10;
    constexpr int VIEW_ROWS = 10;
    constexpr int VIEW_BOX_WIDHT = 6;
    constexpr int VIEW_BOX_HEIGHT = 3;

    class MainView : public IView {
    public:
        ~MainView() override = default;

        void show() override;

    private:
        Element makeBox(int x, int y, std::string &value);
        Element makeGrid();
    };
}// namespace views