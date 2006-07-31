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

import gtk, os, tarfile, time, threading, sys

class App:

        # Constructor
	def __init__(self):
                gtk.gdk.threads_init()
                self.init_GUI()

                # Setting default values 
                self.running = True
                self.tarExporter = False   

                # Starting the GTK main loop                
                gtk.main()

                

        # Initialize the GUI
	def init_GUI(self):
		# Window creation
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.set_title('OpenAlchemist Installer')

                # Add event for window destruction
                self.window.connect("destroy", self._event_quit)

                # Create the mainbox
                self.window.mainbox = gtk.HBox(homogeneous=False, spacing=0)
                self.window.add(self.window.mainbox)
                self.window.mainbox.show()

                # Display the installer bitmap at the left
                self.image = gtk.Image()
                self.window.mainbox.pack_start(self.image, fill=False, expand=False)
                self.image.set_from_file(sys.path[0]+"/install.png")
                self.image.show()

                # Creating Step boxes
                self.window.step_welcome = StepWelcome(self)
                self.window.mainbox.pack_start(self.window.step_welcome, fill=True, expand=True, padding=10)
                self.window.step_welcome.hide()

                self.window.step_directory = StepChooseDirectory(self)
                self.window.mainbox.pack_start(self.window.step_directory, fill=True, expand=True, padding=10)
                self.window.step_directory.show()

                # Show the window
		self.window.show()

              
        # Event to destroy
        def _event_ok(self, event):
                self.tarExporter = ExportThread(self)
                self.tarExporter.export("openalchemist.tar", ".")

        def _event_stop(self, event):
                self.tarExporter.st()

        def hide_all_steps(self):
                self.window.step_welcome.hide()
                self.window.step_directory.hide()

        def show_step_welcome(self):
                self.hide_all_steps()
                self.window.step_welcome.show()

        def show_step_directory(self):
                self.hide_all_steps()
                self.window.step_directory.show()

        # Event when you close the window
        def _event_quit(self, event):
                self.running = False
                gtk.gdk.threads_leave()
                if self.tarExporter:
                        self.tarExporter.st()        
                        self.tarExporter.join()
                gtk.gdk.threads_enter()
                
                gtk.main_quit()
                sys.exit()

# First Step Box 
class StepWelcome(gtk.VBox):

        # Constructor
        def __init__(self, app):
                gtk.VBox.__init__(self)
                self.app = app

                # Welcome Frame
                self.frame = gtk.Frame("Welcome")
                self.pack_start(self.frame, fill=True, expand=False)

                # Welcome Label
                self.lbl = gtk.Label("This program will help you to install OpenAlchemist on your computer.")
                self.frame.add(self.lbl)
                self.lbl.set_line_wrap(True)

                # License Frame
                self.frameLicense = gtk.Frame("License")
                self.pack_start(self.frameLicense, fill=True, expand=False)

                # License Table
                self.table = gtk.Table(columns=3, homogeneous=False)
                self.frameLicense.add(self.table)

                # License Labels and Buttons
                self.lbl_gpl = gtk.Label("* Code is under GNU General Public License 2.0 or earlier")
                self.table.attach(self.lbl_gpl,0,2,0,1)
                self.lbl_gpl.set_justify(gtk.JUSTIFY_LEFT)
                self.bt_gpl = gtk.Button("See License")
                self.table.attach(self.bt_gpl,2,3,0,1, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)

                self.lbl_cc = gtk.Label("* Gaphics are under Creative Commons Attribution-ShareAlike 2.0")
                self.table.attach(self.lbl_cc,0,2,1,2)
                self.bt_cc = gtk.Button("See License")
                self.table.attach(self.bt_cc,2,3,1,2, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)

                # License CheckBox               
                self.table.attach(gtk.Label(),0,1,2,3)
                self.cb_license_ok = gtk.CheckButton(label="I agree licenses agrements")
                self.table.attach(self.cb_license_ok,1,2,2,3, xoptions=gtk.EXPAND|gtk.FILL, yoptions=gtk.EXPAND|gtk.FILL, ypadding=20)
                self.cb_license_ok.connect("clicked", self._event_license_checked)


                # Separator
                self.pack_start(gtk.Label())

                # Bottom table for Prec/Next items
                self.table_bottom = gtk.Table(columns=3, homogeneous=True)
                self.pack_end(self.table_bottom, fill=True, expand=False, padding=10)               

                # Image for next button
                self.img_next = gtk.Image()
                self.img_next.set_from_stock(gtk.STOCK_GO_FORWARD, gtk.ICON_SIZE_BUTTON)

                # Next Button
                self.bt_next = gtk.Button("Next")
                self.bt_next.connect("clicked", self._event_next)
                self.table_bottom.attach(self.bt_next, 2,3,0,1, ypadding=0)
                self.bt_next.set_image(self.img_next)
                self.bt_next.set_sensitive(False)

                # Display this StepBox
                self.show_all()



        # Event when the checkbox is checked
        def _event_license_checked(self, event):
                if self.cb_license_ok.get_active():
                        self.bt_next.set_sensitive(True)
                else:
                        self.bt_next.set_sensitive(False)

        # Event when next button is clicked
        def _event_next(self, event):
                self.app.show_step_directory()
                



