/*
 * Copyright (C) 2009, 2010 Hermann Meyer, James Warden, Andreas Degert
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gtk/gtk.h>
#include <gxw/GxControlParameter.h>
#include <gxw/GxSwitch.h>
#include <glibmm_generate_extra_defs/generate_extra_defs.h>

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
	std::cout << get_defs(GX_TYPE_CONTROL_PARAMETER)
	          << get_defs(GX_TYPE_SWITCH);
	return 0;
}
