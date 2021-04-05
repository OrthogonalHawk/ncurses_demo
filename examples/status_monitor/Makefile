###############################################################################
#
# MIT License
#
# Copyright (c) 2021 OrthogonalHawk
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
###############################################################################

###############################################################################
# Makefile for the 'status monitor' example
#
#     See ../../../falcon_makefiles/Makefile.libs for usage
#
###############################################################################

TARGET ?= NATIVE

FALCON_PATH = $(realpath $(CURDIR)/../../..)
PLATFORM_BUILD=1
export PLATFORM_BUILD
BUILD_OBJS_DIR = build$(LIB_SUFFIX)

###############################################################################
# LIBRARY / EXECUTABLE
###############################################################################

EXE = status_monitor

###############################################################################
# SOURCES
###############################################################################

CC_SOURCES = \
    src/ncurses_colors.cc \
    src/ncurses_field.cc \
    src/ncurses_window.cc \
    status_monitor.cc \

###############################################################################
# Include ../../falcon_makefiles/Makefile.apps for rules
###############################################################################

include ../../../falcon_makefiles/Makefile.apps

###############################################################################
# Adjust *FLAGS and paths as necessary
###############################################################################

CPPFLAGS += -Werror -Wall -Wextra -Wcast-align -Wno-type-limits
CPPFLAGS += -std=c++11 -O3
LIBS += -lncurses

INC_PATH += \
    -I./hdr \
