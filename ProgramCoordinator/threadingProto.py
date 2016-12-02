#!/usr/bin/python
import datetime
import threading
import time
import ctypes

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

threadLocks = []
killedThreads = []


#Used for handling outward bound messages
msgNotRead = False
messageLock = threading.Lock()
outMessage = ""
outMessageID = 0

#Array to hold the current game message
inMessages = []
gameIDToThreadID = {}

tournamentSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
currentIndex = 0

pid = ""
startingTile = ""

#Used for the main client
def socketSetup(port):          # Create a socket object
    host = "localhost"          # Get local machine name
    port = int(port)            # Reserve a port for your service.
    tournamentSocket.connect((host, port))     # connect

#Used for the infinite read by the main client
def readlines(sock, blocking = 1, delim='\r\n'):
    sock.setblocking(blocking)
    returnString = ""
    currentChar = ''
    while (currentChar != delim):
        currentChar = tournamentSocket.recv(1)
        returnString += currentChar
    returnString = re.sub('\x00', '', returnString)
    return returnString

def sendlines(sock, msg, blocking = 1):
    sock.setblocking(blocking)
    sock.sendall(msg)

def createNewThread(gameID):
    global currentIndex
    t = myThread(1, gameID, currentIndex)
    currentIndex += 1
    threads.append(t)


def matchProtocol(tokens):
    print tokens
    msg = readlines(tournamentSocket, 0)
    t = msg.split(" ")
    firstTile(t)

    msg = readlines(tournamentSocket, 0)
    t = msg.split(" ")
    tileStack(t)

    msg = readlines(tournamentSocket, 0)
    t = msg.split(" ")
    regularPrint(t)

def authenticationProtocol(tokens):
    #insert code here
    tournPass = raw_input("Enter tournament password: ")
    usr = raw_input("Enter username: ")
    pswd = raw_input("Enter password: ")

    msg = "JOIN " + tournPass + "\r\n"
    print msg
    sendlines(tournamentSocket, msg)

    msg = readlines(tournamentSocket)
    print msg

    msg = "I AM " + usr + " " + pswd  + "\r\n"
    print msg
    sendlines(tournamentSocket, msg)


def challengeProtocol(tokens):
    #insert code here
    for i in xrange(int(tokens[6])):
        roundProtocol()
        #END OF CHALLENGES || PLEASE WAIT FOR THE NEXT CHALLENGE TO BEGIN 
        msg = readlines(tournamentSocket)

def roundProtocol():
    #BEGIN ROUND <rid> OF <rounds>
    msg = readlines(tournamentSocket)
    tokens = msg.split(" ")
    for i in xrange(int(tokens[4])):
        matchProtocol()
        #END OF ROUND <rid> OF <rounds> || END OF ROUND <rid> OF <rounds> PLEASE WAIT FOR THE NEXT MATCH
        msg = readlines(tournamentSocket)


def matchProtocol():
    #insert code here
    #YOUR OPPONENT IS PLAYER <pid>
    msg = readlines(tournamentSocket)
    #STARTING TILE IS <tile> AT <x> <y> <orientation>
    msg = readlines(tournamentSocket)
    startingTokens = msg.split(" ")
    #THE REMAINING <number_tiles> TILES ARE [ <tiles> ] 
    msg = readlines(tournamentSocket)
    stackTokens = msg.split(" ")
    #MATCH BEGINS IN <timeplan> SECONDS
    msg = readlines(tournamentSocket)

    for i in xrange(int(stackTokens[2]) * 2):
        moveProtocol()
        #GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
        msg = readlines(tournamentSocket)
        #GAME <gid> OVER PLAYER <pid> <score> PLAYER <pid> <score>
        msg = readlines(tournamentSocket)

def getMoveFromGame():


def moveProtocol():
    #insert code here
    msg = readlines(tournamentSocket)
    tokens = msg.split(" ")
    if(tokens[0] == "MAKE"):
        getMoveFromGame()
    elif(tokens[4] == "TILE"):
        specialMove()
    else:
        regularMove()



def doWork():
    print "working"

def setupThreadStuff():
    tl = threading.Lock()
    global threadLocks
    threadLocks.append(t1)
    global inMessages
    inMessages.append("")
    global killedThreads
    killedThreads.append(False)

class myThread (threading.Thread):
    def __init__(self, threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        setupThreadStuff()
        self.tileStack = ""
        self.startingTileName = ""
        self.startingTileX = 0
        self.startingTileY = 0
        self.startingTileRotation = 0
        self.playerNumber = 0
    def run(self):
        while True:
            if(killedThreads[self.threadID]):
                print "exiting"
                break
            threadLocks[self.threadID].acquire()
            doWork()
            threadLocks[self.threadID].release()
            #time.sleep(.1)

    def getName(self):
        return self.name

    def getThreadID(self):
        return self.threadID

    def setStartingTile(self, name, x, y, rotation):
        self.startingTileName = name
        self.startingTileX = x
        self.startingTileY = y
        self.startingTileRotation = rotation

    def setPlayerNumber(self, num):
        self.playerNumber = num



#############################################################################################################
####################################### Main Function #######################################################
#############################################################################################################

