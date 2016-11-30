import zmq
import time

#  Prepare our context and sockets
context = zmq.Context()
socket = context.socket(zmq.REQ)
print socket.connect("tcp://localhost:5555")

#  Do 10 requests, waiting each time for a response

message = socket.recv()
print message
