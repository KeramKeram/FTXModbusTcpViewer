#pragma once
#include "IView.h"

#include <memory>  // for allocator, __shared_ptr_access
#include <stdlib.h>// for EXIT_SUCCESS
#include <string>  // for string, operator+, basic_string, to_string, char_traits
#include <utility>
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
    constexpr int VIEW_BOX_WIDTH = 8;
    constexpr int VIEW_BOX_HEIGHT = 3;

    class MainView : public IView {
    public:
        ~MainView() override = default;

        void show() override;

    private:
        struct BoxParameter {
            BoxParameter(int mXPosition, int mYPosition, std::string mBoxValue, uint8_t mHue,
                         uint8_t mSaturation, uint8_t mHsvValue)
                : mXPosition(mXPosition), mYPosition(mYPosition), mBoxValue(std::move(mBoxValue)), mHue(mHue),
                  mSaturation(mSaturation), mHSVValue(mHsvValue){};
            ~BoxParameter() = default;
            int mXPosition;
            int mYPosition;
            std::string mBoxValue;
            uint8_t mHue;
            uint8_t mSaturation;
            uint8_t mHSVValue;
        };

        Element mGrid;

        static Element makeBox(const BoxParameter &param);
        Element makeGrid();
        static void updateBoxParameters(MainView::BoxParameter &param, int i, int j, int hue, int hsv);
    };
}// namespace views