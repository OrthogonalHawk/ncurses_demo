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
 * @file     ncurses_field.h
 * @author   OrthogonalHawk
 * @date     04-Apr-2021
 *
 * @brief    Container class to organize fields within ncurses window objects.
 *
 * @section  DESCRIPTION
 *
 * Defines a container class to organize fields within ncurses window objects.
 *
 * @section  HISTORY
 *
 * 04-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __NCURSES_FIELD_H__
#define __NCURSES_FIELD_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <string>
#include <vector>

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
 *                           FUNCTION DECLARATION
 *****************************************************************************/

/******************************************************************************
 *                            CLASS DECLARATION
 *****************************************************************************/

template <typename T>
class ncurses_field
{
public:

    ncurses_field(void);
    virtual ~ncurses_field(void);

    bool create_field(WINDOW * window, uint32_t x, uint32_t y, std::string format_str, T default_val);
    bool create_field(WINDOW * window, uint32_t x, uint32_t y, std::string format_str, T default_val, ncurses_cpp_text_colors_e default_color);

    virtual bool update_field(void);

    bool update_field(T field_val);
    bool update_field(T field_val, ncurses_cpp_text_colors_e field_color);

    bool add_field_thresholds(std::pair<T, T> field_threshold_vals, ncurses_cpp_text_colors_e field_color);

private:

    struct field_thresholds_t
    {
        bool operator==(const field_thresholds_t& other) { return threshold == other.threshold && color == other.color; }

        std::pair<T, T>             threshold;
        ncurses_cpp_text_colors_e   color;
    };

    static bool compare_threshold_vals(const field_thresholds_t& a, const field_thresholds_t& b);
    ncurses_cpp_text_colors_e get_color_based_on_thresholds(T field_val);

    WINDOW *                                                  m_window;
    uint32_t                                                  m_x;
    uint32_t                                                  m_y;
    std::string                                               m_format_str;
    T                                                         m_current_value;
    ncurses_cpp_text_colors_e                                 m_default_color;
    std::vector<field_thresholds_t>                           m_threshold_vals;
};

}; /* end of the ncurses_cpp namespace */

#endif // __NCURSES_FIELD_H__
