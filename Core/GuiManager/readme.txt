Dependencies

Latest Python 2
ZMQ - networking library
  Install
  Place zmq.hpp in /usr/local/include
GTK3 and ZMQ for python

when compiling client.cpp or GuiManager.cpp
link header with -lzmq flag
"g++ client.cpp -o client -lzmq"
