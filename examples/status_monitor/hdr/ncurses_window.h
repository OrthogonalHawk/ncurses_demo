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
 * @file     ncurses_window.h
 * @author   OrthogonalHawk
 * @date     02-Apr-2021
 *
 * @brief    Container class to organize an ncurses window object.
 *
 * @section  DESCRIPTION
 *
 * Defines a container class to organize an ncurses window object.
 *
 * @section  HISTORY
 *
 * 02-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __NCURSES_WINDOW_H__
#define __NCURSES_WINDOW_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <map>
#include <string>
#include <vector>

#include <ncurses.h>

#include "ncurses_colors.h"
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
 *                           FUNCTION DECLARATION
 *****************************************************************************/

/******************************************************************************
 *                            CLASS DECLARATION
 *****************************************************************************/

class ncurses_window
{
public:

    static const std::vector<std::string> RESERVED_FIELD_NAMES;
    static bool is_reserved_field(std::string field_name);

    typedef enum {
        LEFT = 0,
        CENTER,
        RIGHT
    } horizontal_alignment_e;

    typedef enum {
        TOP = 0,
        MIDDLE,
        BOTTOM
    } vertical_alignment_e;

    ncurses_window(void);
    ncurses_window(bool outline_window);
    virtual ~ncurses_window(void);

    bool create_window(uint32_t height, uint32_t width, uint32_t start_x, uint32_t start_y);
    bool cleanup_window(void);

    bool clear_window(void);
    bool clear_window(char clear_char);

    bool add_title(std::string title_str);
    bool add_title(std::string title_str, vertical_alignment_e vert_alignment, horizontal_alignment_e horiz_alignment, ncurses_cpp_text_colors_e title_color);

    template <typename T>
    bool add_field(uint32_t x, uint32_t y, std::string field_name, std::string format_str, T default_val);

    template <typename T>
    bool add_field(uint32_t x, uint32_t y, std::string field_name, std::string format_str, T default_val, ncurses_cpp_text_colors_e default_color);

    template <typename T>
    bool add_field_thresholds(std::string field_name, std::pair<T, T> field_threshold_vals, ncurses_cpp_text_colors_e field_color);

    template <typename T>
    bool update_field(std::string field_name, T field_val);

    template <typename T>
    bool update_field(std::string field_name, T field_val, ncurses_cpp_text_colors_e field_color);

private:

    template <typename T>
    bool _add_field(bool allow_reserved_fields, uint32_t x, uint32_t y, std::string field_name, std::string format_str, T default_val, ncurses_cpp_text_colors_e default_color);

    bool field_name_in_use(std::string field_name);

    WINDOW *                                                  m_window;
    uint32_t                                                  m_height;
    uint32_t                                                  m_width;
    bool                                                      m_outline_window;
    std::map<std::string, ncurses_field<std::string>>         m_str_fields;
    std::map<std::string, ncurses_field<int32_t>>             m_int32_fields;
    std::map<std::string, ncurses_field<uint32_t>>            m_uint32_fields;
    std::map<std::string, ncurses_field<float>>               m_float_fields;
    std::map<std::string, ncurses_field<double>>              m_double_fields;
};


/******************************************************************************
 *                            TEMPLATE FUNCTIONS
 *****************************************************************************/

/* these functions do not have specializations for the class; putting them here
 *  helps the linker resolve the template versions */

template <typename T>
bool ncurses_window::add_field(uint32_t x, uint32_t y, std::string field_name, std::string format_str, T default_val)
{
    return add_field<T>(x, y, field_name, format_str, default_val, NCURSES_CPP_TXT_COLOR_DEFAULT);
}

template <typename T>
bool ncurses_window::add_field(uint32_t x, uint32_t y, std::string field_name, std::string format_str, T default_val, ncurses_cpp_text_colors_e default_color)
{
    return _add_field<T>(false, x, y, field_name, format_str, default_val, default_color);
}

template <typename T>
bool ncurses_window::update_field(std::string field_name, T field_val)
{
    return update_field<T>(field_name, field_val, NCURSES_CPP_TXT_COLOR_DEFAULT);
}

}; /* end of the ncurses_cpp namespace */

#endif // __NCURSES_WINDOW_H__
