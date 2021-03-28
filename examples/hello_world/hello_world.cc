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
 * @file     hello_world.cc
 * @author   OrthogonalHawk
 * @date     28-Mar-2021
 *
 * @brief    ncurses 'hello world' example from https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
 *
 * @section  DESCRIPTION
 *
 * 'hello world' ncurses example from https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/helloworld.html
 *
 * @section  HISTORY
 *
 * 28-Mar-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <ncurses.h>


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

int main(void)
{
    initscr();                  /* Start curses mode                */
    printw("Hello World !!!");  /* Print Hello World                */
    refresh();                  /* Print it on to the real screen   */
    getch();                    /* Wait for user input              */
    endwin();                   /* End curses mode                  */

    return 0;
}
