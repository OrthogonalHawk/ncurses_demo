/******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2021 OrthogonalHawk
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * @file     status_monitor.cc
 * @author   OrthogonalHawk
 * @date     02-Apr-2021
 *
 * @brief    Example that shows how to create a 'status monitor' display that
 *            periodically updates based on new information.
 *
 * @section  DESCRIPTION
 *
 * This 'status monitor' example shows how to create an interface that periodically
 *  updates based on new information.
 *
 * @section  HISTORY
 *
 * 02-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <chrono>
#include <thread>

#include <ncurses.h>

#include "ncurses_ui.h"
#include "ncurses_window.h"


/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

const std::string DEMO_UI_WINDOW_NAME = "main";


/******************************************************************************
 *                              ENUMS & TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *                                  MACROS
 *****************************************************************************/

/******************************************************************************
 *                           FUNCTION IMPLEMENTATION
 *****************************************************************************/

/******************************************************************************
 *                           CLASS IMPLEMENTATION
 *****************************************************************************/

class demo_ui : public ncurses_cpp::ncurses_ui
{
public:

    demo_ui(void)
      : ncurses_ui(KEY_F(1), 1000),
        m_ran_tasks(false)
    {
        auto my_window = std::make_shared<ncurses_cpp::ncurses_window>(DEMO_UI_WINDOW_NAME, true);
        my_window->create_window(10, 20, 2, 2);
        my_window->add_field<std::string>(1, 1, "test_str", "%s", "hello", ncurses_cpp::NCURSES_CPP_TXT_COLOR_CYAN);
        my_window->add_field<int32_t>(2, 4, "test_int", "%d", 100);
        my_window->add_field<uint32_t>(5, 8, "test_uint", "0x%08x", 0xFEEDBEEF);
        my_window->add_field<float>(1, 7, "test_float", "%.1f", 0.0);
        my_window->add_field_thresholds<float>("test_float", std::make_pair<float, float>(0.0, 75.0), ncurses_cpp::NCURSES_CPP_TXT_COLOR_GREEN);
        my_window->add_field_thresholds<float>("test_float", std::make_pair<float, float>(75.0, 90.0), ncurses_cpp::NCURSES_CPP_TXT_COLOR_YELLOW);
        my_window->add_field_thresholds<float>("test_float", std::make_pair<float, float>(90.0, 100.0), ncurses_cpp::NCURSES_CPP_TXT_COLOR_RED);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        add_window(my_window);
    }

    void handle_periodic_tasks(void) override
    {
        if (!m_ran_tasks)
        {
            if(!update_field<std::string>(DEMO_UI_WINDOW_NAME, "test_str", "world", ncurses_cpp::NCURSES_CPP_TXT_COLOR_GREEN))
            {
                printf("Failed to update!!!\n");
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));

            update_field<int32_t>(DEMO_UI_WINDOW_NAME, "test_int", 255, ncurses_cpp::NCURSES_CPP_TXT_COLOR_RED);
            std::this_thread::sleep_for(std::chrono::seconds(1));

            update_field<uint32_t>(DEMO_UI_WINDOW_NAME, "test_uint", 0xBEEFBEEF, ncurses_cpp::NCURSES_CPP_TXT_COLOR_YELLOW);
            std::this_thread::sleep_for(std::chrono::seconds(1));

            update_field<float>(DEMO_UI_WINDOW_NAME, "test_float", 50.0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            update_field<float>(DEMO_UI_WINDOW_NAME, "test_float", 60.0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            update_field<float>(DEMO_UI_WINDOW_NAME, "test_float", 76.0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            update_field<float>(DEMO_UI_WINDOW_NAME, "test_float", 91.0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            update_field<float>(DEMO_UI_WINDOW_NAME, "test_float", 100.0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            update_field<float>(DEMO_UI_WINDOW_NAME, "test_float", 101.0);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            m_ran_tasks = true;
        }
    }

private:

    bool                                             m_ran_tasks;
};

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    demo_ui my_ui;
    my_ui.run();

    return 0;
}
