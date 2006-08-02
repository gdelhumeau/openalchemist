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
                self.window.step_welcome.show()

                self.window.step_directory = StepChooseDirectory(self)
                self.window.mainbox.pack_start(self.window.step_directory, fill=True, expand=True, padding=10)
                self.window.step_directory.hide()

                self.window.step_install = StepInstall(self)
                self.window.mainbox.pack_start(self.window.step_install, fill=True, expand=True, padding=10)
                self.window.step_install.hide()

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
                self.window.step_install.hide()

        def show_step_welcome(self):
                self.hide_all_steps()
                self.window.step_welcome.show()

        def show_step_directory(self):
                self.hide_all_steps()
                self.window.step_directory.show()

        def show_step_install(self):                
                self.hide_all_steps()
                self.window.step_install.show()

        # Event when you close the window
        def _event_quit(self, event):
                self.running = False
                gtk.gdk.threads_leave()
                if self.tarExporter:
                        self.tarExporter.stop()        
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

                # Directory Selection Frame
                self.frame_select_dir = gtk.Frame("Folder installation")
                self.pack_start(self.frame_select_dir, fill=True, expand=False)

                # Directory Selection Table
                self.table_select_dir = gtk.Table(columns=2, rows=3, homogeneous=False)
                self.frame_select_dir.add(self.table_select_dir)

                # Directory Selection Labels, Entry and Buttons (path)
                self.lbl_select_dir = gtk.Label("Path installation : ")
                self.table_select_dir.attach(self.lbl_select_dir, 0,1,0,1)
                self.entry_path = gtk.Entry()
                self.entry_path.set_width_chars(40)
                self.table_select_dir.attach(self.entry_path, 1,2,0,1)
                self.bt_path = gtk.Button()
                self.table_select_dir.attach(self.bt_path, 2,3,0,1, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)
                self.img_path = gtk.Image()
                self.img_path.set_from_stock(gtk.STOCK_DIRECTORY, gtk.ICON_SIZE_BUTTON)
                self.bt_path.set_image(self.img_path)
                self.bt_path.connect("clicked", self._event_select_path)

                # Directory Selection CheckButton
                self.cb_make_link = gtk.CheckButton("Make a symbolinc link in the path")
                self.table_select_dir.attach(self.cb_make_link, 0,1,1,2, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)
                self.cb_make_link.connect("clicked", self._event_links_checked)

                # Directory Selection Labels, Entry and Buttons (bin_path)
                self.lbl_bin_path = gtk.Label("Binary path : ")
                self.table_select_dir.attach(self.lbl_bin_path, 0,1,2,3)
                self.entry_bin_path = gtk.Entry()
                self.table_select_dir.attach(self.entry_bin_path, 1,2,2,3)
                self.bt_bin_path = gtk.Button()
                self.table_select_dir.attach(self.bt_bin_path, 2,3,2,3, xoptions=gtk.SHRINK, yoptions=gtk.SHRINK, xpadding=10, ypadding=0)
                self.img_bin_path = gtk.Image()
                self.img_bin_path.set_from_stock(gtk.STOCK_DIRECTORY, gtk.ICON_SIZE_BUTTON)
                self.bt_bin_path.set_image(self.img_bin_path)
                self.bt_bin_path.connect("clicked", self._event_select_bin_path)

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

                # Before Button
                self.bt_before = gtk.Button("Previous")
                self.bt_before.connect("clicked", self._event_before)
                self.table_bottom.attach(self.bt_before, 0,1,0,1, ypadding=0)
                self.bt_before.set_image(self.img_before)                

                self.init_paths()
                
                self.show_all()


        # Initialize paths (if you're root or normal user)
        def init_paths(self):
                if os.access("/usr/local/games/", os.W_OK):
                        self.entry_path.set_text("/usr/local/games/openalchemist")
                elif os.access(sys.path[0], os.W_OK):
                        self.entry_path.set_text(sys.path[0]+"/openalchemist")

                if os.access("/usr/local/bin", os.W_OK):
                        self.entry_bin_path.set_text("/usr/local/bin")
                        self.cb_make_link.set_active(True)
                else:
                        self.cb_make_link.set_active(False)
                        self.entry_bin_path.set_sensitive(False)
                        self.bt_bin_path.set_sensitive(False)

        # Events when the Links CheckButton is checked
        def _event_links_checked(self, event):
                if self.cb_make_link.get_active():
                        self.entry_bin_path.set_sensitive(True)
                        self.bt_bin_path.set_sensitive(True)
                else:
                        self.entry_bin_path.set_sensitive(False)
                        self.bt_bin_path.set_sensitive(False)

        # Events when next button is clicked
        def _event_next(self, event):
                self.app.show_step_install()
                self.app.window.step_install.install(self.entry_path.get_text())

        # Events when before button is clicked
        def _event_before(self, event):
                self.app.show_step_welcome()

        # Events when selection path button is clicked (path)
        def _event_select_path(self, event):
                self.path_selector = gtk.FileChooserDialog(parent=self.app.window, title="Choose", action=gtk.FILE_CHOOSER_ACTION_SELECT_FOLDER, buttons=(gtk.STOCK_CANCEL, gtk.RESPONSE_REJECT,
                      gtk.STOCK_OK, gtk.RESPONSE_ACCEPT))
                self.path_selector.connect("response", lambda hide, event: self.path_selector.hide())
                if self.path_selector.run()==gtk.RESPONSE_ACCEPT:
                        if not os.access(self.path_selector.get_filename(), os.W_OK):
                                self.error_rights = gtk.MessageDialog(parent=self.app.window, type=gtk.MESSAGE_ERROR, buttons=gtk.BUTTONS_CANCEL, flags=gtk.DIALOG_MODAL|gtk.DIALOG_DESTROY_WITH_PARENT, message_format="You don't have write rights (+w) in this folder.")
                                self.error_rights.connect("response", lambda hide,event: self.error_rights.hide())
                                self.error_rights.run()
                                return
                        self.entry_path.set_text(self.path_selector.get_filename())

        # Events when selection path button is clicked (bin_path)
        def _event_select_bin_path(self, event):
                self.path_selector = gtk.FileChooserDialog(parent=self.app.window, title="Choose", action=gtk.FILE_CHOOSER_ACTION_SELECT_FOLDER, buttons=(gtk.STOCK_CANCEL, gtk.RESPONSE_REJECT,
                      gtk.STOCK_OK, gtk.RESPONSE_ACCEPT))
                self.path_selector.connect("response", lambda hide, event: self.path_selector.hide())
                if self.path_selector.run()==gtk.RESPONSE_ACCEPT:
                        if not os.access(self.path_selector.get_filename(), os.W_OK):
                                self.error_rights = gtk.MessageDialog(parent=self.app.window, type=gtk.MESSAGE_ERROR, buttons=gtk.BUTTONS_CANCEL, flags=gtk.DIALOG_MODAL|gtk.DIALOG_DESTROY_WITH_PARENT, message_format="You don't have write rights (+w) in this folder.")
                                self.error_rights.connect("response", lambda hide,event: self.error_rights.hide())
                                self.error_rights.run()
                                return
                        self.entry_bin_path.set_text(self.path_selector.get_filename())



