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

import gtk, threading, time, thread

class Sprite:

    def __init__(self, app):

        self.app = app
        self.width = 0
        self.height = 0
        self.index = 0
        self.maxindex = 0
        self.speed = 0
        self.image = gtk.Image()
        self.end = False

    def open(self, filename):
        self.pixbuf = gtk.gdk.pixbuf_new_from_file(filename)
        self.index = 0
        self.maxindex = int(self.pixbuf.get_width() / self.width)
        print self.maxindex
        #if self.width * self.maxindex <> self.pixbuf.get_width():
        #    print "Exception à faire"        
        

    def get_subpixbuf(self):
        
        subpixbuf = self.pixbuf.subpixbuf(self.index * self.width, 0, self.width, self.height)
        self.index = self.index + 1
        if(self.index == self.maxindex):
            self.index = 0
        
        return subpixbuf

    def anim(self):
        subpixbuf = self.get_subpixbuf()
        self.image.set_from_pixbuf(subpixbuf)
        print self.index

    def start(self):
        self.t = SpriteThread(self, self.app)
        self.t.start()
        
    
    def stop(self):
        self.t.stop()
        self.t.join()
        print "ok"
                


class SpriteThread(threading.Thread):

    def __init__(self, sprite, app):
        threading.Thread.__init__(self)
        self.app = app
        self.sprite = sprite
        print dir(self)

        
    def run(self):
        self._running = True
        ok = True
        while(self._running):
            print "hey"
            time.sleep(self.sprite.speed)
            gtk.gdk.threads_enter()
            self.sprite.anim()
            self.app.window.sprite.show()
            gtk.gdk.threads_leave()
            #lock = threading.Lock()
            #lock.acquire()
            #ok = self._running
            #lock.release()

        print "je sors"

    def stop(self):
        #lock = threading.Lock()
        #lock.acquire()
        self._running = False
        #lock.release()
        
                
        
    
    
        
        
        
        
        
        
        
