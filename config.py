#!/usr/bin/python
# -*- coding: UTF-8 -*-

# Louncher (SVN version)
# ===============
# Copyright (C) 2006 Guillaume Delhumeau
#                                                                             
# This program is free software; you can redistribute it and/or               
# modify it under the terms of the GNU General Public License                 
# as published by the Free Software Foundation; either version 2              
# of the License, Or (at your option) any later version.                      
#                                                                             
# This program is distributed in the hope that it will be useful,             
# but WITHOUT ANY WARRANTY; without even the implied warranty of              
# MERCHANTABILITY Or FITNESS For A PARTICULAR PURPOSE.  See the               
# GNU General Public License For more details.                                
#                                                                             
# You should have received a copy of the GNU General Public License           
# along with this program; if not, write to the Free Software                 
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 
#                                                                             
# Contact me: kephO.O [_at_] gmail [_dot_] com 

# This program needs Python(http://www.python.org) of course, GTK+(http://www.gtk.org) and PyGTK 2.6 (http://www.pygtk.org).

import gtk, os, sys

class App:
	def __init__(self):        
                self.init_GUI()                
                gtk.main()

	def init_GUI(self):
		# Window creation
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.set_title('OpenAlchemist Louncher')

                # Add events
                self.window.connect("destroy", self._event_quit)

                self.window.mainbox = gtk.VBox(homogeneous = False, spacing=10)
                self.window.add(self.window.mainbox)

                #self.window.table = gtk.Table(columns = 2)
                #self.window.mainbox.pack_start(self.window.table)

                self.window.render_frame = gtk.Frame("Render")
                self.window.mainbox.pack_start(self.window.render_frame, fill=False, expand=False)
                self.window.render_box = gtk.VBox(homogeneous = True, spacing = 0)
                self.window.render_frame.add(self.window.render_box)
                self.window.rbt_sdl = gtk.RadioButton(label="SDL")
                self.window.render_box.pack_start(self.window.rbt_sdl, fill=False, expand=False)
                self.window.rbt_opengl = gtk.RadioButton(label="OpenGL", group=self.window.rbt_sdl)
                self.window.render_box.pack_start(self.window.rbt_opengl, fill=False, expand=False)

                self.window.fps_frame = gtk.Frame("Limit framerate to :")
                self.window.mainbox.pack_start(self.window.fps_frame, fill=False, expand=False)
                self.window.txt_fps = gtk.Entry()
                self.window.txt_fps.set_text("200")
                self.window.fps_frame.add(self.window.txt_fps)

               
                self.window.bt_start = gtk.Button("Run game")
                self.window.mainbox.pack_start(self.window.bt_start, fill=False, expand=False)
                self.window.bt_start.connect("clicked", self._event_ok)


		# Show the window and start the main loop.
                #self.window.set_default_size(300,200)
                self.window.set_position(gtk.WIN_POS_CENTER)
		self.window.show_all()

                
        def _event_quit(self,  event):
                gtk.main_quit()

        def _event_ok(self, event):
                os.system("cd " + sys.path[0])
                if self.window.rbt_opengl.get_active():
                        os.system("./openalchemist --opengl")
                else:
                        os.system("./openalchemist --sdl")
                        
                

                

app = App()
