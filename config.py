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

import gtk, os, sys, struct

class App:
	def __init__(self):
                #self.readfile()
                self.init_GUI()                
                gtk.main()

        def readfile(self):
                print "OK"
                
                
	def init_GUI(self):
		# Window creation
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.set_title('OpenAlchemist Louncher')

                # Add events
                self.window.connect("destroy", self._event_quit)

                self.window.mainbox = gtk.VBox(homogeneous = False, spacing=10)
                self.window.mainbox.set_border_width(10)
                self.window.add(self.window.mainbox)

                self.window.render_frame = gtk.Frame("Render")
                self.window.mainbox.pack_start(self.window.render_frame, fill=False, expand=False)
                self.window.render_box = gtk.VBox(homogeneous = True, spacing = 0)
                self.window.render_box.set_border_width(10)
                self.window.render_frame.add(self.window.render_box)
                self.window.rbt_sdl = gtk.RadioButton(label="SDL")
                self.window.render_box.pack_start(self.window.rbt_sdl, fill=False, expand=False)
                self.window.rbt_opengl = gtk.RadioButton(label="OpenGL", group=self.window.rbt_sdl)
                self.window.render_box.pack_start(self.window.rbt_opengl, fill=False, expand=False)

                self.window.fps_frame = gtk.Frame("Limit framerate to :")
                self.window.mainbox.pack_start(self.window.fps_frame, fill=False, expand=False)
                self.window.fps_box = gtk.VBox()
                self.window.fps_frame.add(self.window.fps_box)
                self.window.fps_box.set_border_width(10)
                self.window.txt_fps = gtk.Entry()
                self.window.txt_fps.set_text("200")
                self.window.fps_box.pack_start(self.window.txt_fps, fill=False, expand=False)

                self.window.options_frame = gtk.Frame("Options")
                self.window.mainbox.pack_start(self.window.options_frame, fill=False, expand=False)
                self.window.options_box = gtk.VBox()
                self.window.options_box.set_border_width(10)
                self.window.options_frame.add(self.window.options_box)
                self.window.cb_colorblind = gtk.CheckButton(label="Active color blind mode")
                self.window.options_box.pack_start(self.window.cb_colorblind, fill=False, expand=False)
               
                self.window.bt_start = gtk.Button("Run game")
                self.window.mainbox.pack_start(self.window.bt_start, fill=False, expand=False)
                self.window.bt_start.connect("clicked", self._event_ok)


		# Show the window and start the main loop.
                self.window.set_position(gtk.WIN_POS_CENTER)
		self.window.show_all()

                
        def _event_quit(self,  event):
                gtk.main_quit()

        def _event_ok(self, event):
                os.system("cd " + sys.path[0])
                options = ""
                if self.window.rbt_opengl.get_active():
                        options = " --opengl"
                else:
                        options = " --sdl"
                if self.window.cb_colorblind.get_active():
                        options = options + " --cb"
                else:
                        options = options + " --nocb"
                options = options + " --maxfps " + self.window.txt_fps.get_text()
                os.system("./openalchemist" + options)
                        
                

                

app = App()

