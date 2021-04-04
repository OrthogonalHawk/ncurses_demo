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
 * @file     ncurses_colors.cc
 * @author   OrthogonalHawk
 * @date     03-Apr-2021
 *
 * @brief    Implements helper methods for working with ncurses colors.
 *
 * @section  DESCRIPTION
 *
 * Implements helper methods for working with ncurses colors.
 *
 * @section  HISTORY
 *
 * 03-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <ncurses.h>

#include "ncurses_colors.h"


namespace ncurses_cpp {

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

bool init_colors(int text_background_color)
{
    static bool init_complete = false;

    if (!init_complete)
    {
        printf("Configuring ncurses_cpp colors\n");
        start_color();
        init_pair(NCURSES_CPP_TXT_COLOR_BLACK,    COLOR_BLACK,    text_background_color);
        init_pair(NCURSES_CPP_TXT_COLOR_RED,      COLOR_RED,      text_background_color);
        init_pair(NCURSES_CPP_TXT_COLOR_GREEN,    COLOR_GREEN,    text_background_color);
        init_pair(NCURSES_CPP_TXT_COLOR_YELLOW,   COLOR_YELLOW,   text_background_color);
        init_pair(NCURSES_CPP_TXT_COLOR_BLUE,     COLOR_BLUE,     text_background_color);
        init_pair(NCURSES_CPP_TXT_COLOR_MAGENTA,  COLOR_MAGENTA,  text_background_color);
        init_pair(NCURSES_CPP_TXT_COLOR_CYAN,     COLOR_CYAN,     text_background_color);
        init_pair(NCURSES_CPP_TXT_COLOR_WHITE,    COLOR_WHITE,    text_background_color);
        init_complete = true;
    }

    return init_complete;
}

bool init_colors(void)
{
    return init_colors(COLOR_BLACK);
}


/******************************************************************************
 *                           CLASS IMPLEMENTATION
 *****************************************************************************/

} /* end ncurses_cpp namespace */
