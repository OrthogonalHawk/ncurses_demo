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
 * @file     ncurses_colors.h
 * @author   OrthogonalHawk
 * @date     03-Apr-2021
 *
 * @brief    Helper methods to manage ncurses colors.
 *
 * @section  DESCRIPTION
 *
 * Defines helper methods for working with ncurses colors.
 *
 * @section  HISTORY
 *
 * 03-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __NCURSES_COLORS_H__
#define __NCURSES_COLORS_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <ncurses.h>


namespace ncurses_cpp {

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

/******************************************************************************
 *                              ENUMS & TYPEDEFS
 *****************************************************************************/

typedef enum {
    NCURSES_CPP_TXT_COLOR_DEFAULT = 0,
    NCURSES_CPP_TXT_COLOR_BLACK,
    NCURSES_CPP_TXT_COLOR_RED,
    NCURSES_CPP_TXT_COLOR_GREEN,
    NCURSES_CPP_TXT_COLOR_YELLOW,
    NCURSES_CPP_TXT_COLOR_BLUE,
    NCURSES_CPP_TXT_COLOR_MAGENTA,
    NCURSES_CPP_TXT_COLOR_CYAN,
    NCURSES_CPP_TXT_COLOR_WHITE
} ncurses_cpp_text_colors_e;


/******************************************************************************
 *                                  MACROS
 *****************************************************************************/

/******************************************************************************
 *                           FUNCTION DECLARATION
 *****************************************************************************/

bool init_colors(int text_background_color);

bool init_colors(void);


/******************************************************************************
 *                            CLASS DECLARATION
 *****************************************************************************/

}; /* end of the ncurses_cpp namespace */

#endif // __NCURSES_COLORS_H__
