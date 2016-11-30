#!/usr/bin/python           # This is client.py file
import sys
import socket               # Import socket module
from ctypes import *
extra = ""
active = True
activeGames = 2;

s = socket.socket()         # Create a socket object
host = sys.argv[1]          # Get local machine name
port = int(sys.argv[2])     # Reserve a port for your service.
s.connect((host, port))     # Connect

#Tournament Parameters
tournamentPassword = sys.argv[3]
username = sys.argv[4]
password = sys.argv[5]

class TILEMESSAGE(Structure):
	_field_ = [	("length", c_int),
				("tileStack", c_char * 401)]

class MOVEMESSAGE(Structure):
	_field_ = [	("pid", c_int),
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
	_field_ = [	("tile", TILEMESSAGE),
				("move", MOVEMESSAGE),
				("who", WHOAMIMESSAGE)]

class GAMEMESSAGE(Structure):
	_field_ = [ ("type", c_int),
				("data", DATAMESSAGE)]

def myRead(socket):
    global extra
    buffer = ""
    check = ""
    while True:
        print "looping..."
        check = socket.recv(1)
        print "past socket recv"
        print check
        if check == '\r':
            print 1
            print buffer
            return buffer + '\r'
        if check != '\x00':
            print 2
            buffer += check
            print buffer


#     buffer = socket.recv(513-sys.getsizeof(extra))
#     rmjunk = buffer.split('\x00')
#     rmjunk[0].rstrip('\x00')
#     list = ''
#
#     for i in rmjunk:
#         list += str(i)
#
#     buffer = extra + buffer
#     list = buffer.split("\r",1)
#
#     if len(list) > 1:
#         buffer = list[0]
#         extra = list[1]
# #    print "Line " + buffer + "\tExtra " + extra
    return buffer


def roundprotocol():
    global s
    global activeGames
    global extra

    buffer = myRead(s) #Server: BEGIN ROUND <rid> OF <rounds>
    split = buffer.split(" ")
    rid = split[2]
    rounds = int(split[4])
    print buffer

    activeGames = 2
    matchprotocol()

    buffer = myRead(s) #Server: END OF ROUND <rid> OF <rounds>
    print buffer

    return

def matchprotocol():
    global s
    buffer = myRead(s) #YOUR OPPONENT IS PLAYER <pid>
    split = buffer.split(" ")

    opponentPid = split[4]
    print buffer

    buffer = myRead(s) #STARTING TILE IS <tile> AT <x> <y> <orientation>
    split = buffer.split(" ")
    tile = split[3]
    x = split[5]
    y = split[6]
    orientation = split[7]
    print buffer


	# how to extract tileStack from line below?
    buffer = myRead(s) #THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
    print buffer
    split = buffer.split(" ")
    numTiles = split[2]
    tiles = []
    for i in range(0,int(numTiles)):
        tiles.append(split[6+i])
    print tiles

    print myRead(s) #MATCH BEGINS IN <timeplan> SECONDS

    for i in range(0, int(numTiles)):
		moveprotocol()

    print myRead(s)#GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
    print myRead(s)#GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
    return

def moveprotocol():
    global s
    global activeGames
    global extra

    buffer = myRead(s);#Server: MAKE YOUR MOVE IN GAME <gid> WITHIN <timemove> SECOND: MOVE <#> PLACE <tile>
    print buffer
    split = buffer.split(" ")
    gid = split[5]
    moveNum = split[10]
    tile = split[12]

    #Creat Message object

    #await response

    buffer = "GAME "+gid+" MOVE "+moveNum+" TILE "+tile+" UNPLACEABLE PASS";
    print buffer
    s.send(buffer)

    currentlyActive = activeGames
    for i in range(0,currentlyActive):
        buffer = myRead(s)
        split = buffer.split(" ")
        if split[6] == "FORFEITED":
            activeGames= activeGames - 1
        else:
            print "LET GAME KNOW OF OPPONENTS MOVE"
    return


#AUTHENTICATION PROTOCOL
def authenticationprotocol():
    global s
    global tournamentPassword
    global username
    global password
    global pid

    print myRead(s) #This is SPARTA

    buffer = "JOIN "+tournamentPassword
    s.send(buffer)  #JOIN <tournament password>
    print buffer

    print myRead(s) #HELLO!

    buffer = "I AM " + username + " " + password # space in between username and password?
    s.send(buffer)
    print buffer


    buffer = myRead(s) #WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE
    print buffer
    pid = buffer.split(" ")[1]
    print pid

def challengeprotocol():
    global active
    while active:
        buffer = myRead(s)  #NEW CHALLENGE <cid> YOU WILL PLAY <rounds> MATCH
        split = buffer.split(" ")
        cid = split[2] #id of challenge, basically garbage
        rounds = split[6] #number of rounds
        print buffer

        numRounds = int(rounds)

        for i in range(0, numRounds):
    	       roundprotocol()

        buffer = myRead(s) #END OF CHALLENGES or PLEASE WAIT
        split = buffer.split(" ")
        if split[0] == "END":
            active = False

######################################################################################

authenticationprotocol()
challengeprotocol()


s.close




#
#CODY'S CODE FOR BULDING A MESSAGE
#
#
#<<<<<<< Updated upstream
#s.close
#=======
#tileStackString = s.recv(1024) #THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
#print tileStackString
#tokenizedInput = tileStackString.split(' ')
#
#start = False
#buildMe = ""
#Find the starting list of tiles
#for token in tokenizedInput:
#    if(token == '['):
#        start = True
#    else if(token == ']'):
#        start = False
#    if(start):
#        buildMe += token
#
#currentData = TILEMESSAGE(80, buildMe)
#msg = GAMEMESSAGE(0, currentData)
#...
