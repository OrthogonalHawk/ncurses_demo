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
 * @file     ncurses_ui.h
 * @author   OrthogonalHawk
 * @date     27-Apr-2021
 *
 * @brief    Container class to organize an ncurses user interface.
 *
 * @section  DESCRIPTION
 *
 * Defines a container class to organize an ncurses user interface.
 *
 * @section  HISTORY
 *
 * 27-Apr-2021  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __NCURSES_USER_INTERFACE_H__
#define __NCURSES_USER_INTERFACE_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "ncurses_colors.h"
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
 *                           FUNCTION DECLARATION
 *****************************************************************************/

/******************************************************************************
 *                            CLASS DECLARATION
 *****************************************************************************/

class ncurses_ui
{
public:

    ncurses_ui(void);
    ncurses_ui(int shutdown_key, uint32_t periodic_task_interval_in_ms);
    virtual ~ncurses_ui(void);

    bool run(void);

protected:

    bool add_window(std::shared_ptr<ncurses_window> window);

    template <typename T>
    bool update_field(std::string window_name, std::string field_name, T field_val);

    template <typename T>
    bool update_field(std::string window_name, std::string field_name, T field_val, ncurses_cpp_text_colors_e field_color);

    /* derived class should override; automatically invoked when a new character
     *  is availabe */
    virtual void handle_char(int next_char);

    /* derived class should override; automatically invoked periodically based on the
     *  rate specified by a constructor argument */
    virtual void handle_periodic_tasks(void);

private:

    void setup_ncurses(void);
    void cleanup_ncurses(void);

    int                                                         m_shutdown_key;
    uint32_t                                                    m_periodic_task_interval_in_ms;
    std::chrono::steady_clock::time_point                       m_last_periodic_task_invocation;
    std::map<std::string, std::shared_ptr<ncurses_window>>      m_windows_by_name;
};

/******************************************************************************
 *                            TEMPLATE FUNCTIONS
 *****************************************************************************/

/* these functions do not have specializations for the class; putting them here
 *  helps the linker resolve the template versions */

template <typename T>
bool ncurses_ui::update_field(std::string window_name, std::string field_name, T field_val)
{
    if (m_windows_by_name.count(window_name) > 0)
    {
        return m_windows_by_name[window_name]->update_field<T>(field_name, field_val, NCURSES_CPP_TXT_COLOR_DEFAULT);
    }
    else
    {
        return false;
    }
}

template <typename T>
bool ncurses_ui::update_field(std::string window_name, std::string field_name, T field_val, ncurses_cpp_text_colors_e field_color)
{
    if (m_windows_by_name.count(window_name) > 0)
    {
        return m_windows_by_name[window_name]->update_field<T>(field_name, field_val, field_color);
    }
    else
    {
        return false;
    }
}

}; /* end of the ncurses_cpp namespace */

#endif // __NCURSES_USER_INTERFACE_H__
