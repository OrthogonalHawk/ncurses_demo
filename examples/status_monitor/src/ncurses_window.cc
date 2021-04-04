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
 * @file     ncurses_window.cc
 * @author   OrthogonalHawk
 * @date     02-Apr-2021
 *
 * @brief    Implements a container class for managing an ncurses window.
 *
 * @section  DESCRIPTION
 *
 * Implements a container class for managing an ncurses window.
 *
 * @section  HISTORY
 *
 * 02-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <ncurses.h>

#include "ncurses_window.h"


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

ncurses_window::ncurses_window(void)
  : ncurses_window(true)
{ }

ncurses_window::ncurses_window(bool outline_window)
  : m_window(nullptr),
    m_outline_window(outline_window)
{ }

ncurses_window::~ncurses_window(void)
{
    cleanup_window();
}

bool ncurses_window::create_window(uint32_t height, uint32_t width, uint32_t start_x, uint32_t start_y)
{
    bool ret = false;

    if (nullptr == m_window)
    {
        m_window = newwin(height, width, start_x, start_y);
        if (nullptr != m_window)
        {
            if (m_outline_window)
            {
                /* use default characters for the vertical and horiziontal lines */
                box(m_window, 0 , 0);
                wrefresh(m_window);
            }
            ret = true;
        }
    }

    return ret;
}

bool ncurses_window::cleanup_window(void)
{
    bool ret = false;

    m_str_fields.clear();
    m_int32_fields.clear();
    m_uint32_fields.clear();

    if (nullptr != m_window)
    {
        /* TODO cleanup the screen */

        delwin(m_window);
        m_window = nullptr;
    }

    return ret;
}

bool ncurses_window::add_str_field(uint32_t x, uint32_t y, std::string field_name, std::string format_str, std::string default_val)
{
    bool ret = false;

    if (m_str_fields.count(field_name) == 0)
    {
        m_str_fields[field_name] = ncurses_window::str_field_info_t(x, y, format_str, default_val);
        ret = update_str_field(field_name, default_val);
    }

    return ret;
}

bool ncurses_window::add_int32_field(uint32_t x, uint32_t y, std::string field_name, std::string format_str, int32_t default_val)
{
    bool ret = false;

    if (m_int32_fields.count(field_name) == 0)
    {
        m_int32_fields[field_name] = ncurses_window::int32_field_info_t(x, y, format_str, default_val);
        ret = update_int32_field(field_name, default_val);
    }

    return ret;
}

bool ncurses_window::add_uint32_field(uint32_t x, uint32_t y, std::string field_name, std::string format_str, uint32_t default_val)
{
    bool ret = false;

    if (m_uint32_fields.count(field_name) == 0)
    {
        m_uint32_fields[field_name] = ncurses_window::uint32_field_info_t(x, y, format_str, default_val);
        ret = update_uint32_field(field_name, default_val);
    }

    return ret;
}

bool ncurses_window::update_str_field(std::string field_name, std::string field_val)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_str_fields.count(field_name) > 0)
    {
        auto field_info = m_str_fields[field_name];
        if (OK == mvwprintw(m_window, field_info.y, field_info.x, field_info.format_str.c_str(), field_val.c_str()))
        {
            wrefresh(m_window);
            ret = true;
        }
    }

    return ret;
}

bool ncurses_window::update_int32_field(std::string field_name, int32_t field_val)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_int32_fields.count(field_name) > 0)
    {
        auto field_info = m_int32_fields[field_name];
        if (OK == mvwprintw(m_window, field_info.y, field_info.x, field_info.format_str.c_str(), field_val))
        {
            wrefresh(m_window);
            ret = true;
        }
    }

    return ret;
}

bool ncurses_window::update_uint32_field(std::string field_name, uint32_t field_val)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_uint32_fields.count(field_name) > 0)
    {
        auto field_info = m_uint32_fields[field_name];
        if (OK == mvwprintw(m_window, field_info.y, field_info.x, field_info.format_str.c_str(), field_val))
        {
            wrefresh(m_window);
            ret = true;
        }
    }

    return ret;
}

} /* end ncurses_cpp namespace */
