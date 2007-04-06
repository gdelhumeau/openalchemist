/* OpenAlchemist - just a simple game 
 * ----------------------------------
 *
 * Copyright (C) 2005, 2006 Guillaume Delhumeau <guillaume.delhumeau at laposte.net>
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

#include "headers.h"

void ProgressBar::load_gfx(CL_ResourceManager *gfx)
{
  head = new CL_Sprite("progress-bar/head/sprite", gfx);
  head_ok = new CL_Sprite("progress-bar/head/sprite-ok", gfx);
  foot = new CL_Sprite("progress-bar/foot/sprite", gfx);
  item = new CL_Sprite("progress-bar/item/sprite", gfx);
  item_ok = new CL_Sprite("progress-bar/item/sprite-ok", gfx);

  left = CL_Integer_to_int("progress-bar/left", gfx);
  head_top = CL_Integer_to_int("progress-bar/head/top", gfx);
  foot_top = CL_Integer_to_int("progress-bar/foot/top", gfx);

}

void ProgressBar::unload_gfx()
{
  delete head;
  delete head_ok;
  delete foot;
  delete item;
  delete item_ok;
}