class StepChooseDirectory(gtk.VBox):

        # Constructor
        def __init__(self, app):
                gtk.VBox.__init__(self)
                self.app = app

                self.frame_select_dir = gtk.Frame("Folder installation")
                self.pack_start(self.frame_select_dir, fill=True, expand=False)

                self.table_select_dir = gtk.Table(columns=2, rows=3, homogeneous=False)
                self.frame_select_dir.add(self.table_select_dir)

                self.lbl_select_dir = gtk.Label("Path installation : ")
                self.table_select_dir.attach(self.lbl_select_dir, 0,1,0,1)
                self.entry_path = gtk.Entry()
                self.table_select_dir.attach(self.entry_path, 1,2,0,1)
                self.bt_path = gtk.Button()
                self.table_select_dir.attach(self.bt_path, 2,3,0,1, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)
                self.img_path = gtk.Image()
                self.img_path.set_from_stock(gtk.STOCK_DIRECTORY, gtk.ICON_SIZE_BUTTON)
                self.bt_path.set_image(self.img_path)

                self.cb_make_link = gtk.CheckButton("Make a symbolinc link in the path")
                self.table_select_dir.attach(self.cb_make_link, 0,1,1,2, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)


                self.lbl_bin_path = gtk.Label("Binary path : ")
                self.table_select_dir.attach(self.lbl_bin_path, 0,1,2,3)
                self.entry_bin_path = gtk.Entry()
                self.table_select_dir.attach(self.entry_bin_path, 1,2,2,3)
                self.bt_bin_path = gtk.Button()
                self.table_select_dir.attach(self.bt_bin_path, 2,3,2,3, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)
                self.img_bin_path = gtk.Image()
                self.img_bin_path.set_from_stock(gtk.STOCK_DIRECTORY, gtk.ICON_SIZE_BUTTON)
                self.bt_bin_path.set_image(self.img_bin_path)

                # Separator
                self.pack_start(gtk.Label())


                # Bottom table for Prec/Next items
                self.table_bottom = gtk.Table(columns=3, homogeneous=True)
                self.pack_end(self.table_bottom, fill=True, expand=False, padding=10)               

                # Image for next button
                self.img_next = gtk.Image()
                self.img_next.set_from_stock(gtk.STOCK_GO_FORWARD, gtk.ICON_SIZE_BUTTON)

                # Next Button
                self.bt_next = gtk.Button("Install")
                self.bt_next.connect("clicked", self._event_next)
                self.table_bottom.attach(self.bt_next, 2,3,0,1, ypadding=0)
                self.bt_next.set_image(self.img_next)

                # Image for next button
                self.img_before = gtk.Image()
                self.img_before.set_from_stock(gtk.STOCK_GO_BACK, gtk.ICON_SIZE_BUTTON)

                # Next Button
                self.bt_before = gtk.Button("Previous")
                self.bt_before.connect("clicked", self._event_next)
                self.table_bottom.attach(self.bt_before, 0,1,0,1, ypadding=0)
                self.bt_before.set_image(self.img_before)                
               

                
                self.show_all()

        def _event_next(self, event):
                self.app.show_step_welcome()
                
                

# Thread to export the tar archive
class ExportThread(threading.Thread):

        # Constructor
        def __init__(self, app):
                threading.Thread.__init__(self)
                self.app = app

        # Export
        def export(self, filename, path):
                self.filename = filename
                self.path = path
                self.start()

        # Run
        def run(self):
                tar = tarfile.TarFile(self.filename)
                nbFiles = len(tar.getmembers())+0.0

                k = 0.0
                self.running = True

                # Thread loop
                for f in tar.getmembers():
                        # Condition to exit the loop
                        if not self.running:
                                return
                        
                        #print f.name
                        tar.extract(f, self.path)
                        f = tar.next()
                        k = k + 1
                        #print str(k) +  " of " +str(n)
                        frac = k / n
                        #time.sleep(1)
                        gtk.gdk.threads_enter()
                        if self.app.running:
                                self.app.p.set_fraction(frac)
                                self.app.p.show()
                        gtk.gdk.threads_leave()
                
              
        # Stop method
        def stop(self):
             self.running = False   
                


app = App()

