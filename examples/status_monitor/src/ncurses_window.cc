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

#include <algorithm>

#include <ncurses.h>

#include "ncurses_window.h"


namespace ncurses_cpp {

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

const std::string TITLE_FIELD_NAME = "title";


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

//template <> bool ncurses_window::update_field<std::string>(std::string field_name, std::string field_val, ncurses_cpp_text_colors_e field_color);
//template <> bool ncurses_window::_add_field<std::string>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, std::string default_val);
/*
template <> bool ncurses_window::add_field<std::string>(uint32_t x, uint32_t y, std::string field_name, std::string format_str, std::string default_val);
template <> bool ncurses_window::add_field<int32_t>(uint32_t x, uint32_t y, std::string field_name, std::string format_str, int32_t default_val);
template <> bool ncurses_window::add_field<uint32_t>(uint32_t x, uint32_t y, std::string field_name, std::string format_str, uint32_t default_val);
template <> bool ncurses_window::add_field<float>(uint32_t x, uint32_t y, std::string field_name, std::string format_str, float default_val);
template <> bool ncurses_window::add_field<double>(uint32_t x, uint32_t y, std::string field_name, std::string format_str, double default_val);

template <> bool ncurses_window::update_field<std::string>(std::string field_name, std::string field_val);
template <> bool ncurses_window::update_field<int32_t>(std::string field_name, int32_t field_val);
template <> bool ncurses_window::update_field<uint32_t>(std::string field_name, uint32_t field_val);
template <> bool ncurses_window::update_field<float>(std::string field_name, float field_val);
template <> bool ncurses_window::update_field<double>(std::string field_name, double field_val);

template <> bool ncurses_window::update_field<std::string>(std::string field_name, std::string field_val, ncurses_cpp_text_colors_e field_color);
template <> bool ncurses_window::update_field<int32_t>(std::string field_name, int32_t field_val, ncurses_cpp_text_colors_e field_color);
template <> bool ncurses_window::update_field<uint32_t>(std::string field_name, uint32_t field_val, ncurses_cpp_text_colors_e field_color);
template <> bool ncurses_window::update_field<float>(std::string field_name, float field_val, ncurses_cpp_text_colors_e field_color);
template <> bool ncurses_window::update_field<double>(std::string field_name, double field_val, ncurses_cpp_text_colors_e field_color);

template <> bool ncurses_window::_add_field<std::string>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, std::string default_val);
template <> bool ncurses_window::_add_field<int32_t>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, int32_t default_val);
template <> bool ncurses_window::_add_field<uint32_t>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, uint32_t default_val);
template <> bool ncurses_window::_add_field<float>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, float default_val);
template <> bool ncurses_window::_add_field<double>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, double default_val);
*/

const std::vector<std::string> ncurses_window::RESERVED_FIELD_NAMES = { TITLE_FIELD_NAME };

bool ncurses_window::is_reserved_field(std::string field_name)
{
    auto iter = std::find(RESERVED_FIELD_NAMES.begin(), RESERVED_FIELD_NAMES.end(), field_name);
    if (iter == RESERVED_FIELD_NAMES.end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

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
            m_height = height;
            m_width = width;

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

template <typename T>
bool ncurses_window::update_field(std::string field_name, T field_val)
{
    return update_field<T>(field_name, field_val, NCURSES_CPP_TXT_COLOR_DEFAULT);
}

template <>
bool ncurses_window::update_field<std::string>(std::string field_name, std::string field_val, ncurses_cpp_text_colors_e field_color)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_str_fields.count(field_name) > 0)
    {
        m_str_fields[field_name].update_field(field_val, field_color);
    }

    return ret;
}

template <>
bool ncurses_window::update_field<int32_t>(std::string field_name, int32_t field_val, ncurses_cpp_text_colors_e field_color)
{
    bool ret = false;

    if (nullptr != m_window)
    {
        if (m_int32_fields.count(field_name) > 0)
        {
            ret = m_int32_fields[field_name].update_field(field_val, field_color);
        }
    }

    return ret;
}

template <>
bool ncurses_window::update_field<uint32_t>(std::string field_name, uint32_t field_val, ncurses_cpp_text_colors_e field_color)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_uint32_fields.count(field_name) > 0)
    {
        m_uint32_fields[field_name].update_field(field_val, field_color);
    }

    return ret;
}

template <>
bool ncurses_window::update_field<float>(std::string field_name, float field_val, ncurses_cpp_text_colors_e field_color)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_float_fields.count(field_name) > 0)
    {
        m_float_fields[field_name].update_field(field_val, field_color);
    }

    return ret;
}

