
#   GUI Server in Python
#   Binds REP socket to tcp://*:5555

import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
import time
import zmq

condition = True
def on_button_toggled( button, name):
    global condition
    if button.get_active():
        Gtk.main_quit()
        condition = True


#Setup TCP Socket
context = zmq.Context()
global socket
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

#Create Window X
X = Gtk.Window()
X.__init__(X,"Carcassonne")
X.connect("delete-event", Gtk.main_quit)


#Main Loop
#1. Request message
#2. Create Grid from message
#3. Attach button to grid
#4. Attach grid to view
#5. Show Window & Enter Gtk.main loop until Restart is hit
#6. Delete current Grid

while condition == True:
    condition = False
    #1
    message = socket.recv()
    socket.send(b"Thanks")
    #2
    inputList = message.split(":")
    size = int(inputList[0])
    imgList = inputList[1:]

    grid = Gtk.Grid()
    grid.set_row_homogeneous(1)
    grid.set_column_homogeneous(1)

    for row in range(0,size):
        for col in range(0,size):
            img = Gtk.Image.new_from_file("img/"+imgList[row * size + col]+".png")
            grid.attach(img,col,row,1,1)

    #3
    restart_button = Gtk.ToggleButton("Listen")
    restart_button.connect("toggled", on_button_toggled, "1")
    grid.attach(restart_button,0,size,size,1)
    #4
    X.add(grid)
    #5
    X.show_all()
    Gtk.main()
    #6
    grid.destroy()
