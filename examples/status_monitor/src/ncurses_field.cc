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
 * @file     ncurses_field.cc
 * @author   OrthogonalHawk
 * @date     04-Apr-2021
 *
 * @brief    Implements a container class to organize fields within an ncurses
 *            window object.
 *
 * @section  DESCRIPTION
 *
 * Implements a container class to organize fields within an ncurses window
 *  object.
 *
 * @section  HISTORY
 *
 * 04-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <algorithm>

#include <ncurses.h>

#include "ncurses_field.h"


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

/******************************************************************************
 *                           CLASS IMPLEMENTATION
 *****************************************************************************/

template <typename T>
ncurses_field<T>::ncurses_field(void)
  : m_window(nullptr),
    m_x(0),
    m_y(0),
    m_default_color(NCURSES_CPP_TXT_COLOR_DEFAULT)
{ }

template <typename T>
ncurses_field<T>::~ncurses_field(void)
{ }

template <typename T>
bool ncurses_field<T>::create_field(WINDOW * window, uint32_t x, uint32_t y, std::string format_str, T default_val)
{
    return create_field(window, x, y, format_str, default_val, NCURSES_CPP_TXT_COLOR_DEFAULT);
}

template <typename T>
bool ncurses_field<T>::create_field(WINDOW * window, uint32_t x, uint32_t y, std::string format_str, T default_val, ncurses_cpp_text_colors_e default_color)
{
    bool ret = false;

    if (nullptr != window)
    {
        m_window = window;
        m_x = x;
        m_y = y;
        m_format_str = format_str;
        m_current_value = default_val;
        m_default_color = default_color;
    }

    return ret;
}

template <typename T>
bool ncurses_field<T>::update_field(void)
{
    /* default implementation does not exist; this must be overridden by a derived class */
    return true;
}

template <typename T>
bool ncurses_field<T>::update_field(T field_val)
{
    return update_field(field_val, m_default_color);
}

template <>
bool ncurses_field<std::string>::update_field(std::string field_val, ncurses_cpp_text_colors_e field_color)
{
    bool ret = false;

    if (nullptr != m_window)
    {
        if (NCURSES_CPP_TXT_COLOR_DEFAULT != field_color)
        {
            wattron(m_window, COLOR_PAIR(field_color));
        }

        if (OK == mvwprintw(m_window, m_y, m_x, m_format_str.c_str(), field_val.c_str()))
        {
            wrefresh(m_window);
            ret = true;
        }

        if (NCURSES_CPP_TXT_COLOR_DEFAULT != field_color)
        {
            wattroff(m_window, COLOR_PAIR(field_color));
        }
    }

    return ret;
}

template <typename T>
bool ncurses_field<T>::update_field(T field_val, ncurses_cpp_text_colors_e field_color)
{
    bool ret = false;

    if (nullptr != m_window)
    {
        if (NCURSES_CPP_TXT_COLOR_DEFAULT != field_color)
        {
            wattron(m_window, COLOR_PAIR(field_color));
        }

        if (OK == mvwprintw(m_window, m_y, m_x, m_format_str.c_str(), field_val))
        {
            wrefresh(m_window);
            ret = true;
        }

        if (NCURSES_CPP_TXT_COLOR_DEFAULT != field_color)
        {
            wattroff(m_window, COLOR_PAIR(field_color));
        }
    }

    return ret;
}

/* explicit instantiations of the ncurses_field class */
template class ncurses_field<std::string>;
template class ncurses_field<int32_t>;
template class ncurses_field<uint32_t>;
template class ncurses_field<float>;
template class ncurses_field<double>;

} /* end ncurses_cpp namespace */
