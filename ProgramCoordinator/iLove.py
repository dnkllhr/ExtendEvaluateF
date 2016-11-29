#!/usr/bin/python           # This is client.py file
import sys
import socket               # Import socket module

s = socket.socket()         # Create a socket object
host = sys.argv[1]          # Get local machine name
port = int(sys.argv[2])     # Reserve a port for your service.

s.connect((host, port))
print s.recv(1024)      #THIS IS SPARTA

#Tournament Parameters
tournamentPassword = sys.argv[3]
username = sys.argv[4]
password = sys.argv[5]

#AUTHENTICATION PROTOCOL
buffer = "JOIN "+tournamentPassword
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
print s.recv(1024) #THE REMAINING <number_tiles> TILES ARE [ <tiles> ]
print s.recv(1024) #MATCH BEGINS IN <timeplan> SECONDS 


s.close
