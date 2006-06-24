#!/usr/bin/python
# -*- coding: UTF-8 -*-

# Anim viewer (SVN version)
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

import gtk, sys, time
from sprite import Sprite


class App:
	def __init__(self):
                gtk.gdk.threads_init()
                self.sprite = Sprite(self)
                self.sprite.width = 50
                self.sprite.height = 50
                self.sprite.speed = 0.5
                self.init_GUI()
                self.sprite.start()
                gtk.main()

	def init_GUI(self):
		# Window creation
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.set_title('Animation Viewer')

                # Add events
                self.window.connect("destroy", self._event_quit)

                # Making boxes
                self.window.main_box = gtk.HBox(homogeneous = False, spacing=0)
                self.window.add(self.window.main_box)
                self.window.main_box.show()

                self.window.propreties_box = gtk.VBox(homogeneous = False, spacing=0)
                self.window.main_box.pack_start(self.window.propreties_box, fill=False, expand=False)
                self.window.propreties_box.show()

                # File chooser for animation
                self.window.propreties_box.lbl_anim_file = gtk.Label("Animation : ")
                self.window.propreties_box.pack_start(self.window.propreties_box.lbl_anim_file, fill=False, expand=False)
                self.window.propreties_box.lbl_anim_file.show()

                self.window.file_chooser = gtk.FileChooserButton("Select a file")
                self.window.propreties_box.pack_start(self.window.file_chooser, fill=False, expand=False)
                self.window.file_chooser.show()
                
                filter = gtk.FileFilter()
                filter.add_pattern("*.png")
                filter.set_name("PNG Image")
                self.window.file_chooser.add_filter(filter)

                self.window.propreties_box.lbl_before_file = gtk.Label("File before : ")
                self.window.propreties_box.pack_start(self.window.propreties_box.lbl_before_file, fill=False, expand=False)
                self.window.propreties_box.lbl_before_file.show()

                # File chooser for file before
                self.window.file_before = gtk.FileChooserButton("Select a file")
                self.window.propreties_box.pack_start(self.window.file_before, fill=False, expand=False)
                self.window.file_before.show()
                self.window.file_before.add_filter(filter)

                self.window.separator = gtk.HSeparator()
                self.window.propreties_box.pack_start(self.window.separator, fill=False, expand=False)
                self.window.separator.show()

               
                # Propreties
                self.window.propreties_box.table = gtk.Table(columns = 2)
                self.window.propreties_box.table.set_border_width(10)
                self.window.propreties_box.pack_start(self.window.propreties_box.table, fill=False, expand=False)
                self.window.propreties_box.table.show()

                self.window.propreties_box.lbl_sprite_width = gtk.Label('Sprite width: ')
                self.window.propreties_box.table.attach(self.window.propreties_box.lbl_sprite_width,0,1,0,1)
                self.window.propreties_box.lbl_sprite_width.show()

                self.window.propreties_box.txt_sprite_width = gtk.Entry()                
                self.window.propreties_box.table.attach(self.window.propreties_box.txt_sprite_width,1,2,0,1)
                self.window.propreties_box.txt_sprite_width.set_max_length(4)
                self.window.propreties_box.txt_sprite_width.set_text("50")
                self.window.propreties_box.txt_sprite_width.show()

                self.window.propreties_box.lbl_sprite_height = gtk.Label('Sprite height: ')
                self.window.propreties_box.table.attach(self.window.propreties_box.lbl_sprite_height,0,1,1,2)
                self.window.propreties_box.lbl_sprite_height.show()

                self.window.propreties_box.txt_sprite_height = gtk.Entry()
                self.window.propreties_box.table.attach(self.window.propreties_box.txt_sprite_height,1,2,1,2)
                self.window.propreties_box.txt_sprite_height.set_max_length(4)
                self.window.propreties_box.txt_sprite_height.set_text("50")
                self.window.propreties_box.txt_sprite_height.show()

                self.window.propreties_box.lbl_speed = gtk.Label('Speed: (ms)')
                self.window.propreties_box.table.attach(self.window.propreties_box.lbl_speed,0,1,2,3)
                self.window.propreties_box.lbl_speed.show()

                self.window.propreties_box.txt_speed = gtk.Entry()
                self.window.propreties_box.table.attach(self.window.propreties_box.txt_speed,1,2,2,3)
                self.window.propreties_box.txt_speed.set_max_length(4)
                self.window.propreties_box.txt_speed.set_text("50")
                self.window.propreties_box.txt_speed.show()

                # Action
                self.window.propreties_box.bt_ok = gtk.Button('OK')
                self.window.propreties_box.pack_start(self.window.propreties_box.bt_ok, fill=False, expand=False)
                self.window.propreties_box.bt_ok.show()
                self.window.propreties_box.bt_ok.connect("clicked", self._bt_ok_clicked)

                # Image
                self.window.sprite = self.sprite.image
                self.window.main_box.pack_start(self.window.sprite)
                self.window.sprite.show()


		# Show the window and start the main loop.
                self.window.set_default_size(800,0)
		self.window.show()

        def _bt_ok_clicked(self, widget):
                if self.window.file_chooser.get_filename():
                        self.sprite.open(self.window.file_chooser.get_filename())
                if self.window.file_before.get_filename():
                        self.sprite.open_filebefore(self.window.file_before.get_filename())
                
                try:
                        self.sprite.width = int(self.window.propreties_box.txt_sprite_width.get_text())
                        self.sprite.height = int(self.window.propreties_box.txt_sprite_height.get_text())
                        self.sprite.speed = 0.001 * int(self.window.propreties_box.txt_speed.get_text())
                except TypeError:
                        print "bad value"
                        
                
        def _event_quit(self,  event):
                self.sprite.stop()
                

app = App()

