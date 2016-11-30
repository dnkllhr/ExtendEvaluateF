#!/usr/bin/python        
# This is client.py file
import sys
import socket               # Import socket module
from ctypes import *
import os

class TILEMESSAGE(Structure):
    _field_ = [ ("length", c_int),
                ("tileStack", c_char * 401)]

class MOVEMESSAGE(Structure):
    _field_ = [ ("pid", c_int),
                ("player", c_uint),
                ("tile", c_char * 6),
                ("placeable", c_byte),
                ("x", c_uint),
                ("y", c_uint),
                ("rotationClockwise", c_uint),
                ("meepleType", c_int),
                ("pickupMeeple", c_byte),
                ("passTurn", c_byte),
                ("meepleZone", c_int)]

class WHOAMIMESSAGE(Structure):
    _field_ = [("playerNumber", c_uint)]

class DATAMESSAGE(Union):
    _field_ = [ ("tile", TILEMESSAGE),
                ("move", MOVEMESSAGE),
                ("who", WHOAMIMESSAGE)]

class GAMEMESSAGE(Structure):
    _field_ = [ ("type", c_int),
                ("data", DATAMESSAGE)]

def makeMove():
    t = raw_input("Which tile?")
    place = raw_input("placeable?")
    x = raw_input("x?")
    y = raw_input("y?")
    rot = raw_input("rotation?")
    meep = raw_input("meepleType?")
    pickup = raw_input("pickup?")
    passTurn = raw_input("pass?")
    meepZone = raw_input("meepleZone?")

    mvMsg = MOVEMESSAGE(0, 0, t, place, x, y, rotation, meep, pickup, passTurn, meepZone)
    gameMsg = GAMEMESSAGE(1, mvMsg)

    conn.send(gameMsg)


def recvMove():

    mvMsg = MOVEMESSAGE(myPlayer, myPlayer, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    gameMsg = GAMEMESSAGE(1, mvMsg)

    conn.send(gameMsg)

    gameMsg = conn.recv(sizeof(gameMsg))
    print gameMsg

def tileStack():
    num = raw_input("Enter number of tiles")
    usr_input = raw_input("Enter tile stack")
    tileMsg = TILEMESSAGE(num, usr_input)
    gameMsg = GAMEMESSAGE(0, tileMsg)

    conn.send(gameMsg)

def whoAmI(plyaerNum):
    w = WHOAMIMESSAGE(playerNumber)
    gameMsg = GAMEMESSAGE(2, w)

    conn.send(gameMsg)



def socketSetup(port):        # Create a socket object
    host = "localhost"          # Get local machine name
    port = int(port)     # Reserve a port for your service.
    s.connect((host, port))     # Connect

myPlayer = 0
s = socket.socket() 

import socket
import sys
 
HOST = 'localhost'   # Symbolic name, meaning all available interfaces
PORT = 50000 # Arbitrary non-privileged port
 
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'
 
#Bind socket to local host and port
try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()
     
print 'Socket bind complete'
 
#Start listening on socket
s.listen(10)
print 'Socket now listening'
 
conn, addr = s.accept()
print 'Connected with ' + addr[0] + ':' + str(addr[1])
usr_input = raw_input("Enter AI playerNumber :")
whoAmI(usr_input)
myPlayer = usr_input

#now keep talking with the client
while 1:
    #wait to accept a connection - blocking call
    usr_input = raw_input("Enter your desired message :")
    if (usr_input[0:5] == "MOVE"):
        makeMove()
        recvMove()
    else:
        tileStack()
     
s.close()
