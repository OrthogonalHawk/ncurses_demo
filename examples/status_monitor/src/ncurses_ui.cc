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
 * @file     ncurses_ui.cc
 * @author   OrthogonalHawk
 * @date     27-Apr-2021
 *
 * @brief    Implements a container class for managing an ncurses user interface.
 *
 * @section  DESCRIPTION
 *
 * Implements a container class for managing an ncurses user interface.
 *
 * @section  HISTORY
 *
 * 27-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <ncurses.h>

#include "ncurses_colors.h"

#include "ncurses_ui.h"


namespace ncurses_cpp {

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

const uint32_t DEFAULT_PERIODIC_TASK_INTERVAL_IN_MS = 1000;


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

ncurses_ui::ncurses_ui(void)
  : ncurses_ui(KEY_F(1), DEFAULT_PERIODIC_TASK_INTERVAL_IN_MS)
{ }

ncurses_ui::ncurses_ui(int shutdown_key, uint32_t periodic_task_interval_in_ms)
  : m_shutdown_key(shutdown_key),
    m_periodic_task_interval_in_ms(periodic_task_interval_in_ms)
{
    setup_ncurses();
}

ncurses_ui::~ncurses_ui(void)
{
    cleanup_ncurses();
}

bool ncurses_ui::run(void)
{
    m_last_periodic_task_invocation = std::chrono::steady_clock::now();

    int ch = m_shutdown_key;
    while (true)
    {
        ch = getch();

        if (ch != ERR)
        {
            if (ch == m_shutdown_key)
            {
                break;
            }

            /* pass the received character to a derived class */
            handle_char(ch);
        }

        auto current_time = std::chrono::steady_clock::now();
        auto ms_since_last_periodic_task_invocation = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - m_last_periodic_task_invocation).count();

        if (ms_since_last_periodic_task_invocation >= m_periodic_task_interval_in_ms)
        {
            handle_periodic_tasks();
            m_last_periodic_task_invocation = std::chrono::steady_clock::now();
        }
    }

    return true;
}

void ncurses_ui::handle_char(int next_char)
{
    /* nothing to do here; override in a derived class */
    (void)next_char;
}

void ncurses_ui::handle_periodic_tasks(void)
{
    /* nothing to do here; override in a derived class */
}

void ncurses_ui::setup_ncurses(void)
{
    initscr();                      /* Start curses mode         */
    ncurses_cpp::init_colors();     /* Start the color functionality */
    cbreak();                       /* Line buffering disabled, Pass on
                                     * everything to me         */
    keypad(stdscr, TRUE);           /* I need that nifty F1     */
    noecho();
    curs_set(0);

    timeout(m_periodic_task_interval_in_ms / 4);

    attron(COLOR_PAIR(ncurses_cpp::NCURSES_CPP_TXT_COLOR_MAGENTA));
    printw("Press F1 to exit");
    refresh();
    attroff(COLOR_PAIR(ncurses_cpp::NCURSES_CPP_TXT_COLOR_MAGENTA));
}

void ncurses_ui::cleanup_ncurses(void)
{
    for (auto iter = m_windows_by_name.begin(); iter != m_windows_by_name.end(); ++iter)
    {
        iter->second->cleanup_window();
    }
    m_windows_by_name.clear();

    endwin();                       /* End curses mode          */
}

} /* end ncurses_cpp namespace */
