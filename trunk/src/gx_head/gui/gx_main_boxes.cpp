/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
 * Copyright (C) 2011 Pete Shorthose
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * ---------------------------------------------------------------------------
 *
 *    This file is part of the gx_head GUI main class
 *
 * ----------------------------------------------------------------------------
 */

#include "guitarix.h"           // NOLINT

#include <glibmm/i18n.h>        // NOLINT

#include <iomanip>              // NOLINT
#include <cstring>              // NOLINT
#include <string>               // NOLINT

namespace gx_gui {

/****************************************************************
 ** predefined gtkmm widget classes used in main GUI
 */

/****************************************************************/

GxPaintBox::GxPaintBox(const char *expose_funk)
    : Gxw::PaintBox(), m_hbox(false, 0) {
    property_paint_func() = expose_funk;
    pack_start(m_hbox);
}

GxPaintBox::~GxPaintBox() {}

/****************************************************************/

GxNotebookBox::GxNotebookBox() {
    get_style_context()->add_class("tab_rack");
}

/****************************************************************/
}