class StepInstall(gtk.VBox):

        def __init__(self, app):
                gtk.VBox.__init__(self)
                self.app = app
                
                self.frame_copy = gtk.Frame("Installation")
                self.pack_start(self.frame_copy, fill=True, expand=False, padding=10)

                self.copy_box = gtk.VBox()
                self.frame_copy.add(self.copy_box)
                self.lbl_filename = gtk.Label("Copying ...")
                self.copy_box.pack_start(self.lbl_filename, fill=True, expand=False, padding=10)
                self.progress_bar = gtk.ProgressBar()
                self.copy_box.pack_start(self.progress_bar, padding=10)

                self.frame_uninstall = gtk.Frame("Uninstallation")
                self.pack_start(self.frame_uninstall, fill=True, expand=False, padding=10)
                self.uninstall_box = gtk.VBox()
                self.lbl_uninstall = gtk.Label("To remove openalchemist from your computer, just tip: \n # openalchemist-uninstall")
                self.frame_uninstall.add(self.uninstall_box)
                self.uninstall_box.pack_start(self.lbl_uninstall, fill=True, expand=False, padding=10)

                # Separator
                self.pack_start(gtk.Label())

                # Bottom table for Prec/Next items
                self.table_bottom = gtk.Table(columns=3, homogeneous=True)
                self.pack_end(self.table_bottom, fill=True, expand=False, padding=10)               

                # Image for next button
                self.img_next = gtk.Image()
                self.img_next.set_from_stock(gtk.STOCK_EXECUTE, gtk.ICON_SIZE_BUTTON)

                # Next Button
                self.bt_next = gtk.Button("Run")
                self.bt_next.connect("clicked", self._event_next)
                self.table_bottom.attach(self.bt_next, 2,3,0,1, ypadding=0)
                self.bt_next.set_image(self.img_next)
                self.bt_next.set_sensitive(False)

                # Image for next button
                self.img_before = gtk.Image()
                self.img_before.set_from_stock(gtk.STOCK_GO_BACK, gtk.ICON_SIZE_BUTTON)

                # Before Button
                self.bt_before = gtk.Button("Previous")
                self.bt_before.connect("clicked", self._event_next)
                self.table_bottom.attach(self.bt_before, 0,1,0,1, ypadding=0)
                self.bt_before.set_image(self.img_before)

                self.show_all()
                self.frame_uninstall.hide()

        def install(self, path):
                self.path = path
                self.app.tarExporter = ExportThread(self.app)
                self.app.tarExporter.export(sys.path[0]+"/openalchemist.tar", path)

        def show_message(self):
                self.frame_uninstall.show()
                self.bt_next.set_sensitive(True)

                

        
        # Events when next button is clicked
        def _event_next(self, event):
                print self.path+"/openalchemist"
                os.system(self.path+"/openalchemist")
                sys.exit()

        # Events when before button is clicked
        def _event_before(self, event):
                self.app.show_step_directory()        

                
                
                

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
                        gtk.gdk.threads_enter()
                        if self.app.running:
                                self.app.window.step_install.lbl_filename.set_text("Copying "+f.name+"...")
                        gtk.gdk.threads_leave()
                        tar.extract(f, self.path)
                        f = tar.next()
                        k = k + 1
                        #print str(k) +  " of " +str(n)
                        frac = k / nbFiles
                        #time.sleep(1)
                        gtk.gdk.threads_enter()
                        if self.app.running:
                                self.app.window.step_install.progress_bar.set_fraction(frac)
                                self.app.window.step_install.progress_bar.show()
                        gtk.gdk.threads_leave()

                self.app.window.step_install.show_message()
                
              
        # Stop method
        def stop(self):
             self.running = False   
                


app = App()

