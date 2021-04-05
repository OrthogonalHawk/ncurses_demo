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

#include "ncurses_window.h"


/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

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

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    initscr();                  /* Start curses mode         */
    ncurses_cpp::init_colors(); /* Start the color functionality */
    cbreak();                   /* Line buffering disabled, Pass on
                                 * everything to me         */
    keypad(stdscr, TRUE);       /* I need that nifty F1     */
    noecho();
    curs_set(0);

    attron(COLOR_PAIR(ncurses_cpp::NCURSES_CPP_TXT_COLOR_MAGENTA));
    printw("Press F1 to exit");
    refresh();
    attroff(COLOR_PAIR(ncurses_cpp::NCURSES_CPP_TXT_COLOR_MAGENTA));

    auto my_window = ncurses_cpp::ncurses_window(true);
    my_window.create_window(10, 20, 2, 2);
    my_window.add_field<std::string>(1, 1, "test_str", "%s", "hello");
    my_window.add_field<int32_t>(2, 4, "test_int", "%d", 100);
    my_window.add_field<uint32_t>(5, 8, "test_uint", "0x%08x", 0xFEEDBEEF);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    my_window.update_field<std::string>("test_str", "world", ncurses_cpp::NCURSES_CPP_TXT_COLOR_GREEN);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    my_window.update_field<int32_t>("test_int", 255, ncurses_cpp::NCURSES_CPP_TXT_COLOR_RED);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    my_window.update_field<uint32_t>("test_uint", 0xBEEFBEEF, ncurses_cpp::NCURSES_CPP_TXT_COLOR_YELLOW);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    int ch;
    while ((ch = getch()) != KEY_F(1))
    { }

    endwin();            /* End curses mode          */
    return 0;
}