template <>
bool ncurses_window::update_field<double>(std::string field_name, double field_val, ncurses_cpp_text_colors_e field_color)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_double_fields.count(field_name) > 0)
    {
        m_double_fields[field_name].update_field(field_val, field_color);
    }

    return ret;
}

template <>
bool ncurses_window::_add_field<std::string>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, std::string default_val)
{
    bool ret = false;

    if ( (!is_reserved_field(field_name) || allow_reserved_fields) &&
         m_str_fields.count(field_name) == 0 )
    {
        auto new_field = ncurses_field<std::string>();
        new_field.create_field(m_window, x, y, format_str, default_val);
        m_str_fields[field_name] = new_field;
        ret = m_str_fields[field_name].update_field(default_val);
    }

    return ret;
}

template <>
bool ncurses_window::_add_field<int32_t>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, int32_t default_val)
{
    bool ret = false;

    if ( (!is_reserved_field(field_name) || allow_reserved_fields) &&
         m_int32_fields.count(field_name) == 0 )
    {
        auto new_field = ncurses_field<int32_t>();
        new_field.create_field(m_window, x, y, format_str, default_val);
        m_int32_fields[field_name] = new_field;
        ret = m_int32_fields[field_name].update_field(default_val);
    }

    return ret;
}

template <>
bool ncurses_window::_add_field<uint32_t>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, uint32_t default_val)
{
    bool ret = false;

    if ( (!is_reserved_field(field_name) || allow_reserved_fields) &&
         m_uint32_fields.count(field_name) == 0 )
    {
        auto new_field = ncurses_field<uint32_t>();
        new_field.create_field(m_window, x, y, format_str, default_val);
        m_uint32_fields[field_name] = new_field;
        ret = m_uint32_fields[field_name].update_field(default_val);
    }

    return ret;
}

template <>
bool ncurses_window::_add_field<float>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, float default_val)
{
    bool ret = false;

    if ( (!is_reserved_field(field_name) || allow_reserved_fields) &&
         m_float_fields.count(field_name) == 0 )
    {
        auto new_field = ncurses_field<float>();
        new_field.create_field(m_window, x, y, format_str, default_val);
        m_float_fields[field_name] = new_field;
        ret = m_float_fields[field_name].update_field(default_val);
    }

    return ret;
}

template <>
bool ncurses_window::_add_field<double>(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, double default_val)
{
    bool ret = false;

    if ( (!is_reserved_field(field_name) || allow_reserved_fields) &&
         m_double_fields.count(field_name) == 0 )
    {
        auto new_field = ncurses_field<double>();
        new_field.create_field(m_window, x, y, format_str, default_val);
        m_double_fields[field_name] = new_field;
        ret = m_double_fields[field_name].update_field(default_val);
    }

    return ret;
}

bool ncurses_window::add_title(std::string title_str)
{
    return add_title(title_str, ncurses_window::TOP, ncurses_window::LEFT, NCURSES_CPP_TXT_COLOR_DEFAULT);
}

bool ncurses_window::add_title(std::string title_str, vertical_alignment_e vert_alignment, horizontal_alignment_e horiz_alignment, ncurses_cpp_text_colors_e title_color)
{
    bool ret = false;

    if (nullptr != m_window &&
        m_str_fields.count(TITLE_FIELD_NAME) == 0)
    {
        /* calculate the x and y positions for the title string */
        uint32_t title_x = 0;
        uint32_t title_y = 0;

        switch (vert_alignment)
        {
        case ncurses_window::TOP:
            title_y = 0;
            break;

        case ncurses_window::MIDDLE:
            title_y = m_height / 2;
            break;

        case ncurses_window::BOTTOM:
            title_y = m_height;
            break;
        }

        switch (horiz_alignment)
        {
        case ncurses_window::LEFT:
            title_x = 1;
            break;

        case ncurses_window::CENTER:
            if (title_str.size() < m_width)
            {
                title_x = (m_width - title_str.size()) / 2;
            }
            else
            {
                title_x = 0;
            }
            break;

        case ncurses_window::RIGHT:
            if (title_str.size() < m_width)
            {
                title_x = (m_width - title_str.size());
            }
            else
            {
                title_x = 0;
            }

            break;
        }

        ret = _add_field<std::string>(true, title_x, title_y, TITLE_FIELD_NAME, " %s ", title_str);
        ret &= update_field<std::string>(TITLE_FIELD_NAME, title_str, title_color);
    }

    return ret;
}

} /* end ncurses_cpp namespace */
