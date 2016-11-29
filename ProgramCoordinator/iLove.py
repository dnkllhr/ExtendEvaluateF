#!/usr/bin/python           # This is client.py file
import sys
import socket               # Import socket module
from ctypes import *        #F For defining a structure

class TILEMESSAGE(Structure):
    _fields_ = [("length", c_int),
                ("tileStack", (c_char * 401))]


class MOVEMESSAGE(Structure)
    _fields_ = [("pid", c_int),
                ("player", c_uint),
                ("tile", c_char * 6),
                ("placeable", c_byte),
                ("x", c_uint),
                ("y", c_uint),
                ("rotation", c_uint),
                ("meepleType", c_int),
                ("pickupMeeple", c_byte),
                ("passTurn", c_byte),
                ("zone", c_int)]


class WHOAMIMESSAGE(Structure):
    _fields_ = [("player", c_uint)]


class MESSAGEDATA(Union):
    _fields_ = [("tile", TILEMESSAGE),
                ("move", MOVEMESSAGE),
                ("who",WHOAMIMESSAGE),]

class GAMEMESSAGE(Structure):
    _fields_ = [("type", c_int),
                ("data", MESSAGEDATA)]



s = socket.socket()         # Create a socket object
host = sys.argv[1]          # Get local machine name
port = int(sys.argv[2])     # Reserve a port for your service.

s.connect((host, port))
print s.recv(1024)      #THIS IS SPARTA

#Tournament Parameters
tournamentPassword = sys.argv[3]
username = sys.argv[4]
password = sys.argv[5]

def roundprotol():
	stringData = s.recv(1024) #BEGIN ROUND <rid> OF <rounds>
	rid = stringData[12,14] #assumes rid is 2 digit number
	print stringData
	matchprotocol()
	return

def matchprotocol():
	stringData = s.recv(1024) #YOUR OPPONENT IS PLAYER <pid>
	opponentPid = stringData[24,26] #assumes pid is a 2 digit number
	print stringData
	print s.recv(1024) #STARTING TILE IS <tile> AT <x> <y> <orientation>

	# how to extract tileStack from line below?
	stringData = s.recv(1024) #THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
	numTiles = stringData[14,16] #assumes number_tiles is a 2 digit number
	print stringData
	print s.recv(1024) #MATCH BEGINS IN <timeplan> SECONDS 
	for i in range(0, numTiles):
		moveprotocol()
	print s.recv(1024) #GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
	print s.recv(1024) #GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
	return

def moveprotocol():
	


#AUTHENTICATION PROTOCOL
buffer = "JOIN " + tournamentPassword
s.send(buffer)
print buffer

print s.recv(1024) #HELLO!

buffer = "I AM " + username + password # space in between username and password?
s.send(buffer)
print buffer

print s.recv(1024) #WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE

#CHALLENGE PROTOCOL
#	**with back to back messages and too big of a buffer, may end up reading the start of the following message**
print s.recv(1024) #NEW CHALLENGE <cid> YOU WILL PLAY <rounds> MATCH
print s.recv(1024) #BEGIN ROUND <rid> OF <rounds>
print s.recv(1024) #YOUR OPPONENT IS PLAYER <pid>
print s.recv(1024) #STARTING TILE IS <tile> AT <x> <y> <orientation>


tileStackString = s.recv(1024) #THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
print tileStackString
tokenizedInput = tileStackString.split(' ')

start = False
buildMe = ""
#Find the starting list of tiles
for token in tokenizedInput:
    if(token == '['):
        start = True
    else if(token == ']'):
        start = False
    if(start):
        buildMe += token

currentData = TILEMESSAGE(80, buildMe)
msg = GAMEMESSAGE(0, currentData)


print s.recv(1024) #MATCH BEGINS IN <timeplan> SECONDS 
buffer = "I AM " + username + password # space in between username and password?
s.send(buffer)
print buffer

print s.recv(1024) #WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE

#CHALLENGE PROTOCOL
#	**with back to back messages and too big of a buffer, may end up reading the start of the following message**

stringData = s.recv(1024)  #NEW CHALLENGE <cid> YOU WILL PLAY <rounds> MATCH
cid = stringData[14,16] #assumes cid is 2 digit number
rounds = stringData[31,33] #assumes round is 2 digit number
print stringData

numRounds = int(rounds)
for i in range(0, numRounds):
	roundprotocol()


s.close

buffer = "I AM " + username + password # space in between username and password?
s.send(buffer)
print buffer

print s.recv(1024) #WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE

#CHALLENGE PROTOCOL
#	**with back to back messages and too big of a buffer, may end up reading the start of the following message**

stringData = s.recv(1024)  #NEW CHALLENGE <cid> YOU WILL PLAY <rounds> MATCH
cid = stringData[14,16] #assumes cid is 2 digit number
rounds = stringData[31,33] #assumes round is 2 digit number
print stringData

numRounds = int(rounds)
for i in range(0, numRounds):
	roundprotocol()
buffer = "I AM " + username + password # space in between username and password?
s.send(buffer)
print buffer

print s.recv(1024) #WELCOME <pid> PLEASE WAIT FOR THE NEXT CHALLENGE

#CHALLENGE PROTOCOL
#	**with back to back messages and too big of a buffer, may end up reading the start of the following message**
print s.recv(1024) #NEW CHALLENGE <cid> YOU WILL PLAY <rounds> MATCH
print s.recv(1024) #BEGIN ROUND <rid> OF <rounds>
print s.recv(1024) #YOUR OPPONENT IS PLAYER <pid>
print s.recv(1024) #STARTING TILE IS <tile> AT <x> <y> <orientation>


tileStackString = s.recv(1024) #THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
print tileStackString
tokenizedInput = tileStackString.split(' ')

start = False
buildMe = ""
#Find the starting list of tiles
for token in tokenizedInput:
    if(token == '['):
        start = True
    else if(token == ']'):
        start = False
    if(start):
        buildMe += token

currentData = TILEMESSAGE(80, buildMe)
msg = GAMEMESSAGE(0, currentData)


print s.recv(1024) #MATCH BEGINS IN <timeplan> SECONDS 